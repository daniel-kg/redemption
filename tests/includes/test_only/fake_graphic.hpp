/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   Product name: redemption, a FLOSS RDP proxy
   Copyright (C) Wallix 2010-2013
   Author(s): Christophe Grosjean

   Fake Front class for Unit Testing
*/

#pragma once

#include "gdi/graphic_api.hpp"
#include "core/RDP/RDPDrawable.hpp"

class FakeGraphic : public gdi::GraphicApi
{
public:
    FakeGraphic(uint8_t bpp, size_t width, size_t height, uint32_t verbose);

    void draw(RDP::FrameMarker    const & cmd) override;

    void draw(RDPDestBlt          const & cmd, Rect clip) override;

    void draw(RDPMultiDstBlt      const & cmd, Rect clip) override;

    void draw(RDPPatBlt           const & cmd, Rect clip, gdi::ColorCtx color_ctx) override;

    void draw(RDP::RDPMultiPatBlt const & cmd, Rect clip, gdi::ColorCtx color_ctx) override;

    void draw(RDPOpaqueRect       const & cmd, Rect clip, gdi::ColorCtx color_ctx) override;

    void draw(RDPMultiOpaqueRect  const & cmd, Rect clip, gdi::ColorCtx color_ctx) override;

    void draw(RDPScrBlt           const & cmd, Rect clip) override;

    void draw(RDP::RDPMultiScrBlt const & cmd, Rect clip) override;

    void draw(RDPLineTo           const & cmd, Rect clip, gdi::ColorCtx color_ctx) override;

    void draw(RDPPolygonSC        const & cmd, Rect clip, gdi::ColorCtx color_ctx) override;

    void draw(RDPPolygonCB        const & cmd, Rect clip, gdi::ColorCtx color_ctx) override;

    void draw(RDPPolyline         const & cmd, Rect clip, gdi::ColorCtx color_ctx) override;

    void draw(RDPEllipseSC        const & cmd, Rect clip, gdi::ColorCtx color_ctx) override;

    void draw(RDPEllipseCB        const & cmd, Rect clip, gdi::ColorCtx color_ctx) override;

    void draw(RDPBitmapData       const & cmd, Bitmap const & bmp) override;

    void draw(RDPMemBlt           const & cmd, Rect clip, Bitmap const & bmp) override;

    void draw(RDPMem3Blt          const & cmd, Rect clip, gdi::ColorCtx color_ctx, Bitmap const & bmp) override;

    void draw(RDPGlyphIndex       const & cmd, Rect clip, gdi::ColorCtx color_ctx, GlyphCache const & gly_cache) override;

    void draw(const RDP::RAIL::NewOrExistingWindow            & cmd) override;
    void draw(const RDP::RAIL::WindowIcon                     & cmd) override;

    void draw(const RDP::RAIL::CachedIcon                     & cmd) override;

    void draw(const RDP::RAIL::DeletedWindow                  & cmd) override;

    void draw(const RDP::RAIL::NewOrExistingNotificationIcons & cmd) override;

    void draw(const RDP::RAIL::DeletedNotificationIcons       & cmd) override;

    void draw(const RDP::RAIL::ActivelyMonitoredDesktop       & cmd) override;

    void draw(const RDP::RAIL::NonMonitoredDesktop            & cmd) override;

    void draw(RDPColCache   const & cmd) override;

    void draw(RDPBrushCache const & cmd) override;

    void draw(RDPNineGrid const & , Rect , gdi::ColorCtx , Bitmap const & ) override {}

    void set_palette(const BGRPalette &) override;

    void set_pointer(const Pointer & cursor) override;

    void sync() override;

    void begin_update() override;

    void end_update() override;

    void dump_png(const char * prefix);

    void save_to_png(const char * filename);

    operator ConstImageDataView () const;

private:
    uint32_t                    verbose;
public:
    uint8_t                     mod_bpp;
    BGRPalette                  mod_palette;
    RDPDrawable gd;
};
