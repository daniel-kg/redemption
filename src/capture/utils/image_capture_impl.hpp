/*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*   Product name: redemption, a FLOSS RDP proxy
*   Copyright (C) Wallix 2010-2016
*   Author(s): Jonathan Poelen
*/


#pragma once

#include <algorithm>

#include "transport/out_meta_sequence_transport.hpp"

#include "capture/image_capture.hpp"
#include "utils/drawable.hpp"

#include "apis_register.hpp"


static void scale_data(uint8_t *dest, const uint8_t *src,
                       unsigned int dest_width, unsigned int src_width,
                       unsigned int dest_height, unsigned int src_height,
                       unsigned int src_rowsize) {
    const uint32_t Bpp = 3;
    unsigned int y_pixels = dest_height;
    unsigned int y_int_part = src_height / dest_height * src_rowsize;
    unsigned int y_fract_part = src_height % dest_height;
    unsigned int yE = 0;
    unsigned int x_int_part = src_width / dest_width * Bpp;
    unsigned int x_fract_part = src_width % dest_width;

    while (y_pixels-- > 0) {
        unsigned int xE = 0;
        const uint8_t * x_src = src;
        unsigned int x_pixels = dest_width;
        while (x_pixels-- > 0) {
            dest[0] = x_src[2];
            dest[1] = x_src[1];
            dest[2] = x_src[0];

            dest += Bpp;
            x_src += x_int_part;
            xE += x_fract_part;
            if (xE >= dest_width) {
                xE -= dest_width;
                x_src += Bpp;
            }
        }
        src += y_int_part;
        yE += y_fract_part;
        if (yE >= dest_height) {
            yE -= dest_height;
            src += src_rowsize;
        }
    }
}

class PngCapture final : private gdi::UpdateConfigCaptureApi, gdi::CaptureApi
{

    OutFilenameSequenceTransport trans;
    std::chrono::microseconds png_interval;

    timeval start_capture;
    std::chrono::microseconds frame_interval;

    unsigned zoom_factor;
    unsigned scaled_width;
    unsigned scaled_height;

    Drawable & drawable;
    std::unique_ptr<uint8_t[]> scaled_buffer;

public:
    PngCapture(
        const timeval & now, auth_api * authentifier, Drawable & drawable,
        const char * record_tmp_path, const char * basename, int groupid,
        unsigned zoom,
        std::chrono::microseconds png_interval)
    : trans(FilenameGenerator::PATH_FILE_COUNT_EXTENSION,
            record_tmp_path, basename, ".png", groupid, authentifier)
    , png_interval(png_interval)
    , start_capture(now)
    , frame_interval(png_interval)
    , zoom_factor(zoom)
    , scaled_width(drawable.width())
    , scaled_height(drawable.height())
    , drawable(drawable)
    {}

    void attach_apis(ApisRegister & apis_register, const Inifile & ini) {
        apis_register.capture_list.push_back(static_cast<gdi::CaptureApi&>(*this));
        apis_register.graphic_snapshot_list->push_back(static_cast<gdi::CaptureApi&>(*this));
    }

    void zoom(unsigned percent) {
        percent = std::min(percent, 100u);
        const unsigned zoom_width = (this->drawable.width() * percent) / 100;
        const unsigned zoom_height = (this->drawable.height() * percent) / 100;
        this->zoom_factor = percent;
        this->scaled_width = (zoom_width + 3) & 0xFFC;
        this->scaled_height = zoom_height;
        if (this->zoom_factor != 100) {
            this->scaled_buffer.reset(
                new uint8_t[this->scaled_width * this->scaled_height * 3]);
        }
    }

    void next(const timeval & now) {
        tm ptm;
        localtime_r(&now.tv_sec, &ptm);
        this->drawable.trace_timestamp(ptm);
        const uint8_t * buffer = this->drawable.data();
        unsigned height = this->drawable.height();
        unsigned width = this->drawable.width();
        unsigned rowsize = this->drawable.rowsize();
        bool bgr = true;
        if (this->zoom_factor != 100) {
            scale_data(
                this->scaled_buffer.get(), buffer,
                this->scaled_width, width,
                this->scaled_height, height,
                this->drawable.rowsize());
            buffer = this->scaled_buffer.get();
            height = this->drawable.height();
            width = this->scaled_width;
            rowsize = this->scaled_width * 3;
            bgr = false;
        }
        ::transport_dump_png24(this->trans, buffer, width, height, rowsize, bgr);
        this->trans.next();
        this->drawable.clear_timestamp();
    }

private:
    void update_config(Inifile const & ini) override {
    }

    std::chrono::microseconds do_snapshot(
        timeval const & now, int x, int y, bool ignore_frame_in_timeval
    ) override {
        (void)x;
        (void)y;
        (void)ignore_frame_in_timeval;
        using std::chrono::microseconds;
        uint64_t const duration = difftimeval(now, this->start_capture);
        uint64_t const interval = this->frame_interval.count();
        if (duration >= interval) {
            if (this->drawable.logical_frame_ended
                // Force snapshot if diff_time_val >= 1.5 x frame_interval.
                || (duration >= interval * 3 / 2)) {
                this->drawable.trace_mouse();
                tm ptm;
                localtime_r(&now.tv_sec, &ptm);
                this->drawable.trace_timestamp(ptm);
                if (this->zoom_factor == 100) {
                    ::transport_dump_png24(
                        this->trans, this->drawable.data(),
                        this->drawable.width(), this->drawable.height(),
                        this->drawable.rowsize(), true);
                }
                else {
                    scale_data(
                        this->scaled_buffer.get(), this->drawable.data(),
                        this->scaled_width, this->drawable.width(),
                        this->scaled_height, this->drawable.height(),
                        this->drawable.rowsize());
                    ::transport_dump_png24(
                        this->trans, this->scaled_buffer.get(),
                        this->scaled_width, this->scaled_height,
                        this->scaled_width * 3, false);
                }
                this->trans.next();
                this->drawable.clear_timestamp();
                this->start_capture = now;
                this->drawable.clear_mouse();

                return microseconds(interval ? interval - duration % interval : 0u);
            }
            else {
                // Wait 0.3 x frame_interval.
                return this->frame_interval / 3;
            }
        }
        return microseconds(interval - duration);
    }

    void do_pause_capture(timeval const & now) override {
        // Draw Pause message
        time_t rawtime = now.tv_sec;
        tm ptm;
        localtime_r(&rawtime, &ptm);
        this->drawable.trace_pausetimestamp(ptm);
        if (this->zoom_factor == 100) {
            ::transport_dump_png24(
                this->trans, this->drawable.data(),
                this->drawable.width(), this->drawable.height(),
                this->drawable.rowsize(), true);
        }
        else {
            scale_data(
                this->scaled_buffer.get(), this->drawable.data(),
                this->scaled_width, this->drawable.width(),
                this->scaled_height, this->drawable.height(),
                this->drawable.rowsize());
            ::transport_dump_png24(
                this->trans, this->scaled_buffer.get(),
                this->scaled_width, this->scaled_height,
                this->scaled_width * 3, false);
        }
        this->trans.next();
        this->drawable.clear_pausetimestamp();
        this->start_capture = now;
    }

    void do_resume_capture(timeval const & now) override {
    }
};

class PngCaptureRT final : private gdi::UpdateConfigCaptureApi, gdi::CaptureApi
{
    struct ImageTransportBuilder final : private Transport
    {
        OutFilenameSequenceTransport trans;
        bool enable_rt;
        uint32_t num_start = 0;
        unsigned png_limit;

        ImageTransportBuilder(
            const char * path, const char * basename, int groupid,
            auth_api * authentifier, bool enable_rt, uint32_t png_limit)
        : trans(
            FilenameGenerator::PATH_FILE_COUNT_EXTENSION,
            path, basename, ".png", groupid, authentifier)
        , enable_rt(enable_rt)
        , png_limit(enable_rt ? png_limit : 0)
        {}

        ~ImageTransportBuilder() {
            if (this->enable_rt) {
                this->unlink_all_png();
            }
        }

        bool next() override {
            if (this->png_limit && this->trans.get_seqno() >= this->png_limit) {
                // unlink may fail, for instance if file does not exist, just don't care
                ::unlink(this->trans.seqgen()->get(this->trans.get_seqno() - this->png_limit));
            }
            return this->trans.next();
        }

        void do_send(const uint8_t * const buffer, size_t len) override {
            this->trans.send(buffer, len);
        }

        Transport & get_transport() {
            return this->png_limit ? static_cast<Transport&>(*this) : this->trans;
        }

        void unlink_all_png()
        {
            for(uint32_t until_num = this->trans.get_seqno() + 1; this->num_start < until_num; ++this->num_start) {
                // unlink may fail, for instance if file does not exist, just don't care
                ::unlink(this->trans.seqgen()->get(this->num_start));
            }
        }
    };

    std::chrono::microseconds png_interval;
    ImageTransportBuilder trans_builder;
    
    
    class DrawableToFileLocal
    {
    protected:
        Transport & trans;
        unsigned zoom_factor;
        unsigned scaled_width;
        unsigned scaled_height;

        const Drawable & drawable;

    private:
        std::unique_ptr<uint8_t[]> scaled_buffer;

    public:
        DrawableToFileLocal(Transport & trans, const Drawable & drawable, unsigned zoom)
        : trans(trans)
        , zoom_factor(std::min(zoom, 100u))
        , scaled_width(drawable.width())
        , scaled_height(drawable.height())
        , drawable(drawable)
        {
            const unsigned zoom_width = (this->drawable.width() * this->zoom_factor) / 100;
            const unsigned zoom_height = (this->drawable.height() * this->zoom_factor) / 100;
            this->scaled_width = (zoom_width + 3) & 0xFFC;
            this->scaled_height = zoom_height;
            if (this->zoom_factor != 100) {
                this->scaled_buffer.reset(new uint8_t[this->scaled_width * this->scaled_height * 3]);
            }
        }

        ~DrawableToFileLocal() = default;

        bool logical_frame_ended() const {
            return this->drawable.logical_frame_ended;
        }

        void flush() {
            if (this->zoom_factor == 100) {
                this->dump24();
            }
            else {
                this->scale_dump24();
            }
        }

    private:
        void dump24() const {
            ::transport_dump_png24(
                this->trans, this->drawable.data(),
                this->drawable.width(), this->drawable.height(),
                this->drawable.rowsize(), true);
        }

        void scale_dump24() const {
            scale_data(
                this->scaled_buffer.get(), this->drawable.data(),
                this->scaled_width, this->drawable.width(),
                this->scaled_height, this->drawable.height(),
                this->drawable.rowsize());
            ::transport_dump_png24(
                this->trans, this->scaled_buffer.get(),
                this->scaled_width, this->scaled_height,
                this->scaled_width * 3, false);
        }

        static void scale_data(uint8_t *dest, const uint8_t *src,
                               unsigned int dest_width, unsigned int src_width,
                               unsigned int dest_height, unsigned int src_height,
                               unsigned int src_rowsize) {
            const uint32_t Bpp = 3;
            unsigned int y_pixels = dest_height;
            unsigned int y_int_part = src_height / dest_height * src_rowsize;
            unsigned int y_fract_part = src_height % dest_height;
            unsigned int yE = 0;
            unsigned int x_int_part = src_width / dest_width * Bpp;
            unsigned int x_fract_part = src_width % dest_width;

            while (y_pixels-- > 0) {
                unsigned int xE = 0;
                const uint8_t * x_src = src;
                unsigned int x_pixels = dest_width;
                while (x_pixels-- > 0) {
                    dest[0] = x_src[2];
                    dest[1] = x_src[1];
                    dest[2] = x_src[0];

                    dest += Bpp;
                    x_src += x_int_part;
                    xE += x_fract_part;
                    if (xE >= dest_width) {
                        xE -= dest_width;
                        x_src += Bpp;
                    }
                }
                src += y_int_part;
                yE += y_fract_part;
                if (yE >= dest_height) {
                    yE -= dest_height;
                    src += src_rowsize;
                }
            }
        }
    };
    
    
    class ImageCaptureLocal : private DrawableToFileLocal
    {
        timeval start_capture;
        std::chrono::microseconds frame_interval;

    public:
        ImageCaptureLocal (
            const timeval & now, const Drawable & drawable, Transport & trans,
            unsigned zoom, std::chrono::microseconds png_interval)
        : DrawableToFileLocal(trans, drawable, zoom)
        , start_capture(now)
        , frame_interval(png_interval)
        {}

        void breakpoint(const timeval & now)
        {
            tm ptm;
            localtime_r(&now.tv_sec, &ptm);
            const_cast<Drawable&>(this->drawable).trace_timestamp(ptm);
            this->flush_png();
            const_cast<Drawable&>(this->drawable).clear_timestamp();
        }

        void flush_png()
        {
            this->flush();
            this->trans.next();
        }

        std::chrono::microseconds do_snapshot(
            const timeval & now, int x, int y, bool ignore_frame_in_timeval
        )  {
            (void)x;
            (void)y;
            (void)ignore_frame_in_timeval;
            using std::chrono::microseconds;
            uint64_t const duration = difftimeval(now, this->start_capture);
            uint64_t const interval = this->frame_interval.count();
            if (duration >= interval) {
                if (   this->logical_frame_ended()
                    // Force snapshot if diff_time_val >= 1.5 x frame_interval.
                    || (duration >= interval * 3 / 2)) {
                    const_cast<Drawable&>(this->drawable).trace_mouse();
                    this->breakpoint(now);
                    this->start_capture = now;
                    const_cast<Drawable&>(this->drawable).clear_mouse();

                    return microseconds(interval ? interval - duration % interval : 0u);
                }
                else {
                    // Wait 0.3 x frame_interval.
                    return this->frame_interval / 3;
                }
            }
            return microseconds(interval - duration);
        }

        void do_pause_capture(timeval const & now) {
            // Draw Pause message
            time_t rawtime = now.tv_sec;
            tm ptm;
            localtime_r(&rawtime, &ptm);
            const_cast<Drawable&>(this->drawable).trace_pausetimestamp(ptm);
            this->flush_png();
            const_cast<Drawable&>(this->drawable).clear_pausetimestamp();
            this->start_capture = now;
        }

        void do_resume_capture(timeval const & now)
        {
        }        
        
    } ic;
    bool enable_rt_display = false;

public:
    PngCaptureRT(
        const timeval & now, bool enable_rt, auth_api * authentifier, Drawable & drawable,
        const char * record_tmp_path, const char * basename, int groupid,
        unsigned zoom,
        std::chrono::microseconds png_interval,
        uint32_t png_limit)
    : png_interval(png_interval)
    , trans_builder(record_tmp_path, basename, groupid, authentifier, enable_rt, png_limit)
    , ic(now, drawable, this->trans_builder.get_transport(), zoom, png_interval)
    {}

    void attach_apis(ApisRegister & apis_register, const Inifile & ini) {
        this->enable_rt_display = ini.get<cfg::video::rt_display>();
        apis_register.capture_list.push_back(static_cast<gdi::CaptureApi&>(*this));
        apis_register.graphic_snapshot_list->push_back(static_cast<gdi::CaptureApi&>(*this));
        apis_register.update_config_capture_list.push_back(static_cast<gdi::UpdateConfigCaptureApi&>(*this));
    }

    void next(const timeval & now) {
        this->ic.breakpoint(now);
    }

private:
    void update_config(Inifile const & ini) override {
        auto const old_enable_rt_display = this->enable_rt_display;
        this->enable_rt_display = ini.get<cfg::video::rt_display>();

        if (old_enable_rt_display == this->enable_rt_display) {
            return ;
        }

        if (ini.get<cfg::debug::capture>()) {
            LOG(LOG_INFO, "Enable real time: %d", int(this->enable_rt_display));
        }

        if (!this->enable_rt_display) {
            this->trans_builder.unlink_all_png();
        }
    }

    std::chrono::microseconds do_snapshot(
        timeval const & now, int cursor_x, int cursor_y, bool ignore_frame_in_timeval
    ) override {
        if (this->enable_rt_display) {
            return this->ic.do_snapshot(now, cursor_x, cursor_y, ignore_frame_in_timeval);
        }
        return this->png_interval;
    }

    void do_pause_capture(timeval const & now) override {
        if (this->enable_rt_display) {
            this->ic.do_pause_capture(now);
        }
    }

    void do_resume_capture(timeval const & now) override {
        if (this->enable_rt_display) {
            this->ic.do_resume_capture(now);
        }
    }
};


