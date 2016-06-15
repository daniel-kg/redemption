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

#include <iostream>
#include <utility>

#include "configs/generators/utils/write_template.hpp"
#include "configs/generators/utils/multi_filename_writer.hpp"

#include "configs/enumeration.hpp"


namespace cfg_generators {

namespace cpp_enumeration_writer
{

    template<class E>
    auto e_map(E & e) {
        return map(
            bind('e', e.name),
            bind('u', e.values.size()),
            bind('d', cpp_comment(e.desc, 0)),
            bind('i', cpp_comment(e.info, 0))
        );
    }

    inline void write_utility_ini(std::ostream & out, type_enumerations const & enums)
    {
        auto write = [&](auto & e, char const * fmt) {
            write_template(out, e_map(e), fmt);
        };

        auto loop = [&](auto & e, char const * fmt) {
            for (auto & v : e.values) {
                write_template(
                    out, map(
                        bind('s', v.name),
                        bind('a', v.alias ? v.alias : v.name),
                        bind('d', cpp_comment(v.desc, 4))
                    ).merge(e_map(e)),
                    fmt
                );
            }
        };

        auto cfg_to_s_fmt = [&](auto & e) {
            write(e, "template<> struct zstr_buffer_traits<%e> : ");
            out << "zstr_buffer_traits<" << (e.is_icase_parser ? "void" : "unsigned long") << "> {};\n\n";
            write(e,
                "inline array_view_const_char assign_zbuf_from_cfg(\n"
                "    zstr_buffer_from<%e> & buf,\n"
                "    cfg_s_type<%e>,\n"
                "    %e x\n"
                ") {\n"
            );
            if (e.is_icase_parser) {
                out <<
                    "    (void)buf;"
                    "    static constexpr array_view_const_char arr[]{\n";
                loop(e, "        cstr_array_view(\"%s\"),\n");
                write(e,
                    "    };\n"
                    "    assert(static_cast<unsigned long>(x) < %u);\n"
                    "    return arr[static_cast<unsigned long>(x)];\n"
                );
            }
            else {
                write(e,
                    "    int sz = snprintf(buf.get(), buf.size(), \"%%lu\", static_cast<unsigned long>(x));\n"
                    "    return array_view_const_char(buf.get(), sz);\n"
                );
            }
            out << "}\n\n";
        };

        auto parse_fmt = [&](auto & e, auto lazy_integral_parse_fmt){
            write(e,
                "inline parse_error parse(%e & x, spec_type<%e>, array_view_const_char value)\n"
                "{\n"
            );
            if (e.is_icase_parser) {
                out << "    return parse_enum_str(x, value, {\n";
                loop(e,"        {cstr_array_view(\"%a\"), %e::%s},\n");
                out << "    });\n";
            }
            else {
                lazy_integral_parse_fmt();
            }
            out << "}\n\n";
        };

        out <<
            "//\n"
            "// ATTENTION -- This file is auto-generated\n"
            "//\n\n"
            "#pragma once\n"
            "\n"
            "#include \"configs/io.hpp\"\n"
            "#include \"configs/autogen/enums.hpp\"\n"
            "\n"
            "#include <cerrno>\n"
            "#include <cstdio>\n"
            "#include <cstdlib>\n"
            "#include <cassert>\n"
            "#include <cstring>\n"
            "\n"
            "\n"
            "namespace configs {\n"
            "\n"
        ;
        for (auto & e : enums.enumerations_) {
            cfg_to_s_fmt(e);
            parse_fmt(e, [&]{ write(e,
                "    return parse_enum_u(x, value, static_cast<unsigned long>((1 << (%u - 1)) - 1));\n"
            ); });
        }
        for (auto & e : enums.enumerations_set_) {
            cfg_to_s_fmt(e);
            parse_fmt(e, [&]{
                out << "    return parse_enum_list(x, value, {\n";
                loop(e,"        %e::%s,\n");
                out << "    });\n";
            });
        }
        out << "}\n";
    }

    inline void write_type(std::ostream & out, type_enumerations const & enums)
    {
        auto write = [&](auto & e, char const * fmt){
            write_template(out, e_map(e), fmt);
        };

        auto enum_def = [&](auto & e, auto next_value) {
            write(e,
                "%d"
                "%i"
                "enum class %e {\n"
            );
            for (auto & v : e.values) {
                write_template(
                    out, map(
                        bind('s', v.name),
                        bind('d', cpp_comment(v.desc, 4)),
                        bind('x', next_value(v))
                    ),
                    "%d"
                    "    %s = %x,\n"
                );
            }
            out << "};\n\n";
        };

        auto write_io = [write](auto && e) {
            write(e,
                "template<class Ch, class Tr>\n"
                "std::basic_ostream<Ch, Tr> &\n"
                "operator << (std::basic_ostream<Ch, Tr> & os, %e e)\n"
                "{ return os << static_cast<unsigned long>(e); }\n"
                "\n"
                "\n"
            );
        };

#ifdef IN_IDE_PARSER
#define CPP_IDE(...)
#else
#define CPP_IDE(...) __VA_ARGS__
#endif

        out <<
            "//\n"
            "// ATTENTION -- This file is auto-generated\n"
            "//\n\n"
            "#pragma once\n"
            "\n"
            "#include <iosfwd>\n"
            "\n"
            "\n"
        ;
        for (auto & e : enums.enumerations_) {
            if (e.flag == type_enumeration::flags) {
                enum_def(e, [CPP_IDE(d = 0, x = 0)] (auto &) mutable {
                    unsigned ret = (x << d) >> 1;
                    x |= 1;
                    ++d;
                    return ret;
                });
                write(e,
                    "inline bool is_valid_enum_value(%e e)\n"
                    "{\n"
                    "    auto const i = static_cast<unsigned long>(e);\n"
                    "    return i == (i & static_cast<unsigned long>(1 << (%u - 1)));\n"
                    "}\n\n"
                    "inline %e operator | (%e x, %e y)\n"
                    "{ return static_cast<%e>(static_cast<unsigned long>(x) | static_cast<unsigned long>(y)); }\n"
                    "inline %e operator & (%e x, %e y)\n"
                    "{ return static_cast<%e>(static_cast<unsigned long>(x) & static_cast<unsigned long>(y)); }\n"
                    "inline %e operator ~ (%e x)\n"
                    "{ return static_cast<%e>(~static_cast<unsigned long>(x) & static_cast<unsigned long>(1 << (%u - 1))); }\n"
                    "inline %e operator + (%e & x, %e y) { return x | y; }\n"
                    "inline %e operator - (%e & x, %e y) { return x & ~y; }\n"
                    "inline %e & operator |= (%e & x, %e y) { return x = x | y; }\n"
                    "inline %e & operator &= (%e & x, %e y) { return x = x & y; }\n"
                    "inline %e & operator += (%e & x, %e y) { return x = x + y; }\n"
                    "inline %e & operator -= (%e & x, %e y) { return x = x - y; }\n\n"
                );
            }
            else {
                enum_def(e, [CPP_IDE(i = 0)] (auto &) mutable { return i++; });
                write(e,
                    "inline bool is_valid_enum_value(%e e)\n"
                    "{ return static_cast<unsigned long>(e) < %u; }\n\n"
                );
            }
            write_io(e);
        }

        for (auto & e : enums.enumerations_set_) {
            enum_def(e, [] (auto & v) mutable { return v.val; });
            write(e,
                "inline bool is_valid_enum_value(%e e)\n"
                "{\n"
                "    auto const i = static_cast<unsigned long>(e);\n"
                "    return false\n"
            );
            for (auto & v : e.values) {
                out << "     || i == " << v.val << "\n";
            }
            write(e,
                "    ;\n"
                "}\n\n"
            );
            write_io(e);
        }
    }
}

template<class Writer>
int app_write_cpp_enumeration(Writer && writer, int ac, char const ** av)
{
    if (ac < 3) {
        std::cerr << av[0] << " type.h utility-ini.h\n";
        return 1;
    }

    type_enumerations e;
    writer(e);
    MultiFilenameWriter<type_enumerations> sw(e);
    sw.then(av[1], &cpp_enumeration_writer::write_type)
      .then(av[2], &cpp_enumeration_writer::write_utility_ini)
    ;
    if (sw.err) {
        std::cerr << av[0] << ": " << sw.filename << ": " << (errno ? strerror(errno) : "unknown error") << "\n";
        return sw.errnum;
    }
    return 0;
}


template<class Writer>
int app_write_cpp_enumeration(Writer && writer, int ac, char ** av)
{
    return app_write_cpp_enumeration(std::forward<Writer>(writer), ac, const_cast<char const **>(av));
}

}