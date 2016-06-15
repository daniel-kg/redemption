"## Config file for RDP proxy.\n\n\n"
"[globals]\n\n"

"# Support of Bitmap Cache.\n"
"#_advanced\n"
"bitmap_cache = boolean(default=True)\n\n"

"#_advanced\n"
"glyph_cache = boolean(default=False)\n\n"

"#_advanced\n"
"port = integer(min=0, default=3389)\n\n"

"#_advanced\n"
"nomouse = boolean(default=False)\n\n"

"#_advanced\n"
"notimestamp = boolean(default=False)\n\n"

"#_advanced\n"
"encryptionLevel = option('low', 'medium', 'high', default='low')\n\n"

"#_advanced\n"
"authfile = string(default='/var/run/redemption-sesman-sock')\n\n"

"# Time out during RDP handshake stage.\n"
"# (is in second)\n"
"handshake_timeout = integer(min=0, default=10)\n\n"

"# No traffic auto disconnection.\n"
"# (is in second)\n"
"session_timeout = integer(min=0, default=900)\n\n"

"# Keepalive.\n"
"# (is in second)\n"
"#_advanced\n"
"keepalive_grace_delay = integer(min=0, default=30)\n\n"

"# Specifies the time to spend on the login screen of proxy RDP before closing client window (0 to desactivate).\n"
"# (is in second)\n"
"#_advanced\n"
"authentication_timeout = integer(min=0, default=120)\n\n"

"# Specifies the time to spend on the close box of proxy RDP before closing client window (0 to desactivate).\n"
"# (is in second)\n"
"#_advanced\n"
"close_timeout = integer(min=0, default=600)\n\n"

"# Session record options.\n"
"#   0: No encryption (faster).\n"
"#   1: No encryption, with checksum.\n"
"#   2: Encryption enabled.\n"
"# When session records are encrypted, they can be read only by the WAB where they have been generated.\n"
"#_advanced\n"
"trace_type = option(0, 1, 2, default=1)\n\n"

"#_advanced\n"
"listen_address = ip_addr(default='0.0.0.0')\n\n"

"# Allow IP Transparent.\n"
"#_iptables\n"
"enable_ip_transparent = boolean(default=False)\n\n"

"# Proxy certificate password.\n"
"#_advanced\n"
"#_password\n"
"certificate_password = string(max=254, default='inquisition')\n\n"

"#_advanced\n"
"png_path = string(max=4096, default='" PNG_PATH "')\n\n"

"#_advanced\n"
"wrm_path = string(max=4096, default='" WRM_PATH "')\n\n"

"#_hidden\n"
"movie = boolean(default=False)\n\n"

"#_advanced\n"
"movie_path = string(default='')\n\n"

"# Support of Bitmap Update.\n"
"#_advanced\n"
"enable_bitmap_update = boolean(default=True)\n\n"

"# Show close screen.\n"
"enable_close_box = boolean(default=True)\n\n"

"#_advanced\n"
"enable_osd = boolean(default=True)\n\n"

"#_advanced\n"
"enable_osd_display_remote_target = boolean(default=True)\n\n"

"#_advanced\n"
"persistent_path = string(max=4096, default='" PERSISTENT_PATH "')\n\n"

"#_hidden\n"
"disable_proxy_opt = boolean(default=False)\n\n"

"allow_using_multiple_monitors = boolean(default=False)\n\n"

"# Needed to refresh screen of Windows Server 2012.\n"
"#_advanced\n"
"bogus_refresh_rect = boolean(default=True)\n\n"

"[session_log]\n\n"

"enable_session_log = boolean(default=True)\n\n"

"#   0: keyboard input are not masked\n"
"#   1: only passwords are masked\n"
"#   2: passwords and unidentified texts are masked\n"
"#   3: keyboard input are fully masked\n"
"#_advanced\n"
"keyboard_input_masking_level = option(0, 1, 2, 3, default=3)\n\n"

"[client]\n\n"

"# cs-CZ, da-DK, de-DE, el-GR, en-US, es-ES, fi-FI.finnish, fr-FR, is-IS, it-IT, nl-NL, nb-NO, pl-PL.programmers, pt-BR.abnt, ro-RO, ru-RU, hr-HR, sk-SK, sv-SE, tr-TR.q, uk-UA, sl-SI, et-EE, lv-LV, lt-LT.ibm, mk-MK, fo-FO, mt-MT.47, se-NO, kk-KZ, ky-KG, tt-RU, mn-MN, cy-GB, lb-LU, mi-NZ, de-CH, en-GB, es-MX, fr-BE.fr, nl-BE, pt-PT, sr-La, se-SE, uz-Cy, iu-La, fr-CA, sr-Cy, en-CA.fr, fr-CH, bs-Cy, bg-BG.latin, cs-CZ.qwerty, en-IE.irish, de-DE.ibm, el-GR.220, es-ES.variation, hu-HU, en-US.dvorak, it-IT.142, pl-PL, pt-BR.abnt2, ru-RU.typewriter, sk-SK.qwerty, tr-TR.f, lv-LV.qwerty, lt-LT, mt-MT.48, se-NO.ext_norway, fr-BE, se-SE, en-CA.multilingual, en-IE, cs-CZ.programmers, el-GR.319, en-US.international, se-SE.ext_finland_sweden, bg-BG, el-GR.220_latin, en-US.dvorak_left, el-GR.319_latin, en-US.dvorak_right, el-GR.latin, el-GR.polytonic\n"
"#_advanced\n"
"keyboard_layout_proposals = string_list(default=list('en-US, fr-FR, de-DE, ru-RU'))\n\n"

"# If true, ignore password provided by RDP client, user need do login manually.\n"
"#_advanced\n"
"ignore_logon_password = boolean(default=False)\n\n"

"# Enable font smoothing (0x80).\n"
"#_advanced\n"
"#_hex\n"
"performance_flags_default = integer(min=0, default=128)\n\n"

"# Disable theme (0x8).\n"
"# Disable mouse cursor shadows (0x20).\n"
"#_advanced\n"
"#_hex\n"
"performance_flags_force_present = integer(min=0, default=40)\n\n"

"#_advanced\n"
"#_hex\n"
"performance_flags_force_not_present = integer(min=0, default=0)\n\n"

"# If enabled, avoid automatically font smoothing in recorded session.\n"
"#_advanced\n"
"auto_adjust_performance_flags = boolean(default=True)\n\n"

"# Fallback to RDP Legacy Encryption if client does not support TLS.\n"
"tls_fallback_legacy = boolean(default=False)\n\n"

"tls_support = boolean(default=True)\n\n"

"# Needed to connect with jrdp, based on bogus X224 layer code.\n"
"#_advanced\n"
"bogus_neg_request = boolean(default=False)\n\n"

"# Needed to connect with Remmina 0.8.3 and freerdp 0.9.4, based on bogus MCS layer code.\n"
"#_advanced\n"
"bogus_user_id = boolean(default=True)\n\n"

"# If enabled, ignore CTRL+ALT+DEL and CTRL+SHIFT+ESCAPE (or the equivalents) keyboard sequences.\n"
"#_advanced\n"
"disable_tsk_switch_shortcuts = boolean(default=False)\n\n"

"# Specifies the highest compression package support available on the front side\n"
"#   0: The RDP bulk compression is disabled\n"
"#   1: RDP 4.0 bulk compression\n"
"#   2: RDP 5.0 bulk compression\n"
"#   3: RDP 6.0 bulk compression\n"
"#   4: RDP 6.1 bulk compression\n"
"#_advanced\n"
"rdp_compression = option(0, 1, 2, 3, 4, default=4)\n\n"

"# Specifies the maximum color resolution (color depth) for client session:\n"
"#   8: 8-bit\n"
"#   15: 15-bit 555 RGB mask (5 bits for red, 5 bits for green, and 5 bits for blue)\n"
"#   16: 16-bit 565 RGB mask (5 bits for red, 6 bits for green, and 5 bits for blue)\n"
"#   24: 24-bit RGB mask (8 bits for red, 8 bits for green, and 8 bits for blue)\n"
"#_advanced\n"
"max_color_depth = option(8, 15, 16, 24, default=24)\n\n"

"# Persistent Disk Bitmap Cache on the front side.\n"
"#_advanced\n"
"persistent_disk_bitmap_cache = boolean(default=True)\n\n"

"# Support of Cache Waiting List (this value is ignored if Persistent Disk Bitmap Cache is disabled).\n"
"#_advanced\n"
"cache_waiting_list = boolean(default=False)\n\n"

"# If enabled, the contents of Persistent Bitmap Caches are stored on disk.\n"
"#_advanced\n"
"persist_bitmap_cache_on_disk = boolean(default=False)\n\n"

"# Support of Bitmap Compression.\n"
"#_advanced\n"
"bitmap_compression = boolean(default=True)\n\n"

"# Enables support of Clent Fast-Path Input Event PDUs.\n"
"#_advanced\n"
"fast_path = boolean(default=True)\n\n"

"enable_suppress_output = boolean(default=True)\n\n"

"#_hidden\n"
"ssl_cipher_list = string(default='')\n\n"

"[mod_rdp]\n\n"

"# Specifies the highest compression package support available on the front side\n"
"#   0: The RDP bulk compression is disabled\n"
"#   1: RDP 4.0 bulk compression\n"
"#   2: RDP 5.0 bulk compression\n"
"#   3: RDP 6.0 bulk compression\n"
"#   4: RDP 6.1 bulk compression\n"
"#_advanced\n"
"rdp_compression = option(0, 1, 2, 3, 4, default=4)\n\n"

"#_advanced\n"
"disconnect_on_logon_user_change = boolean(default=False)\n\n"

"# (is in second)\n"
"#_advanced\n"
"open_session_timeout = integer(min=0, default=0)\n\n"

"# Enables support of additional drawing orders:\n"
"#   15: MultiDstBlt\n"
"#   16: MultiPatBlt\n"
"#   17: MultiScrBlt\n"
"#   18: MultiOpaqueRect\n"
"#   22: Polyline\n"
"#_advanced\n"
"extra_orders = string_list(default=list('15,16,17,18,22'))\n\n"

"# NLA authentication in secondary target.\n"
"enable_nla = boolean(default=True)\n\n"

"# If enabled, NLA authentication will try Kerberos before NTLM.\n"
"# (if enable_nla is disabled, this value is ignored).\n"
"enable_kerberos = boolean(default=False)\n\n"

"# Persistent Disk Bitmap Cache on the mod side.\n"
"#_advanced\n"
"persistent_disk_bitmap_cache = boolean(default=True)\n\n"

"# Support of Cache Waiting List (this value is ignored if Persistent Disk Bitmap Cache is disabled).\n"
"#_advanced\n"
"cache_waiting_list = boolean(default=True)\n\n"

"# If enabled, the contents of Persistent Bitmap Caches are stored on disk.\n"
"#_advanced\n"
"persist_bitmap_cache_on_disk = boolean(default=False)\n\n"

"# Enables channels names (example: channel1,channel2,etc). Character * only, activate all with low priority.\n"
"#_advanced\n"
"allow_channels = string_list(default=list('*'))\n\n"

"# Disable channels names (example: channel1,channel2,etc). Character * only, deactivate all with low priority.\n"
"#_advanced\n"
"deny_channels = string_list(default=list())\n\n"

"# Enables support of Server Fast-Path Update PDUs.\n"
"#_advanced\n"
"fast_path = boolean(default=True)\n\n"

"# Enables Server Redirection Support.\n"
"#_advanced\n"
"server_redirection_support = boolean(default=False)\n\n"

"# Needed to connect with VirtualBox, based on bogus TS_UD_SC_NET data block.\n"
"#_advanced\n"
"bogus_sc_net_size = boolean(default=True)\n\n"

"# Needed to get the old behavior of cursor rendering.\n"
"#_advanced\n"
"bogus_linux_cursor = boolean(default=False)\n\n"

"#_advanced\n"
"proxy_managed_drives = string_list(default=list())\n\n"

"#_hidden\n"
"ignore_auth_channel = boolean(default=False)\n\n"

"# Authentication channel used by Auto IT scripts. May be '*' to use default name. Keep empty to disable virtual channel.\n"
"auth_channel = string(max=7, default='*')\n\n"

"#_hidden\n"
"alternate_shell = string(default='')\n\n"

"#_hidden\n"
"shell_working_directory = string(default='')\n\n"

"#_hidden\n"
"use_client_provided_alternate_shell = boolean(default=False)\n\n"

"#_hidden\n"
"enable_session_probe = boolean(default=False)\n\n"

"# Minimum supported server : Windows Server 2008.\n"
"# Clipboard redirection should be remain enabled on Terminal Server.\n"
"#_hidden\n"
"session_probe_use_smart_launcher = boolean(default=True)\n\n"

"#_hidden\n"
"enable_session_probe_launch_mask = boolean(default=True)\n\n"

"# Behavior on failure to launch Session Probe.\n"
"#   0: ignore failure and continue.\n"
"#   1: disconnect user.\n"
"#   2: reconnect without Session Probe.\n"
"#_hidden\n"
"session_probe_on_launch_failure = option(0, 1, 2, default=2)\n\n"

"# This parameter is used if session_probe_on_launch_failure is 1 (disconnect user).\n"
"# 0 to disable timeout.\n"
"# (is in millisecond)\n"
"#_hidden\n"
"session_probe_launch_timeout = integer(min=0, default=20000)\n\n"

"# This parameter is used if session_probe_on_launch_failure is 0 (ignore failure and continue) or 2 (reconnect without Session Probe).\n"
"# 0 to disable timeout.\n"
"# (is in millisecond)\n"
"#_hidden\n"
"session_probe_launch_fallback_timeout = integer(min=0, default=7000)\n\n"

"# Minimum supported server : Windows Server 2008.\n"
"#_hidden\n"
"session_probe_start_launch_timeout_timer_only_after_logon = boolean(default=True)\n\n"

"# (is in millisecond)\n"
"#_hidden\n"
"session_probe_keepalive_timeout = integer(min=0, default=5000)\n\n"

"#_hidden\n"
"session_probe_on_keepalive_timeout_disconnect_user = boolean(default=True)\n\n"

"# End automatically a disconnected session\n"
"#_hidden\n"
"session_probe_end_disconnected_session = boolean(default=False)\n\n"

"#_advanced\n"
"session_probe_customize_executable_name = boolean(default=False)\n\n"

"#_hidden\n"
"session_probe_alternate_shell = string(max=511, default='cmd /k')\n\n"

"# Keep known server certificates on WAB\n"
"#_hidden\n"
"server_cert_store = boolean(default=True)\n\n"

"# Behavior of certificates check.\n"
"#   0: fails if certificates doesn't match or miss.\n"
"#   1: fails if certificate doesn't match, succeed if no known certificate.\n"
"#   2: succeed if certificates exists (not checked), fails if missing.\n"
"#   3: always succeed.\n"
"# System errors like FS access rights issues or certificate decode are always check errors leading to connection rejection.\n"
"#_hidden\n"
"server_cert_check = option(0, 1, 2, 3, default=1)\n\n"

"# Warn if check allow connexion to server.\n"
"#   0: nobody\n"
"#   1: message sent to syslog\n"
"#   2: User notified (through proxy interface)\n"
"#   4: admin notified (wab notification)\n"
"(note: values can be added (everyone: 1+2+4=7, mute: 0))\n"
"#_hidden\n"
"server_access_allowed_message = integer(min=0, max=7, default=1)\n\n"

"# Warn that new server certificate file was created.\n"
"#   0: nobody\n"
"#   1: message sent to syslog\n"
"#   2: User notified (through proxy interface)\n"
"#   4: admin notified (wab notification)\n"
"(note: values can be added (everyone: 1+2+4=7, mute: 0))\n"
"#_hidden\n"
"server_cert_create_message = integer(min=0, max=7, default=1)\n\n"

"# Warn that server certificate file was successfully checked.\n"
"#   0: nobody\n"
"#   1: message sent to syslog\n"
"#   2: User notified (through proxy interface)\n"
"#   4: admin notified (wab notification)\n"
"(note: values can be added (everyone: 1+2+4=7, mute: 0))\n"
"#_hidden\n"
"server_cert_success_message = integer(min=0, max=7, default=1)\n\n"

"# Warn that server certificate file checking failed.\n"
"#   0: nobody\n"
"#   1: message sent to syslog\n"
"#   2: User notified (through proxy interface)\n"
"#   4: admin notified (wab notification)\n"
"(note: values can be added (everyone: 1+2+4=7, mute: 0))\n"
"#_hidden\n"
"server_cert_failure_message = integer(min=0, max=7, default=1)\n\n"

"# Warn that server certificate check raised some internal error.\n"
"#   0: nobody\n"
"#   1: message sent to syslog\n"
"#   2: User notified (through proxy interface)\n"
"#   4: admin notified (wab notification)\n"
"(note: values can be added (everyone: 1+2+4=7, mute: 0))\n"
"#_hidden\n"
"server_cert_error_message = integer(min=0, max=7, default=1)\n\n"

"# Do not transmit client machine name or RDP server.\n"
"hide_client_name = boolean(default=False)\n\n"

"[mod_vnc]\n\n"

"# Enable or disable the clipboard from client (client to server).\n"
"clipboard_up = boolean(default=False)\n\n"

"# Enable or disable the clipboard from server (server to client).\n"
"clipboard_down = boolean(default=False)\n\n"

"# Sets the encoding types in which pixel data can be sent by the VNC server:\n"
"#   0: Raw\n"
"#   1: CopyRect\n"
"#   2: RRE\n"
"#   16: ZRLE\n"
"#   -239 (0xFFFFFF11): Cursor pseudo-encoding\n"
"#_advanced\n"
"encodings = string_list(default=list())\n\n"

"#_advanced\n"
"allow_authentification_retries = boolean(default=False)\n\n"

"# VNC server clipboard data encoding type.\n"
"#_advanced\n"
"server_clipboard_encoding_type = option('utf-8', 'latin1', default='latin1')\n\n"

"#   0: delayed\n"
"#   1: duplicated\n"
"#   2: continued\n"
"#_advanced\n"
"bogus_clipboard_infinite_loop = option(0, 1, 2, default=0)\n\n"

"[mod_replay]\n\n"

"# 0 - Wait for Escape, 1 - End session\n"
"#_hidden\n"
"on_end_of_data = boolean(default=False)\n\n"

"[video]\n\n"

"#_advanced\n"
"capture_groupid = integer(min=0, default=33)\n\n"

"# Specifies the type of data to be captured:\n"
"#   0: none\n"
"#   1: png\n"
"#   2: wrm\n"
"#   4: flv\n"
"#   8: ocr\n"
"(note: values can be added (everyone: 1+2+4=7, mute: 0))\n"
"#_advanced\n"
"capture_flags = integer(min=0, max=15, default=3)\n\n"

"# Frame interval.\n"
"# (is in 1/10 second)\n"
"#_advanced\n"
"png_interval = integer(min=0, default=10)\n\n"

"# Frame interval.\n"
"# (is in 1/100 second)\n"
"#_advanced\n"
"frame_interval = integer(min=0, default=40)\n\n"

"# Time between 2 wrm movies.\n"
"# (is in second)\n"
"#_advanced\n"
"break_interval = integer(min=0, default=600)\n\n"

"# Number of png captures to keep.\n"
"#_advanced\n"
"png_limit = integer(min=0, default=5)\n\n"

"#_advanced\n"
"replay_path = string(max=4096, default='/tmp/')\n\n"

"#_advanced\n"
"hash_path = string(max=4096, default='" HASH_PATH "')\n\n"

"#_advanced\n"
"record_tmp_path = string(max=4096, default='" RECORD_TMP_PATH "')\n\n"

"#_advanced\n"
"record_path = string(max=4096, default='" RECORD_PATH "')\n\n"

"# Disable keyboard log:\n"
"#   0: none\n"
"#   1: disable keyboard log in syslog\n"
"#   2: disable keyboard log in recorded sessions\n"
"(note: values can be added (everyone: 1+2+4=7, mute: 0))\n"
"disable_keyboard_log = integer(min=0, max=3, default=1)\n\n"

"# Disable clipboard log:\n"
"#   0: none\n"
"#   1: disable clipboard log in syslog\n"
"#   2: disable clipboard log in recorded sessions\n"
"(note: values can be added (everyone: 1+2+4=7, mute: 0))\n"
"disable_clipboard_log = integer(min=0, max=3, default=1)\n\n"

"# Disable (redirected) file system log:\n"
"#   0: none\n"
"#   1: disable (redirected) file system log in syslog\n"
"#   2: disable (redirected) file system log in recorded sessions\n"
"(note: values can be added (everyone: 1+2+4=7, mute: 0))\n"
"disable_file_system_log = integer(min=0, max=3, default=1)\n\n"

"#_hidden\n"
"rt_display = integer(min=0, default=0)\n\n"

"# The method by which the proxy RDP establishes criteria on which to chosse a color depth for native video capture:\n"
"#   0: 24-bit\n"
"#   1: 16-bit\n"
"#_advanced\n"
"wrm_color_depth_selection_strategy = option(0, 1, default=1)\n\n"

"# The compression method of native video capture:\n"
"#   0: no compression\n"
"#   1: gzip\n"
"#   2: snappy\n"
"#_advanced\n"
"wrm_compression_algorithm = option(0, 1, 2, default=1)\n\n"

"[crypto]\n\n"

"#_hidden\n"
"encryption_key = string(min=64, max=64, default='000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F')\n\n"

"#_hidden\n"
"sign_key = string(min=64, max=64, default='000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F')\n\n"

"[debug]\n\n"

"#_advanced\n"
"x224 = integer(min=0, default=0)\n\n"

"#_advanced\n"
"mcs = integer(min=0, default=0)\n\n"

"#_advanced\n"
"sec = integer(min=0, default=0)\n\n"

"#_advanced\n"
"rdp = integer(min=0, default=0)\n\n"

"#_advanced\n"
"primary_orders = integer(min=0, default=0)\n\n"

"#_advanced\n"
"secondary_orders = integer(min=0, default=0)\n\n"

"#_advanced\n"
"bitmap = integer(min=0, default=0)\n\n"

"#_advanced\n"
"capture = integer(min=0, default=0)\n\n"

"#_advanced\n"
"auth = integer(min=0, default=0)\n\n"

"#_advanced\n"
"session = integer(min=0, default=0)\n\n"

"#_advanced\n"
"front = integer(min=0, default=0)\n\n"

"#_advanced\n"
"mod_rdp = integer(min=0, default=0)\n\n"

"#_advanced\n"
"mod_vnc = integer(min=0, default=0)\n\n"

"#_advanced\n"
"mod_int = integer(min=0, default=0)\n\n"

"#_advanced\n"
"mod_xup = integer(min=0, default=0)\n\n"

"#_advanced\n"
"widget = integer(min=0, default=0)\n\n"

"#_advanced\n"
"input = integer(min=0, default=0)\n\n"

"#_advanced\n"
"password = integer(min=0, default=0)\n\n"

"#_advanced\n"
"compression = integer(min=0, default=0)\n\n"

"#_advanced\n"
"cache = integer(min=0, default=0)\n\n"

"#_advanced\n"
"bitmap_update = integer(min=0, default=0)\n\n"

"#_advanced\n"
"performance = integer(min=0, default=0)\n\n"

"#_advanced\n"
"pass_dialog_box = integer(min=0, default=0)\n\n"

"#_advanced\n"
"config = boolean(default=True)\n\n"

"[translation]\n\n"

"#_advanced\n"
"language = option('en', 'fr', default='en')\n\n"

"#_advanced\n"
"password_en = string(default='')\n\n"

"#_advanced\n"
"password_fr = string(default='')\n\n"

"[internal_mod]\n\n"

"#_advanced\n"
"load_theme = string(default='')\n\n"
