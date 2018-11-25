zcc +zx -v -m -startup=31 -clib=sdcc_iy -SO3 --max-allocs-per-node200000 @zproject.lst -pragma-include:zpragma.inc -o misifu -lay/vt_sound_6.lib
dir *.bin
appmake +zx -b screen.scr --org 16384 --noloader --blockname screen -o screen.tap
appmake +zx -b misifu_CODE.bin --org 24500 --noloader --blockname code -o code.tap
appmake +zx -b misifu_BANK_6.bin --org 49152 --noloader --blockname bank6 -o bank6.tap
copy /b loader.tap + screen.tap + code.tap + bank6.tap misifu.tap
del *.bin zcc_opt.def screen.tap code.tap bank6.tap
@rem del zcc_opt.def screen.tap code.tap bank6.tap
