#!/bin/sh
# set -e
zcc +zx -v -m -startup=31 -clib=sdcc_iy -SO3 --opt-code-size --max-allocs-per-node200000 @zproject.lst -pragma-include:zpragma.inc -o misifu -lay/vt_sound_6.lib
ls *.bin
z88dk-appmake +zx -b screen.scr --org 16384 --noloader --blockname screen -o screen.tap
z88dk-appmake +zx -b misifu_CODE.bin --org 24500 --noloader --blockname code -o code.tap
z88dk-appmake +zx -b misifu_BANK_6.bin --org 49152 --noloader --blockname bank6 -o bank6.tap
touch misifu.tap
rm misifu.tap
mkdir -p out
cat loader.tap screen.tap code.tap bank6.tap > misifu.tap
cp misifu.tap ./out
cp misifu.map ./out
#rm *.bin zcc_opt.def screen.tap code.tap bank6.tap
# del zcc_opt.def screen.tap code.tap bank6.tap
