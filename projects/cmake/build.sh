#!/bin/bash

if [ $(uname) = "Darwin" ]; then
    OS=Darwin
else
    OS=$(uname -o)
fi

BUILD_TYPE="Debug"
if [ $# -eq 1 ]; then
    # If given an argument, interpret it as the build type
    # Valid values are:
    # Debug Release RelWithDebInfo MinSizeRel
    BUILD_TYPE=$1
fi

echo "Build type: ${BUILD_TYPE}"

# Set some variables we'll be using
if [ "$OS" = "Msys" ]; then
	PROJECTTYPE="Ninja"
	EXT=".exe"
    BINDIR="bin/win32"
    BUILDTOOL="ninja"
elif [ "$OS" = "GNU/Linux" ]; then
    PROJECTTYPE="Unix Makefiles"
    EXT=""
    BINDIR="bin/gnulinux32"
    BUILDTOOL="make"
elif [ "$OS" = "Darwin" ]; then
    PROJECTTYPE="Ninja"
    EXT=""
    BINDIR="bin/osx32"
    BUILDTOOL="ninja"
fi

# Compile PXTB and PXTP
for PROJECT in pxtb pxtp; do
    echo "Making ${PROJECT}"
    rm -rf ${PROJECT}_build
    mkdir ${PROJECT}_build
    cd ${PROJECT}_build
    cmake -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" -G "${PROJECTTYPE}" ../${PROJECT}
    $BUILDTOOL
    cd ..
done

# Copy binaries to a common "bin" folder
if ! [ -d ${BINDIR} ]; then
    mkdir -p ${BINDIR}
fi
cp pxtb_build/pxtb${EXT} ${BINDIR}
cp pxtp_build/pxtp${EXT} ${BINDIR}

# Copy dependencies to the bin dir (for Windows)
# However, we can do better:
# We can download SDL2 & SDL_mixer from their sites, and use their binaries
# which include far less deps
# Dependency inspection in MSYS:
# for i in *; do echo $i;objdump -p $i | grep DLL; done
if [ "$OS" = "Msys" ]; then
    for EXTRADLL in libbz2-1 libFLAC-8 libfluidsynth-1 libfreetype-6 libgcc_s_dw2-1 libglib-2.0-0 libharfbuzz-0 libiconv-2 libintl-8 libmad-0 libmodplug-1 libogg-0 libopenal-1 libpng16-16 libportaudio-2 libsndfile-1 libspeex-1 libstdc++-6 libtheora-0 libtre-5 libvorbis-0 libvorbisenc-2 libvorbisfile-3 libwinpthread-1 SDL2 SDL2_mixer zlib1 libcurl-4 libidn-11 libeay32 librtmp-1 libssh2-1 ssleay32 libgnutls-30 libhogweed-4-1 libgmp-10 libnettle-6-1 libp11-kit-0 libffi-6 libtasn1-6; do
        cp /mingw32/bin/${EXTRADLL}.dll ${BINDIR}
    done
fi
