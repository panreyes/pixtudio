#!/bin/bash
rm -rf pxtp_build
mkdir -p pxtp_build
cd pxtp_build
cmake -D__PSP_VITA__=1 ../pxtp
make