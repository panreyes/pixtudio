if(NOT NO_MODCHIPMUNK)
	if(C_PXTRTM)
	  list(APPEND SOURCE_FILES
		${PXT_MODULES_PATH}/mod_chipmunk/agua.h
		${PXT_MODULES_PATH}/mod_chipmunk/arbitros.h
		${PXT_MODULES_PATH}/mod_chipmunk/Arreglos.h
		${PXT_MODULES_PATH}/mod_chipmunk/automGenTerr.h
		${PXT_MODULES_PATH}/mod_chipmunk/constantes.h
		${PXT_MODULES_PATH}/mod_chipmunk/Constraints.h
		${PXT_MODULES_PATH}/mod_chipmunk/convexHull.h
		${PXT_MODULES_PATH}/mod_chipmunk/Cuerpo.h
		${PXT_MODULES_PATH}/mod_chipmunk/Espacio.h
		${PXT_MODULES_PATH}/mod_chipmunk/estructuras.h
		${PXT_MODULES_PATH}/mod_chipmunk/globales.h
		${PXT_MODULES_PATH}/mod_chipmunk/Handlers.h
		${PXT_MODULES_PATH}/mod_chipmunk/inl.h
		${PXT_MODULES_PATH}/mod_chipmunk/LL.h
		${PXT_MODULES_PATH}/mod_chipmunk/locales.h
		${PXT_MODULES_PATH}/mod_chipmunk/Miscelanea.h
		${PXT_MODULES_PATH}/mod_chipmunk/mod_chipmunk_symbols.h)
	endif(C_PXTRTM)
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
					  ${THEORA_INCLUDE_DIR}
					  ${OPENAL_INCLUDE_DIR}
					  ${VORBIS_INCLUDE_DIR})
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
