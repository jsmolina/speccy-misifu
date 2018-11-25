#!/usr/bin/env bash
# set SO3
zcc +zx -v -m -startup=31 -clib=sdcc_iy -O3 --max-allocs-per-node200000 @zproject.lst -pragma-include:zpragma.inc -o misifu -lay/vt_sound_6.lib
ls *.bin
appmake +zx -b screen.scr --org 16384 --noloader --blockname screen -o screen.tap
appmake +zx -b misifu_CODE.bin --org 24500 --noloader --blockname code -o code.tap
appmake +zx -b misifu_BANK_6.bin --org 49152 --noloader --blockname bank6 -o bank6.tap

rm misifu.tap
cat loader.tap screen.tap code.tap bank6.tap > misifu.tap

#rm *.bin zcc_opt.def screen.tap code.tap bank6.tap
# del zcc_opt.def screen.tap code.tap bank6.tap
