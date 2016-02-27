#!/bin/sh
make ARCH=arm64 clean
make ARCH=arm64 -j8
cp nx_vpu.ko ../../../../../hardware/samsung_slsi/slsiap/prebuilt/modules/
