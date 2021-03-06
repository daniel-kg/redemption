//
// DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN
//

#pragma once

#include <iosfwd>


// Specifies the type of data to be captured:
enum class CaptureFlags {
    none = 0,
    png = 1,
    wrm = 2,
    video = 4,
    ocr = 8,
};

inline bool is_valid_enum_value(CaptureFlags e)
{
    return static_cast<unsigned long>(e) <= 15;
}

inline CaptureFlags operator | (CaptureFlags x, CaptureFlags y)
{ return static_cast<CaptureFlags>(static_cast<unsigned long>(x) | static_cast<unsigned long>(y)); }
inline CaptureFlags operator & (CaptureFlags x, CaptureFlags y)
{ return static_cast<CaptureFlags>(static_cast<unsigned long>(x) & static_cast<unsigned long>(y)); }
inline CaptureFlags operator ~ (CaptureFlags x)
{ return static_cast<CaptureFlags>(~static_cast<unsigned long>(x) & static_cast<unsigned long>(15)); }
inline CaptureFlags operator + (CaptureFlags & x, CaptureFlags y) { return x | y; }
inline CaptureFlags operator - (CaptureFlags & x, CaptureFlags y) { return x & ~y; }
inline CaptureFlags & operator |= (CaptureFlags & x, CaptureFlags y) { return x = x | y; }
inline CaptureFlags & operator &= (CaptureFlags & x, CaptureFlags y) { return x = x & y; }
inline CaptureFlags & operator += (CaptureFlags & x, CaptureFlags y) { return x = x + y; }
inline CaptureFlags & operator -= (CaptureFlags & x, CaptureFlags y) { return x = x - y; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, CaptureFlags e)
{ return os << static_cast<unsigned long>(e); }


enum class Level {
    low = 0,
    medium = 1,
    high = 2,
};

inline bool is_valid_enum_value(Level e)
{ return static_cast<unsigned long>(e) <= 2; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, Level e)
{ return os << static_cast<unsigned long>(e); }


enum class Language {
    en = 0,
    fr = 1,
};

inline bool is_valid_enum_value(Language e)
{ return static_cast<unsigned long>(e) <= 1; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, Language e)
{ return os << static_cast<unsigned long>(e); }


enum class ClipboardEncodingType {
    utf8 = 0,
    latin1 = 1,
};

inline bool is_valid_enum_value(ClipboardEncodingType e)
{ return static_cast<unsigned long>(e) <= 1; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, ClipboardEncodingType e)
{ return os << static_cast<unsigned long>(e); }


enum class KeyboardLogFlags {
    none = 0,
    // keyboard log in syslog
    syslog = 1,
    // keyboard log in recorded sessions
    wrm = 2,
    // keyboard log in recorded meta
    meta = 4,
};

inline bool is_valid_enum_value(KeyboardLogFlags e)
{
    return static_cast<unsigned long>(e) <= 7;
}

inline KeyboardLogFlags operator | (KeyboardLogFlags x, KeyboardLogFlags y)
{ return static_cast<KeyboardLogFlags>(static_cast<unsigned long>(x) | static_cast<unsigned long>(y)); }
inline KeyboardLogFlags operator & (KeyboardLogFlags x, KeyboardLogFlags y)
{ return static_cast<KeyboardLogFlags>(static_cast<unsigned long>(x) & static_cast<unsigned long>(y)); }
inline KeyboardLogFlags operator ~ (KeyboardLogFlags x)
{ return static_cast<KeyboardLogFlags>(~static_cast<unsigned long>(x) & static_cast<unsigned long>(7)); }
inline KeyboardLogFlags operator + (KeyboardLogFlags & x, KeyboardLogFlags y) { return x | y; }
inline KeyboardLogFlags operator - (KeyboardLogFlags & x, KeyboardLogFlags y) { return x & ~y; }
inline KeyboardLogFlags & operator |= (KeyboardLogFlags & x, KeyboardLogFlags y) { return x = x | y; }
inline KeyboardLogFlags & operator &= (KeyboardLogFlags & x, KeyboardLogFlags y) { return x = x & y; }
inline KeyboardLogFlags & operator += (KeyboardLogFlags & x, KeyboardLogFlags y) { return x = x + y; }
inline KeyboardLogFlags & operator -= (KeyboardLogFlags & x, KeyboardLogFlags y) { return x = x - y; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, KeyboardLogFlags e)
{ return os << static_cast<unsigned long>(e); }


enum class ClipboardLogFlags {
    none = 0,
    // clipboard log in syslog
    syslog = 1,
    // clipboard log in recorded sessions
    wrm = 2,
};

inline bool is_valid_enum_value(ClipboardLogFlags e)
{
    return static_cast<unsigned long>(e) <= 3;
}

inline ClipboardLogFlags operator | (ClipboardLogFlags x, ClipboardLogFlags y)
{ return static_cast<ClipboardLogFlags>(static_cast<unsigned long>(x) | static_cast<unsigned long>(y)); }
inline ClipboardLogFlags operator & (ClipboardLogFlags x, ClipboardLogFlags y)
{ return static_cast<ClipboardLogFlags>(static_cast<unsigned long>(x) & static_cast<unsigned long>(y)); }
inline ClipboardLogFlags operator ~ (ClipboardLogFlags x)
{ return static_cast<ClipboardLogFlags>(~static_cast<unsigned long>(x) & static_cast<unsigned long>(3)); }
inline ClipboardLogFlags operator + (ClipboardLogFlags & x, ClipboardLogFlags y) { return x | y; }
inline ClipboardLogFlags operator - (ClipboardLogFlags & x, ClipboardLogFlags y) { return x & ~y; }
inline ClipboardLogFlags & operator |= (ClipboardLogFlags & x, ClipboardLogFlags y) { return x = x | y; }
inline ClipboardLogFlags & operator &= (ClipboardLogFlags & x, ClipboardLogFlags y) { return x = x & y; }
inline ClipboardLogFlags & operator += (ClipboardLogFlags & x, ClipboardLogFlags y) { return x = x + y; }
inline ClipboardLogFlags & operator -= (ClipboardLogFlags & x, ClipboardLogFlags y) { return x = x - y; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, ClipboardLogFlags e)
{ return os << static_cast<unsigned long>(e); }


enum class FileSystemLogFlags {
    none = 0,
    // (redirected) file system log in syslog
    syslog = 1,
    // (redirected) file system log in recorded sessions
    wrm = 2,
};

inline bool is_valid_enum_value(FileSystemLogFlags e)
{
    return static_cast<unsigned long>(e) <= 3;
}

inline FileSystemLogFlags operator | (FileSystemLogFlags x, FileSystemLogFlags y)
{ return static_cast<FileSystemLogFlags>(static_cast<unsigned long>(x) | static_cast<unsigned long>(y)); }
inline FileSystemLogFlags operator & (FileSystemLogFlags x, FileSystemLogFlags y)
{ return static_cast<FileSystemLogFlags>(static_cast<unsigned long>(x) & static_cast<unsigned long>(y)); }
inline FileSystemLogFlags operator ~ (FileSystemLogFlags x)
{ return static_cast<FileSystemLogFlags>(~static_cast<unsigned long>(x) & static_cast<unsigned long>(3)); }
inline FileSystemLogFlags operator + (FileSystemLogFlags & x, FileSystemLogFlags y) { return x | y; }
inline FileSystemLogFlags operator - (FileSystemLogFlags & x, FileSystemLogFlags y) { return x & ~y; }
inline FileSystemLogFlags & operator |= (FileSystemLogFlags & x, FileSystemLogFlags y) { return x = x | y; }
inline FileSystemLogFlags & operator &= (FileSystemLogFlags & x, FileSystemLogFlags y) { return x = x & y; }
inline FileSystemLogFlags & operator += (FileSystemLogFlags & x, FileSystemLogFlags y) { return x = x + y; }
inline FileSystemLogFlags & operator -= (FileSystemLogFlags & x, FileSystemLogFlags y) { return x = x - y; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, FileSystemLogFlags e)
{ return os << static_cast<unsigned long>(e); }


enum class ServerNotification {
    nobody = 0,
    // message sent to syslog
    syslog = 1,
    // User notified (through proxy interface)
    user = 2,
    // admin notified (wab notification)
    admin = 4,
};

inline bool is_valid_enum_value(ServerNotification e)
{
    return static_cast<unsigned long>(e) <= 7;
}

inline ServerNotification operator | (ServerNotification x, ServerNotification y)
{ return static_cast<ServerNotification>(static_cast<unsigned long>(x) | static_cast<unsigned long>(y)); }
inline ServerNotification operator & (ServerNotification x, ServerNotification y)
{ return static_cast<ServerNotification>(static_cast<unsigned long>(x) & static_cast<unsigned long>(y)); }
inline ServerNotification operator ~ (ServerNotification x)
{ return static_cast<ServerNotification>(~static_cast<unsigned long>(x) & static_cast<unsigned long>(7)); }
inline ServerNotification operator + (ServerNotification & x, ServerNotification y) { return x | y; }
inline ServerNotification operator - (ServerNotification & x, ServerNotification y) { return x & ~y; }
inline ServerNotification & operator |= (ServerNotification & x, ServerNotification y) { return x = x | y; }
inline ServerNotification & operator &= (ServerNotification & x, ServerNotification y) { return x = x & y; }
inline ServerNotification & operator += (ServerNotification & x, ServerNotification y) { return x = x + y; }
inline ServerNotification & operator -= (ServerNotification & x, ServerNotification y) { return x = x - y; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, ServerNotification e)
{ return os << static_cast<unsigned long>(e); }


// Behavior of certificates check.
// System errors like FS access rights issues or certificate decode are always check errors leading to connection rejection.
enum class ServerCertCheck {
    // fails if certificates doesn't match or miss.
    fails_if_no_match_or_missing = 0,
    // fails if certificate doesn't match, succeed if no known certificate.
    fails_if_no_match_and_succeed_if_no_know = 1,
    // succeed if certificates exists (not checked), fails if missing.
    succeed_if_exists_and_fails_if_missing = 2,
    // always succeed.
    always_succeed = 3,
};

inline bool is_valid_enum_value(ServerCertCheck e)
{ return static_cast<unsigned long>(e) <= 3; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, ServerCertCheck e)
{ return os << static_cast<unsigned long>(e); }


// Session record options.
// When session records are encrypted, they can be read only by the WAB where they have been generated.
enum class TraceType {
    // No encryption (faster).
    localfile = 0,
    // No encryption, with checksum.
    localfile_hashed = 1,
    // Encryption enabled.
    cryptofile = 2,
};

inline bool is_valid_enum_value(TraceType e)
{ return static_cast<unsigned long>(e) <= 2; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, TraceType e)
{ return os << static_cast<unsigned long>(e); }


enum class KeyboardInputMaskingLevel {
    // keyboard input are not masked
    unmasked = 0,
    // only passwords are masked
    password_only = 1,
    // passwords and unidentified texts are masked
    password_and_unidentified = 2,
    // keyboard input are fully masked
    fully_masked = 3,
};

inline bool is_valid_enum_value(KeyboardInputMaskingLevel e)
{ return static_cast<unsigned long>(e) <= 3; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, KeyboardInputMaskingLevel e)
{ return os << static_cast<unsigned long>(e); }


// Behavior on failure to launch Session Probe.
enum class SessionProbeOnLaunchFailure {
    // ignore failure and continue.
    ignore_and_continue = 0,
    // disconnect user.
    disconnect_user = 1,
    // reconnect without Session Probe.
    retry_without_session_probe = 2,
};

inline bool is_valid_enum_value(SessionProbeOnLaunchFailure e)
{ return static_cast<unsigned long>(e) <= 2; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, SessionProbeOnLaunchFailure e)
{ return os << static_cast<unsigned long>(e); }


enum class VncBogusClipboardInfiniteLoop {
    delayed = 0,
    duplicated = 1,
    continued = 2,
};

inline bool is_valid_enum_value(VncBogusClipboardInfiniteLoop e)
{ return static_cast<unsigned long>(e) <= 2; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, VncBogusClipboardInfiniteLoop e)
{ return os << static_cast<unsigned long>(e); }


// The method by which the proxy RDP establishes criteria on which to chosse a color depth for native video capture:
enum class ColorDepthSelectionStrategy {
    // 24-bit
    depth24 = 0,
    // 16-bit
    depth16 = 1,
};

inline bool is_valid_enum_value(ColorDepthSelectionStrategy e)
{ return static_cast<unsigned long>(e) <= 1; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, ColorDepthSelectionStrategy e)
{ return os << static_cast<unsigned long>(e); }


// The compression method of native video capture:
enum class WrmCompressionAlgorithm {
    no_compression = 0,
    gzip = 1,
    snappy = 2,
};

inline bool is_valid_enum_value(WrmCompressionAlgorithm e)
{ return static_cast<unsigned long>(e) <= 2; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, WrmCompressionAlgorithm e)
{ return os << static_cast<unsigned long>(e); }


// Specifies the highest compression package support available on the front side
enum class RdpCompression {
    // The RDP bulk compression is disabled
    none = 0,
    // RDP 4.0 bulk compression
    rdp4 = 1,
    // RDP 5.0 bulk compression
    rdp5 = 2,
    // RDP 6.0 bulk compression
    rdp6 = 3,
    // RDP 6.1 bulk compression
    rdp6_1 = 4,
};

inline bool is_valid_enum_value(RdpCompression e)
{ return static_cast<unsigned long>(e) <= 4; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, RdpCompression e)
{ return os << static_cast<unsigned long>(e); }


// Needed to get the old behavior of cursor rendering.
enum class BogusLinuxCursor {
    // More compatible with MSTSC.
    disable = 0,
    // The old behavior of cursor rendering.
    enable = 1,
    // Depend on platform RDP client.
    smart = 2,
};

inline bool is_valid_enum_value(BogusLinuxCursor e)
{ return static_cast<unsigned long>(e) <= 2; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, BogusLinuxCursor e)
{ return os << static_cast<unsigned long>(e); }


enum class OcrLocale {
    latin = 0,
    cyrillic = 1,
};

inline bool is_valid_enum_value(OcrLocale e)
{ return static_cast<unsigned long>(e) <= 1; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, OcrLocale e)
{ return os << static_cast<unsigned long>(e); }


enum class BogusNumberOfFastpathInputEvent {
    disabled = 0,
    pause_key_only = 1,
    all_input_events = 2,
};

inline bool is_valid_enum_value(BogusNumberOfFastpathInputEvent e)
{ return static_cast<unsigned long>(e) <= 2; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, BogusNumberOfFastpathInputEvent e)
{ return os << static_cast<unsigned long>(e); }


enum class SessionProbeOnKeepaliveTimeout {
    ignore_and_continue = 0,
    disconnect_user = 1,
    freeze_connection_and_wait = 2,
};

inline bool is_valid_enum_value(SessionProbeOnKeepaliveTimeout e)
{ return static_cast<unsigned long>(e) <= 2; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, SessionProbeOnKeepaliveTimeout e)
{ return os << static_cast<unsigned long>(e); }


enum class SmartVideoCropping {
    // Disabled. When replaying the session video, the content of the RDP viewer matches the size of the client's desktop
    disable = 0,
    // When replaying the session video, the content of the RDP viewer is restricted to the greatest area covered by the application during session
    v1 = 1,
    // When replaying the session video, the content of the RDP viewer is fully covered by the size of the greatest application window during session
    v2 = 2,
};

inline bool is_valid_enum_value(SmartVideoCropping e)
{ return static_cast<unsigned long>(e) <= 2; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, SmartVideoCropping e)
{ return os << static_cast<unsigned long>(e); }


enum class RdpModeConsole {
    allow = 0,
    force = 1,
    forbid = 2,
};

inline bool is_valid_enum_value(RdpModeConsole e)
{ return static_cast<unsigned long>(e) <= 2; }

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, RdpModeConsole e)
{ return os << static_cast<unsigned long>(e); }


// Specifies the maximum color resolution (color depth) for client session:
enum class ColorDepth {
    // 8-bit
    depth8 = 8,
    // 15-bit 555 RGB mask (5 bits for red, 5 bits for green, and 5 bits for blue)
    depth15 = 15,
    // 16-bit 565 RGB mask (5 bits for red, 6 bits for green, and 5 bits for blue)
    depth16 = 16,
    // 24-bit RGB mask (8 bits for red, 8 bits for green, and 8 bits for blue)
    depth24 = 24,
};

inline bool is_valid_enum_value(ColorDepth e)
{
    auto const i = static_cast<unsigned long>(e);
    return false /* NOLINT(readability-simplify-boolean-expr) */
     || i == 8
     || i == 15
     || i == 16
     || i == 24
    ;
}

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, ColorDepth e)
{ return os << static_cast<unsigned long>(e); }


enum class OcrVersion {
    v1 = 1,
    v2 = 2,
};

inline bool is_valid_enum_value(OcrVersion e)
{
    auto const i = static_cast<unsigned long>(e);
    return false /* NOLINT(readability-simplify-boolean-expr) */
     || i == 1
     || i == 2
    ;
}

template<class Ch, class Tr>
std::basic_ostream<Ch, Tr> &
operator << (std::basic_ostream<Ch, Tr> & os, OcrVersion e)
{ return os << static_cast<unsigned long>(e); }


