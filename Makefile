compile:
	zcc +zx -vn -m -startup=31 -clib=sdcc_iy misifu.c protar.asm -o misifu -create-app
	rm -f misifu.bin
	rm -f misifu_CODE.bin
	rm -f misifu.map
	rm -f misifu
	rm -f zcc_opt.def
	rm -f zcc_proj.lst


sprites:
	png2sp1sprite ./sprites/cat_sprites.png -i sprite_protar -f 32 > protar.asm

udg:
	png2udg ./background/udg_valla1.png
	png2udg ./background/udg_valla2.png
	png2udg ./background/udg_valla3.png
	png2udg ./background/cubo_down1.png
	png2udg ./background/cubo_down2.png
	png2udg ./background/cubo_down3.png
	png2udg ./background/cubo_middle1.png
	png2udg ./background/cubo_middle2.png
	png2udg ./background/cubo_middle3.png
	png2udg ./background/cubotop1.png
	png2udg ./background/cubotop2.png
	png2udg ./background/cubotop3.png
