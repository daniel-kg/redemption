/*
    This program is free software; you can redistribute it and/or modify it
     under the terms of the GNU General Public License as published by the
     Free Software Foundation; either version 2 of the License, or (at your
     option) any later version.

    This program is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
     Public License for more details.

    You should have received a copy of the GNU General Public License along
     with this program; if not, write to the Free Software Foundation, Inc.,
     675 Mass Ave, Cambridge, MA 02139, USA.

    Product name: redemption, a FLOSS RDP proxy
    Copyright (C) Wallix 2014
    Author(s): Christophe Grosjean, Raphael Zhou
*/

#include "mod/internal/locally_integrable_mod.hpp"
#include "core/wait_obj.hpp"
#include "core/RDP/slowpath.hpp"
#include "mod/internal/client_execute.hpp"

void LocallyIntegrableMod::FirstClickDownEventHandler
  ::operator()(time_t /*now*/, wait_obj& /*event*/, gdi::GraphicApi& /*drawable*/)
{
    assert(this->mod_.rail_enabled);

    if (this->mod_.first_click_down_event.is_trigger_time_set() &&
        this->mod_.first_click_down_event.is_waked_up_by_time()) {
        this->mod_.cancel_double_click_detection();
    }
}


LocallyIntegrableMod::LocallyIntegrableMod(
    FrontAPI & front, uint16_t front_width, uint16_t front_height,
    Font const & font, ClientExecute & client_execute,
    Theme const & theme)
: InternalMod(front, front_width, front_height, font, theme, false)
, client_execute(client_execute)
, dvc_manager(false)
, dc_state(DCState::Wait)
, first_click_down_event_handler(*this)
, rail_enabled(client_execute.is_rail_enabled())
, current_mouse_owner(MouseOwner::WidgetModule)
{}

LocallyIntegrableMod::~LocallyIntegrableMod()
{
    this->client_execute.reset(true);
}

void LocallyIntegrableMod::get_event_handlers(std::vector<EventHandler>& out_event_handlers)
{
    if (this->rail_enabled) {
        if (this->first_click_down_event.is_trigger_time_set()) {
            out_event_handlers.emplace_back(
                &this->first_click_down_event,
                &this->first_click_down_event_handler,
                INVALID_SOCKET
            );
        }

        this->client_execute.get_event_handlers(out_event_handlers);
    }

    InternalMod::get_event_handlers(out_event_handlers);
}

void LocallyIntegrableMod::rdp_input_invalidate(Rect r)
{
    InternalMod::rdp_input_invalidate(r);

    if (this->rail_enabled) {
        this->client_execute.input_invalidate(r);
    }
}

void LocallyIntegrableMod::rdp_input_mouse(int device_flags, int x, int y, Keymap2 * keymap)
{
    if (device_flags & (MOUSE_FLAG_WHEEL | MOUSE_FLAG_HWHEEL)) {
        x = this->old_mouse_x;
        y = this->old_mouse_y;
    }
    else {
        this->old_mouse_x = x;
        this->old_mouse_y = y;
    }

    bool out_mouse_captured = false;

    if (!this->rail_enabled ||
        !this->client_execute.input_mouse(device_flags, x, y, out_mouse_captured)) {

        if (this->rail_enabled) {
            switch (this->dc_state) {
                case DCState::Wait:
                    if (device_flags == (SlowPath::PTRFLAGS_DOWN | SlowPath::PTRFLAGS_BUTTON1)) {
                        this->dc_state = DCState::FirstClickDown;

                        this->first_click_down_event.set_trigger_time(1000000);
                    }
                break;

                case DCState::FirstClickDown:
                    if (device_flags == SlowPath::PTRFLAGS_BUTTON1) {
                        this->dc_state = DCState::FirstClickRelease;
                    }
                    else if (device_flags == (SlowPath::PTRFLAGS_DOWN | SlowPath::PTRFLAGS_BUTTON1)) {
                    }
                    else {
                        this->cancel_double_click_detection();
                    }
                break;

                case DCState::FirstClickRelease:
                    if (device_flags == (SlowPath::PTRFLAGS_DOWN | SlowPath::PTRFLAGS_BUTTON1)) {
                        this->dc_state = DCState::SecondClickDown;
                    }
                    else {
                        this->cancel_double_click_detection();
                    }
                break;

                case DCState::SecondClickDown:
                    if (device_flags == SlowPath::PTRFLAGS_BUTTON1) {
                        this->dc_state = DCState::Wait;

                        bool out_mouse_captured_2 = false;

                        this->client_execute.input_mouse(PTRFLAGS_EX_DOUBLE_CLICK, x, y, out_mouse_captured_2);

                        this->cancel_double_click_detection();
                    }
                    else if (device_flags == (SlowPath::PTRFLAGS_DOWN | SlowPath::PTRFLAGS_BUTTON1)) {
                    }
                    else {
                        this->cancel_double_click_detection();
                    }
                break;

                default:
                    assert(false);

                    this->cancel_double_click_detection();
                break;
            }

            if (out_mouse_captured) {
                this->allow_mouse_pointer_change(false);

                this->current_mouse_owner = MouseOwner::ClientExecute;
            }
            else {
                if (MouseOwner::WidgetModule != this->current_mouse_owner) {
                    this->redo_mouse_pointer_change(x, y);
                }

                this->current_mouse_owner = MouseOwner::WidgetModule;
            }
        }

        InternalMod::rdp_input_mouse(device_flags, x, y, keymap);

        if (this->rail_enabled && out_mouse_captured) {
            this->allow_mouse_pointer_change(true);
        }
    }
}

void LocallyIntegrableMod::rdp_input_scancode(
    long param1, long param2, long param3, long param4, Keymap2 * keymap)
{
    InternalMod::rdp_input_scancode(param1, param2, param3, param4, keymap);

    if (this->rail_enabled) {
        if (!this->alt_key_pressed) {
            if ((param1 == 56) && !(param3 & SlowPath::KBDFLAGS_RELEASE)) {
                this->alt_key_pressed = true;
            }
        }
        else {
//            if ((param1 == 56) && (param3 == (SlowPath::KBDFLAGS_DOWN | SlowPath::KBDFLAGS_RELEASE))) {
            if ((param1 == 56) && (param3 & SlowPath::KBDFLAGS_RELEASE)) {
                this->alt_key_pressed = false;
            }
            else if ((param1 == 62) && !param3) {
                LOG(LOG_INFO, "LocallyIntegrableMod::rdp_input_scancode: Close by user (Alt+F4)");
                throw Error(ERR_WIDGET);    // F4 key pressed
            }
        }
    }
}

void LocallyIntegrableMod::refresh(Rect r)
{
    InternalMod::refresh(r);

    if (this->rail_enabled) {
        this->client_execute.input_invalidate(r);
    }
}

void LocallyIntegrableMod::draw_event(time_t, gdi::GraphicApi &)
{
    if (this->rail_enabled &&
        (false == static_cast<bool>(this->client_execute))/* &&
        this->event.is_waked_up_by_time()*/) {

        this->client_execute.ready(*this, this->front_width, this->front_height, this->font(),
            this->is_resizing_hosted_desktop_allowed());

        this->dvc_manager.ready(this->front);
    }
}

void LocallyIntegrableMod::send_to_mod_channel(
    CHANNELS::ChannelNameId front_channel_name, InStream& chunk,
    size_t length, uint32_t flags)
{
    if (this->rail_enabled && this->client_execute &&
        front_channel_name == CHANNELS::channel_names::rail) {

        this->client_execute.send_to_mod_rail_channel(length, chunk, flags);
    }
    else if (this->rail_enabled && this->client_execute &&
        front_channel_name == CHANNELS::channel_names::drdynvc) {

        this->dvc_manager.send_to_mod_drdynvc_channel(length, chunk, flags);
    }
}

void LocallyIntegrableMod::cancel_double_click_detection()
{
    assert(this->rail_enabled);

    this->first_click_down_event.reset_trigger_time();

    this->dc_state = DCState::Wait;
}

bool LocallyIntegrableMod::is_resizing_hosted_desktop_allowed() const
{
    assert(this->rail_enabled);

    return false;
}
