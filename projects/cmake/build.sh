#!/bin/bash

# This function will try to copy the required dependencies for the
# binaries in the given directory.
function copy_dependencies {
    # We require two params:
    #   * the dir to install the dependencies into
    #   * the dir where we should be looking for deps
    NUMFILES=$(ls ${1}/* | wc -l)
    if [ "$OS" = "Msys" ]; then
        for i in "${1}/*"; do
            for DEP in $(objdump -p $i | grep "DLL Name" | cut -d ":" -f 2); do
                # Is the dependency in the given dir? => copy it if not present
                if [ -f "${2}/${DEP}" ]; then
                    if ! [ -f "${1}/${DEP}" ]; then
                        cp "${2}/${DEP}" "${1}"
                    fi
                fi
            done
        done
    elif [ "$OS" = "Darwin" ]; then
        # Here we should be doing pretty much the same thing as in Msys
        # but we should also be changing the dependency path to use
        # relative paths when looking for the dependencies
        echo "Darwin!"
    fi

    # If the number of files has changed, iterate again
    if [ ! "${NUMFILES}" = "$(ls ${1}/* | wc -l)" ]; then
        copy_dependencies ${1} ${2}
    fi
}

# Determine the OS
if [ $(uname) = "Darwin" ]; then
    OS=Darwin
else
    OS=$(uname -o)
fi

# If given an argument, interpret it as the build type
# Valid values are:
# Debug Release RelWithDebInfo MinSizeRel
# Otherwise compile with Debug configuration
BUILD_TYPE="Release"
if [ $# -eq 1 ]; then
    BUILD_TYPE=$1
fi

echo "Build type: ${BUILD_TYPE}"

# Set some variables we'll be using
EXTRACMAKEFLAGS=""
if [ "$OS" = "Msys" ]; then
    PROJECTTYPE="Ninja"
    EXT=".exe"
    BINDIR="bin/win32"
    BUILDTOOL="ninja"
    INSTALLTOOL="ninja install"
elif [ "$OS" = "GNU/Linux" ]; then
    PROJECTTYPE="Ninja"
    EXT=""
    BINDIR="bin/gnulinux32"
    if ! [ "$(type -p ninja)" = "" ]; then
        BUILDTOOL="ninja"
        INSTALLTOOL="ninja install"
    else
        BUILDTOOL="ninja-build"
        INSTALLTOOL="ninja-build install"
    fi

    if [ "$(lsb_release -is)" == "Ubuntu" ]; then
        EXTRACMAKEFLAGS="-DCMAKE_LIBRARY_PATH=/usr/lib/i386-linux-gnu"
    fi
    
    # -m32 seems to be only required in Linux x86_64
    if [ "`uname -m`" == "x86_64" ]; then
        EXTRACMAKEFLAGS="${EXTRACMAKEFLAGS} -DUSE_M32=1"
    fi
    
elif [ "$OS" = "Darwin" ]; then
    PROJECTTYPE="Ninja"
    EXT=""
    BINDIR="bin/osx32"
    BUILDTOOL="ninja"
    INSTALLTOOL="ninja install"
fi

# Compile PXTB and PXTP
dont_install=0
for PROJECT in pxtb pxtp; do
    echo "Making ${PROJECT}"
    rm -rf ${PROJECT}_build
    mkdir ${PROJECT}_build
    cd ${PROJECT}_build
    cmake -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" ${EXTRACMAKEFLAGS} -G "${PROJECTTYPE}" -DSTEAMWORKS_PATH=$(pwd)/../../../3rdparty/steamworks -DEPICSDK_PATH=$(pwd)/../../../3rdparty/epicsdk -DTMX_PATH=$(pwd)/../../../3rdparty/libtmx -DXML2_PATH=$(pwd)/../../../3rdparty/libxml2 -DCMAKE_INSTALL_PREFIX=$(pwd)/../ ../${PROJECT}
    $BUILDTOOL 
    if [ $? -eq 0 ]; then
        $INSTALLTOOL
    else
        dont_install=1
        echo "Could not compile $PROJECT"
        continue
    fi
    cd ..
done

# Copy binaries to a common "bin" folder
if [ $dont_install -eq 0 ]; then
    if ! [ -d ${BINDIR} ]; then
        mkdir -p ${BINDIR}
    fi
    cp pxtb_build/pxtb${EXT} ${BINDIR}
    cp pxtp_build/pxtp${EXT} ${BINDIR}

    # Copy dependencies to the bin dir (for Windows/OS X)
    # However, we could do better:
    # We can download SDL2 & SDL_mixer from their sites, and use their binaries
    # which include far less deps
    if [ "$OS" = "Msys" ] || [ "$OS" = "Darwin" ]; then
        if ! [ "${BUILD_TYPE}" = "Debug" ]; then
            copy_dependencies ${BINDIR} /mingw32/bin/
        fi
    fi
fi
