if(NOT NO_MODCHIPMUNK)
    if(C_PXTRTM)
      list(APPEND SOURCE_FILES
           ${PXT_MODULES_PATH}/mod_chipmunk/mod_chipmunk_symbols.h
           ${PXT_MODULES_PATH}/mod_chipmunk/main.c
           ${PXT_MODULES_PATH}/mod_chipmunk/Arreglos.c
           ${PXT_MODULES_PATH}/mod_chipmunk/Miscelanea.c
           ${PXT_MODULES_PATH}/mod_chipmunk/Cuerpo.c
           ${PXT_MODULES_PATH}/mod_chipmunk/LL.c
           ${PXT_MODULES_PATH}/mod_chipmunk/Handlers.c
           ${PXT_MODULES_PATH}/mod_chipmunk/Constraints.c
           ${PXT_MODULES_PATH}/mod_chipmunk/arbitros.c
           ${PXT_MODULES_PATH}/mod_chipmunk/Espacio.c
           ${PXT_MODULES_PATH}/mod_chipmunk/automGenTerr.c
           ${PXT_MODULES_PATH}/mod_chipmunk/agua.c
           ${PXT_MODULES_PATH}/mod_chipmunk/convexHull.c)
    endif(C_PXTRTM)
    
    include_directories(${PXT_MODULES_PATH}/mod_chipmunk/
                        ${CHIPMUNK_INCLUDE_DIR})
endif(NOT NO_MODCHIPMUNK)

if(NOT NO_MODICONV)
    if(C_PXTRTM)
    endif(C_PXTRTM)
endif(NOT NO_MODICONV)

if(NOT NO_MODSTEAM)
    if(C_PXTRTM)
      list(APPEND SOURCE_FILES
           ${PXT_MODULES_PATH}/mod_steam/mod_steam.cpp
           ${PXT_MODULES_PATH}/mod_steam/mod_steam.h
           ${PXT_MODULES_PATH}/mod_steam/mod_steam_symbols.h)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/mod_steam/
                        ${STEAMWORKS_INCLUDE_DIR})
endif(NOT NO_MODSTEAM)

if(NOT NO_MODEPIC)
    if(C_PXTRTM)
      list(APPEND SOURCE_FILES
           ${PXT_MODULES_PATH}/mod_epic/mod_epic.cpp
           ${PXT_MODULES_PATH}/mod_epic/mod_epic.h
           ${PXT_MODULES_PATH}/mod_epic/mod_epic_symbols.h)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/mod_epic/
                        ${EPICSDK_INCLUDE_DIR})
endif(NOT NO_MODEPIC)


if(NOT NO_MODCURL)
    if(C_PXTRTM)
      list(APPEND SOURCE_FILES
           ${PXT_MODULES_PATH}/mod_curl/mod_curl_symbols.h
           ${PXT_MODULES_PATH}/mod_curl/mod_curl.c)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/mod_curl/
                      ${CURL_INCLUDE_DIR})
endif(NOT NO_MODCURL)

if(NOT NO_MODMEM)
    if(C_PXTRTM)
      list(APPEND SOURCE_FILES
        ${PXT_MODULES_PATH}/mod_mem/mod_mem.c
        ${PXT_MODULES_PATH}/mod_mem/mod_mem_symbols.h)
    endif(C_PXTRTM)
endif(NOT NO_MODMEM)

if(NOT NO_MODFSOCK)
    if(C_PXTRTM)
      list(APPEND SOURCE_FILES
        ${PXT_MODULES_PATH}/mod_fsock/mod_fsock.c
        ${PXT_MODULES_PATH}/mod_fsock/mod_fsock_symbols.h
        ${PXT_MODULES_PATH}/libsocket/libsocket.c
        ${PXT_MODULES_PATH}/libsocket/libsocket.h)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/libsocket/                    
                      ${PXT_MODULES_PATH}/mod_fsock/)
endif(NOT NO_MODFSOCK)

if(NOT NO_MODMULTI)
    if(C_PXTRTM)
      list(APPEND SOURCE_FILES
        ${PXT_MODULES_PATH}/mod_multi/mod_multi.c
        ${PXT_MODULES_PATH}/mod_multi/mod_multi.h
        ${PXT_MODULES_PATH}/mod_multi/mod_multi_symbols.h)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/mod_multi/)
endif(NOT NO_MODMULTI)

if(NOT NO_MODDEBUG)
    if(C_PXTRTM)
      list(APPEND SOURCE_FILES
        ${PXT_MODULES_PATH}/mod_debug/mod_debug.c
        ${PXT_MODULES_PATH}/mod_debug/mod_debug_symbols.h)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/mod_debug/)
endif(NOT NO_MODDEBUG)

if(NOT NO_MODTHEORA)
    if(C_PXTRTM)
      list(APPEND SOURCE_FILES
        ${PXT_MODULES_PATH}/mod_theora/mod_theora.c
        ${PXT_MODULES_PATH}/mod_theora/mod_theora_symbols.h
        ${PXT_3RDPARTY}/theoraplay/theoraplay.c)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/mod_theora/
                      ${PXT_3RDPARTY}/theoraplay/
                      ${THEORA_INCLUDE_DIR})
endif(NOT NO_MODTHEORA)

if(NOT NO_MODEFFECTS)
    if(C_PXTRTM)
      list(APPEND SOURCE_FILES
        ${PXT_MODULES_PATH}/mod_effects/mod_effects.c
        ${PXT_MODULES_PATH}/mod_effects/mod_effects.h
        ${PXT_MODULES_PATH}/mod_effects/mod_effects_symbols.h)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/mod_effects/)
endif(NOT NO_MODEFFECTS)

if(NOT NO_MODREGEX)
    if(C_PXTRTM)
      list(APPEND SOURCE_FILES
        ${PXT_MODULES_PATH}/mod_regex/mod_regex.c
        ${PXT_MODULES_PATH}/mod_regex/mod_regex_symbols.h)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/mod_regex/
                        ${TRE_INCLUDE_DIR})
endif(NOT NO_MODREGEX)

if(NOT NO_MODSQLITE)
    if(C_PXTRTM)
        list(APPEND SOURCE_FILES
            ${PXT_MODULES_PATH}/mod_sqlite3/mod_sqlite3_symbols.h)
    endif(C_PXTRTM)
endif(NOT NO_MODSQLITE)

if(NOT NO_MODNSWITCH)
    if(C_PXTRTM)
        list(APPEND SOURCE_FILES
            ${PXT_MODULES_PATH}/mod_nswitch/mod_nswitch.cpp
            ${PXT_MODULES_PATH}/mod_nswitch/mod_nswitch_symbols.h)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/mod_nswitch/)
endif(NOT NO_MODNSWITCH)

if(NOT NO_MODSHADER)
    if(C_PXTRTM)
        list(APPEND SOURCE_FILES
            ${PXT_MODULES_PATH}/mod_shader/mod_shader.c
            ${PXT_MODULES_PATH}/mod_shader/mod_shader_symbols.h)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/mod_shader/)
endif(NOT NO_MODSHADER)

if(NOT NO_MODTMX)
    if(C_PXTRTM)
        list(APPEND SOURCE_FILES
            ${PXT_MODULES_PATH}/mod_tmx/mod_tmx.c
			${PXT_MODULES_PATH}/mod_tmx/mod_tmx.h
            ${PXT_MODULES_PATH}/mod_tmx/mod_tmx_symbols.h)
    endif(C_PXTRTM)
    include_directories(${PXT_MODULES_PATH}/mod_tmx/
						${TMX_INCLUDE_DIR})
endif(NOT NO_MODTMX)