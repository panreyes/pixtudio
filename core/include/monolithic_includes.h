/*
 *  Copyright (C) 2014-2016 Joseba García Etxebarria <joseba.gar@gmail.com>
 *
 *  This file is part of PixTudio
 *
 *  Bennu is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Bennu is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#ifndef __MONOLITHIC_INCLUDES_H
#define __MONOLITHIC_INCLUDES_H

#include <libsdlhandler_symbols.h>
#include <mod_say_symbols.h>
#include <mod_string_symbols.h>
#include <mod_math_symbols.h>
#include <mod_time_symbols.h>
#include <mod_file_symbols.h>
#ifndef NO_MODSOUND
#include <mod_sound_symbols.h>
#endif
#include <mod_proc_symbols.h>
#include <mod_sort_symbols.h>
#include <mod_timers_symbols.h>
#ifndef NO_MODREGEX
#include <mod_regex_symbols.h>
#endif
#include <libgrbase_symbols.h>
#include <libblit_symbols.h>
#include <libvideo_symbols.h>
#include <librender_symbols.h>
#include <mod_gamecontroller_symbols.h>
#include <libjoy_symbols.h>
#include <mod_joy_symbols.h>
#include <mod_video_symbols.h>
#include <libmouse_symbols.h>
#include <mod_mouse_symbols.h>
#include <mod_map_symbols.h>
#include <libfont_symbols.h>
#include <mod_dir_symbols.h>
#include <libtext_symbols.h>
#include <mod_text_symbols.h>
#include <mod_rand_symbols.h>
#include <mod_grproc_symbols.h>
#include <libscroll_symbols.h>
#include <mod_scroll_symbols.h>
#include <libkey_symbols.h>
#include <mod_key_symbols.h>
#include <mod_draw_symbols.h>
#include <mod_screen_symbols.h>
#include <mod_path_symbols.h>
#include <libwm_symbols.h>
#include <mod_wm_symbols.h>
#include <mod_sys_symbols.h>

#ifndef NO_MODSHADER
#   include <mod_shader_symbols.h>
#endif

#ifndef NO_MODMEM
#  include <mod_mem_symbols.h>
#endif
#ifndef NO_MODDEBUG
#   include <mod_debug_symbols.h>
#endif
#ifndef NO_MODEFFECTS
#   include <mod_effects_symbols.h>
#endif
/* Unofficial modules */
#ifndef NO_MODICONV
#   include <iconv_symbols.h>
#endif
#ifndef NO_MODCHIPMUNK
#   include <mod_chipmunk_symbols.h>
#endif
#ifndef NO_MODMULTI
#include <mod_multi_symbols.h>
#endif
#ifndef NO_MODCURL
#   include <mod_curl_symbols.h>
#endif
#ifndef NO_MODFSOCK
#include <mod_fsock_symbols.h>
#endif
#ifndef NO_MODTHEORA
#include <mod_theora_symbols.h>
#endif
#ifndef NO_MODSTEAM
#include <mod_steam_symbols.h>
#endif
#ifndef NO_MODNSWITCH
#include <mod_nswitch_symbols.h>
#endif

typedef struct
{
    char       * module_name;
    void       * module_dependencies;
    void       * constants_def;
    void       * types_def;
    void       * globals_def;
    void       * locals_def;
    void       * exported_functions;
} basic_symbols ;

#ifndef __PXTB__
typedef struct
{
    void          * globals_fixup;
    void          * locals_fixup;
    FN_HOOK         module_initialize;
    FN_HOOK         module_finalize;
    INSTANCE_HOOK   instance_create_hook;
    INSTANCE_HOOK   instance_destroy_hook;
    INSTANCE_HOOK   process_exec_hook;
    void          * handler_hooks;
} extra_symbols;
#endif

// Basic symbols used by the compiler and the runtime
basic_symbols symbol_list[] = {
    // Libs go first, modules later
    // name              , deps, constants, types, globals, locals, func_exp
    { "libsdlhandler.fakelib", NULL, NULL, NULL, NULL, NULL, NULL },
    { "mod_gamecontroller.fakelib" , NULL, mod_gamecontroller_constants_def, NULL, NULL, NULL, mod_gamecontroller_exported_functions },
    { "libjoy.fakelib"       , libjoy_module_dependencies, libjoy_constants_def, NULL, NULL, NULL, NULL },
    { "mod_joy.fakelib"      , mod_joy_module_dependencies, NULL, NULL, NULL, NULL, mod_joy_exported_functions },
    { "libgrbase.fakelib"    , NULL, NULL, NULL, libgrbase_globals_def, NULL, NULL },
    { "libblit.fakelib"      , NULL, libblit_constants_def, NULL, NULL, NULL, NULL },
    { "libvideo.fakelib"     , libvideo_module_dependencies, libvideo_constants_def, NULL, libvideo_globals_def, NULL, NULL },
    { "librender.fakelib"    , librender_module_dependencies, librender_constants_def, NULL, librender_globals_def, librender_locals_def, NULL },
    { "libmouse.fakelib"     , libmouse_module_dependencies, NULL, NULL, libmouse_globals_def, NULL, NULL },
    { "libfont.fakelib"      , libfont_module_dependencies, NULL, NULL, NULL, NULL, NULL },
    { "libtext.fakelib"      , libtext_module_dependencies, NULL, NULL, libtext_globals_def, NULL, NULL },
    { "libscroll.fakelib"    , libscroll_module_dependencies, libscroll_constants_def, NULL, libscroll_globals_def, libscroll_locals_def, NULL },
    { "libkey.fakelib"       , libkey_module_dependencies, libkey_constants_def, NULL, libkey_globals_def, NULL, NULL},
    { "libdraw.fakelib"      , NULL, NULL, NULL, NULL, NULL, NULL },
    { "libwm.fakelib"        , libwm_module_dependencies, NULL, NULL, libwm_globals_def, NULL, NULL },
    { "mod_say.fakelib"      , NULL, NULL, NULL, NULL, NULL, mod_say_exported_functions },
    { "mod_string.fakelib"   , NULL, NULL, NULL, NULL, NULL, mod_string_exported_functions },
    { "mod_math.fakelib"     , NULL, mod_math_constants_def, NULL, NULL, NULL, mod_math_exported_functions },
    { "mod_time.fakelib"     , NULL, NULL, NULL, NULL, NULL, mod_time_exported_functions },
    { "mod_file.fakelib"     , NULL, mod_file_constants_def, NULL, NULL, NULL, mod_file_exported_functions },
#ifndef NO_MODSOUND
    { "mod_sound.fakelib"    , NULL, mod_sound_constants_def, NULL, mod_sound_globals_def, NULL, mod_sound_exported_functions },
#endif
    { "mod_proc.fakelib"     , NULL, mod_proc_constants_def, NULL, NULL, mod_proc_locals_def, mod_proc_exported_functions },
    { "mod_sort.fakelib"     , NULL, NULL, NULL, NULL, NULL, mod_sort_exported_functions },
    { "mod_timers.fakelib"   , NULL, NULL, NULL, mod_timers_globals_def, NULL, NULL },
#ifndef NO_MODREGEX
    { "mod_regex.fakelib"    , NULL, NULL, NULL, mod_regex_globals_def, NULL, mod_regex_exported_functions },
#endif
    { "mod_video.fakelib"    , mod_video_module_dependencies, NULL, NULL, NULL, NULL, mod_video_exported_functions },
    { "mod_mouse.fakelib"    , mod_mouse_module_dependencies, NULL, NULL, NULL, NULL, NULL },
    { "mod_map.fakelib"      , mod_map_module_dependencies, mod_map_constants_def, NULL, NULL, NULL, mod_map_exported_functions },
    { "mod_dir.fakelib"      , NULL, NULL, NULL, mod_dir_globals_def, NULL, mod_dir_exported_functions },
    { "mod_text.fakelib"     , mod_text_module_dependencies, mod_text_constants_def, NULL, NULL, NULL, mod_text_exported_functions },
    { "mod_rand.fakelib"     , NULL, NULL, NULL, NULL, NULL, mod_rand_exported_functions },
    { "mod_grproc.fakelib"   , mod_grproc_module_dependencies, NULL, NULL, NULL, mod_grproc_locals_def, mod_grproc_exported_functions },
    { "mod_scroll.fakelib"   , mod_scroll_module_dependencies, NULL, NULL, NULL, NULL, mod_scroll_exported_functions },
    { "mod_key.fakelib"      , mod_key_module_dependencies, NULL, NULL, NULL, NULL, mod_key_exported_functions },
    { "mod_draw.fakelib"     , mod_draw_module_dependencies, NULL, NULL, NULL, NULL, mod_draw_exported_functions },
    { "mod_screen.fakelib"   , mod_screen_module_dependencies, NULL, NULL, NULL, NULL, mod_screen_exported_functions },
    { "mod_path.fakelib"     , mod_path_module_dependencies, mod_path_constants_def, NULL, NULL, NULL, mod_path_exported_functions },
    { "mod_wm.fakelib"       , mod_wm_module_dependencies, mod_wm_constants_def, NULL, NULL, NULL, mod_wm_exported_functions },
    { "mod_sys.fakelib"      , NULL, mod_sys_constants_def, NULL, NULL, NULL, mod_sys_exported_functions },
#ifndef NO_MODSHADER
    { "mod_shader.fakelib"   , NULL, NULL, NULL, NULL, NULL, mod_shader_exported_functions },
#endif
#ifndef NO_MODMEM
    { "mod_mem.fakelib"      , NULL, NULL, NULL, NULL, NULL, mod_mem_exported_functions },
#endif
#ifndef NO_MODDEBUG
    { "mod_debug.fakelib"    , mod_debug_module_dependencies, NULL, NULL, NULL, NULL, NULL },
#endif
#ifndef NO_MODEFFECTS
    { "mod_effects.fakelib"  , mod_effects_module_dependencies, mod_effects_constants_def, NULL, NULL, NULL, mod_effects_exported_functions },
#endif
    /* Unofficial modules */
#ifndef NO_MODICONV
    { "mod_iconv.fakelib"    , NULL, NULL, NULL, NULL, NULL, mod_iconv_exported_functions },
#endif
#ifndef NO_MODCHIPMUNK
    { "mod_chipmunk.fakelib" , mod_chipmunk_module_dependencies, mod_chipmunk_constants_def, mod_chipmunk_types_def, mod_chipmunk_globals_def, mod_chipmunk_locals_def, mod_chipmunk_exported_functions },
#endif
#ifndef NO_MODMULTI
    { "mod_multi.fakelib"    , mod_multi_module_dependencies, mod_multi_constants_def, NULL, NULL, NULL, mod_multi_exported_functions },
#endif
#ifndef NO_MODCURL
    { "mod_curl.fakelib"     , NULL, mod_curl_constants_def, NULL, NULL, NULL, mod_curl_exported_functions },
#endif
#ifndef NO_MODSTEAM
    { "mod_steam.fakelib"    , mod_steam_module_dependencies, mod_steam_constants_def, NULL, mod_steam_globals_def, NULL, mod_steam_exported_functions },
#endif
#ifndef NO_MODNSWITCH
    { "mod_nswitch.fakelib"  , mod_nswitch_module_dependencies, mod_nswitch_constants_def, NULL, mod_nswitch_globals_def, NULL, mod_nswitch_exported_functions },
#endif
#ifndef NO_MODFSOCK
    { "mod_fsock.fakelib"    , NULL, NULL, NULL, NULL, NULL, mod_fsock_exported_functions },
#endif
#ifndef NO_MODTHEORA
    { "mod_theora.fakelib"   , mod_theora_module_dependencies, NULL, NULL, NULL, NULL, mod_theora_exported_functions },
#endif
    { NULL                   , NULL, NULL, NULL, NULL, NULL, NULL }
};

#ifndef __PXTB__
// Symbols only required by the runtime, ordered just as on symbol_list
// As a separate array to avoid compilation nightmares
extra_symbols symbol_list_runtime[] = {
    { NULL, NULL, libsdlhandler_module_initialize, libsdlhandler_module_finalize, NULL, NULL, NULL, libsdlhandler_handler_hooks },      //libsdlhandler
    { NULL, NULL, mod_gamecontroller_module_initialize, mod_gamecontroller_module_finalize, NULL, NULL, NULL, NULL }, //mod_gamecontroller
    { NULL, NULL, libjoy_module_initialize, libjoy_module_finalize, NULL, NULL, NULL, NULL }, //libjoy
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_joy
    { libgrbase_globals_fixup, NULL, libgrbase_module_initialize, NULL, NULL, NULL, NULL, NULL }, //libgrbase
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //libblit
    { libvideo_globals_fixup, NULL, libvideo_module_initialize, libvideo_module_finalize, NULL, NULL, NULL, NULL }, //libvideo
    { librender_globals_fixup, librender_locals_fixup, librender_module_initialize, librender_module_finalize, librender_instance_create_hook, librender_instance_destroy_hook, NULL, librender_handler_hooks }, //librender
    { libmouse_globals_fixup, NULL, libmouse_module_initialize, NULL, NULL, NULL, NULL, libmouse_handler_hooks}, //libmouse
    { NULL, NULL, libfont_module_initialize, NULL, NULL, NULL, NULL, NULL }, //libfont
    { libtext_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //libtext
    { libscroll_globals_fixup, libscroll_locals_fixup, NULL, NULL, NULL, NULL, NULL, NULL }, //libscroll
    { libkey_globals_fixup, NULL, libkey_module_initialize, libkey_module_finalize, NULL, NULL, NULL, libkey_handler_hooks }, //libkey
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //libdraw
    { libwm_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, libwm_handler_hooks }, //libwm
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_say
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_string
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_math
    { NULL, NULL, mod_time_module_initialize, mod_time_module_finalize, NULL, NULL, NULL, NULL }, //mod_time
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_file
#ifndef NO_MODSOUND
    { mod_sound_globals_fixup, NULL, mod_sound_module_initialize, mod_sound_module_finalize, NULL, NULL, NULL, NULL}, //mod_sound
#endif
    { NULL, mod_proc_locals_fixup, NULL, NULL, NULL, NULL, mod_proc_process_exec_hook, NULL}, //mod_proc
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_sort
    { mod_timers_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, mod_timers_handler_hooks }, //mod_timers
    #ifndef NO_MODREGEX
    { mod_regex_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_regex
    #endif
    { mod_video_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_video
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_mouse
    { NULL, NULL, NULL, mod_map_module_finalize, NULL, NULL, NULL, NULL }, //mod_map
    { mod_dir_globals_fixup, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_dir
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_text
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_rand
    { mod_grproc_globals_fixup, mod_grproc_locals_fixup, NULL, NULL, NULL, NULL, mod_grproc_process_exec_hook, NULL }, //mod_grproc
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_scroll
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_key
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_draw
    { mod_screen_globals_fixup, mod_screen_locals_fixup, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_screen
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_path
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_wm
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_sys
#ifndef NO_MODSHADER
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_shader
#endif
#ifndef NO_MODMEM
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_mem
#endif
#ifndef NO_MODDEBUG
    { mod_debug_globals_fixup, mod_debug_locals_fixup, mod_debug_module_initialize, mod_debug_module_finalize, NULL, NULL, mod_debug_process_exec_hook, NULL }, //mod_debug
#endif
#ifndef NO_MODEFFECTS
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //modeffects
#endif
    /* Unofficial modules */
#ifndef NO_MODICONV
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_iconv
#endif
#ifndef NO_MODCHIPMUNK
    { mod_chipmunk_globals_fixup, mod_chipmunk_locals_fixup, mod_chipmunk_module_initialize, mod_chipmunk_module_finalize, NULL, NULL, NULL, mod_chipmunk_handler_hooks }, //mod_chipmunk
#endif
#ifndef NO_MODMULTI
    { NULL, NULL, mod_multi_module_initialize, NULL, NULL, NULL, NULL, mod_multi_handler_hooks }, //mod_multi
#endif
#ifndef NO_MODCURL
    { NULL, NULL, mod_curl_module_initialize, mod_curl_module_finalize, NULL, NULL, NULL, NULL }, //mod_curl
#endif
#ifndef NO_MODSTEAM
    { mod_steam_globals_fixup, NULL, mod_steam_module_initialize, mod_steam_module_finalize, NULL, NULL, NULL, NULL }, //mod_steam
#endif
#ifndef NO_MODNSWITCH
    { mod_nswitch_globals_fixup, NULL, mod_nswitch_module_initialize, mod_nswitch_module_finalize, NULL, NULL, NULL, NULL }, //mod_nswitch
#endif
#ifndef NO_MODFSOCK
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }, //mod_fsock
#endif
#ifndef NO_MODTHEORA
    { NULL, NULL, mod_theora_module_initialize, mod_theora_module_finalize, NULL, NULL, NULL, mod_theora_handler_hooks }, //mod_theora
#endif
};
#endif

#endif
