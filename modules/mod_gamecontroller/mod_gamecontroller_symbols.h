/*
 *  Copyright (C) 2015 Joseba García Etxebarria <joseba.gar@gmail.com>
 *
 *  This file is part of PixTudio
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *     distribution.
 *
 */

#ifndef __MODGAMECONTROLLER_SYMBOLS_H
#define __MODGAMECONTROLLER_SYMBOLS_H

#include <SDL_gamecontroller.h>
#include <bgddl.h>
#include "mod_gamecontroller.h"

#ifndef __PXTB__
extern void  __bgdexport( mod_gamecontroller, module_initialize )();
extern void __bgdexport( mod_gamecontroller, module_finalize )();

extern int modgamecontroller_num( INSTANCE * my, int * params );
extern int modgamecontroller_open( INSTANCE * my, int * params );
extern int modgamecontroller_close( INSTANCE * my, int * params );
extern int modgamecontroller_getbutton( INSTANCE * my, int * params );
extern int modgamecontroller_getaxis( INSTANCE * my, int * params );
extern int modgamecontroller_getname( INSTANCE * my, int * params );
#endif

DLCONSTANT  __bgdexport( mod_gamecontroller, constants_def )[] = {
    { "CONTROLLER_INVALID"               , TYPE_DWORD, CONTROLLER_INVALID                  },
    { "CONTROLLER_BUTTON_INVALID"        , TYPE_DWORD, SDL_CONTROLLER_BUTTON_INVALID       },
    { "CONTROLLER_BUTTON_A"              , TYPE_DWORD, SDL_CONTROLLER_BUTTON_A             },
    { "CONTROLLER_BUTTON_B"              , TYPE_DWORD, SDL_CONTROLLER_BUTTON_B             },
    { "CONTROLLER_BUTTON_X"              , TYPE_DWORD, SDL_CONTROLLER_BUTTON_X             },
    { "CONTROLLER_BUTTON_Y"              , TYPE_DWORD, SDL_CONTROLLER_BUTTON_Y             },
    { "CONTROLLER_BUTTON_BACK"           , TYPE_DWORD, SDL_CONTROLLER_BUTTON_BACK          },
    { "CONTROLLER_BUTTON_GUIDE"          , TYPE_DWORD, SDL_CONTROLLER_BUTTON_GUIDE         },
    { "CONTROLLER_BUTTON_START"          , TYPE_DWORD, SDL_CONTROLLER_BUTTON_START         },
    { "CONTROLLER_BUTTON_LEFTSTICK"      , TYPE_DWORD, SDL_CONTROLLER_BUTTON_LEFTSTICK     },
    { "CONTROLLER_BUTTON_RIGHTSTICK"     , TYPE_DWORD, SDL_CONTROLLER_BUTTON_RIGHTSTICK    },
    { "CONTROLLER_BUTTON_LEFTSHOULDER"   , TYPE_DWORD, SDL_CONTROLLER_BUTTON_LEFTSHOULDER  },
    { "CONTROLLER_BUTTON_RIGHTSHOULDER"  , TYPE_DWORD, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER },
    { "CONTROLLER_BUTTON_DPAD_UP"        , TYPE_DWORD, SDL_CONTROLLER_BUTTON_DPAD_UP       },
    { "CONTROLLER_BUTTON_DPAD_DOWN"      , TYPE_DWORD, SDL_CONTROLLER_BUTTON_DPAD_DOWN     },
    { "CONTROLLER_BUTTON_DPAD_LEFT"      , TYPE_DWORD, SDL_CONTROLLER_BUTTON_DPAD_LEFT     },
    { "CONTROLLER_BUTTON_DPAD_RIGHT"     , TYPE_DWORD, SDL_CONTROLLER_BUTTON_DPAD_RIGHT    },
    { "CONTROLLER_BUTTON_MAX"            , TYPE_DWORD, SDL_CONTROLLER_BUTTON_MAX           },
    { "CONTROLLER_AXIS_INVALID"          , TYPE_DWORD, SDL_CONTROLLER_AXIS_INVALID         },
    { "CONTROLLER_AXIS_LEFTX"            , TYPE_DWORD, SDL_CONTROLLER_AXIS_LEFTX           },
    { "CONTROLLER_AXIS_LEFTY"            , TYPE_DWORD, SDL_CONTROLLER_AXIS_LEFTY           },
    { "CONTROLLER_AXIS_RIGHTX"           , TYPE_DWORD, SDL_CONTROLLER_AXIS_RIGHTX          },
    { "CONTROLLER_AXIS_RIGHTY"           , TYPE_DWORD, SDL_CONTROLLER_AXIS_RIGHTY          },
    { "CONTROLLER_AXIS_TRIGGERLEFT"      , TYPE_DWORD, SDL_CONTROLLER_AXIS_TRIGGERLEFT     },
    { "CONTROLLER_AXIS_TRIGGERRIGHT"     , TYPE_DWORD, SDL_CONTROLLER_AXIS_TRIGGERRIGHT    },
    { "CONTROLLER_AXIS_MAX"              , TYPE_DWORD, SDL_CONTROLLER_AXIS_MAX             },
    { NULL          , 0       , 0  }
};

DLSYSFUNCS  __bgdexport( mod_gamecontroller, exported_functions )[] = {
    FUNC( "CONTROLLER_NUM"       , ""      , TYPE_INT    , modgamecontroller_num       ),
    FUNC( "CONTROLLER_OPEN"      , "I"     , TYPE_INT    , modgamecontroller_open      ),
    FUNC( "CONTROLLER_CLOSE"     , "I"     , TYPE_INT    , modgamecontroller_close     ),
    FUNC( "CONTROLLER_GETBUTTON" , "II"    , TYPE_INT    , modgamecontroller_getbutton ),
    FUNC( "CONTROLLER_GETAXIS"   , "II"    , TYPE_INT    , modgamecontroller_getaxis   ),
    FUNC( "CONTROLLER_GETNAME"   , "I"     , TYPE_STRING , modgamecontroller_getname   ),
    { 0                     , 0       , 0           , 0 }
};

#endif
