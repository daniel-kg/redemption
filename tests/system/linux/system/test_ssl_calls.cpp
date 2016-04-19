/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   Product name: redemption, a FLOSS RDP proxy
   Copyright (C) Wallix 2013
   Author(s): Christophe Grosjean, Meng Tan

*/

#define BOOST_AUTO_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestXXX
#include <boost/test/auto_unit_test.hpp>

#define LOGPRINT
// #define LOGNULL

#include <stdio.h>
#include "system/ssl_calls.hpp"

// uint8_t data[512];

// UdevRandom udevRand;

// udevRand.random(data, sizeof(data));
// hexdump_d(data, sizeof(data), 8);


BOOST_AUTO_TEST_CASE(TestSslSha1)
{
    uint8_t sig[20];

    uint8_t data[512] = {
        /* 0000 */ 0x86, 0x79, 0x05, 0x32, 0x6c, 0x24, 0x43, 0x02,  // .y.2l$C.
        /* 0008 */ 0x15, 0xc6, 0x44, 0x58, 0x29, 0x07, 0x8f, 0x73,  // ..DX)..s
        /* 0010 */ 0xda, 0x67, 0x62, 0x9f, 0xa7, 0x6b, 0xaf, 0x23,  // .gb..k.#
        /* 0018 */ 0xa3, 0xc7, 0x6b, 0x2d, 0x53, 0xea, 0xb1, 0xfb,  // ..k-S...
        /* 0020 */ 0x92, 0x19, 0xfa, 0xc5, 0x98, 0x55, 0xfb, 0x34,  // .....U.4
        /* 0028 */ 0x79, 0xec, 0xad, 0x46, 0xaa, 0xe9, 0xe8, 0xcc,  // y..F....
        /* 0030 */ 0x6c, 0x13, 0x08, 0x6b, 0x3a, 0x45, 0xe6, 0xe8,  // l..k:E..
        /* 0038 */ 0x4e, 0x9c, 0x25, 0x6d, 0xe7, 0x79, 0x36, 0xb3,  // N.%m.y6.
        /* 0040 */ 0x76, 0x35, 0x5d, 0x00, 0x54, 0xfc, 0x28, 0xb2,  // v5].T.(.
        /* 0048 */ 0x9e, 0x41, 0xfa, 0xd4, 0xc8, 0x85, 0x57, 0x28,  // .A....W(
        /* 0050 */ 0x89, 0x6a, 0x56, 0xe5, 0x89, 0x79, 0xb5, 0x1b,  // .jV..y..
        /* 0058 */ 0x96, 0x38, 0xe8, 0x54, 0x7b, 0xd4, 0x16, 0xd7,  // .8.T{...
        /* 0060 */ 0xbc, 0x50, 0xdc, 0xfa, 0x3b, 0xb9, 0xdb, 0x3e,  // .P..;..>
        /* 0068 */ 0x34, 0xd2, 0x80, 0xc3, 0xaf, 0x8b, 0xe0, 0xb7,  // 4.......
        /* 0070 */ 0x66, 0x94, 0xfa, 0x95, 0x2b, 0xa7, 0x4a, 0x1c,  // f...+.J.
        /* 0078 */ 0xf1, 0x71, 0x28, 0x55, 0x35, 0x43, 0xeb, 0xd5,  // .q(U5C..
        /* 0080 */ 0xf3, 0xc0, 0x8f, 0x69, 0x32, 0x19, 0x0d, 0x88,  // ...i2...
        /* 0088 */ 0x24, 0x79, 0x9a, 0xba, 0xd0, 0x75, 0xbc, 0x42,  // $y...u.B
        /* 0090 */ 0x84, 0x36, 0x3f, 0x29, 0xa9, 0x07, 0x68, 0x4f,  // .6?)..hO
        /* 0098 */ 0x68, 0x2f, 0xbf, 0x95, 0x9a, 0x75, 0xdd, 0x7c,  // h/...u.|
        /* 00a0 */ 0x30, 0x37, 0xef, 0xed, 0x2f, 0xd9, 0xdd, 0x8f,  // 07../...
        /* 00a8 */ 0x31, 0x34, 0x4a, 0x15, 0xc4, 0x22, 0x76, 0x33,  // 14J.."v3
        /* 00b0 */ 0xa1, 0x60, 0xa2, 0x5b, 0x2e, 0x95, 0xce, 0x41,  // .`.[...A
        /* 00b8 */ 0x98, 0x1a, 0xea, 0xe6, 0x4b, 0x4a, 0x53, 0xc8,  // ....KJS.
        /* 00c0 */ 0x80, 0x8f, 0x94, 0x5e, 0x03, 0xab, 0xc8, 0x72,  // ...^...r
        /* 00c8 */ 0xc8, 0xdd, 0xca, 0x79, 0xf5, 0x78, 0x4e, 0x43,  // ...y.xNC
        /* 00d0 */ 0x32, 0x0d, 0xc8, 0x19, 0x60, 0xe0, 0x19, 0xe0,  // 2...`...
        /* 00d8 */ 0x12, 0xe4, 0xdc, 0x23, 0x65, 0x57, 0x2d, 0xb6,  // ...#eW-.
        /* 00e0 */ 0x19, 0x4b, 0x0f, 0xc1, 0x4a, 0xb9, 0x22, 0x24,  // .K..J."$
        /* 00e8 */ 0x17, 0x2a, 0xad, 0xe7, 0x70, 0xcd, 0xe3, 0x62,  // .*..p..b
        /* 00f0 */ 0xe0, 0x1d, 0x01, 0xf3, 0xc6, 0xbe, 0x80, 0x36,  // .......6
        /* 00f8 */ 0xac, 0x50, 0x5a, 0xb0, 0xa9, 0xf4, 0xd6, 0x13,  // .PZ.....
        /* 0100 */ 0x6c, 0xcf, 0x82, 0xe3, 0x9b, 0xe2, 0xb6, 0x1f,  // l.......
        /* 0108 */ 0xbb, 0xe3, 0x58, 0xfe, 0x8e, 0xdd, 0x3b, 0x27,  // ..X...;'
        /* 0110 */ 0xc7, 0xa5, 0x4f, 0x3b, 0xf6, 0xbb, 0x15, 0x1e,  // ..O;....
        /* 0118 */ 0x65, 0x04, 0x85, 0x45, 0x9e, 0x7c, 0x53, 0x88,  // e..E.|S.
        /* 0120 */ 0x39, 0x87, 0x0d, 0x4d, 0x21, 0xb6, 0x8e, 0x01,  // 9..M!...
        /* 0128 */ 0xc4, 0xc7, 0x6f, 0x7f, 0x57, 0x94, 0xef, 0x2a,  // ..o.W..*
        /* 0130 */ 0x06, 0x02, 0x0a, 0xd5, 0x8d, 0x0c, 0xd9, 0x8d,  // ........
        /* 0138 */ 0xe2, 0x40, 0x3b, 0x99, 0x83, 0x28, 0xd5, 0xef,  // .@;..(..
        /* 0140 */ 0x7c, 0xf4, 0x4b, 0xb8, 0xb8, 0x53, 0xe1, 0x25,  // |.K..S.%
        /* 0148 */ 0x44, 0x38, 0x0d, 0x35, 0xca, 0x4f, 0xde, 0x08,  // D8.5.O..
        /* 0150 */ 0xc6, 0xdc, 0x5f, 0x16, 0xc6, 0x90, 0x24, 0x4e,  // .._...$N
        /* 0158 */ 0xd1, 0x39, 0x32, 0x29, 0x35, 0xf7, 0x55, 0x1c,  // .92)5.U.
        /* 0160 */ 0x58, 0xe5, 0x73, 0x24, 0x7d, 0xc5, 0x17, 0xc0,  // X.s$}...
        /* 0168 */ 0x6f, 0xf6, 0x30, 0x9e, 0x48, 0x12, 0xf9, 0xe0,  // o.0.H...
        /* 0170 */ 0x5a, 0x7e, 0x00, 0xd8, 0x04, 0x0c, 0x3a, 0x6e,  // Z~....:n
        /* 0178 */ 0xa1, 0xf1, 0x96, 0xa8, 0x27, 0x83, 0x5b, 0xc6,  // ....'.[.
        /* 0180 */ 0x53, 0xd4, 0x46, 0xad, 0x9e, 0x00, 0x87, 0x1e,  // S.F.....
        /* 0188 */ 0x20, 0x3c, 0x5e, 0x2e, 0x67, 0x56, 0xe7, 0x9b,  //  <^.gV..
        /* 0190 */ 0x24, 0x8b, 0x86, 0x25, 0x02, 0x3a, 0x30, 0x18,  // $..%.:0.
        /* 0198 */ 0x90, 0x13, 0x72, 0x56, 0x68, 0xcc, 0xdf, 0x87,  // ..rVh...
        /* 01a0 */ 0x7e, 0xf7, 0x16, 0x99, 0xe1, 0x59, 0x54, 0xc9,  // ~....YT.
        /* 01a8 */ 0x88, 0x4e, 0x97, 0xf1, 0x99, 0x97, 0x06, 0x3c,  // .N.....<
        /* 01b0 */ 0x60, 0x55, 0xeb, 0x5e, 0xd4, 0xc7, 0xba, 0xf9,  // `U.^....
        /* 01b8 */ 0xa3, 0x99, 0x3d, 0xa0, 0xc2, 0x2e, 0x42, 0x3b,  // ..=...B;
        /* 01c0 */ 0x42, 0x24, 0xbe, 0x69, 0x72, 0x87, 0xc3, 0x2c,  // B$.ir..,
        /* 01c8 */ 0xaa, 0xc5, 0xdc, 0xb0, 0x61, 0xb0, 0x6c, 0xd0,  // ....a.l.
        /* 01d0 */ 0xb9, 0xa8, 0x61, 0x86, 0x2f, 0x86, 0xc5, 0x27,  // ..a./..'
        /* 01d8 */ 0x86, 0xe1, 0x73, 0x41, 0xfc, 0xcf, 0x04, 0x93,  // ..sA....
        /* 01e0 */ 0x07, 0xcd, 0xc2, 0x4e, 0x4b, 0x28, 0xf6, 0xfd,  // ...NK(..
        /* 01e8 */ 0x28, 0x17, 0x62, 0x4b, 0x07, 0x5d, 0x89, 0x24,  // (.bK.].$
        /* 01f0 */ 0xd2, 0x14, 0xbd, 0x13, 0xe8, 0x0a, 0xe9, 0x85,  // ........
        /* 01f8 */ 0x8d, 0x47, 0x39, 0x5c, 0x98, 0xd3, 0x1f, 0x56,  // .G9....V
    };

    {
        SslSha1 sha1;

        sha1.update(data, sizeof(data));
        sha1.final(sig, sizeof(sig));
        // hexdump96_c(sig, sizeof(sig));

        BOOST_CHECK_EQUAL(memcmp(sig,
                                 "\x47\x44\xa9\x9d\xe9\xe5\xf1\xd0\x61\x7a"
                                 "\x9d\x64\x47\xe2\xf1\xe3\x49\xa7\xf3\xef",
                                 sizeof(sig)),
                          0);
    }

    {
        SslSha1 sha1;

        sha1.update(data, 128);
        sha1.update(data + 128, 128);
        sha1.update(data + 256, 128);
        sha1.update(data + 384, 128);
        sha1.final(sig, sizeof(sig));
        // hexdump96_c(sig, sizeof(sig));

        BOOST_CHECK_EQUAL(memcmp(sig,
                                 "\x47\x44\xa9\x9d\xe9\xe5\xf1\xd0\x61\x7a"
                                 "\x9d\x64\x47\xe2\xf1\xe3\x49\xa7\xf3\xef",
                                 sizeof(sig)),
                          0);
    }

}

BOOST_AUTO_TEST_CASE(TestSslMd5)
{
    uint8_t sig[16];
    uint8_t data[512] = {
        /* 0000 */ 0xba, 0x96, 0x63, 0xe9, 0x11, 0x42, 0xf1, 0xec,  // ..c..B..
        /* 0008 */ 0x31, 0xed, 0xd5, 0xb4, 0xcd, 0x2e, 0xee, 0x64,  // 1......d
        /* 0010 */ 0x77, 0x2c, 0x53, 0x6d, 0xef, 0x3b, 0xb7, 0xf9,  // w,Sm.;..
        /* 0018 */ 0x1d, 0x2c, 0x3c, 0x90, 0xcb, 0x60, 0x5a, 0x27,  // .,<..`Z'
        /* 0020 */ 0xeb, 0x82, 0xf0, 0x1d, 0x87, 0x01, 0x9e, 0xf7,  // ........
        /* 0028 */ 0x29, 0x4a, 0xcb, 0x7e, 0x4d, 0x14, 0xf6, 0x9c,  // )J.~M...
        /* 0030 */ 0xd6, 0x17, 0x9d, 0xd4, 0x92, 0x6d, 0x3d, 0xda,  // .....m=.
        /* 0038 */ 0x6f, 0x23, 0xeb, 0xea, 0x43, 0x1b, 0x01, 0x31,  // o#..C..1
        /* 0040 */ 0xca, 0x93, 0x7a, 0x4d, 0xa3, 0xf2, 0x0b, 0x30,  // ..zM...0
        /* 0048 */ 0xeb, 0xdb, 0x2b, 0xf3, 0xb9, 0xfc, 0xcb, 0xbc,  // ..+.....
        /* 0050 */ 0xd5, 0x0f, 0x22, 0x19, 0x92, 0x47, 0x36, 0x0f,  // .."..G6.
        /* 0058 */ 0xf3, 0x79, 0xe3, 0x4b, 0x08, 0x64, 0x29, 0xf6,  // .y.K.d).
        /* 0060 */ 0x64, 0x8a, 0xdc, 0x57, 0xc9, 0x2b, 0xb3, 0xbe,  // d..W.+..
        /* 0068 */ 0x2a, 0xff, 0x24, 0xbb, 0xa2, 0xd0, 0x1b, 0x0f,  // *.$.....
        /* 0070 */ 0xea, 0x65, 0xaa, 0x11, 0x6c, 0x0e, 0x45, 0x56,  // .e..l.EV
        /* 0078 */ 0x9e, 0xf0, 0x54, 0x00, 0x55, 0x5a, 0x12, 0x4b,  // ..T.UZ.K
        /* 0080 */ 0x94, 0x71, 0xf5, 0x03, 0x52, 0x56, 0xb9, 0x13,  // .q..RV..
        /* 0088 */ 0xfc, 0x25, 0x09, 0x80, 0x51, 0x23, 0x10, 0x19,  // .%..Q#..
        /* 0090 */ 0x9a, 0x68, 0x2c, 0xf5, 0x7e, 0xd6, 0xb0, 0xbf,  // .h,.~...
        /* 0098 */ 0x07, 0xf0, 0xf2, 0x69, 0x75, 0xa6, 0x4f, 0x40,  // ...iu.O@
        /* 00a0 */ 0x0d, 0x8f, 0xaf, 0x2f, 0x61, 0x62, 0xd7, 0xcb,  // .../ab..
        /* 00a8 */ 0x51, 0x1a, 0x1e, 0x03, 0x7b, 0xa8, 0x6e, 0x41,  // Q...{.nA
        /* 00b0 */ 0xec, 0x3a, 0x08, 0x45, 0xf3, 0xa1, 0xbf, 0x9c,  // .:.E....
        /* 00b8 */ 0xcc, 0xd7, 0xcd, 0x59, 0x77, 0x49, 0x40, 0xd0,  // ...YwI@.
        /* 00c0 */ 0xb0, 0x33, 0x97, 0x5a, 0xbf, 0xba, 0x5e, 0x3a,  // .3.Z..^:
        /* 00c8 */ 0x77, 0x81, 0x55, 0xa5, 0x7f, 0xdc, 0x71, 0x43,  // w.U...qC
        /* 00d0 */ 0x4e, 0x6b, 0xbc, 0x0f, 0xc9, 0xaf, 0xfc, 0xcf,  // Nk......
        /* 00d8 */ 0xc4, 0x2b, 0x02, 0x65, 0x4f, 0x09, 0x92, 0x64,  // .+.eO..d
        /* 00e0 */ 0x2d, 0x29, 0x23, 0xea, 0xf5, 0x02, 0xe3, 0xd2,  // -)#.....
        /* 00e8 */ 0x05, 0x21, 0x06, 0xde, 0x6a, 0x0d, 0xd2, 0xe7,  // .!..j...
        /* 00f0 */ 0xf8, 0x2b, 0xbd, 0xea, 0x07, 0xc6, 0xc2, 0x79,  // .+.....y
        /* 00f8 */ 0x1c, 0xa5, 0x10, 0xf4, 0xb5, 0x51, 0x4f, 0x03,  // .....QO.
        /* 0100 */ 0x5e, 0x23, 0x2a, 0x67, 0xd6, 0x65, 0x5b, 0x94,  // ^#*g.e[.
        /* 0108 */ 0xe2, 0x1c, 0xda, 0x78, 0xf6, 0x7b, 0xd8, 0x97,  // ...x.{..
        /* 0110 */ 0x71, 0xb4, 0x1a, 0x05, 0xc1, 0x62, 0xfb, 0x38,  // q....b.8
        /* 0118 */ 0x92, 0xba, 0x2a, 0x21, 0x65, 0xdb, 0x0e, 0xb2,  // ..*!e...
        /* 0120 */ 0xcb, 0xa1, 0x78, 0x29, 0x9b, 0xed, 0x3d, 0xbe,  // ..x)..=.
        /* 0128 */ 0x84, 0x8b, 0xe9, 0xc9, 0x82, 0xfe, 0x5f, 0x66,  // ......_f
        /* 0130 */ 0x24, 0x16, 0x51, 0xdf, 0x6c, 0xd6, 0xc8, 0x7f,  // $.Q.l...
        /* 0138 */ 0x99, 0xe1, 0x2a, 0xe4, 0x39, 0x1c, 0x49, 0xc4,  // ..*.9.I.
        /* 0140 */ 0xbc, 0xd2, 0x76, 0xd3, 0x2a, 0x58, 0x48, 0x5b,  // ..v.*XH[
        /* 0148 */ 0x13, 0xc4, 0x9c, 0x81, 0xc1, 0x4a, 0xec, 0x5b,  // .....J.[
        /* 0150 */ 0xab, 0x7f, 0xfa, 0x96, 0x02, 0xc6, 0x19, 0x1e,  // ........
        /* 0158 */ 0xbd, 0x83, 0x35, 0x1b, 0xfd, 0x26, 0x68, 0xba,  // ..5..&h.
        /* 0160 */ 0x68, 0x70, 0x47, 0x5a, 0xfc, 0xb0, 0xc8, 0x15,  // hpGZ....
        /* 0168 */ 0x50, 0xe0, 0x4d, 0x81, 0x64, 0x79, 0x31, 0x80,  // P.M.dy1.
        /* 0170 */ 0x5b, 0x5c, 0x17, 0xa2, 0x56, 0x3f, 0x15, 0xd6,  // [...V?..
        /* 0178 */ 0x74, 0x22, 0x3e, 0x79, 0x19, 0x69, 0x42, 0x5c,  // t">y.iB.
        /* 0180 */ 0x8c, 0x7d, 0x73, 0xbe, 0x71, 0x11, 0x39, 0xca,  // .}s.q.9.
        /* 0188 */ 0x80, 0xcb, 0xc1, 0xb6, 0x76, 0xb8, 0x14, 0xfb,  // ....v...
        /* 0190 */ 0x03, 0x35, 0x3d, 0xdf, 0x00, 0x08, 0x2c, 0x3a,  // .5=...,:
        /* 0198 */ 0x76, 0xff, 0x3b, 0xca, 0xca, 0x47, 0x0c, 0x58,  // v.;..G.X
        /* 01a0 */ 0x56, 0x21, 0xcb, 0x75, 0xa4, 0x88, 0x75, 0xef,  // V!.u..u.
        /* 01a8 */ 0xd9, 0x8c, 0x87, 0x69, 0xed, 0x4a, 0x72, 0xb6,  // ...i.Jr.
        /* 01b0 */ 0x9e, 0x61, 0x03, 0x0b, 0xe5, 0xac, 0x90, 0x0d,  // .a......
        /* 01b8 */ 0x5c, 0x03, 0x9a, 0x2f, 0x51, 0x53, 0xc6, 0x5e,  // .../QS.^
        /* 01c0 */ 0xbd, 0x58, 0xdc, 0x52, 0xc9, 0xb1, 0x85, 0x4e,  // .X.R...N
        /* 01c8 */ 0x1b, 0x06, 0x20, 0xb3, 0x0f, 0x02, 0x96, 0x3c,  // .. ....<
        /* 01d0 */ 0xa0, 0x86, 0xff, 0xdf, 0xca, 0xf2, 0xdb, 0x96,  // ........
        /* 01d8 */ 0xc2, 0xc8, 0xce, 0xa8, 0x6d, 0xae, 0x56, 0x9f,  // ....m.V.
        /* 01e0 */ 0xfd, 0x6d, 0xf5, 0x51, 0x13, 0x71, 0xe9, 0x27,  // .m.Q.q.'
        /* 01e8 */ 0x15, 0x1d, 0x4c, 0x4e, 0x88, 0xf3, 0xc8, 0x0f,  // ..LN....
        /* 01f0 */ 0x09, 0xca, 0xcc, 0x22, 0x28, 0x66, 0xae, 0x8e,  // ..."(f..
        /* 01f8 */ 0xd4, 0x96, 0xd4, 0x5a, 0x38, 0xf6, 0x33, 0xfd,  // ...Z8.3.
    };

    {
        SslMd5 md;

        md.update(data, sizeof(data));
        md.final(sig, sizeof(sig));
        // hexdump96_c(sig, sizeof(sig));

        BOOST_CHECK_EQUAL(memcmp(sig,
                                 "\x0b\x82\xd2\xb3\xd6\x75\x9c\xc2"
                                 "\x71\xab\x1d\xf7\x9e\x0b\xfa\xcc",
                                 sizeof(sig)),
                          0);
    }

    {
        SslMd5 md;

        md.update(data, 128);
        md.update(data + 128, 128);
        md.update(data + 256, 128);
        md.update(data + 384, 128);
        md.final(sig, sizeof(sig));
        // hexdump96_c(sig, sizeof(sig));

        BOOST_CHECK_EQUAL(memcmp(sig,
                                 "\x0b\x82\xd2\xb3\xd6\x75\x9c\xc2"
                                 "\x71\xab\x1d\xf7\x9e\x0b\xfa\xcc",
                                 sizeof(sig)),
                          0);
    }

}

BOOST_AUTO_TEST_CASE(TestSslMd4)
{
    uint8_t sig[16];
    uint8_t data[512] = {
        /* 0000 */ 0xba, 0x96, 0x63, 0xe9, 0x11, 0x42, 0xf1, 0xec,  // ..c..B..
        /* 0008 */ 0x31, 0xed, 0xd5, 0xb4, 0xcd, 0x2e, 0xee, 0x64,  // 1......d
        /* 0010 */ 0x77, 0x2c, 0x53, 0x6d, 0xef, 0x3b, 0xb7, 0xf9,  // w,Sm.;..
        /* 0018 */ 0x1d, 0x2c, 0x3c, 0x90, 0xcb, 0x60, 0x5a, 0x27,  // .,<..`Z'
        /* 0020 */ 0xeb, 0x82, 0xf0, 0x1d, 0x87, 0x01, 0x9e, 0xf7,  // ........
        /* 0028 */ 0x29, 0x4a, 0xcb, 0x7e, 0x4d, 0x14, 0xf6, 0x9c,  // )J.~M...
        /* 0030 */ 0xd6, 0x17, 0x9d, 0xd4, 0x92, 0x6d, 0x3d, 0xda,  // .....m=.
        /* 0038 */ 0x6f, 0x23, 0xeb, 0xea, 0x43, 0x1b, 0x01, 0x31,  // o#..C..1
        /* 0040 */ 0xca, 0x93, 0x7a, 0x4d, 0xa3, 0xf2, 0x0b, 0x30,  // ..zM...0
        /* 0048 */ 0xeb, 0xdb, 0x2b, 0xf3, 0xb9, 0xfc, 0xcb, 0xbc,  // ..+.....
        /* 0050 */ 0xd5, 0x0f, 0x22, 0x19, 0x92, 0x47, 0x36, 0x0f,  // .."..G6.
        /* 0058 */ 0xf3, 0x79, 0xe3, 0x4b, 0x08, 0x64, 0x29, 0xf6,  // .y.K.d).
        /* 0060 */ 0x64, 0x8a, 0xdc, 0x57, 0xc9, 0x2b, 0xb3, 0xbe,  // d..W.+..
        /* 0068 */ 0x2a, 0xff, 0x24, 0xbb, 0xa2, 0xd0, 0x1b, 0x0f,  // *.$.....
        /* 0070 */ 0xea, 0x65, 0xaa, 0x11, 0x6c, 0x0e, 0x45, 0x56,  // .e..l.EV
        /* 0078 */ 0x9e, 0xf0, 0x54, 0x00, 0x55, 0x5a, 0x12, 0x4b,  // ..T.UZ.K
        /* 0080 */ 0x94, 0x71, 0xf5, 0x03, 0x52, 0x56, 0xb9, 0x13,  // .q..RV..
        /* 0088 */ 0xfc, 0x25, 0x09, 0x80, 0x51, 0x23, 0x10, 0x19,  // .%..Q#..
        /* 0090 */ 0x9a, 0x68, 0x2c, 0xf5, 0x7e, 0xd6, 0xb0, 0xbf,  // .h,.~...
        /* 0098 */ 0x07, 0xf0, 0xf2, 0x69, 0x75, 0xa6, 0x4f, 0x40,  // ...iu.O@
        /* 00a0 */ 0x0d, 0x8f, 0xaf, 0x2f, 0x61, 0x62, 0xd7, 0xcb,  // .../ab..
        /* 00a8 */ 0x51, 0x1a, 0x1e, 0x03, 0x7b, 0xa8, 0x6e, 0x41,  // Q...{.nA
        /* 00b0 */ 0xec, 0x3a, 0x08, 0x45, 0xf3, 0xa1, 0xbf, 0x9c,  // .:.E....
        /* 00b8 */ 0xcc, 0xd7, 0xcd, 0x59, 0x77, 0x49, 0x40, 0xd0,  // ...YwI@.
        /* 00c0 */ 0xb0, 0x33, 0x97, 0x5a, 0xbf, 0xba, 0x5e, 0x3a,  // .3.Z..^:
        /* 00c8 */ 0x77, 0x81, 0x55, 0xa5, 0x7f, 0xdc, 0x71, 0x43,  // w.U...qC
        /* 00d0 */ 0x4e, 0x6b, 0xbc, 0x0f, 0xc9, 0xaf, 0xfc, 0xcf,  // Nk......
        /* 00d8 */ 0xc4, 0x2b, 0x02, 0x65, 0x4f, 0x09, 0x92, 0x64,  // .+.eO..d
        /* 00e0 */ 0x2d, 0x29, 0x23, 0xea, 0xf5, 0x02, 0xe3, 0xd2,  // -)#.....
        /* 00e8 */ 0x05, 0x21, 0x06, 0xde, 0x6a, 0x0d, 0xd2, 0xe7,  // .!..j...
        /* 00f0 */ 0xf8, 0x2b, 0xbd, 0xea, 0x07, 0xc6, 0xc2, 0x79,  // .+.....y
        /* 00f8 */ 0x1c, 0xa5, 0x10, 0xf4, 0xb5, 0x51, 0x4f, 0x03,  // .....QO.
        /* 0100 */ 0x5e, 0x23, 0x2a, 0x67, 0xd6, 0x65, 0x5b, 0x94,  // ^#*g.e[.
        /* 0108 */ 0xe2, 0x1c, 0xda, 0x78, 0xf6, 0x7b, 0xd8, 0x97,  // ...x.{..
        /* 0110 */ 0x71, 0xb4, 0x1a, 0x05, 0xc1, 0x62, 0xfb, 0x38,  // q....b.8
        /* 0118 */ 0x92, 0xba, 0x2a, 0x21, 0x65, 0xdb, 0x0e, 0xb2,  // ..*!e...
        /* 0120 */ 0xcb, 0xa1, 0x78, 0x29, 0x9b, 0xed, 0x3d, 0xbe,  // ..x)..=.
        /* 0128 */ 0x84, 0x8b, 0xe9, 0xc9, 0x82, 0xfe, 0x5f, 0x66,  // ......_f
        /* 0130 */ 0x24, 0x16, 0x51, 0xdf, 0x6c, 0xd6, 0xc8, 0x7f,  // $.Q.l...
        /* 0138 */ 0x99, 0xe1, 0x2a, 0xe4, 0x39, 0x1c, 0x49, 0xc4,  // ..*.9.I.
        /* 0140 */ 0xbc, 0xd2, 0x76, 0xd3, 0x2a, 0x58, 0x48, 0x5b,  // ..v.*XH[
        /* 0148 */ 0x13, 0xc4, 0x9c, 0x81, 0xc1, 0x4a, 0xec, 0x5b,  // .....J.[
        /* 0150 */ 0xab, 0x7f, 0xfa, 0x96, 0x02, 0xc6, 0x19, 0x1e,  // ........
        /* 0158 */ 0xbd, 0x83, 0x35, 0x1b, 0xfd, 0x26, 0x68, 0xba,  // ..5..&h.
        /* 0160 */ 0x68, 0x70, 0x47, 0x5a, 0xfc, 0xb0, 0xc8, 0x15,  // hpGZ....
        /* 0168 */ 0x50, 0xe0, 0x4d, 0x81, 0x64, 0x79, 0x31, 0x80,  // P.M.dy1.
        /* 0170 */ 0x5b, 0x5c, 0x17, 0xa2, 0x56, 0x3f, 0x15, 0xd6,  // [...V?..
        /* 0178 */ 0x74, 0x22, 0x3e, 0x79, 0x19, 0x69, 0x42, 0x5c,  // t">y.iB.
        /* 0180 */ 0x8c, 0x7d, 0x73, 0xbe, 0x71, 0x11, 0x39, 0xca,  // .}s.q.9.
        /* 0188 */ 0x80, 0xcb, 0xc1, 0xb6, 0x76, 0xb8, 0x14, 0xfb,  // ....v...
        /* 0190 */ 0x03, 0x35, 0x3d, 0xdf, 0x00, 0x08, 0x2c, 0x3a,  // .5=...,:
        /* 0198 */ 0x76, 0xff, 0x3b, 0xca, 0xca, 0x47, 0x0c, 0x58,  // v.;..G.X
        /* 01a0 */ 0x56, 0x21, 0xcb, 0x75, 0xa4, 0x88, 0x75, 0xef,  // V!.u..u.
        /* 01a8 */ 0xd9, 0x8c, 0x87, 0x69, 0xed, 0x4a, 0x72, 0xb6,  // ...i.Jr.
        /* 01b0 */ 0x9e, 0x61, 0x03, 0x0b, 0xe5, 0xac, 0x90, 0x0d,  // .a......
        /* 01b8 */ 0x5c, 0x03, 0x9a, 0x2f, 0x51, 0x53, 0xc6, 0x5e,  // .../QS.^
        /* 01c0 */ 0xbd, 0x58, 0xdc, 0x52, 0xc9, 0xb1, 0x85, 0x4e,  // .X.R...N
        /* 01c8 */ 0x1b, 0x06, 0x20, 0xb3, 0x0f, 0x02, 0x96, 0x3c,  // .. ....<
        /* 01d0 */ 0xa0, 0x86, 0xff, 0xdf, 0xca, 0xf2, 0xdb, 0x96,  // ........
        /* 01d8 */ 0xc2, 0xc8, 0xce, 0xa8, 0x6d, 0xae, 0x56, 0x9f,  // ....m.V.
        /* 01e0 */ 0xfd, 0x6d, 0xf5, 0x51, 0x13, 0x71, 0xe9, 0x27,  // .m.Q.q.'
        /* 01e8 */ 0x15, 0x1d, 0x4c, 0x4e, 0x88, 0xf3, 0xc8, 0x0f,  // ..LN....
        /* 01f0 */ 0x09, 0xca, 0xcc, 0x22, 0x28, 0x66, 0xae, 0x8e,  // ..."(f..
        /* 01f8 */ 0xd4, 0x96, 0xd4, 0x5a, 0x38, 0xf6, 0x33, 0xfd,  // ...Z8.3.
    };

    {
        SslMd4 md;

        md.update(data, sizeof(data));
        md.final(sig, sizeof(sig));
        // hexdump96_c(sig, sizeof(sig));

        BOOST_CHECK_EQUAL(memcmp(sig,
                                 "\x33\xce\xe5\xdd\x0b\x6f\x3a\xf7"
                                 "\xd9\xa4\xa1\x9a\xbc\x1b\xc6\x58",
                                 sizeof(sig)),
                          0);
    }

    {
        SslMd4 md;

        md.update(data, 128);
        md.update(data + 128, 128);
        md.update(data + 256, 128);
        md.update(data + 384, 128);
        md.final(sig, sizeof(sig));
        // hexdump96_c(sig, sizeof(sig));

        BOOST_CHECK_EQUAL(memcmp(sig,
                                 "\x33\xce\xe5\xdd\x0b\x6f\x3a\xf7"
                                 "\xd9\xa4\xa1\x9a\xbc\x1b\xc6\x58",
                                 sizeof(sig)),
                          0);
    }

}

BOOST_AUTO_TEST_CASE(TestSslRc4)
{

    uint8_t key[] = "A key nobody knows";

    uint8_t data[512] = {
        /* 0000 */ 0xba, 0x96, 0x63, 0xe9, 0x11, 0x42, 0xf1, 0xec,  // ..c..B..
        /* 0008 */ 0x31, 0xed, 0xd5, 0xb4, 0xcd, 0x2e, 0xee, 0x64,  // 1......d
        /* 0010 */ 0x77, 0x2c, 0x53, 0x6d, 0xef, 0x3b, 0xb7, 0xf9,  // w,Sm.;..
        /* 0018 */ 0x1d, 0x2c, 0x3c, 0x90, 0xcb, 0x60, 0x5a, 0x27,  // .,<..`Z'
        /* 0020 */ 0xeb, 0x82, 0xf0, 0x1d, 0x87, 0x01, 0x9e, 0xf7,  // ........
        /* 0028 */ 0x29, 0x4a, 0xcb, 0x7e, 0x4d, 0x14, 0xf6, 0x9c,  // )J.~M...
        /* 0030 */ 0xd6, 0x17, 0x9d, 0xd4, 0x92, 0x6d, 0x3d, 0xda,  // .....m=.
        /* 0038 */ 0x6f, 0x23, 0xeb, 0xea, 0x43, 0x1b, 0x01, 0x31,  // o#..C..1
        /* 0040 */ 0xca, 0x93, 0x7a, 0x4d, 0xa3, 0xf2, 0x0b, 0x30,  // ..zM...0
        /* 0048 */ 0xeb, 0xdb, 0x2b, 0xf3, 0xb9, 0xfc, 0xcb, 0xbc,  // ..+.....
        /* 0050 */ 0xd5, 0x0f, 0x22, 0x19, 0x92, 0x47, 0x36, 0x0f,  // .."..G6.
        /* 0058 */ 0xf3, 0x79, 0xe3, 0x4b, 0x08, 0x64, 0x29, 0xf6,  // .y.K.d).
        /* 0060 */ 0x64, 0x8a, 0xdc, 0x57, 0xc9, 0x2b, 0xb3, 0xbe,  // d..W.+..
        /* 0068 */ 0x2a, 0xff, 0x24, 0xbb, 0xa2, 0xd0, 0x1b, 0x0f,  // *.$.....
        /* 0070 */ 0xea, 0x65, 0xaa, 0x11, 0x6c, 0x0e, 0x45, 0x56,  // .e..l.EV
        /* 0078 */ 0x9e, 0xf0, 0x54, 0x00, 0x55, 0x5a, 0x12, 0x4b,  // ..T.UZ.K
        /* 0080 */ 0x94, 0x71, 0xf5, 0x03, 0x52, 0x56, 0xb9, 0x13,  // .q..RV..
        /* 0088 */ 0xfc, 0x25, 0x09, 0x80, 0x51, 0x23, 0x10, 0x19,  // .%..Q#..
        /* 0090 */ 0x9a, 0x68, 0x2c, 0xf5, 0x7e, 0xd6, 0xb0, 0xbf,  // .h,.~...
        /* 0098 */ 0x07, 0xf0, 0xf2, 0x69, 0x75, 0xa6, 0x4f, 0x40,  // ...iu.O@
        /* 00a0 */ 0x0d, 0x8f, 0xaf, 0x2f, 0x61, 0x62, 0xd7, 0xcb,  // .../ab..
        /* 00a8 */ 0x51, 0x1a, 0x1e, 0x03, 0x7b, 0xa8, 0x6e, 0x41,  // Q...{.nA
        /* 00b0 */ 0xec, 0x3a, 0x08, 0x45, 0xf3, 0xa1, 0xbf, 0x9c,  // .:.E....
        /* 00b8 */ 0xcc, 0xd7, 0xcd, 0x59, 0x77, 0x49, 0x40, 0xd0,  // ...YwI@.
        /* 00c0 */ 0xb0, 0x33, 0x97, 0x5a, 0xbf, 0xba, 0x5e, 0x3a,  // .3.Z..^:
        /* 00c8 */ 0x77, 0x81, 0x55, 0xa5, 0x7f, 0xdc, 0x71, 0x43,  // w.U...qC
        /* 00d0 */ 0x4e, 0x6b, 0xbc, 0x0f, 0xc9, 0xaf, 0xfc, 0xcf,  // Nk......
        /* 00d8 */ 0xc4, 0x2b, 0x02, 0x65, 0x4f, 0x09, 0x92, 0x64,  // .+.eO..d
        /* 00e0 */ 0x2d, 0x29, 0x23, 0xea, 0xf5, 0x02, 0xe3, 0xd2,  // -)#.....
        /* 00e8 */ 0x05, 0x21, 0x06, 0xde, 0x6a, 0x0d, 0xd2, 0xe7,  // .!..j...
        /* 00f0 */ 0xf8, 0x2b, 0xbd, 0xea, 0x07, 0xc6, 0xc2, 0x79,  // .+.....y
        /* 00f8 */ 0x1c, 0xa5, 0x10, 0xf4, 0xb5, 0x51, 0x4f, 0x03,  // .....QO.
        /* 0100 */ 0x5e, 0x23, 0x2a, 0x67, 0xd6, 0x65, 0x5b, 0x94,  // ^#*g.e[.
        /* 0108 */ 0xe2, 0x1c, 0xda, 0x78, 0xf6, 0x7b, 0xd8, 0x97,  // ...x.{..
        /* 0110 */ 0x71, 0xb4, 0x1a, 0x05, 0xc1, 0x62, 0xfb, 0x38,  // q....b.8
        /* 0118 */ 0x92, 0xba, 0x2a, 0x21, 0x65, 0xdb, 0x0e, 0xb2,  // ..*!e...
        /* 0120 */ 0xcb, 0xa1, 0x78, 0x29, 0x9b, 0xed, 0x3d, 0xbe,  // ..x)..=.
        /* 0128 */ 0x84, 0x8b, 0xe9, 0xc9, 0x82, 0xfe, 0x5f, 0x66,  // ......_f
        /* 0130 */ 0x24, 0x16, 0x51, 0xdf, 0x6c, 0xd6, 0xc8, 0x7f,  // $.Q.l...
        /* 0138 */ 0x99, 0xe1, 0x2a, 0xe4, 0x39, 0x1c, 0x49, 0xc4,  // ..*.9.I.
        /* 0140 */ 0xbc, 0xd2, 0x76, 0xd3, 0x2a, 0x58, 0x48, 0x5b,  // ..v.*XH[
        /* 0148 */ 0x13, 0xc4, 0x9c, 0x81, 0xc1, 0x4a, 0xec, 0x5b,  // .....J.[
        /* 0150 */ 0xab, 0x7f, 0xfa, 0x96, 0x02, 0xc6, 0x19, 0x1e,  // ........
        /* 0158 */ 0xbd, 0x83, 0x35, 0x1b, 0xfd, 0x26, 0x68, 0xba,  // ..5..&h.
        /* 0160 */ 0x68, 0x70, 0x47, 0x5a, 0xfc, 0xb0, 0xc8, 0x15,  // hpGZ....
        /* 0168 */ 0x50, 0xe0, 0x4d, 0x81, 0x64, 0x79, 0x31, 0x80,  // P.M.dy1.
        /* 0170 */ 0x5b, 0x5c, 0x17, 0xa2, 0x56, 0x3f, 0x15, 0xd6,  // [...V?..
        /* 0178 */ 0x74, 0x22, 0x3e, 0x79, 0x19, 0x69, 0x42, 0x5c,  // t">y.iB.
        /* 0180 */ 0x8c, 0x7d, 0x73, 0xbe, 0x71, 0x11, 0x39, 0xca,  // .}s.q.9.
        /* 0188 */ 0x80, 0xcb, 0xc1, 0xb6, 0x76, 0xb8, 0x14, 0xfb,  // ....v...
        /* 0190 */ 0x03, 0x35, 0x3d, 0xdf, 0x00, 0x08, 0x2c, 0x3a,  // .5=...,:
        /* 0198 */ 0x76, 0xff, 0x3b, 0xca, 0xca, 0x47, 0x0c, 0x58,  // v.;..G.X
        /* 01a0 */ 0x56, 0x21, 0xcb, 0x75, 0xa4, 0x88, 0x75, 0xef,  // V!.u..u.
        /* 01a8 */ 0xd9, 0x8c, 0x87, 0x69, 0xed, 0x4a, 0x72, 0xb6,  // ...i.Jr.
        /* 01b0 */ 0x9e, 0x61, 0x03, 0x0b, 0xe5, 0xac, 0x90, 0x0d,  // .a......
        /* 01b8 */ 0x5c, 0x03, 0x9a, 0x2f, 0x51, 0x53, 0xc6, 0x5e,  // .../QS.^
        /* 01c0 */ 0xbd, 0x58, 0xdc, 0x52, 0xc9, 0xb1, 0x85, 0x4e,  // .X.R...N
        /* 01c8 */ 0x1b, 0x06, 0x20, 0xb3, 0x0f, 0x02, 0x96, 0x3c,  // .. ....<
        /* 01d0 */ 0xa0, 0x86, 0xff, 0xdf, 0xca, 0xf2, 0xdb, 0x96,  // ........
        /* 01d8 */ 0xc2, 0xc8, 0xce, 0xa8, 0x6d, 0xae, 0x56, 0x9f,  // ....m.V.
        /* 01e0 */ 0xfd, 0x6d, 0xf5, 0x51, 0x13, 0x71, 0xe9, 0x27,  // .m.Q.q.'
        /* 01e8 */ 0x15, 0x1d, 0x4c, 0x4e, 0x88, 0xf3, 0xc8, 0x0f,  // ..LN....
        /* 01f0 */ 0x09, 0xca, 0xcc, 0x22, 0x28, 0x66, 0xae, 0x8e,  // ..."(f..
        /* 01f8 */ 0xd4, 0x96, 0xd4, 0x5a, 0x38, 0xf6, 0x33, 0xfd,  // ...Z8.3.
    };

    SslRC4 rc;
    uint8_t encrypted_data[512];
    rc.set_key(key, sizeof(key));
    rc.crypt(512, data, encrypted_data);
    // hexdump_c(encrypted_data, sizeof(encrypted_data));


    uint8_t expected_data[] = {
        /* 0000 */ 0xbb, 0xcc, 0x0f, 0x8e, 0xef, 0x5c, 0x71, 0x0d,  // ......q.
        /* 0008 */ 0x39, 0x1a, 0x94, 0x47, 0xc5, 0xed, 0xed, 0xbb,  // 9..G....
        /* 0010 */ 0x50, 0x41, 0x48, 0xf5, 0x33, 0x77, 0xae, 0xd6,  // PAH.3w..
        /* 0018 */ 0x52, 0x49, 0x00, 0x32, 0xdc, 0x7e, 0x93, 0x5c,  // RI.2.~..
        /* 0020 */ 0xf8, 0x68, 0xd2, 0xed, 0xa9, 0x9b, 0xa4, 0x09,  // .h......
        /* 0028 */ 0x74, 0x10, 0xf4, 0xc4, 0x5a, 0xa7, 0x92, 0x48,  // t...Z..H
        /* 0030 */ 0xa8, 0xc6, 0x88, 0x37, 0xe1, 0x37, 0xbd, 0x2f,  // ...7.7./
        /* 0038 */ 0x53, 0xca, 0x50, 0xe3, 0xf3, 0xad, 0xbf, 0x9d,  // S.P.....
        /* 0040 */ 0x5f, 0x22, 0x9f, 0x85, 0xba, 0xf2, 0xaa, 0xf9,  // _"......
        /* 0048 */ 0x2f, 0x0e, 0x61, 0xd5, 0xec, 0x8b, 0x26, 0xcd,  // /.a...&.
        /* 0050 */ 0xfb, 0x3e, 0xc8, 0xfb, 0x17, 0xac, 0xf8, 0xae,  // .>......
        /* 0058 */ 0xe5, 0xc1, 0xf8, 0x5e, 0xcc, 0x9a, 0xe6, 0x09,  // ...^....
        /* 0060 */ 0xac, 0x0b, 0x83, 0xc3, 0x59, 0x0a, 0xf1, 0x80,  // ....Y...
        /* 0068 */ 0xb1, 0xd2, 0x19, 0x73, 0x1a, 0x4f, 0xf7, 0x02,  // ...s.O..
        /* 0070 */ 0x29, 0x8c, 0xaf, 0x70, 0x2a, 0x2b, 0x86, 0x05,  // )..p*+..
        /* 0078 */ 0x0b, 0x48, 0xc0, 0x01, 0x57, 0x67, 0x02, 0xb5,  // .H..Wg..
        /* 0080 */ 0xca, 0x59, 0x36, 0xc7, 0x86, 0x06, 0x4b, 0xd4,  // .Y6...K.
        /* 0088 */ 0xed, 0x68, 0x75, 0xa5, 0x05, 0xf6, 0xe2, 0x13,  // .hu.....
        /* 0090 */ 0x26, 0x88, 0x22, 0xc4, 0x08, 0xdf, 0x71, 0x8c,  // &."...q.
        /* 0098 */ 0x83, 0x58, 0x48, 0x5b, 0x5e, 0x08, 0x1c, 0x0c,  // .XH[^...
        /* 00a0 */ 0x88, 0xc2, 0xb0, 0xe3, 0x59, 0x2c, 0x74, 0x96,  // ....Y,t.
        /* 00a8 */ 0x36, 0x2d, 0x7e, 0x79, 0x47, 0xa5, 0x59, 0x5b,  // 6-~yG.Y[
        /* 00b0 */ 0x49, 0xc1, 0xb8, 0xb2, 0xd6, 0x23, 0x63, 0x58,  // I....#cX
        /* 00b8 */ 0xf1, 0xea, 0x6e, 0xed, 0xca, 0x69, 0x29, 0xe8,  // ..n..i).
        /* 00c0 */ 0xf3, 0xcf, 0x5a, 0x99, 0x54, 0xb3, 0xb0, 0xbb,  // ..Z.T...
        /* 00c8 */ 0x3a, 0x79, 0x03, 0x18, 0x47, 0xf6, 0x2d, 0x89,  // :y..G.-.
        /* 00d0 */ 0x39, 0x50, 0x17, 0xbc, 0xcc, 0x79, 0xf8, 0xf3,  // 9P...y..
        /* 00d8 */ 0xb5, 0xff, 0x70, 0x03, 0x70, 0xb7, 0x1b, 0x02,  // ..p.p...
        /* 00e0 */ 0x41, 0x99, 0xd7, 0x27, 0x58, 0xf1, 0xc6, 0x0f,  // A..'X...
        /* 00e8 */ 0x2b, 0x3a, 0x05, 0x54, 0x32, 0xce, 0xba, 0x87,  // +:.T2...
        /* 00f0 */ 0xc5, 0xc6, 0x7d, 0x58, 0x68, 0x83, 0xb9, 0xbb,  // ..}Xh...
        /* 00f8 */ 0xb0, 0x81, 0x92, 0xf1, 0xf7, 0x29, 0x1a, 0xd2,  // .....)..
        /* 0100 */ 0x5e, 0x1f, 0xee, 0x04, 0x8b, 0x82, 0x53, 0x21,  // ^.....S!
        /* 0108 */ 0x75, 0xbf, 0x12, 0xf3, 0xbc, 0xd5, 0x06, 0xc2,  // u.......
        /* 0110 */ 0x2a, 0xb3, 0xef, 0x2d, 0x47, 0xf4, 0x0b, 0x83,  // *..-G...
        /* 0118 */ 0xf2, 0xfa, 0x03, 0x30, 0x39, 0xd4, 0xae, 0x98,  // ...09...
        /* 0120 */ 0x3a, 0x76, 0x29, 0x92, 0x12, 0x3d, 0xd2, 0xe5,  // :v)..=..
        /* 0128 */ 0xa5, 0xf5, 0xfd, 0x30, 0x1d, 0xfd, 0xd0, 0x84,  // ...0....
        /* 0130 */ 0x14, 0x69, 0x03, 0x34, 0x23, 0x78, 0xe8, 0xbd,  // .i.4#x..
        /* 0138 */ 0x66, 0xbf, 0xe4, 0xf2, 0xd9, 0xf7, 0x48, 0xdb,  // f.....H.
        /* 0140 */ 0x24, 0x19, 0xb0, 0x6c, 0x87, 0x87, 0xfd, 0xd0,  // $..l....
        /* 0148 */ 0x58, 0x40, 0xbd, 0x05, 0x75, 0x5d, 0xce, 0xc5,  // X@..u]..
        /* 0150 */ 0xd4, 0x9b, 0x93, 0x79, 0xa1, 0x14, 0x0c, 0xf1,  // ...y....
        /* 0158 */ 0xae, 0x5e, 0x52, 0x91, 0x65, 0x58, 0x1b, 0xe3,  // .^R.eX..
        /* 0160 */ 0x26, 0x76, 0xef, 0x61, 0xb5, 0xd6, 0xcd, 0x51,  // &v.a...Q
        /* 0168 */ 0x1d, 0xa9, 0x67, 0x21, 0x6c, 0x3a, 0x3e, 0xf9,  // ..g!l:>.
        /* 0170 */ 0x5f, 0x40, 0x7d, 0x24, 0x82, 0xc4, 0x28, 0x36,  // _@}$..(6
        /* 0178 */ 0x82, 0x2d, 0x0a, 0x16, 0x55, 0x2a, 0xf1, 0xd5,  // .-..U*..
        /* 0180 */ 0x15, 0x15, 0xd0, 0xfb, 0x71, 0x9b, 0x0d, 0x6b,  // ....q..k
        /* 0188 */ 0x63, 0x75, 0x9a, 0xd1, 0xab, 0xe9, 0x46, 0xc0,  // cu....F.
        /* 0190 */ 0x35, 0x7b, 0x19, 0xf1, 0x90, 0x03, 0x0a, 0x34,  // 5{.....4
        /* 0198 */ 0xc5, 0x5f, 0x64, 0x41, 0xc7, 0x73, 0x08, 0x41,  // ._dA.s.A
        /* 01a0 */ 0x56, 0xa2, 0xd4, 0x03, 0xd4, 0x11, 0xa2, 0xad,  // V.......
        /* 01a8 */ 0x6a, 0x3a, 0xd6, 0xd1, 0x45, 0x32, 0xb7, 0x1b,  // j:..E2..
        /* 01b0 */ 0x97, 0x90, 0xd5, 0x75, 0x03, 0xee, 0x1f, 0xe2,  // ...u....
        /* 01b8 */ 0xd4, 0xc1, 0xd5, 0xf7, 0x6b, 0x41, 0x35, 0x66,  // ....kA5f
        /* 01c0 */ 0x92, 0xb6, 0x65, 0x20, 0x4c, 0x9c, 0xd2, 0x94,  // ..e L...
        /* 01c8 */ 0xd1, 0xe9, 0x35, 0x71, 0xe8, 0xcb, 0xea, 0xc8,  // ..5q....
        /* 01d0 */ 0x6c, 0x8c, 0xc4, 0x0c, 0xfa, 0xb9, 0x6b, 0x81,  // l.....k.
        /* 01d8 */ 0x9f, 0xd2, 0x2d, 0x71, 0xb0, 0x37, 0x12, 0xb7,  // ..-q.7..
        /* 01e0 */ 0x65, 0x83, 0xc0, 0xf1, 0x1a, 0xf6, 0xab, 0xa1,  // e.......
        /* 01e8 */ 0xd5, 0x66, 0x3f, 0x7a, 0xcb, 0xa6, 0x4b, 0xa4,  // .f?z..K.
        /* 01f0 */ 0xca, 0x4c, 0xeb, 0x28, 0x2e, 0x55, 0xe9, 0xa3,  // .L.(.U..
        /* 01f8 */ 0xac, 0x2f, 0x14, 0x6b, 0xd1, 0xc1, 0x43, 0xe1,  // ./.k..C.
    };
    BOOST_CHECK_EQUAL(memcmp(encrypted_data,
                             expected_data,
                             sizeof(encrypted_data)),
                      0);

    uint8_t decrypted_data[512];
    rc.set_key(key, sizeof(key));
    rc.crypt(512, encrypted_data, decrypted_data);
    // hexdump96_c(decrypted_data, sizeof(decrypted_data));

    BOOST_CHECK_EQUAL(memcmp(decrypted_data,
                             data,
                             sizeof(data)),
                      0);


}

BOOST_AUTO_TEST_CASE(TestSslHmacSHA256)
{
    const uint8_t key[] = "key";
    // const uint8_t key[] = "";
    SslHMAC_Sha256 hmac(key, sizeof(key)-1);

    const uint8_t msg[] = "The quick brown fox jumps over the lazy dog";
    // const uint8_t msg[] = "";
    hmac.update(msg, sizeof(msg)-1);

    uint8_t sig[SHA256_DIGEST_LENGTH];
    hmac.final(sig, SHA256_DIGEST_LENGTH);

    BOOST_CHECK_EQUAL(SHA256_DIGEST_LENGTH, 32);

    BOOST_CHECK_EQUAL(memcmp(sig,
                             "\xf7\xbc\x83\xf4\x30\x53\x84\x24\xb1\x32\x98\xe6\xaa\x6f\xb1\x43"
                             "\xef\x4d\x59\xa1\x49\x46\x17\x59\x97\x47\x9d\xbc\x2d\x1a\x3c\xd8",
                             SHA256_DIGEST_LENGTH),
                      0);
    // hexdump96_c(sigstream.get_data(), sigstream.size());

}

BOOST_AUTO_TEST_CASE(TestSslHmacMd5)
{
    const uint8_t key[] = "key";
    // const uint8_t key[] = "";
    SslHMAC_Md5 hmac(key, sizeof(key) - 1);

    const uint8_t msg[] = "The quick brown fox jumps over the lazy dog";
    // const uint8_t msg[] = "";
    hmac.update(msg, sizeof(msg) - 1);

    uint8_t sig[16];
    hmac.final(sig, sizeof(sig));
    // hexdump96_c(sig, sizeof(sig));
    BOOST_CHECK_EQUAL(memcmp(sig,
                             "\x80\x07\x07\x13\x46\x3e\x77\x49"
                             "\xb9\x0c\x2d\xc2\x49\x11\xe2\x75",
                             sizeof(sig)),
                      0);
}


BOOST_AUTO_TEST_CASE(TestSslHmacSign)
{
    const uint8_t key[] = "key";
    // const uint8_t key[] = "";
    Sign hmac(key, sizeof(key) - 1);

    const uint8_t msg[] = "The quick brown fox jumps over the lazy dog";
    // const uint8_t msg[] = "";
    hmac.update(msg, sizeof(msg) - 1);

    uint8_t sig[16];
    hmac.final(sig, sizeof(sig));
    // hexdump96_c(sig, sizeof(sig));
    BOOST_CHECK_EQUAL(memcmp(sig,
                             "\x10\xfb\x60\x2c\xef\xe7\xe0\x0b"
                             "\x91\xc2\xe2\x12\x39\x80\xe1\x94",
                             sizeof(sig)),
                      0);
}


BOOST_AUTO_TEST_CASE(TestNTLMAUTH)
{
    SslMd4 md4;

    uint8_t password[] = {
        // 0x50, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00,
        // 0x77, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x64, 0x00
        0x70, 0x00, 0x61, 0x00, 0x73, 0x00, 0x73, 0x00,
        0x77, 0x00, 0x6f, 0x00, 0x72, 0x00, 0x64, 0x00
    };
    // uint8_t user[] = {
    //     0x75, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00,
    //     0x6e, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00
    // };
    uint8_t userUpper[] = {
        // 0x55, 0x00, 0x53, 0x00, 0x45, 0x00, 0x52, 0x00
        0x55, 0x00, 0x53, 0x00, 0x45, 0x00, 0x52, 0x00,
        0x4e, 0x00, 0x41, 0x00, 0x4d, 0x00, 0x45, 0x00
    };
    uint8_t userDomain[] = {
        // 0x44, 0x00, 0x6f, 0x00, 0x6d, 0x00, 0x61, 0x00,
        // 0x69, 0x00, 0x6e, 0x00
        0x77, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x37, 0x00
    };


    uint8_t md4password[16] = {};
    md4.update(password, sizeof(password));
    md4.final(md4password, sizeof(md4password));
    // hexdump96_c(md4password, sizeof(md4password));

    SslHMAC_Md5 hmac_md5(md4password, sizeof(md4password));
    hmac_md5.update(userUpper, sizeof(userUpper));
    hmac_md5.update(userDomain, sizeof(userDomain));
    // equivalent: hmac_md5.update(useranddomain, sizeof(useranddomain));

    uint8_t sig[16] = {};
    hmac_md5.final(sig, sizeof(sig));
    // hexdump96_c(sig, sizeof(sig));


    // NTOWFv2(password, user, userdomain) =
    //   HMAC_MD5( MD4(UNICODE(password)),
    //             UNICODE( Concat( Upper(user), userdomain) )
    //           )


    const uint8_t NTOWFv2[] = {
        0xef, 0xc2, 0xc0, 0x9f, 0x06, 0x11, 0x3d, 0x71,
        0x08, 0xd0, 0xd2, 0x29, 0xfa, 0x4d, 0xe6, 0x98
    };

    BOOST_CHECK_EQUAL(memcmp(sig,
                             NTOWFv2,
                             sizeof(sig)),
                      0);



    // CHALLENGE_MESSAGE.TargetInfo.MsvAvTimestamp 8-bytes (little endian)
    // const uint8_t ServerTimeStamp[] = {
    //     0xa9, 0x8d, 0x9b, 0x1a, 0x6c, 0xb0, 0xcb, 0x01
    // };
    // Current time ?
    const uint8_t ClientTimeStamp[] = {
        0xc3, 0x83, 0xa2, 0x1c, 0x6c, 0xb0, 0xcb, 0x01
    };
    // nonce generated by client
    const uint8_t ClientChallenge[] = {
        0x47, 0xa2, 0xe5, 0xcf, 0x27, 0xf7, 0x3c, 0x43
    };

    // CHALLENGE_MESSAGE.AvPairs
    const uint8_t AvPairs[] = {
        0x02, 0x00, 0x08, 0x00, 0x57, 0x00, 0x49, 0x00,
        0x4e, 0x00, 0x37, 0x00, 0x01, 0x00, 0x08, 0x00,
        0x57, 0x00, 0x49, 0x00, 0x4e, 0x00, 0x37, 0x00,
        0x04, 0x00, 0x08, 0x00, 0x77, 0x00, 0x69, 0x00,
        0x6e, 0x00, 0x37, 0x00, 0x03, 0x00, 0x08, 0x00,
        0x77, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x37, 0x00,
        0x07, 0x00, 0x08, 0x00, 0xa9, 0x8d, 0x9b, 0x1a,
        0x6c, 0xb0, 0xcb, 0x01, 0x00, 0x00, 0x00, 0x00
    };
    uint8_t temp[1 + 1 + 6 + 8 + 8 + 4 + sizeof(AvPairs) + 4] = {};

    temp[0] = 0x01;
    temp[1] = 0x01;

    // memcpy(&temp[1+1+6], ServerTimeStamp, sizeof(ServerTimeStamp));
    memcpy(&temp[1+1+6], ClientTimeStamp, sizeof(ClientTimeStamp));
    memcpy(&temp[1+1+6+8], ClientChallenge, sizeof(ClientChallenge));
    memcpy(&temp[1+1+6+8+8+4], AvPairs, sizeof(AvPairs));

    // temp = { 0x01, 0x01, Z(6), Time, ClientChallenge, Z(4), ServerName , Z(4) }
    // Z(n) = { 0x00, ... , 0x00 } n times
    // ServerName = AvPairs received in Challenge message

    // CHALLENGE_MESSAGE.ServerChallenge 8-bytes
    const uint8_t ServerChallenge[] = {
        // 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
        0x26, 0x6e, 0xcd, 0x75, 0xaa, 0x41, 0xe7, 0x6f
    };
    // hexdump_c(temp, sizeof(temp));

    uint8_t computed_NtProofStr[16] = {};
    SslHMAC_Md5 hmac_md5resp(NTOWFv2, sizeof(NTOWFv2));
    hmac_md5resp.update(ServerChallenge, sizeof(ServerChallenge));
    hmac_md5resp.update(temp, sizeof(temp));
    hmac_md5resp.final(computed_NtProofStr, sizeof(computed_NtProofStr));
    // hexdump96_c(computed_NtProofStr, sizeof(computed_NtProofStr));

    // NtProofStr = HMAC_MD5(NTOWFv2(password, user, userdomain),
    //                       Concat(ServerChallenge, temp))

    // NTLMv2 Response (NtProofStr)
    const uint8_t NtProofStr[] = {
        0x01, 0x4a, 0xd0, 0x8c, 0x24, 0xb4, 0x90, 0x74,
        0x39, 0x68, 0xe8, 0xbd, 0x0d, 0x2b, 0x70, 0x10
    };
    BOOST_CHECK_EQUAL(memcmp(computed_NtProofStr,
                             NtProofStr,
                             sizeof(computed_NtProofStr)),
                      0);

    // NtChallengeResponse = Concat(NtProofStr, temp)

    // LmChallengeResponse.Response = HMAC_MD5(NTOWFv2(password, user, userdomain),
    //                                         Concat(ServerChallenge, ClientChallenge))
    // hmac_md5resp = SslHMAC_Md5(NTOWFv2, sizeof(NTOWFv2));
    SslHMAC_Md5 hmac_md5lmresp(NTOWFv2, sizeof(NTOWFv2));
    hmac_md5lmresp.update(ServerChallenge, sizeof(ServerChallenge));
    hmac_md5lmresp.update(ClientChallenge, sizeof(ClientChallenge));
    uint8_t LmChallengeResponse[16] = {};
    hmac_md5lmresp.final(LmChallengeResponse, sizeof(LmChallengeResponse));
    // hexdump96_c(LmChallengeResponse, sizeof(LmChallengeResponse));

    // LmChallengeResponse.ChallengeFromClient = ClientChallenge

    uint8_t LmChallengeResp[sizeof(LmChallengeResponse) + sizeof(ClientChallenge)] = {};
    memcpy(LmChallengeResp, LmChallengeResponse, sizeof(LmChallengeResponse));
    memcpy(&LmChallengeResp[sizeof(LmChallengeResponse)], ClientChallenge, sizeof(ClientChallenge));

    uint8_t LmChallengeRespExpected[] = {
        0xa0, 0x98, 0x01, 0x10, 0x19, 0xbb, 0x5d, 0x00,
        0xf6, 0xbe, 0x00, 0x33, 0x90, 0x20, 0x34, 0xb3,
        0x47, 0xa2, 0xe5, 0xcf, 0x27, 0xf7, 0x3c, 0x43
    };
    BOOST_CHECK_EQUAL(memcmp(LmChallengeResp,
                             LmChallengeRespExpected,
                             sizeof(LmChallengeResp)),
                      0);

    // SessionBaseKey = HMAC_MD5(NTOWFv2(password, user, userdomain),
    //                           NtProofStr)
    uint8_t SessionBaseKey[16] = {};
    SslHMAC_Md5 hmac_md5seskey(NTOWFv2, sizeof(NTOWFv2));
    hmac_md5seskey.update(NtProofStr, sizeof(NtProofStr));
    hmac_md5seskey.final(SessionBaseKey, sizeof(SessionBaseKey));
    // hexdump96_c(SessionBaseKey, sizeof(SessionBaseKey));

    // EncryptedRandomSessionKey = RC4K(KeyExchangeKey, ExportedSessionKey)
    // ExportedSessionKey = NONCE(16) (random 16bytes number)
    // KeyExchangeKey = SessionBaseKey
    // EncryptedRandomSessionKey = RC4K(SessionBaseKey, NONCE(16))
    SslRC4 rc4;
    rc4.set_key(SessionBaseKey, sizeof(SessionBaseKey));
    uint8_t EncryptedRandomSessionKey[16] = {};
    uint8_t ExportedSessionKey[16] = {
        0x89, 0x90, 0x0d, 0x5d, 0x2c, 0x53, 0x2b, 0x36,
        0x31, 0xcc, 0x1a, 0x46, 0xce, 0xa9, 0x34, 0xf1
    };
    rc4.crypt(sizeof(EncryptedRandomSessionKey), ExportedSessionKey, EncryptedRandomSessionKey);
    // hexdump96_c(EncryptedRandomSessionKey, sizeof(EncryptedRandomSessionKey));

    uint8_t EncryptedRandomSessionKeyExpected[16] = {
        0xb1, 0xd2, 0x45, 0x42, 0x0f, 0x37, 0x9a, 0x0e,
        0xe0, 0xce, 0x77, 0x40, 0x10, 0x8a, 0xda, 0xba
    };
    BOOST_CHECK_EQUAL(memcmp(EncryptedRandomSessionKeyExpected,
                             EncryptedRandomSessionKey,
                             sizeof(ExportedSessionKey)),
                      0);


    static const uint8_t client_sign_magic[] = "session key to client-to-server signing key magic constant";
    static const uint8_t server_sign_magic[] = "session key to server-to-client signing key magic constant";
    static const uint8_t client_seal_magic[] = "session key to client-to-server sealing key magic constant";
    static const uint8_t server_seal_magic[] = "session key to server-to-client sealing key magic constant";
    // ClientSignKey = MD5(Concat(ExportedSessionKey,
    //                            "session key to client-to-server signing key magic constant"))

    uint8_t ClientSignKey[16] = {};
    SslMd5 md5clientsign;
    md5clientsign.update(ExportedSessionKey, sizeof(ExportedSessionKey));
    md5clientsign.update(client_sign_magic, sizeof(client_sign_magic));
    md5clientsign.final(ClientSignKey, sizeof(ClientSignKey));
    // hexdump_d(ClientSignKey, sizeof(ClientSignKey));
    uint8_t ClientSignKeyExpected[16] = {
        0xbf, 0x5e, 0x42, 0x76, 0x55, 0x68, 0x38, 0x97,
        0x45, 0xd3, 0xb4, 0x9f, 0x5e, 0x2f, 0xbc, 0x89
    };
    BOOST_CHECK_EQUAL(memcmp(ClientSignKeyExpected,
                             ClientSignKey,
                             sizeof(ClientSignKey)),
                      0);

    // ServerSignKey = MD5(Concat(ExportedSessionKey,
    //                            "session key to server-to-client signing key magic constant"))
    uint8_t ServerSignKey[16] = {};
    SslMd5 md5serversign;
    md5serversign.update(ExportedSessionKey, sizeof(ExportedSessionKey));
    md5serversign.update(server_sign_magic, sizeof(server_sign_magic));
    md5serversign.final(ServerSignKey, sizeof(ServerSignKey));
    // hexdump_d(ServerSignKey, sizeof(ServerSignKey));
    uint8_t ServerSignKeyExpected[16] = {
        0x9b, 0x3b, 0x64, 0x89, 0xda, 0x84, 0x52, 0x17,
        0xd5, 0xc2, 0x6e, 0x90, 0x16, 0x3b, 0x42, 0x11
    };
    BOOST_CHECK_EQUAL(memcmp(ServerSignKeyExpected,
                             ServerSignKey,
                             sizeof(ServerSignKey)),
                      0);

    // ClientSealKey = MD5(Concat(ExportedSessionKey,
    //                            "session key to client-to-server sealing key magic constant"))
    uint8_t ClientSealKey[16] = {};
    SslMd5 md5clientseal;
    md5clientseal.update(ExportedSessionKey, sizeof(ExportedSessionKey));
    md5clientseal.update(client_seal_magic, sizeof(client_seal_magic));
    md5clientseal.final(ClientSealKey, sizeof(ClientSealKey));
    // hexdump_d(ClientSealKey, sizeof(ClientSealKey));
    uint8_t ClientSealKeyExpected[16] = {
        0xca, 0x41, 0xcd, 0x08, 0x48, 0x07, 0x22, 0x6e,
        0x0d, 0x84, 0xc3, 0x88, 0xa5, 0x07, 0xa9, 0x73
    };
    BOOST_CHECK_EQUAL(memcmp(ClientSealKeyExpected,
                             ClientSealKey,
                             sizeof(ClientSealKey)),
                      0);


    // ServerSealKey = MD5(Concat(ExportedSessionKey,
    //                            "session key to server-to-client sealing key magic constant"))
    uint8_t ServerSealKey[16] = {};
    SslMd5 md5serverseal;
    md5serverseal.update(ExportedSessionKey, sizeof(ExportedSessionKey));
    md5serverseal.update(server_seal_magic, sizeof(server_seal_magic));
    md5serverseal.final(ServerSealKey, sizeof(ServerSealKey));
    // hexdump_d(ServerSealKey, sizeof(ServerSealKey));
    uint8_t ServerSealKeyExpected[16] = {
        0x14, 0xb7, 0x1d, 0x06, 0x2c, 0x68, 0x2e, 0xad,
        0x4b, 0x0e, 0x95, 0x23, 0x70, 0x91, 0x98, 0x90
    };
    BOOST_CHECK_EQUAL(memcmp(ServerSealKeyExpected,
                             ServerSealKey,
                             sizeof(ServerSealKey)),
                      0);

}

BOOST_AUTO_TEST_CASE(TestAES)
{
    SslAES aes;

    uint8_t key24[] = "clef très très secrete";
    uint8_t iv[] = "vecteur d'initialisation pas secret du tout";
    uint8_t iv2[] = "vecteur d'initialisation pas secret du tout";

    uint8_t inbuf[1024]= "secret très confidentiel\x00\x00\x00\x00\x00\x00\x00\x00";
    uint8_t outbuf[1024] = {};
    uint8_t decrypted[1024] = {};


    aes.set_key(key24, 24);

    aes.crypt_cbc(32, iv, inbuf, outbuf);

    aes.decrypt_cbc(32, iv2, outbuf, decrypted);

    BOOST_CHECK_EQUAL(memcmp(inbuf,
                             decrypted,
                             32),
                      0);

}

//-- =================== SC_SECURITY =============
//-- receiving SC_SECURITY begin
//-- 0000 02 0c 36 22 02 00 00 00 02 00 00 00 20 00 00 00 ..6"........ ...
//-- 0010 02 22 00 00 31 67 6c 98 f5 8d 5b 66 c2 33 f3 6b ."..1gl...[f.3.k
//-- 0020 ce d5 50 3e 80 1c 28 84 c1 b0 13 38 62 7b b9 a6 ..P>..(....8b{..
//-- 0030 81 5b 83 94 02 00 00 00 06 00 00 00 16 04 00 00 .[..............
//-- 0040 30 82 04 12 30 82 02 fa a0 03 02 01 02 02 0f 00 0...0...........
//-- 0050 c1 00 8b 3c 3c 88 11 d1 3e f6 63 ec df 40 30 0d ...<<...>.c..@0.
//-- 0060 06 09 2a 86 48 86 f7 0d 01 01 04 05 00 30 70 31 ..*.H........0p1
//-- 0070 2b 30 29 06 03 55 04 0b 13 22 43 6f 70 79 72 69 +0)..U..."Copyri
//-- 0080 67 68 74 20 28 63 29 20 31 39 39 37 20 4d 69 63 ght (c) 1997 Mic
//-- 0090 72 6f 73 6f 66 74 20 43 6f 72 70 2e 31 1e 30 1c rosoft Corp.1.0.
//-- 00a0 06 03 55 04 0b 13 15 4d 69 63 72 6f 73 6f 66 74 ..U....Microsoft
//-- 00b0 20 43 6f 72 70 6f 72 61 74 69 6f 6e 31 21 30 1f  Corporation1!0.
//-- 00c0 06 03 55 04 03 13 18 4d 69 63 72 6f 73 6f 66 74 ..U....Microsoft
//-- 00d0 20 52 6f 6f 74 20 41 75 74 68 6f 72 69 74 79 30  Root Authority0
//-- 00e0 1e 17 0d 39 37 30 31 31 30 30 37 30 30 30 30 5a ...970110070000Z
//-- 00f0 17 0d 32 30 31 32 33 31 30 37 30 30 30 30 5a 30 ..201231070000Z0
//-- 0100 70 31 2b 30 29 06 03 55 04 0b 13 22 43 6f 70 79 p1+0)..U..."Copy
//-- 0110 72 69 67 68 74 20 28 63 29 20 31 39 39 37 20 4d right (c) 1997 M
//-- 0120 69 63 72 6f 73 6f 66 74 20 43 6f 72 70 2e 31 1e icrosoft Corp.1.
//-- 0130 30 1c 06 03 55 04 0b 13 15 4d 69 63 72 6f 73 6f 0...U....Microso
//-- 0140 66 74 20 43 6f 72 70 6f 72 61 74 69 6f 6e 31 21 ft Corporation1!
//-- 0150 30 1f 06 03 55 04 03 13 18 4d 69 63 72 6f 73 6f 0...U....Microso
//-- 0160 66 74 20 52 6f 6f 74 20 41 75 74 68 6f 72 69 74 ft Root Authorit
//-- 0170 79 30 82 01 22 30 0d 06 09 2a 86 48 86 f7 0d 01 y0.."0...*.H....
//-- 0180 01 01 05 00 03 82 01 0f 00 30 82 01 0a 02 82 01 .........0......
//-- 0190 01 00 a9 02 bd c1 70 e6 3b f2 4e 1b 28 9f 97 78 ......p.;.N.(..x
//-- 01a0 5e 30 ea a2 a9 8d 25 5f f8 fe 95 4c a3 b7 fe 9d ^0....%_...L....
//-- 01b0 a2 20 3e 7c 51 a2 9b a2 8f 60 32 6b d1 42 64 79 . >|Q....`2k.Bdy
//-- 01c0 ee ac 76 c9 54 da f2 eb 9c 86 1c 8f 9f 84 66 b3 ..v.T.........f.
//-- 01d0 c5 6b 7a 62 23 d6 1d 3c de 0f 01 92 e8 96 c4 bf .kzb#..<........
//-- receiving SC_SECURITY done

#include "utils/stream.hpp"
#include "core/RDP/gcc.hpp"

BOOST_AUTO_TEST_CASE(TestSCSecurity)
{

//-- 0000 02 0c 36 22 02 00 00 00 02 00 00 00 20 00 00 00 ..6"........ ...
//-- 0010 02 22 00 00 31 67 6c 98 f5 8d 5b 66 c2 33 f3 6b ."..1gl...[f.3.k
//-- 0020 ce d5 50 3e 80 1c 28 84 c1 b0 13 38 62 7b b9 a6 ..P>..(....8b{..
//-- 0030 81 5b 83 94 02 00 00 00 06 00 00 00 16 04 00 00 .[..............
//-- 0040 30 82 04 12 30 82 02 fa a0 03 02 01 02 02 0f 00 0...0...........
//-- 0050 c1 00 8b 3c 3c 88 11 d1 3e f6 63 ec df 40 30 0d ...<<...>.c..@0.
//-- 0060 06 09 2a 86 48 86 f7 0d 01 01 04 05 00 30 70 31 ..*.H........0p1
//-- 0070 2b 30 29 06 03 55 04 0b 13 22 43 6f 70 79 72 69 +0)..U..."Copyri
//-- 0080 67 68 74 20 28 63 29 20 31 39 39 37 20 4d 69 63 ght (c) 1997 Mic
//-- 0090 72 6f 73 6f 66 74 20 43 6f 72 70 2e 31 1e 30 1c rosoft Corp.1.0.
//-- 00a0 06 03 55 04 0b 13 15 4d 69 63 72 6f 73 6f 66 74 ..U....Microsoft
//-- 00b0 20 43 6f 72 70 6f 72 61 74 69 6f 6e 31 21 30 1f  Corporation1!0.
//-- 00c0 06 03 55 04 03 13 18 4d 69 63 72 6f 73 6f 66 74 ..U....Microsoft
//-- 00d0 20 52 6f 6f 74 20 41 75 74 68 6f 72 69 74 79 30  Root Authority0
//-- 00e0 1e 17 0d 39 37 30 31 31 30 30 37 30 30 30 30 5a ...970110070000Z
//-- 00f0 17 0d 32 30 31 32 33 31 30 37 30 30 30 30 5a 30 ..201231070000Z0
//-- 0100 70 31 2b 30 29 06 03 55 04 0b 13 22 43 6f 70 79 p1+0)..U..."Copy
//-- 0110 72 69 67 68 74 20 28 63 29 20 31 39 39 37 20 4d right (c) 1997 M
//-- 0120 69 63 72 6f 73 6f 66 74 20 43 6f 72 70 2e 31 1e icrosoft Corp.1.
//-- 0130 30 1c 06 03 55 04 0b 13 15 4d 69 63 72 6f 73 6f 0...U....Microso
//-- 0140 66 74 20 43 6f 72 70 6f 72 61 74 69 6f 6e 31 21 ft Corporation1!
//-- 0150 30 1f 06 03 55 04 03 13 18 4d 69 63 72 6f 73 6f 0...U....Microso
//-- 0160 66 74 20 52 6f 6f 74 20 41 75 74 68 6f 72 69 74 ft Root Authorit
//-- 0170 79 30 82 01 22 30 0d 06 09 2a 86 48 86 f7 0d 01 y0.."0...*.H....
//-- 0180 01 01 05 00 03 82 01 0f 00 30 82 01 0a 02 82 01 .........0......
//-- 0190 01 00 a9 02 bd c1 70 e6 3b f2 4e 1b 28 9f 97 78 ......p.;.N.(..x
//-- 01a0 5e 30 ea a2 a9 8d 25 5f f8 fe 95 4c a3 b7 fe 9d ^0....%_...L....
//-- 01b0 a2 20 3e 7c 51 a2 9b a2 8f 60 32 6b d1 42 64 79 . >|Q....`2k.Bdy
//-- 01c0 ee ac 76 c9 54 da f2 eb 9c 86 1c 8f 9f 84 66 b3 ..v.T.........f.
//-- 01d0 c5 6b 7a 62 23 d6 1d 3c de 0f 01 92 e8 96 c4 bf .kzb#..<........
//-- 01e0 2d 66 9a 9a 68 26 99 d0 3a 2c bf 0c b5 58 26 c1 -f..h&..:,...X&.
//-- 01f0 46 e7 0a 3e 38 96 2c a9 28 39 a8 ec 49 83 42 e3 F..>8.,.(9..I.B.
//-- 0200 84 0f bb 9a 6c 55 61 ac 82 7c a1 60 2d 77 4c e9 ....lUa..|.`-wL.
//-- 0210 99 b4 64 3b 9a 50 1c 31 08 24 14 9f a9 e7 91 2b ..d;.P.1.$.....+
//-- 0220 18 e6 3d 98 63 14 60 58 05 65 9f 1d 37 52 87 f7 ..=.c.`X.e..7R..
//-- 0230 a7 ef 94 02 c6 1b d3 bf 55 45 b3 89 80 bf 3a ec ........UE....:.
//-- 0240 54 94 4e ae fd a7 7a 6d 74 4e af 18 cc 96 09 28 T.N...zmtN.....(
//-- 0250 21 00 57 90 60 69 37 bb 4b 12 07 3c 56 ff 5b fb !.W.`i7.K..<V.[.
//-- 0260 a4 66 0a 08 a6 d2 81 56 57 ef b6 3b 5e 16 81 77 .f.....VW..;^..w
//-- 0270 04 da f6 be ae 80 95 fe b0 cd 7f d6 a7 1a 72 5c ..............r.
//-- 0280 3c ca bc f0 08 a3 22 30 b3 06 85 c9 b3 20 77 13 <....."0..... w.
//-- 0290 85 df 02 03 01 00 01 a3 81 a8 30 81 a5 30 81 a2 ..........0..0..
//-- 02a0 06 03 55 1d 01 04 81 9a 30 81 97 80 10 5b d0 70 ..U.....0....[.p
//-- 02b0 ef 69 72 9e 23 51 7e 14 b2 4d 8e ff cb a1 72 30 .ir.#Q~..M....r0
//-- 02c0 70 31 2b 30 29 06 03 55 04 0b 13 22 43 6f 70 79 p1+0)..U..."Copy
//-- 02d0 72 69 67 68 74 20 28 63 29 20 31 39 39 37 20 4d right (c) 1997 M
//-- 02e0 69 63 72 6f 73 6f 66 74 20 43 6f 72 70 2e 31 1e icrosoft Corp.1.
//-- 02f0 30 1c 06 03 55 04 0b 13 15 4d 69 63 72 6f 73 6f 0...U....Microso
//-- 0300 66 74 20 43 6f 72 70 6f 72 61 74 69 6f 6e 31 21 ft Corporation1!
//-- 0310 30 1f 06 03 55 04 03 13 18 4d 69 63 72 6f 73 6f 0...U....Microso
//-- 0320 66 74 20 52 6f 6f 74 20 41 75 74 68 6f 72 69 74 ft Root Authorit
//-- 0330 79 82 0f 00 c1 00 8b 3c 3c 88 11 d1 3e f6 63 ec y......<<...>.c.
//-- 0340 df 40 30 0d 06 09 2a 86 48 86 f7 0d 01 01 04 05 .@0...*.H.......
//-- 0350 00 03 82 01 01 00 95 e8 0b c0 8d f3 97 18 35 ed ..............5.
//-- 0360 b8 01 24 d8 77 11 f3 5c 60 32 9f 9e 0b cb 3e 05 ..$.w...`2....>.
//-- 0370 91 88 8f c9 3a e6 21 f2 f0 57 93 2c b5 a0 47 c8 ....:.!..W.,..G.
//-- 0380 62 ef fc d7 cc 3b 3b 5a a9 36 54 69 fe 24 6d 3f b....;;Z.6Ti.$m?
//-- 0390 c9 cc aa de 05 7c dd 31 8d 3d 9f 10 70 6a bb fe .....|.1.=..pj..
//-- 03a0 12 4f 18 69 c0 fc d0 43 e3 11 5a 20 4f ea 62 7b .O.i...C..Z O.b{
//-- 03b0 af aa 19 c8 2b 37 25 2d be 65 a1 12 8a 25 0f 63 ....+7%-.e...%.c
//-- 03c0 a3 f7 54 1c f9 21 c9 d6 15 f3 52 ac 6e 43 32 07 ..T..!....R.nC2.
//-- 03d0 fd 82 17 f8 e5 67 6c 0d 51 f6 bd f1 52 c7 bd e7 .....gl.Q...R...
//-- 03e0 c4 30 fc 20 31 09 88 1d 95 29 1a 4d d5 1d 02 a5 .0. 1....).M....
//-- 03f0 f1 80 e0 03 b4 5b f4 b1 dd c8 57 ee 65 49 c7 52 .....[....W.eI.R
//-- 0400 54 b6 b4 03 28 12 ff 90 d6 f0 08 8f 7e b8 97 c5 T...(.......~...
//-- 0410 ab 37 2c e4 7a e4 a8 77 e3 76 a0 00 d0 6a 3f c1 .7,.z..w.v...j?.
//-- 0420 d2 36 8a e0 41 12 a8 35 6a 1b 6a db 35 e1 d4 1c .6..A..5j.j.5...
//-- 0430 04 e4 a8 45 04 c8 5a 33 38 6e 4d 1c 0d 62 b7 0a ...E..Z38nM..b..
//-- 0440 a2 8c d3 d5 54 3f 46 cd 1c 55 a6 70 db 12 3a 87 ....T?F..U.p..:.
//-- 0450 93 75 9f a7 d2 a0 c7 04 00 00 30 82 04 c3 30 82 .u........0...0.
//-- 0460 03 ab a0 03 02 01 02 02 0a 3a ab 11 de e5 2f 1b .........:..../.
//-- 0470 19 d0 56 30 0d 06 09 2a 86 48 86 f7 0d 01 01 04 ..V0...*.H......
//-- 0480 05 00 30 70 31 2b 30 29 06 03 55 04 0b 13 22 43 ..0p1+0)..U..."C
//-- 0490 6f 70 79 72 69 67 68 74 20 28 63 29 20 31 39 39 opyright (c) 199
//-- 04a0 37 20 4d 69 63 72 6f 73 6f 66 74 20 43 6f 72 70 7 Microsoft Corp
//-- 04b0 2e 31 1e 30 1c 06 03 55 04 0b 13 15 4d 69 63 72 .1.0...U....Micr
//-- 04c0 6f 73 6f 66 74 20 43 6f 72 70 6f 72 61 74 69 6f osoft Corporatio
//-- 04d0 6e 31 21 30 1f 06 03 55 04 03 13 18 4d 69 63 72 n1!0...U....Micr
//-- 04e0 6f 73 6f 66 74 20 52 6f 6f 74 20 41 75 74 68 6f osoft Root Autho
//-- 04f0 72 69 74 79 30 1e 17 0d 30 39 31 32 31 30 30 31 rity0...09121001
//-- 0500 35 35 33 35 5a 17 0d 31 36 31 30 32 33 30 38 30 5535Z..161023080
//-- 0510 30 30 30 5a 30 81 b9 31 0b 30 09 06 03 55 04 06 000Z0..1.0...U..
//-- 0520 13 02 55 53 31 13 30 11 06 03 55 04 08 13 0a 57 ..US1.0...U....W
//-- 0530 61 73 68 69 6e 67 74 6f 6e 31 10 30 0e 06 03 55 ashington1.0...U
//-- 0540 04 07 13 07 52 65 64 6d 6f 6e 64 31 1e 30 1c 06 ....Redmond1.0..
//-- 0550 03 55 04 0a 13 15 4d 69 63 72 6f 73 6f 66 74 20 .U....Microsoft
//-- 0560 43 6f 72 70 6f 72 61 74 69 6f 6e 31 2b 30 29 06 Corporation1+0).
//-- 0570 03 55 04 0b 13 22 43 6f 70 79 72 69 67 68 74 20 .U..."Copyright
//-- 0580 28 63 29 20 31 39 39 39 20 4d 69 63 72 6f 73 6f (c) 1999 Microso
//-- 0590 66 74 20 43 6f 72 70 2e 31 36 30 34 06 03 55 04 ft Corp.1604..U.
//-- 05a0 03 13 2d 4d 69 63 72 6f 73 6f 66 74 20 45 6e 66 ..-Microsoft Enf
//-- 05b0 6f 72 63 65 64 20 4c 69 63 65 6e 73 69 6e 67 20 orced Licensing
//-- 05c0 49 6e 74 65 72 6d 65 64 69 61 74 65 20 50 43 41 Intermediate PCA
//-- 05d0 30 82 01 22 30 0d 06 09 2a 86 48 86 f7 0d 01 01 0.."0...*.H.....
//-- 05e0 01 05 00 03 82 01 0f 00 30 82 01 0a 02 82 01 01 ........0.......
//-- 05f0 00 fa c9 3f 35 cb b4 42 4c 19 a8 98 e2 f4 e6 ca ...?5..BL.......
//-- 0600 c5 b2 ff e9 29 25 63 9a b7 eb b9 28 2b a7 58 1f ....)%c....(+.X.
//-- 0610 05 df d8 f8 cf 4a f1 92 47 15 c0 b5 e0 42 32 37 .....J..G....B27
//-- 0620 82 99 d6 4b 3a 5a d6 7a 25 2a 9b 13 8f 75 75 cb ...K:Z.z%*...uu.
//-- 0630 9e 52 c6 65 ab 6a 0a b5 7f 7f 20 69 a4 59 04 2c .R.e.j.... i.Y.,
//-- 0640 b7 b5 eb 7f 2c 0d 82 a8 3b 10 d1 7f a3 4e 39 e0 ....,...;....N9.
//-- 0650 28 2c 39 f3 78 d4 84 77 36 ba 68 0f e8 5d e5 52 (,9.x..w6.h..].R
//-- 0660 e1 6c e2 78 d6 d7 c6 b9 dc 7b 08 44 ad 7d 72 ee .l.x.....{.D.}r.
//-- 0670 4a f4 d6 5a a8 59 63 f4 a0 ee f3 28 55 7d 2b 78 J..Z.Yc....(U}+x
//-- 0680 68 2e 79 b6 1d e6 af 69 8a 09 ba 39 88 b4 92 65 h.y....i...9...e
//-- 0690 0d 12 17 09 ea 2a a4 b8 4a 8e 40 f3 74 de a4 74 .....*..J.@.t..t
//-- 06a0 e5 08 5a 25 cc 80 7a 76 2e ee ff 21 4e b0 65 6c ..Z%..zv...!N.el
//-- 06b0 64 50 5c ad 8f c6 59 9b 07 3e 05 f8 e5 92 cb d9 dP....Y..>......
//-- 06c0 56 1d 30 0f 72 f0 ac a8 5d 43 41 ff c9 fd 5e fa V.0.r...]CA...^.
//-- 06d0 81 cc 3b dc f0 fd 56 4c 21 7c 7f 5e ed 73 30 3a ..;...VL!|.^.s0:
//-- 06e0 3f f2 e8 93 8b d5 f3 cd 0e 27 14 49 67 94 ce b9 ?........'.Ig...
//-- 06f0 25 02 03 01 00 01 a3 82 01 13 30 82 01 0f 30 2b %.........0...0+
//-- 0700 06 03 55 1d 25 04 24 30 22 06 08 2b 06 01 05 05 ..U.%.$0"..+....
//-- 0710 07 03 03 06 0a 2b 06 01 04 01 82 37 0a 06 01 06 .....+.....7....
//-- 0720 0a 2b 06 01 04 01 82 37 0a 06 02 30 81 a2 06 03 .+.....7...0....
//-- 0730 55 1d 01 04 81 9a 30 81 97 80 10 5b d0 70 ef 69 U.....0....[.p.i
//-- 0740 72 9e 23 51 7e 14 b2 4d 8e ff cb a1 72 30 70 31 r.#Q~..M....r0p1
//-- 0750 2b 30 29 06 03 55 04 0b 13 22 43 6f 70 79 72 69 +0)..U..."Copyri
//-- 0760 67 68 74 20 28 63 29 20 31 39 39 37 20 4d 69 63 ght (c) 1997 Mic
//-- 0770 72 6f 73 6f 66 74 20 43 6f 72 70 2e 31 1e 30 1c rosoft Corp.1.0.
//-- 0780 06 03 55 04 0b 13 15 4d 69 63 72 6f 73 6f 66 74 ..U....Microsoft
//-- 0790 20 43 6f 72 70 6f 72 61 74 69 6f 6e 31 21 30 1f  Corporation1!0.
//-- 07a0 06 03 55 04 03 13 18 4d 69 63 72 6f 73 6f 66 74 ..U....Microsoft
//-- 07b0 20 52 6f 6f 74 20 41 75 74 68 6f 72 69 74 79 82  Root Authority.
//-- 07c0 0f 00 c1 00 8b 3c 3c 88 11 d1 3e f6 63 ec df 40 .....<<...>.c..@
//-- 07d0 30 0f 06 03 55 1d 13 01 01 ff 04 05 30 03 01 01 0...U.......0...
//-- 07e0 ff 30 1d 06 03 55 1d 0e 04 16 04 14 6a 97 e0 c8 .0...U......j...
//-- 07f0 9f f4 49 b4 89 24 b3 e3 d1 a8 22 86 aa d4 94 43 ..I..$...."....C
//-- 0800 30 0b 06 03 55 1d 0f 04 04 03 02 01 86 30 0d 06 0...U........0..
//-- 0810 09 2a 86 48 86 f7 0d 01 01 04 05 00 03 82 01 01 .*.H............
//-- 0820 00 5d 2b 68 a5 e2 da c7 2b 5c 77 ec ea 0e 1f e3 .]+h....+.w.....
//-- 0830 8e 41 57 60 b4 8f 3f a2 88 d2 0f 77 1a 92 9f 37 .AW`..?....w...7
//-- 0840 59 bb 15 97 dc a8 73 56 60 87 e3 3d bc b4 e1 10 Y.....sV`..=....
//-- 0850 64 2d c8 b8 d6 81 00 06 89 1f 96 41 ac 05 1a ca d-.........A....
//-- 0860 78 00 d9 db 5f b6 f9 71 87 8e 04 7b fa 78 f2 1e x..._..q...{.x..
//-- 0870 2f df 8b b3 04 fe 7a cc ef af 5e 98 da 1d ad 94 /.....z...^.....
//-- 0880 95 74 b0 d9 87 97 58 1c 4f a4 82 c7 f9 b3 ae 09 .t....X.O.......
//-- 0890 06 12 7e cb fd 22 6a 94 99 4a c3 b9 32 44 87 bc ..~.."j..J..2D..
//-- 08a0 bf f7 7c 60 6c 88 cc c0 fd b6 5c 14 19 71 31 5f ..|`l........q1_
//-- 08b0 99 d2 db a7 0c 9d c2 75 9d ba ed b1 88 6c 52 1b .......u.....lR.
//-- 08c0 42 5a 2d b0 e3 13 04 78 ff 51 d7 58 e7 18 c0 01 BZ-....x.Q.X....
//-- 08d0 8c f8 43 12 a8 9d 8c b5 81 f3 70 a0 ad 19 c6 e4 ..C.......p.....
//-- 08e0 e4 44 e5 55 05 50 d3 88 40 65 aa d0 02 0e 00 4d .D.U.P..@e.....M
//-- 08f0 84 bb 6a 39 0c 6d 88 f1 1e d6 95 72 34 70 9b c5 ..j9.m.....r4p..
//-- 0900 a6 6f 66 bc 94 14 df 34 ff e4 63 3a 93 31 13 de .of....4..c:.1..
//-- 0910 a0 2c 7a 73 68 7c 0e 44 98 a0 a8 37 3e 2e 3a 5b .,zsh|.D...7>.:[
//-- 0920 22 76 09 00 00 30 82 09 72 30 82 08 5a a0 03 02 "v...0..r0..Z...
//-- 0930 01 02 02 0a 61 1a 02 b7 00 02 00 00 00 12 30 0d ....a.........0.
//-- 0940 06 09 2a 86 48 86 f7 0d 01 01 04 05 00 30 81 b9 ..*.H........0..
//-- 0950 31 0b 30 09 06 03 55 04 06 13 02 55 53 31 13 30 1.0...U....US1.0
//-- 0960 11 06 03 55 04 08 13 0a 57 61 73 68 69 6e 67 74 ...U....Washingt
//-- 0970 6f 6e 31 10 30 0e 06 03 55 04 07 13 07 52 65 64 on1.0...U....Red
//-- 0980 6d 6f 6e 64 31 1e 30 1c 06 03 55 04 0a 13 15 4d mond1.0...U....M
//-- 0990 69 63 72 6f 73 6f 66 74 20 43 6f 72 70 6f 72 61 icrosoft Corpora
//-- 09a0 74 69 6f 6e 31 2b 30 29 06 03 55 04 0b 13 22 43 tion1+0)..U..."C
//-- 09b0 6f 70 79 72 69 67 68 74 20 28 63 29 20 31 39 39 opyright (c) 199
//-- 09c0 39 20 4d 69 63 72 6f 73 6f 66 74 20 43 6f 72 70 9 Microsoft Corp
//-- 09d0 2e 31 36 30 34 06 03 55 04 03 13 2d 4d 69 63 72 .1604..U...-Micr
//-- 09e0 6f 73 6f 66 74 20 45 6e 66 6f 72 63 65 64 20 4c osoft Enforced L
//-- 09f0 69 63 65 6e 73 69 6e 67 20 49 6e 74 65 72 6d 65 icensing Interme
//-- 0a00 64 69 61 74 65 20 50 43 41 30 1e 17 0d 30 39 31 diate PCA0...091
//-- 0a10 32 31 31 30 30 30 33 35 38 5a 17 0d 31 36 31 30 211000358Z..1610
//-- 0a20 32 33 30 38 30 30 30 30 5a 30 81 c2 31 0b 30 09 23080000Z0..1.0.
//-- 0a30 06 03 55 04 06 13 02 55 53 31 13 30 11 06 03 55 ..U....US1.0...U
//-- 0a40 04 08 13 0a 57 61 73 68 69 6e 67 74 6f 6e 31 10 ....Washington1.
//-- 0a50 30 0e 06 03 55 04 07 13 07 52 65 64 6d 6f 6e 64 0...U....Redmond
//-- 0a60 31 1e 30 1c 06 03 55 04 0a 13 15 4d 69 63 72 6f 1.0...U....Micro
//-- 0a70 73 6f 66 74 20 43 6f 72 70 6f 72 61 74 69 6f 6e soft Corporation
//-- 0a80 31 2b 30 29 06 03 55 04 0b 13 22 43 6f 70 79 72 1+0)..U..."Copyr
//-- 0a90 69 67 68 74 20 28 63 29 20 32 30 30 33 20 4d 69 ight (c) 2003 Mi
//-- 0aa0 63 72 6f 73 6f 66 74 20 43 6f 72 70 2e 31 3f 30 crosoft Corp.1?0
//-- 0ab0 3d 06 03 55 04 03 13 36 4d 69 63 72 6f 73 6f 66 =..U...6Microsof
//-- 0ac0 74 20 45 6e 66 6f 72 63 65 64 20 4c 69 63 65 6e t Enforced Licen
//-- 0ad0 73 69 6e 67 20 52 65 67 69 73 74 72 61 74 69 6f sing Registratio
//-- 0ae0 6e 20 41 75 74 68 6f 72 69 74 79 20 43 41 30 82 n Authority CA0.
//-- 0af0 01 22 30 0d 06 09 2a 86 48 86 f7 0d 01 01 01 05 ."0...*.H.......
//-- 0b00 00 03 82 01 0f 00 30 82 01 0a 02 82 01 01 00 8e ......0.........
//-- 0b10 98 07 ed 46 50 30 aa 8a 95 5e 36 7f bc 71 30 a1 ...FP0...^6..q0.
//-- 0b20 1d 49 cf e7 96 ff 2f 9a 09 16 12 f0 98 31 55 45 .I..../......1UE
//-- 0b30 52 40 63 7d 57 67 46 a2 2b 08 98 6d 9b c6 69 25 R@c}WgF.+..m..i%
//-- 0b40 40 87 49 e7 01 37 84 00 1d 69 9d 85 2f e1 a0 2c @.I..7...i../..,
//-- 0b50 27 83 4c 75 60 8b 2c eb f9 90 8e 5e 4a 8f fd d3 '.Lu`.,....^J...
//-- 0b60 5b 8c 89 c8 0f f8 cf 2e 9f 3c 8a 3d 41 cc b6 84 [........<.=A...
//-- 0b70 0c 9c 73 97 46 dd 52 26 12 a5 44 8d df 0a 50 1f ..s.F.R&..D...P.
//-- 0b80 4a 79 dc e3 19 3c ef ed 82 c9 89 14 91 fd 99 69 Jy...<.........i
//-- 0b90 a4 f2 8a a6 c8 8e bd 38 3b 80 30 8a 59 c8 a0 ab .......8;.0.Y...
//-- 0ba0 de 71 44 1b 24 f9 b9 a1 8f 19 9d fd 19 b4 69 16 .qD.$.........i.
//-- 0bb0 17 a2 23 31 a7 11 12 65 cd c0 9d 78 5d 42 e5 95 ..#1...e...x]B..
//-- 0bc0 8e 13 2f ac f8 00 87 6e 96 ef 73 d4 0f 7e 3c 9f ../....n..s..~<.
//-- 0bd0 81 47 d0 1f 8f 79 1d 3c 3f cb ae 34 22 d6 cd fc .G...y.<?..4"...
//-- 0be0 21 80 35 11 0d a9 90 cc 55 b4 65 fc 2d 37 7d 80 !.5.....U.e.-7}.
//-- 0bf0 7a 97 ee 5b 4a c5 3e 8b 03 aa ae 4d 22 37 66 70 z..[J.>....M"7fp
//-- 0c00 84 1c 69 c5 d7 97 9a 8f 1e 3a b2 24 84 8f ef 02 ..i......:.$....
//-- 0c10 03 01 00 01 a3 82 05 6f 30 82 05 6b 30 0f 06 03 .......o0..k0...
//-- 0c20 55 1d 13 01 01 ff 04 05 30 03 01 01 ff 30 1d 06 U.......0....0..
//-- 0c30 03 55 1d 0e 04 16 04 14 b4 a1 d8 de fb 0e c4 cb .U..............
//-- 0c40 9d 9f 06 cf 36 0d 91 1a f8 9f 5b e3 30 0b 06 03 ....6.....[.0...
//-- 0c50 55 1d 0f 04 04 03 02 01 c6 30 12 06 09 2b 06 01 U........0...+..
//-- 0c60 04 01 82 37 15 01 04 05 02 03 01 00 01 30 23 06 ...7.........0#.
//-- 0c70 09 2b 06 01 04 01 82 37 15 02 04 16 04 14 9b 90 .+.....7........
//-- 0c80 78 38 67 95 29 80 6b 2f e3 54 96 1a 70 5f f1 c3 x8g.).k/.T..p_..
//-- 0c90 11 ad 30 19 06 09 2b 06 01 04 01 82 37 14 02 04 ..0...+.....7...
//-- 0ca0 0c 1e 0a 00 53 00 75 00 62 00 43 00 41 30 1f 06 ....S.u.b.C.A0..
//-- 0cb0 03 55 1d 23 04 18 30 16 80 14 6a 97 e0 c8 9f f4 .U.#..0...j.....
//-- 0cc0 49 b4 89 24 b3 e3 d1 a8 22 86 aa d4 94 43 30 54 I..$...."....C0T
//-- 0cd0 06 03 55 1d 1f 04 4d 30 4b 30 49 a0 47 a0 45 86 ..U...M0K0I.G.E.
//-- 0ce0 43 68 74 74 70 3a 2f 2f 63 72 6c 2e 6d 69 63 72 Chttp://crl.micr
//-- 0cf0 6f 73 6f 66 74 2e 63 6f 6d 2f 70 6b 69 2f 63 72 osoft.com/pki/cr
//-- 0d00 6c 2f 70 72 6f 64 75 63 74 73 2f 4d 69 63 45 6e l/products/MicEn
//-- 0d10 66 4c 69 63 50 43 41 5f 31 32 2d 31 30 2d 30 39 fLicPCA_12-10-09
//-- 0d20 2e 63 72 6c 30 1f 06 03 55 1d 25 04 18 30 16 06 .crl0...U.%..0..
//-- 0d30 08 2b 06 01 05 05 07 03 03 06 0a 2b 06 01 04 01 .+.........+....
//-- 0d40 82 37 0a 06 02 30 82 04 3e 06 0a 2b 06 01 04 01 .7...0..>..+....
//-- 0d50 82 37 02 01 0a 01 01 ff 04 82 04 2b 30 82 04 1f .7.........+0...
//-- 0d60 a0 29 80 27 68 74 74 70 73 3a 2f 2f 77 77 77 2e .).'https://www.
//-- 0d70 6d 69 63 72 6f 73 6f 66 74 2e 63 6f 6d 2f 72 65 microsoft.com/re
//-- 0d80 70 6f 73 69 74 6f 72 79 2f 43 50 53 a1 82 03 b8 pository/CPS....
//-- 0d90 81 82 03 b4 54 68 69 73 20 63 65 72 74 69 66 69 ....This certifi
//-- 0da0 63 61 74 65 20 69 6e 63 6f 72 70 6f 72 61 74 65 cate incorporate
//-- 0db0 73 20 62 79 20 72 65 66 65 72 65 6e 63 65 2c 20 s by reference,
//-- 0dc0 61 6e 64 20 69 74 73 20 75 73 65 20 69 73 20 73 and its use is s
//-- 0dd0 74 72 69 63 74 6c 79 0a 73 75 62 6a 65 63 74 20 trictly.subject
//-- 0de0 74 6f 2c 20 74 68 65 20 4d 69 63 72 6f 73 6f 66 to, the Microsof
//-- 0df0 74 20 43 65 72 74 69 66 69 63 61 74 69 6f 6e 20 t Certification
//-- 0e00 50 72 61 63 74 69 63 65 20 53 74 61 74 65 6d 65 Practice Stateme
//-- 0e10 6e 74 20 28 43 50 53 29 0a 76 65 72 73 69 6f 6e nt (CPS).version
//-- 0e20 20 32 2e 30 2c 20 61 76 61 69 6c 61 62 6c 65 20  2.0, available
//-- 0e30 69 6e 20 74 68 65 20 4d 69 63 72 6f 73 6f 66 74 in the Microsoft
//-- 0e40 20 72 65 70 6f 73 69 74 6f 72 79 20 61 74 3a 0a  repository at:.
//-- 0e50 68 74 74 70 73 3a 2f 2f 77 77 77 2e 6d 69 63 72 https://www.micr
//-- 0e60 6f 73 6f 66 74 2e 63 6f 6d 3b 20 62 79 20 45 2d osoft.com; by E-
//-- 0e70 6d 61 69 6c 20 61 74 20 43 50 53 2d 72 65 71 75 mail at CPS-requ
//-- 0e80 65 73 74 73 40 6d 69 63 72 6f 73 6f 66 74 2e 63 ests@microsoft.c
//-- 0e90 6f 6d 3b 20 6f 72 0a 62 79 20 6d 61 69 6c 20 61 om; or.by mail a
//-- 0ea0 74 20 4d 69 63 72 6f 73 6f 66 74 20 43 6f 72 70 t Microsoft Corp
//-- 0eb0 2c 20 64 65 70 74 2e 20 43 50 53 2c 31 20 4d 69 , dept. CPS,1 Mi
//-- 0ec0 63 72 6f 73 6f 66 74 20 57 61 79 2c 52 65 64 6d crosoft Way,Redm
//-- 0ed0 6f 6e 64 2c 20 57 41 20 39 38 30 35 32 0a 55 53 ond, WA 98052.US
//-- 0ee0 41 20 43 6f 70 79 72 69 67 68 74 20 28 63 29 31 A Copyright (c)1
//-- 0ef0 39 39 39 20 4d 69 63 72 6f 73 6f 66 74 20 43 6f 999 Microsoft Co
//-- 0f00 72 70 2e 20 20 41 6c 6c 20 52 69 67 68 74 73 20 rp.  All Rights
//-- 0f10 52 65 73 65 72 76 65 64 2e 20 43 45 52 54 41 49 Reserved. CERTAI
//-- 0f20 4e 0a 57 41 52 52 41 4e 54 49 45 53 20 44 49 53 N.WARRANTIES DIS
//-- 0f30 43 4c 41 49 4d 45 44 20 41 4e 44 20 4c 49 41 42 CLAIMED AND LIAB
//-- 0f40 49 4c 49 54 59 20 4c 49 4d 49 54 45 44 2e 0a 0a ILITY LIMITED...
//-- 0f50 57 41 52 4e 49 4e 47 3a 20 54 48 45 20 55 53 45 WARNING: THE USE
//-- 0f60 20 4f 46 20 54 48 49 53 20 43 45 52 54 49 46 49  OF THIS CERTIFI
//-- 0f70 43 41 54 45 20 49 53 20 53 54 52 49 43 54 4c 59 CATE IS STRICTLY
//-- 0f80 20 53 55 42 4a 45 43 54 20 54 4f 20 54 48 45 0a  SUBJECT TO THE.
//-- 0f90 56 45 52 49 53 49 47 4e 20 43 45 52 54 49 46 49 VERISIGN CERTIFI
//-- 0fa0 43 41 54 49 4f 4e 20 50 52 41 43 54 49 43 45 20 CATION PRACTICE
//-- 0fb0 53 54 41 54 45 4d 45 4e 54 2e 20 20 54 48 45 20 STATEMENT.  THE
//-- 0fc0 49 53 53 55 49 4e 47 20 41 55 54 48 4f 52 49 54 ISSUING AUTHORIT
//-- 0fd0 59 0a 44 49 53 43 4c 41 49 4d 53 20 43 45 52 54 Y.DISCLAIMS CERT
//-- 0fe0 41 49 4e 20 49 4d 50 4c 49 45 44 20 41 4e 44 20 AIN IMPLIED AND
//-- 0ff0 45 58 50 52 45 53 53 20 57 41 52 52 41 4e 54 49 EXPRESS WARRANTI
//-- 1000 45 53 2c 20 49 4e 43 4c 55 44 49 4e 47 20 57 41 ES, INCLUDING WA
//-- 1010 52 52 41 4e 54 49 45 53 0a 4f 46 20 4d 45 52 43 RRANTIES.OF MERC
//-- 1020 48 41 4e 54 41 42 49 4c 49 54 59 20 4f 52 20 46 HANTABILITY OR F
//-- 1030 49 54 4e 45 53 53 20 46 4f 52 20 41 20 50 41 52 ITNESS FOR A PAR
//-- 1040 54 49 43 55 4c 41 52 20 50 55 52 50 4f 53 45 2c TICULAR PURPOSE,
//-- 1050 20 41 4e 44 20 57 49 4c 4c 20 4e 4f 54 0a 42 45  AND WILL NOT.BE
//-- 1060 20 4c 49 41 42 4c 45 20 46 4f 52 20 43 4f 4e 53  LIABLE FOR CONS
//-- 1070 45 51 55 45 4e 54 49 41 4c 2c 20 50 55 4e 49 54 EQUENTIAL, PUNIT
//-- 1080 49 56 45 2c 20 41 4e 44 20 43 45 52 54 41 49 4e IVE, AND CERTAIN
//-- 1090 20 4f 54 48 45 52 20 44 41 4d 41 47 45 53 2e 20  OTHER DAMAGES.
//-- 10a0 53 45 45 0a 54 48 45 20 43 50 53 20 46 4f 52 20 SEE.THE CPS FOR
//-- 10b0 44 45 54 41 49 4c 53 2e 0a 0a 43 6f 6e 74 65 6e DETAILS...Conten
//-- 10c0 74 73 20 6f 66 20 74 68 65 20 4d 69 63 72 6f 73 ts of the Micros
//-- 10d0 6f 66 74 20 72 65 67 69 73 74 65 72 65 64 20 6e oft registered n
//-- 10e0 6f 6e 76 65 72 69 66 69 65 64 53 75 62 6a 65 63 onverifiedSubjec
//-- 10f0 74 41 74 74 72 69 62 75 74 65 73 0a 65 78 74 65 tAttributes.exte
//-- 1100 6e 73 69 6f 6e 20 76 61 6c 75 65 20 73 68 61 6c nsion value shal
//-- 1110 6c 20 6e 6f 74 20 62 65 20 63 6f 6e 73 69 64 65 l not be conside
//-- 1120 72 65 64 20 61 73 20 61 63 63 75 72 61 74 65 20 red as accurate
//-- 1130 69 6e 66 6f 72 6d 61 74 69 6f 6e 0a 76 61 6c 69 information.vali
//-- 1140 64 61 74 65 64 20 62 79 20 74 68 65 20 49 41 2e dated by the IA.
//-- 1150 0a a3 36 80 34 68 74 74 70 73 3a 2f 2f 77 77 77 ..6.4https://www
//-- 1160 2e 6d 69 63 72 6f 73 6f 66 74 2e 63 6f 6d 2f 72 .microsoft.com/r
//-- 1170 65 70 6f 73 69 74 6f 72 79 2f 6d 73 63 70 73 6c epository/mscpsl
//-- 1180 6f 67 6f 2e 67 69 66 30 0d 06 09 2a 86 48 86 f7 ogo.gif0...*.H..
//-- 1190 0d 01 01 04 05 00 03 82 01 01 00 24 ab ed f7 72 ...........$...r
//-- 11a0 44 44 98 71 f6 d1 b9 b5 69 e0 ef 1c b0 4c 04 98 DD.q....i....L..
//-- 11b0 0f bf 4c a9 74 47 b0 84 a1 48 e2 81 b3 ea e1 c9 ..L.tG...H......
//-- 11c0 53 92 53 11 c8 45 ba 88 76 68 cd dc be f3 a0 65 S.S..E..vh.....e
//-- 11d0 80 76 d7 93 03 69 8d c7 bc 7a ae 89 7c df 12 10 .v...i...z..|...
//-- 11e0 0a a6 29 a6 d4 e5 9b 55 ab ca ec 4b d9 c1 28 37 ..)....U...K..(7
//-- 11f0 d0 d6 71 38 6d 5e 75 fd 66 ab 2a c0 b9 24 6f 9e ..q8m^u.f.*..$o.
//-- 1200 42 33 0f 71 b4 6e a6 f7 ba 23 1a 74 ed cd b1 ae B3.q.n...#.t....
//-- 1210 0a 32 a8 5c 26 16 fa 31 76 23 e8 a7 24 80 f1 de .2..&..1v#..$...
//-- 1220 45 b5 42 bd f1 58 08 8f e2 f2 70 86 2e 13 83 24 E.B..X....p....$
//-- 1230 de 50 88 88 c0 23 32 59 74 fa 7a 5f 73 d7 63 bd .P...#2Yt.z_s.c.
//-- 1240 58 9d c0 68 b0 53 21 71 50 45 b8 27 cf 3c e5 64 X..h.S!qPE.'.<.d
//-- 1250 fb 7c 13 8b c1 01 3e 90 d9 43 f7 3e cc 19 16 b3 .|....>..C.>....
//-- 1260 b6 16 8f 27 7a f9 46 ed 8a da e7 c5 91 c2 c8 2a ...'z.F........*
//-- 1270 08 21 5a b8 7a 88 4e a6 2a a5 f7 ed 20 01 14 48 .!Z.z.N.*... ..H
//-- 1280 56 df 57 7d 6f bf 95 75 18 29 17 19 84 a3 13 61 V.W}o..u.).....a
//-- 1290 54 82 c3 55 58 3d 83 a3 90 75 aa 70 05 00 00 30 T..UX=...u.p...0
//-- 12a0 82 05 6c 30 82 04 54 a0 03 02 01 02 02 0a 61 03 ..l0..T.......a.
//-- 12b0 73 c5 00 01 00 00 00 1a 30 0d 06 09 2a 86 48 86 s.......0...*.H.
//-- 12c0 f7 0d 01 01 04 05 00 30 81 c2 31 0b 30 09 06 03 .......0..1.0...
//-- 12d0 55 04 06 13 02 55 53 31 13 30 11 06 03 55 04 08 U....US1.0...U..
//-- 12e0 13 0a 57 61 73 68 69 6e 67 74 6f 6e 31 10 30 0e ..Washington1.0.
//-- 12f0 06 03 55 04 07 13 07 52 65 64 6d 6f 6e 64 31 1e ..U....Redmond1.
//-- 1300 30 1c 06 03 55 04 0a 13 15 4d 69 63 72 6f 73 6f 0...U....Microso
//-- 1310 66 74 20 43 6f 72 70 6f 72 61 74 69 6f 6e 31 2b ft Corporation1+
//-- 1320 30 29 06 03 55 04 0b 13 22 43 6f 70 79 72 69 67 0)..U..."Copyrig
//-- 1330 68 74 20 28 63 29 20 32 30 30 33 20 4d 69 63 72 ht (c) 2003 Micr
//-- 1340 6f 73 6f 66 74 20 43 6f 72 70 2e 31 3f 30 3d 06 osoft Corp.1?0=.
//-- 1350 03 55 04 03 13 36 4d 69 63 72 6f 73 6f 66 74 20 .U...6Microsoft
//-- 1360 45 6e 66 6f 72 63 65 64 20 4c 69 63 65 6e 73 69 Enforced Licensi
//-- 1370 6e 67 20 52 65 67 69 73 74 72 61 74 69 6f 6e 20 ng Registration
//-- 1380 41 75 74 68 6f 72 69 74 79 20 43 41 30 1e 17 0d Authority CA0...
//-- 1390 31 30 30 32 31 39 32 31 34 38 33 39 5a 17 0d 31 100219214839Z..1
//-- 13a0 32 30 32 31 39 32 31 34 38 33 39 5a 30 81 80 31 20219214839Z0..1
//-- 13b0 13 30 11 06 0a 09 92 26 89 93 f2 2c 64 01 19 16 .0.....&...,d...
//-- 13c0 03 63 6f 6d 31 19 30 17 06 0a 09 92 26 89 93 f2 .com1.0.....&...
//-- 13d0 2c 64 01 19 16 09 6d 69 63 72 6f 73 6f 66 74 31 ,d....microsoft1
//-- 13e0 18 30 16 06 0a 09 92 26 89 93 f2 2c 64 01 19 16 .0.....&...,d...
//-- 13f0 08 65 78 74 72 61 6e 65 74 31 18 30 16 06 0a 09 .extranet1.0....
//-- 1400 92 26 89 93 f2 2c 64 01 19 16 08 70 61 72 74 6e .&...,d....partn
//-- 1410 65 72 73 31 1a 30 18 06 03 55 04 03 13 11 4d 69 ers1.0...U....Mi
//-- 1420 63 72 6f 73 6f 66 74 20 4c 53 52 41 20 50 41 30 crosoft LSRA PA0
//-- 1430 82 01 22 30 0d 06 09 2a 86 48 86 f7 0d 01 01 01 .."0...*.H......
//-- 1440 05 00 03 82 01 0f 00 30 82 01 0a 02 82 01 01 00 .......0........
//-- 1450 d7 27 32 63 50 bc ca 67 6c 44 c2 08 0a fb aa e8 .'2cP..glD......
//-- 1460 25 ff e5 a8 f3 32 53 0b 53 af b7 29 cc 2c 91 34 %....2S.S..).,.4
//-- 1470 01 f1 52 59 55 73 df 56 2c 25 ae 41 d1 2a de 09 ..RYUs.V,%.A.*..
//-- 1480 d1 90 41 bf 2c c7 6d e6 1b 0d 5c 1f c4 62 06 1f ..A.,.m......b..
//-- 1490 72 6a fc a6 d7 19 57 c1 06 42 35 50 78 ec 6d a2 rj....W..B5Px.m.
//-- 14a0 13 b0 90 9d 0c 9d d8 5f b7 bf f0 cc b1 a9 b8 c1 ......._........
//-- 14b0 f7 b9 a9 e3 14 c6 9a bb 6a 8c c8 6f bb c4 e6 3b ........j..o...;
//-- 14c0 de c3 16 25 cf 76 d4 7c e5 88 80 e9 4e 27 6d b9 ...%.v.|....N'm.
//-- 14d0 c6 fb a6 6e b0 65 15 e3 4d b3 1b e9 ac fa 87 37 ...n.e..M......7
//-- 14e0 8a e9 81 d1 4e 49 26 b8 26 72 3d bf cc cb d3 9c ....NI&.&r=.....
//-- 14f0 55 cf a9 2b 4b 22 78 44 85 0b 04 ee 09 84 bb 65 U..+K"xD.......e
//-- 1500 c4 31 8a 83 3b fa 53 98 a1 fd a1 f4 4c 71 4c e9 .1..;.S.....LqL.
//-- 1510 15 87 2b 13 ef dc d6 52 84 ed 1c e5 35 4a 22 2c ..+....R....5J",
//-- 1520 14 84 6b f2 8a ef 9b f6 d3 75 ce 6d 0e 81 1f 6d ..k......u.m...m
//-- 1530 df 22 ee b3 ec 01 36 d8 ff 68 ff 4e ba 75 d5 4e ."....6..h.N.u.N
//-- 1540 18 e6 b4 00 7e b9 a3 ee 31 2e 4e a0 0c e5 21 eb ....~...1.N...!.
//-- 1550 02 03 01 00 01 a3 82 01 a2 30 82 01 9e 30 12 06 .........0...0..
//-- 1560 03 55 1d 13 01 01 ff 04 08 30 06 01 01 ff 02 01 .U.......0......
//-- 1570 00 30 1d 06 03 55 1d 0e 04 16 04 14 75 e8 03 58 .0...U......u..X
//-- 1580 5d fb 65 e4 d9 a6 ac 17 b6 03 7e 47 ad 2e 81 af ].e.......~G....
//-- 1590 30 0b 06 03 55 1d 0f 04 04 03 02 01 86 30 10 06 0...U........0..
//-- 15a0 09 2b 06 01 04 01 82 37 15 01 04 03 02 01 00 30 .+.....7.......0
//-- 15b0 19 06 09 2b 06 01 04 01 82 37 14 02 04 0c 1e 0a ...+.....7......
//-- 15c0 00 53 00 75 00 62 00 43 00 41 30 1f 06 03 55 1d .S.u.b.C.A0...U.
//-- 15d0 23 04 18 30 16 80 14 b4 a1 d8 de fb 0e c4 cb 9d #..0............
//-- 15e0 9f 06 cf 36 0d 91 1a f8 9f 5b e3 30 81 ac 06 03 ...6.....[.0....
//-- 15f0 55 1d 1f 04 81 a4 30 81 a1 30 81 9e a0 81 9b a0 U.....0..0......
//-- 1600 81 98 86 4a 68 74 74 70 3a 2f 2f 63 72 6c 2e 6d ...Jhttp://crl.m
//-- 1610 69 63 72 6f 73 6f 66 74 2e 63 6f 6d 2f 70 6b 69 icrosoft.com/pki
//-- 1620 2f 63 72 6c 2f 70 72 6f 64 75 63 74 73 2f 4d 69 /crl/products/Mi
//-- 1630 63 45 6e 66 4c 69 63 52 65 67 41 75 74 43 41 5f cEnfLicRegAutCA_
//-- 1640 32 30 30 39 2d 31 32 2d 31 30 2e 63 72 6c 86 4a 2009-12-10.crl.J
//-- 1650 68 74 74 70 3a 2f 2f 77 77 77 2e 6d 69 63 72 6f http://www.micro
//-- 1660 73 6f 66 74 2e 63 6f 6d 2f 70 6b 69 2f 63 72 6c soft.com/pki/crl
//-- 1670 2f 70 72 6f 64 75 63 74 73 2f 4d 69 63 45 6e 66 /products/MicEnf
//-- 1680 4c 69 63 52 65 67 41 75 74 43 41 5f 32 30 30 39 LicRegAutCA_2009
//-- 1690 2d 31 32 2d 31 30 2e 63 72 6c 30 5f 06 08 2b 06 -12-10.crl0_..+.
//-- 16a0 01 05 05 07 01 01 04 53 30 51 30 4f 06 08 2b 06 .......S0Q0O..+.
//-- 16b0 01 05 05 07 30 02 86 43 68 74 74 70 3a 2f 2f 77 ....0..Chttp://w
//-- 16c0 77 77 2e 6d 69 63 72 6f 73 6f 66 74 2e 63 6f 6d ww.microsoft.com
//-- 16d0 2f 70 6b 69 2f 63 65 72 74 73 2f 4d 69 63 45 6e /pki/certs/MicEn
//-- 16e0 66 4c 69 63 52 65 67 41 75 74 43 41 5f 32 30 30 fLicRegAutCA_200
//-- 16f0 39 2d 31 32 2d 31 30 2e 63 72 74 30 0d 06 09 2a 9-12-10.crt0...*
//-- 1700 86 48 86 f7 0d 01 01 04 05 00 03 82 01 01 00 5c .H..............
//-- 1710 b5 59 bb 13 8c dc 55 00 48 24 53 8d fe 09 69 eb .Y....U.H$S...i.
//-- 1720 8e 5e f9 79 6d 92 33 7a f2 29 7f 61 1d c7 fe 4c .^.ym.3z.).a...L
//-- 1730 f0 1b 5a ad ff 6c 36 bc 20 0a 03 31 6a 6e a0 ac ..Z..l6. ..1jn..
//-- 1740 6b 27 c8 99 9c 5d 29 80 a5 c0 61 42 2f b5 0a f3 k'...])...aB/...
//-- 1750 2e 69 b3 6f 3e 64 e1 33 5b 03 7b f1 b7 c9 24 a0 .i.o>d.3[.{...$.
//-- 1760 40 91 29 22 07 52 1b 52 39 b7 49 c8 16 f9 e2 e4 @.)".R.R9.I.....
//-- 1770 54 a7 67 47 64 86 fc c6 cf 32 b9 91 49 30 66 0e T.gGd....2..I0f.
//-- 1780 9f a6 d7 6c e0 48 7e 11 65 42 48 fb 0e 09 09 3a ...l.H~.eBH....:
//-- 1790 aa 48 e6 ee 5c 0c 51 40 58 19 8b 4c 26 92 ee c8 .H....Q@X..L&...
//-- 17a0 55 93 40 20 91 d4 dc 33 dd d2 e6 1c 12 d6 72 bb U.@ ...3......r.
//-- 17b0 c0 ad 53 2f f8 99 43 11 4a 6c dc a1 f4 0c 5a 21 ..S/..C.Jl....Z!
//-- 17c0 b5 05 ea ac e8 50 1f 29 04 c9 81 c7 8e 95 2c 7c .....P.)......,|
//-- 17d0 72 4f 78 e9 c5 4c c4 8e c8 db ee 09 10 7b 5b 38 rOx..L.......{[8
//-- 17e0 c9 b3 b9 18 ad 87 f6 1b 98 25 da 1a 56 61 76 c9 .........%..Vav.
//-- 17f0 12 7c 98 1a 06 f0 a0 86 38 6a 25 0f 5d b9 1f 7f .|......8j%.]...
//-- 1800 c0 85 6a aa 69 fb 23 91 ca 41 8a 0c 19 44 5c 9d ..j.i.#..A...D..
//-- 1810 05 00 00 30 82 05 99 30 82 04 81 a0 03 02 01 02 ...0...0........
//-- 1820 02 0a 1b 16 4d 75 00 00 00 08 6e 9e 30 0d 06 09 ....Mu....n.0...
//-- 1830 2a 86 48 86 f7 0d 01 01 04 05 00 30 81 80 31 13 *.H........0..1.
//-- 1840 30 11 06 0a 09 92 26 89 93 f2 2c 64 01 19 16 03 0.....&...,d....
//-- 1850 63 6f 6d 31 19 30 17 06 0a 09 92 26 89 93 f2 2c com1.0.....&...,
//-- 1860 64 01 19 16 09 6d 69 63 72 6f 73 6f 66 74 31 18 d....microsoft1.
//-- 1870 30 16 06 0a 09 92 26 89 93 f2 2c 64 01 19 16 08 0.....&...,d....
//-- 1880 65 78 74 72 61 6e 65 74 31 18 30 16 06 0a 09 92 extranet1.0.....
//-- 1890 26 89 93 f2 2c 64 01 19 16 08 70 61 72 74 6e 65 &...,d....partne
//-- 18a0 72 73 31 1a 30 18 06 03 55 04 03 13 11 4d 69 63 rs1.0...U....Mic
//-- 18b0 72 6f 73 6f 66 74 20 4c 53 52 41 20 50 41 30 1e rosoft LSRA PA0.
//-- 18c0 17 0d 31 31 31 31 32 32 31 35 34 32 34 38 5a 17 ..111122154248Z.
//-- 18d0 0d 31 32 30 32 31 39 32 31 34 38 33 39 5a 30 1f .120219214839Z0.
//-- 18e0 31 1d 30 1b 06 03 55 04 03 13 14 54 65 72 6d 69 1.0...U....Termi
//-- 18f0 6e 61 6c 20 53 65 72 76 69 63 65 73 20 4c 53 30 nal Services LS0
//-- 1900 82 01 22 30 0d 06 09 2a 86 48 86 f7 0d 01 01 01 .."0...*.H......
//-- 1910 05 00 03 82 01 0f 00 30 82 01 0a 02 82 01 01 00 .......0........
//-- 1920 b5 8d 97 59 ce 02 1c 8d f8 8f 6f af 8c 27 57 17 ...Y......o..'W.
//-- 1930 18 7a 85 41 74 d1 62 0f df ea 3f 6e a3 82 0e 9e .z.At.b...?n....
//-- 1940 c5 da aa 52 9f 60 65 28 9b 86 d7 bb 46 3b 37 01 ...R.`e(....F;7.
//-- 1950 50 52 95 b5 e9 bf d8 0c 1a 51 e2 91 ea 28 a6 38 PR.......Q...(.8
//-- 1960 2a 5f cb b0 dc 82 ed 81 27 5f b8 15 6a a5 7d d9 *_......'_..j.}.
//-- 1970 f5 b5 c0 d4 da 7e 3a 8e 3e dd 12 43 38 5b 34 bd .....~:.>..C8[4.
//-- 1980 d6 2c c0 4f 4b 65 15 40 20 7d 50 45 9d f9 7c 92 .,.OKe.@ }PE..|.
//-- 1990 1e e9 21 47 f0 0b a9 c2 2f d0 30 3e a4 2c e6 7f ..!G..../.0>.,..
//-- 19a0 32 36 b7 81 fa 53 89 30 d2 36 b2 54 df 71 3b 9c 26...S.0.6.T.q;.
//-- 19b0 11 e9 87 11 df d5 30 7c 81 63 d1 17 3b c7 1f b2 ......0|.c..;...
//-- 19c0 6b e5 3f 7a 53 5d 15 3c 45 6d c3 0c b1 26 fe 54 k.?zS].<Em...&.T
//-- 19d0 61 94 31 49 28 ce c0 29 61 37 4c fb a3 ca 99 e3 a.1I(..)a7L.....
//-- 19e0 af 33 03 59 3a 33 4a 8e 82 24 9e 51 22 a5 30 09 .3.Y:3J..$.Q".0.
//-- 19f0 1a 3c 3f 91 eb 54 d9 59 e7 a6 ef 5c 2b 40 03 d0 .<?..T.Y....+@..
//-- 1a00 c2 31 d0 f2 8b 4b f3 67 90 4b 9d 7c d7 0e 1f d2 .1...K.g.K.|....
//-- 1a10 d1 fa 3c 31 98 64 d1 7a 40 ee 05 27 1b e0 31 85 ..<1.d.z@..'..1.
//-- 1a20 02 03 01 00 01 a3 82 02 73 30 82 02 6f 30 1d 06 ........s0..o0..
//-- 1a30 03 55 1d 0e 04 16 04 14 a3 1c f6 a5 1c 68 e6 46 .U...........h.F
//-- 1a40 b2 02 89 2f 43 f5 3f b2 82 3e 31 50 30 1f 06 03 .../C.?..>1P0...
//-- 1a50 55 1d 23 04 18 30 16 80 14 75 e8 03 58 5d fb 65 U.#..0...u..X].e
//-- 1a60 e4 d9 a6 ac 17 b6 03 7e 47 ad 2e 81 af 30 81 ca .......~G....0..
//-- 1a70 06 03 55 1d 1f 04 81 c2 30 81 bf 30 81 bc a0 81 ..U.....0..0....
//-- 1a80 b9 a0 81 b6 86 5a 68 74 74 70 3a 2f 2f 74 6b 35 .....Zhttp://tk5
//-- 1a90 70 61 78 70 72 64 73 72 76 30 39 2e 70 61 72 74 paxprdsrv09.part
//-- 1aa0 6e 65 72 73 2e 65 78 74 72 61 6e 65 74 2e 6d 69 ners.extranet.mi
//-- 1ab0 63 72 6f 73 6f 66 74 2e 63 6f 6d 2f 43 65 72 74 crosoft.com/Cert
//-- 1ac0 45 6e 72 6f 6c 6c 2f 4d 69 63 72 6f 73 6f 66 74 Enroll/Microsoft
//-- 1ad0 25 32 30 4c 53 52 41 25 32 30 50 41 2e 63 72 6c %20LSRA%20PA.crl
//-- 1ae0 86 58 66 69 6c 65 3a 2f 2f 5c 5c 54 4b 35 50 41 .Xfile://..TK5PA
//-- 1af0 58 50 52 44 53 52 56 30 39 2e 70 61 72 74 6e 65 XPRDSRV09.partne
//-- 1b00 72 73 2e 65 78 74 72 61 6e 65 74 2e 6d 69 63 72 rs.extranet.micr
//-- 1b10 6f 73 6f 66 74 2e 63 6f 6d 5c 43 65 72 74 45 6e osoft.com.CertEn
//-- 1b20 72 6f 6c 6c 5c 4d 69 63 72 6f 73 6f 66 74 20 4c roll.Microsoft L
//-- 1b30 53 52 41 20 50 41 2e 63 72 6c 30 82 01 42 06 08 SRA PA.crl0..B..
//-- 1b40 2b 06 01 05 05 07 01 01 04 82 01 34 30 82 01 30 +..........40..0
//-- 1b50 30 81 96 06 08 2b 06 01 05 05 07 30 02 86 81 89 0....+.....0....
//-- 1b60 68 74 74 70 3a 2f 2f 74 6b 35 70 61 78 70 72 64 http://tk5paxprd
//-- 1b70 73 72 76 30 39 2e 70 61 72 74 6e 65 72 73 2e 65 srv09.partners.e
//-- 1b80 78 74 72 61 6e 65 74 2e 6d 69 63 72 6f 73 6f 66 xtranet.microsof
//-- 1b90 74 2e 63 6f 6d 2f 43 65 72 74 45 6e 72 6f 6c 6c t.com/CertEnroll
//-- 1ba0 2f 54 4b 35 50 41 58 50 52 44 53 52 56 30 39 2e /TK5PAXPRDSRV09.
//-- 1bb0 70 61 72 74 6e 65 72 73 2e 65 78 74 72 61 6e 65 partners.extrane
//-- 1bc0 74 2e 6d 69 63 72 6f 73 6f 66 74 2e 63 6f 6d 5f t.microsoft.com_
//-- 1bd0 4d 69 63 72 6f 73 6f 66 74 25 32 30 4c 53 52 41 Microsoft%20LSRA
//-- 1be0 25 32 30 50 41 2e 63 72 74 30 81 94 06 08 2b 06 %20PA.crt0....+.
//-- 1bf0 01 05 05 07 30 02 86 81 87 66 69 6c 65 3a 2f 2f ....0....file://
//-- 1c00 5c 5c 54 4b 35 50 41 58 50 52 44 53 52 56 30 39 ..TK5PAXPRDSRV09
//-- 1c10 2e 70 61 72 74 6e 65 72 73 2e 65 78 74 72 61 6e .partners.extran
//-- 1c20 65 74 2e 6d 69 63 72 6f 73 6f 66 74 2e 63 6f 6d et.microsoft.com
//-- 1c30 5c 43 65 72 74 45 6e 72 6f 6c 6c 5c 54 4b 35 50 .CertEnroll.TK5P
//-- 1c40 41 58 50 52 44 53 52 56 30 39 2e 70 61 72 74 6e AXPRDSRV09.partn
//-- 1c50 65 72 73 2e 65 78 74 72 61 6e 65 74 2e 6d 69 63 ers.extranet.mic
//-- 1c60 72 6f 73 6f 66 74 2e 63 6f 6d 5f 4d 69 63 72 6f rosoft.com_Micro
//-- 1c70 73 6f 66 74 20 4c 53 52 41 20 50 41 2e 63 72 74 soft LSRA PA.crt
//-- 1c80 30 1a 06 08 2b 06 01 04 01 82 37 12 01 01 ff 04 0...+.....7.....
//-- 1c90 0b 16 09 54 4c 53 7e 42 41 53 49 43 30 0d 06 09 ...TLS~BASIC0...
//-- 1ca0 2a 86 48 86 f7 0d 01 01 04 05 00 03 82 01 01 00 *.H.............
//-- 1cb0 11 ce 32 58 56 85 eb ea dd 44 a3 15 e8 d9 63 10 ..2XV....D....c.
//-- 1cc0 bb 23 b9 59 43 52 d4 27 4b b5 f3 7e c4 f9 3f b4 .#.YCR.'K..~..?.
//-- 1cd0 96 e9 2e dc 6f 98 7a 19 f9 0c fb 3c 58 5d ad 18 ....o.z....<X]..
//-- 1ce0 99 96 31 b2 8f e3 9d 10 cd e1 98 e6 65 ac 75 26 ..1.........e.u&
//-- 1cf0 96 5b d9 96 04 eb b4 cf 5f 2e ed fa 69 99 db 2a .[......_...i..*
//-- 1d00 2b b3 13 89 a4 e3 87 a7 ee 9a a1 61 35 72 23 8e +..........a5r#.
//-- 1d10 40 70 f5 54 dc 5e 93 74 4b 75 9f 72 f5 fd 9c db @p.T.^.tKu.r....
//-- 1d20 4f f1 b5 26 56 b6 d9 cd 45 b7 57 14 90 04 8f a7 O..&V...E.W.....
//-- 1d30 56 aa 2b db e3 62 38 c3 b3 13 f5 d9 6f fd 5b 02 V.+..b8.....o.[.
//-- 1d40 04 cc 9c 8b d0 cb 6f 6e c4 9c 50 82 50 9e f5 31 ......on..P.P..1
//-- 1d50 6e 32 a2 87 54 58 d3 59 7c c8 78 d5 8d 57 ad e7 n2..TX.Y|.x..W..
//-- 1d60 d0 d7 81 ae 5d 16 13 ec c8 fb 8b 9c d2 1f d8 8f ....]...........
//-- 1d70 f6 81 d4 b9 ba e3 93 01 a0 d7 ac 91 de 08 3c 78 ..............<x
//-- 1d80 cc f9 e0 e4 78 a7 7c 63 3a 40 ab b4 69 e0 9a bd ....x.|c:@..i...
//-- 1d90 99 7f 70 97 33 dc 2d 0c d4 78 ad f6 4c 84 07 e0 ..p.3.-..x..L...
//-- 1da0 8e 47 d2 df 00 e0 02 3a 2f 71 58 9f e6 77 63 fe .G.....:/qX..wc.
//-- 1db0 62 04 00 00 30 82 04 5e 30 82 03 4a a0 03 02 01 b...0..^0..J....
//-- 1dc0 02 02 05 01 00 00 00 0c 30 09 06 05 2b 0e 03 02 ........0...+...
//-- 1dd0 1d 05 00 30 1f 31 1d 30 1b 06 03 55 04 03 13 14 ...0.1.0...U....
//-- 1de0 54 65 72 6d 69 6e 61 6c 20 53 65 72 76 69 63 65 Terminal Service
//-- 1df0 73 20 4c 53 30 1e 17 0d 31 31 31 32 30 31 30 39 s LS0...11120109
//-- 1e00 35 34 34 39 5a 17 0d 33 38 30 31 31 39 30 33 31 5449Z..380119031
//-- 1e10 34 30 37 5a 30 81 a4 31 81 a1 30 27 06 03 55 04 407Z0..1..0'..U.
//-- 1e20 03 1e 20 00 6e 00 63 00 61 00 63 00 6e 00 5f 00 .. .n.c.a.c.n._.
//-- 1e30 6e 00 70 00 3a 00 31 00 30 00 2e 00 31 00 30 00 n.p.:.1.0...1.0.
//-- 1e40 2e 00 31 30 31 06 03 55 04 07 1e 2a 00 6e 00 63 ..101..U...*.n.c
//-- 1e50 00 61 00 63 00 6e 00 5f 00 6e 00 70 00 3a 00 31 .a.c.n._.n.p.:.1
//-- 1e60 00 30 00 2e 00 31 00 30 00 2e 00 31 00 34 00 2e .0...1.0...1.4..
//-- 1e70 00 31 00 34 00 34 30 43 06 03 55 04 05 1e 3c 00 .1.4.40C..U...<.
//-- 1e80 31 00 42 00 63 00 4b 00 65 00 54 00 4c 00 38 00 1.B.c.K.e.T.L.8.
//-- 1e90 72 00 56 00 59 00 6f 00 4e 00 6a 00 4a 00 79 00 r.V.Y.o.N.j.J.y.
//-- 1ea0 55 00 6c 00 78 00 6a 00 53 00 68 00 61 00 65 00 U.l.x.j.S.h.a.e.
//-- 1eb0 50 00 6d 00 41 00 3d 00 0d 00 0a 30 58 30 09 06 P.m.A.=....0X0..
//-- 1ec0 05 2b 0e 03 02 0f 05 00 03 4b 00 30 48 02 41 00 .+.......K.0H.A.
//-- 1ed0 bf de a4 5d 90 34 e9 47 8a 70 4e 01 2d 16 6e b7 ...].4.G.pN.-.n.
//-- 1ee0 02 ae 20 24 55 00 7a cd db c4 25 99 ee d2 cd 47 .. $U.z...%....G
//-- 1ef0 13 d6 e8 9d 96 29 64 65 3b d5 05 be 9e c1 c4 85 .....)de;.......
//-- 1f00 65 11 a4 b1 42 3c 23 ae 09 1f 20 43 50 84 18 fd e...B<#... CP...
//-- 1f10 02 03 01 00 01 a3 82 01 ed 30 82 01 e9 30 14 06 .........0...0..
//-- 1f20 09 2b 06 01 04 01 82 37 12 04 01 01 ff 04 04 01 .+.....7........
//-- 1f30 00 05 00 30 3c 06 09 2b 06 01 04 01 82 37 12 02 ...0<..+.....7..
//-- 1f40 01 01 ff 04 2c 4d 00 69 00 63 00 72 00 6f 00 73 ....,M.i.c.r.o.s
//-- 1f50 00 6f 00 66 00 74 00 20 00 43 00 6f 00 72 00 70 .o.f.t. .C.o.r.p
//-- 1f60 00 6f 00 72 00 61 00 74 00 69 00 6f 00 6e 00 00 .o.r.a.t.i.o.n..
//-- 1f70 00 30 81 cd 06 09 2b 06 01 04 01 82 37 12 05 01 .0....+.....7...
//-- 1f80 01 ff 04 81 bc 00 30 00 00 01 00 00 00 02 00 00 ......0.........
//-- 1f90 00 0c 04 00 00 1c 00 4a 00 66 00 4a 00 b0 00 01 .......J.f.J....
//-- 1fa0 00 33 00 64 00 32 00 36 00 37 00 39 00 35 00 34 .3.d.2.6.7.9.5.4
//-- 1fb0 00 2d 00 65 00 65 00 62 00 37 00 2d 00 31 00 31 .-.e.e.b.7.-.1.1
//-- 1fc0 00 64 00 31 00 2d 00 62 00 39 00 34 00 65 00 2d .d.1.-.b.9.4.e.-
//-- 1fd0 00 30 00 30 00 63 00 30 00 34 00 66 00 61 00 33 .0.0.c.0.4.f.a.3
//-- 1fe0 00 30 00 38 00 30 00 64 00 00 00 33 00 64 00 32 .0.8.0.d...3.d.2
//-- 1ff0 00 36 00 37 00 39 00 35 00 34 00 2d 00 65 00 65 .6.7.9.5.4.-.e.e
//-- 2000 00 62 00 37 00 2d 00 31 00 31 00 64 00 31 00 2d .b.7.-.1.1.d.1.-
//-- 2010 00 62 00 39 00 34 00 65 00 2d 00 30 00 30 00 63 .b.9.4.e.-.0.0.c
//-- 2020 00 30 00 34 00 66 00 61 00 33 00 30 00 38 00 30 .0.4.f.a.3.0.8.0
//-- 2030 00 64 00 00 00 00 00 00 10 00 80 e4 00 00 00 00 .d..............
//-- 2040 00 30 81 97 06 09 2b 06 01 04 01 82 37 12 06 01 .0....+.....7...
//-- 2050 01 ff 04 81 86 00 30 00 00 00 00 12 00 42 00 57 ......0......B.W
//-- 2060 00 49 00 4e 00 32 00 4b 00 38 00 44 00 43 00 00 .I.N.2.K.8.D.C..
//-- 2070 00 35 00 35 00 30 00 34 00 31 00 2d 00 32 00 32 .5.5.0.4.1.-.2.2
//-- 2080 00 32 00 2d 00 32 00 33 00 30 00 33 00 33 00 33 .2.-.2.3.0.3.3.3
//-- 2090 00 37 00 2d 00 37 00 36 00 30 00 30 00 32 00 00 .7.-.7.6.0.0.2..
//-- 20a0 00 53 00 65 00 72 00 76 00 65 00 75 00 72 00 20 .S.e.r.v.e.u.r.
//-- 20b0 00 64 00 65 00 20 00 6c 00 69 00 63 00 65 00 6e .d.e. .l.i.c.e.n
//-- 20c0 00 63 00 65 00 73 00 20 00 64 00 65 00 20 00 73 .c.e.s. .d.e. .s
//-- 20d0 00 69 00 74 00 65 00 00 00 00 00 30 29 06 03 55 .i.t.e.....0)..U
//-- 20e0 1d 23 01 01 ff 04 1f 30 1d a1 14 a4 12 57 00 49 .#.....0.....W.I
//-- 20f0 00 4e 00 32 00 4b 00 38 00 44 00 43 00 00 00 82 .N.2.K.8.D.C....
//-- 2100 05 01 00 00 00 0c 30 09 06 05 2b 0e 03 02 1d 05 ......0...+.....
//-- 2110 00 03 82 01 01 00 7c 0b d3 35 43 12 79 a3 f7 ce ......|..5C.y...
//-- 2120 d9 0f 33 57 9b 4d 2e b9 89 8e 5c 16 ea ad f0 2a ..3W.M.........*
//-- 2130 a3 8c e6 24 d5 95 a2 49 50 ca 9f e9 61 88 ac 65 ...$...IP...a..e
//-- 2140 24 85 19 c3 00 33 70 50 b8 0b 75 fd eb 02 db 7c $....3pP..u....|
//-- 2150 9e 08 2d a6 29 b4 99 cb e5 21 6a 88 de 4f a6 50 ..-.)....!j..O.P
//-- 2160 05 07 6c 27 b6 57 32 a4 d5 e8 2e ac 43 bd 75 51 ..l'.W2.....C.uQ
//-- 2170 e0 50 9b 54 f6 e5 32 dd 71 83 49 a9 97 85 0e 0f .P.T..2.q.I.....
//-- 2180 e6 33 59 52 05 1e 33 c2 bd a5 65 dc 06 9a 94 bb .3YR..3...e.....
//-- 2190 14 68 b0 d2 5f 82 17 5d e7 45 d2 a1 51 f6 50 2f .h.._..].E..Q.P/
//-- 21a0 3c e3 d3 5e a1 ef de 3c 0f 6f e2 fd 23 6e 6d b5 <..^...<.o..#nm.
//-- 21b0 28 f5 cb f9 35 08 0a ea f2 f1 60 eb 55 66 64 c3 (...5.....`.Ufd.
//-- 21c0 8c 6d 87 0b 29 3b a4 bf 0b f7 ca 5b 72 e2 bf 18 .m..);.....[r...
//-- 21d0 35 62 47 49 15 86 83 87 d8 88 d5 8d 89 99 ef 74 5bGI...........t
//-- 21e0 7d 9f 69 06 60 9a 7d 8a 8e e7 f0 cf 83 12 be 47 }.i.`.}........G
//-- 21f0 5d a2 6e 53 03 f3 7b 73 68 fc 78 cd d4 52 43 45 ].nS..{sh.x..RCE
//-- 2200 3c e8 44 fa 7d 20 02 59 8f dc d4 f0 06 98 3a 81 <.D.} .Y......:.
//-- 2210 0e 91 8d 1d b9 2e 00 00 00 00 00 00 00 00 00 00 ................
//-- 2220 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 2230 00 00 00 00 00 00                               ......
//-- receiving SC_SECURITY done

uint8_t security[] = {
    0x02, 0x0c, 0x36, 0x22, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x02, 0x22, 0x00, 0x00, 0x31, 0x67, 0x6c, 0x98, 0xf5, 0x8d, 0x5b, 0x66, 0xc2, 0x33, 0xf3, 0x6b,
    0xce, 0xd5, 0x50, 0x3e, 0x80, 0x1c, 0x28, 0x84, 0xc1, 0xb0, 0x13, 0x38, 0x62, 0x7b, 0xb9, 0xa6,
    0x81, 0x5b, 0x83, 0x94, 0x02, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x16, 0x04, 0x00, 0x00,
    0x30, 0x82, 0x04, 0x12, 0x30, 0x82, 0x02, 0xfa, 0xa0, 0x03, 0x02, 0x01, 0x02, 0x02, 0x0f, 0x00,
    0xc1, 0x00, 0x8b, 0x3c, 0x3c, 0x88, 0x11, 0xd1, 0x3e, 0xf6, 0x63, 0xec, 0xdf, 0x40, 0x30, 0x0d,
    0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x04, 0x05, 0x00, 0x30, 0x70, 0x31,
    0x2b, 0x30, 0x29, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x22, 0x43, 0x6f, 0x70, 0x79, 0x72, 0x69,
    0x67, 0x68, 0x74, 0x20, 0x28, 0x63, 0x29, 0x20, 0x31, 0x39, 0x39, 0x37, 0x20, 0x4d, 0x69, 0x63,
    0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x43, 0x6f, 0x72, 0x70, 0x2e, 0x31, 0x1e, 0x30, 0x1c,
    0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x15, 0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74,
    0x20, 0x43, 0x6f, 0x72, 0x70, 0x6f, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x31, 0x21, 0x30, 0x1f,
    0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x18, 0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74,
    0x20, 0x52, 0x6f, 0x6f, 0x74, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74, 0x79, 0x30,
    0x1e, 0x17, 0x0d, 0x39, 0x37, 0x30, 0x31, 0x31, 0x30, 0x30, 0x37, 0x30, 0x30, 0x30, 0x30, 0x5a,
    0x17, 0x0d, 0x32, 0x30, 0x31, 0x32, 0x33, 0x31, 0x30, 0x37, 0x30, 0x30, 0x30, 0x30, 0x5a, 0x30,
    0x70, 0x31, 0x2b, 0x30, 0x29, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x22, 0x43, 0x6f, 0x70, 0x79,
    0x72, 0x69, 0x67, 0x68, 0x74, 0x20, 0x28, 0x63, 0x29, 0x20, 0x31, 0x39, 0x39, 0x37, 0x20, 0x4d,
    0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x43, 0x6f, 0x72, 0x70, 0x2e, 0x31, 0x1e,
    0x30, 0x1c, 0x06, 0x03, 0x55, 0x04, 0x0b, 0x13, 0x15, 0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f,
    0x66, 0x74, 0x20, 0x43, 0x6f, 0x72, 0x70, 0x6f, 0x72, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x31, 0x21,
    0x30, 0x1f, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13, 0x18, 0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f,
    0x66, 0x74, 0x20, 0x52, 0x6f, 0x6f, 0x74, 0x20, 0x41, 0x75, 0x74, 0x68, 0x6f, 0x72, 0x69, 0x74,
    0x79, 0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01,
    0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00, 0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01,
    0x01, 0x00, 0xa9, 0x02, 0xbd, 0xc1, 0x70, 0xe6, 0x3b, 0xf2, 0x4e, 0x1b, 0x28, 0x9f, 0x97, 0x78,
    0x5e, 0x30, 0xea, 0xa2, 0xa9, 0x8d, 0x25, 0x5f, 0xf8, 0xfe, 0x95, 0x4c, 0xa3, 0xb7, 0xfe, 0x9d,
    0xa2, 0x20, 0x3e, 0x7c, 0x51, 0xa2, 0x9b, 0xa2, 0x8f, 0x60, 0x32, 0x6b, 0xd1, 0x42, 0x64, 0x79,
    0xee, 0xac, 0x76, 0xc9, 0x54, 0xda, 0xf2, 0xeb, 0x9c, 0x86, 0x1c, 0x8f, 0x9f, 0x84, 0x66, 0xb3,
    0xc5, 0x6b, 0x7a, 0x62, 0x23, 0xd6, 0x1d, 0x3c, 0xde, 0x0f, 0x01, 0x92, 0xe8, 0x96, 0xc4, 0xbf,
};

    InStream input(security, sizeof(security));
    GCC::UserData::SCSecurity sc_sec1;
//    sc_sec1.recv(input);
//    BOOST_CHECK_EQUAL(sc_sec1.encryptionMethod, 1);
//    BOOST_CHECK_EQUAL(sc_sec1.dwVersion, 2);
}



//-- ================= SC_SECURITY CERT_CHAIN_X509
//-- ================= SC_SECURITY X509_get_pubkey
//-- ================= SC_SECURITY rsa_encrypt
//-- ================= SC_SECURITY client_random
//-- 0000 b8 6c da a6 f0 f6 30 8d a8 16 a6 6e e0 c3 e5 cc .l....0....n....
//-- 0010 98 76 dd f5 d0 26 74 5f 88 4c c2 50 c0 df c9 50 .v...&t_.L.P...P
//-- ================= SC_SECURITY SEC_RANDOM_SIZE=32
//-- ================= SC_SECURITY server_public_key_len
//-- 0000 fd 18 84 50 43 20 1f 09 ae 23 3c 42 b1 a4 11 65 ...PC ...#<B...e
//-- 0010 85 c4 c1 9e be 05 d5 3b 65 64 29 96 9d e8 d6 13 .......;ed).....
//-- 0020 47 cd d2 ee 99 25 c4 db cd 7a 00 55 24 20 ae 02 G....%...z.U$ ..
//-- 0030 b7 6e 16 2d 01 4e 70 8a 47 e9 34 90 5d a4 de bf .n.-.Np.G.4.]...
//-- ================= SC_SECURITY server_public_key_len=64
//-- ================= SC_SECURITY exponent
//-- 0000 01 00 01 00                                     ....
//-- ================= SC_SECURITY exponent_size=4
//-- ================= SC_SECURITY client_crypt_random
//-- 0000 b5 80 dc 30 51 b7 26 ac ef 6c 32 9a 1c 04 77 07 ...0Q.&..l2...w.
//-- 0010 a8 60 d4 37 fb a9 ad dd d7 84 62 61 23 b6 37 77 .`.7......ba#.7w
//-- 0020 88 34 c7 da d5 ad 67 19 52 44 2e 6f c0 59 66 08 .4....g.RD.o.Yf.
//-- 0030 c6 ad 23 84 3a 67 0c ad 02 fd 79 cb 04 cd aa 20 ..#.:g....y....
//-- 0040 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0050 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0060 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0070 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0080 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0090 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 00a0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 00b0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 00c0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 00d0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 00e0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 00f0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0100 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0110 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0120 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0130 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0140 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0150 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0160 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0170 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0180 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 0190 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 01a0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 01b0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 01c0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
//-- 01d0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
////--
//-- ================= SC_SECURITY SEC_RANDOM_SIZE=512
//-- send extended login info (RDP5-style) 1017b qa:administrateur
//-- Rdp::Get license: username="administrateur@qa"

//-- /* 0000 */ 0xff, 0x03, 0x10, 0x00, 0x07, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,  // ................

