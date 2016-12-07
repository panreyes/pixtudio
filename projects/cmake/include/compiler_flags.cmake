# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_C_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_C_COMPILER_ID} MATCHES "Clang" OR
    ${CMAKE_C_COMPILER_ID} MATCHES "AppleClang")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -Wshadow -fno-strict-aliasing")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG} -g")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE} -O2")
        set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
elseif (${CMAKE_C_COMPILER_ID} MATCHES "MSVC")
        if (CMAKE_C_FLAGS MATCHES "/W[0-4]")
                string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
        else()
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
        endif()
endif()
