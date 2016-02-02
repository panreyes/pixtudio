#!/bin/bash

# Does not work on OS X
OS=$(uname -o)

# Set some variables we'll be using
if [ "$OS" = "Msys" ]; then
	PROJECTTYPE="MSYS Makefiles"
	EXT=".exe"
    BINDIR="bin/win32"
elif [ "$OS" = "GNU/Linux" ]; then
    PROJECTTYPE="Unix Makefiles"
    EXT=""
    BINDIR="bin/gnulinux32"
fi

# Compile PXTB and PXTP
for PROJECT in pxtb pxtp; do
    echo "Making ${PROJECT}"
    rm -rf ${PROJECT}_build
    mkdir ${PROJECT}_build
    cd ${PROJECT}_build
    cmake -G "${PROJECTTYPE}" ../${PROJECT}
    make
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
    for EXTRADLL in libbz2-1 libFLAC-8 libfluidsynth-1 libfreetype-6 libgcc_s_dw2-1 libglib-2.0-0 libharfbuzz-0 libiconv-2 libintl-8 libmad-0 libmodplug-1 libogg-0 libopenal-1 libpng16-16 libportaudio-2 libsndfile-1 libspeex-1 libstdc++-6 libtheora-0 libtre-5 libvorbis-0 libvorbisenc-2 libvorbisfile-3 libwinpthread-1 SDL2 SDL2_mixer zlib1; do
        cp /mingw32/bin/${EXTRADLL}.dll ${BINDIR}
    done
fi
