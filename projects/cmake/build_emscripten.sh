#!/bin/bash
export EMCC_CFLAGS="-v --emit-symbol-map -g2 -s ALLOW_MEMORY_GROWTH=1 -s FORCE_FILESYSTEM=1 -s USE_FREETYPE=1 -s USE_VORBIS=1 -s USE_LIBJPEG=1 -s USE_LIBPNG=1 -s USE_ZLIB=1 -s USE_OGG=1 -s USE_SDL=2 -s USE_SDL_MIXER=2"
rm -rf pxtp_build
mkdir -p pxtp_build
cd pxtp_build
emcmake cmake ../pxtp
emmake make