#!/usr/bin/env bash
zcc +zx -vn juegozx.c -o juegozx.bin -lndos -zorg=24200 -create-app

rm -f juegozx.bin
rm -f zcc_opt.def

