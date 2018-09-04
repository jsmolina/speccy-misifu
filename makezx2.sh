#!/usr/bin/env bash
# todo https://github.com/reidrac/png2sprite
# todo http://www.mojontwins.com/mojoniaplus/viewtopic.php?t=1976
# todo https://www.z88dk.org/wiki/doku.php?id=libnew:examples:sp1_ex1
# todo https://www.z88dk.org/forum/viewtopic.php?id=10277
# png2sp1sprite ./sprites/cat_sprites.png -i sprite_protar -f 32 > protar.asm
#png2sp1sprite ./sprites/cat_sprites.png -i sprite_protar -f 32 > protar.asm
# png2udg ./background/cubotop1.png
zcc +zx -vn -m -startup=31 -clib=sdcc_iy juegozx2.c protar.asm -o juegozx2 -create-app

rm -f juegozx2.bin
rm -f juegozx2_CODE.bin
rm -f juegozx2.map
rm -f juegozx2

rm -f zcc_opt.def
rm -f zcc_proj.lst

