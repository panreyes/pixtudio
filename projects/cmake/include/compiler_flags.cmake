# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_C_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_C_COMPILER_ID} MATCHES "Clang" OR
    ${CMAKE_C_COMPILER_ID} MATCHES "AppleClang")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -Wshadow -fno-strict-aliasing")
        if(WIN32)
                set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va")
        endif()
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG} -g")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE} -O2")
elseif (MSVC)
        # The following flags disable warnings that suggest to use MSVC-specific functions
        set(CMAKE_C_FLAGS "/wd4996 ${CMAKE_C_FLAGS}" CACHE STRING "" FORCE)
        if (CMAKE_C_FLAGS MATCHES "/W[0-4]")
                string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        else()
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
        endif()
endif()
