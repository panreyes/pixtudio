# Build instructions

* Install [Visual Studio Community 2015](https://www.visualstudio.com/en/vs/community/) with C++ development tools.
* Install [CMake](https://cmake.org/).
* Install [NASM](http://www.nasm.us/) Choose the 64 of 32 bit version, depending on your system (both should work fine).
* Open a command prompt at the PixTudio source code folder and ensure that CMake & NASM are available in your path.

##Compile zlib:
    cd 3rdparty/zlib-1.2.8
    md build
    cd build
    cmake -G"Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%cd%/../dist ..
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
    cd ..\..\..\

##Compile libpng
    cd 3rdparty\libpng-1.6.23
    md build
    cd build
    cmake -G"Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%cd%/../dist -DZLIB_ROOT=%cd%/../../zlib-1.2.8/dist ..
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
    cd ..\..\..\

##Compile libjpeg-turbo
    cd 3rdparty\libjpeg-turbo-1.5.1
    md build
    cd build
    cmake -G"Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%cd%/../dist ..
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
    cd ..\..\..\

##Compile FreeType
    cd 3rdparty\freetype-2.7
    md build
    cd build
    cmake -G"Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%cd%/../dist ..
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
    cd ..\..\..\

##Compile libcurl
    cd 3rdparty\curl-7.51.0
    md build
    cd build
    cmake -G"Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%cd%/../dist -DBUILD_TESTING=OFF -DBUILD_CURL_EXE=OFF -DCMAKE_STATICLIB=ON -DZLIB_ROOT=%cd%/../../zlib-1.2.8/dist ..
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
    cd ..\..\..\

##Compile libogg
    cd 3rdparty\SDL2_mixer\external\libogg-1.3.1\
    md build
    cd build
    cmake -G"Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%cd%/../dist ..
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
    cd ..\..\..\..\..\

##Compile libvorbis
    cd 3rdparty\SDL2_mixer\external\libvorbis-1.3.3
    md build
    cd build
    cmake -G"Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%cd%/../dist -DLIBOGG_PATH=%cd%/../../libogg-1.3.1 ..
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
    cd ..\..\..\..\..\

##Compile libtheora
    cd 3rdparty\libtheora-1.1.1
    md build
    cd build
    cmake -G"Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%cd%/../dist -DLIBOGG_PATH=%cd%/../../SDL2_mixer/external/libogg-1.3.1 ..
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
    cd ..\..\..\

##Compile libtre
    cd 3rdparty\tre
    md build
    cd build
    cmake -G"Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%cd%/../dist ..
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
    cd ..\..\..\

##Compile SDL2
    cd 3rdparty\SDL2
    md build
    cd build
    cmake -G"Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%cd%/../dist ..
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
    cd ..\..\..\

##Compile PXTB
    cd projects\cmake\pxtb
    md build
    cd build
    cmake -G"Visual Studio 14 2015" -DCMAKE_INSTALL_PREFIX=%cd%/../../ -DSDL2_PATH=%cd%/../../../../3rdparty/SDL2/dist -DZLIB_ROOT=%cd%/../../../../3rdparty/zlib-1.2.8/dist -DSTEAMWORKS_PATH=%cd%/../../../../3rdparty/steamworks ..
    cmake --build . --config Release
    cmake --build . --config Release --target INSTALL
    cd ..\..\bin\win32
    copy ..\..\..\..\3rdparty\zlib-1.2.8\dist\bin\zlib.dll .
    cd ..\..\..\..\
