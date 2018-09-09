compile:
	zcc +zx -vn -m -startup=31 -clib=sdcc_iy misifu.c protar.asm dogr.asm bincat.asm funcs.asm clothes.asm clothes2.asm -o misifu -create-app
	rm -f misifu.bin
	rm -f misifu_CODE.bin
	rm -f misifu.map
	rm -f misifu
	rm -f zcc_opt.def
	rm -f zcc_proj.lst


sprites:
	png2sp1sprite ./sprites/cat_sprites.png -i sprite_protar -f 32 > protar.asm

dogsprites:
	png2sp1sprite ./sprites/dog_sprites.png -i sprite_dog -f 32 > dogr.asm

bincat:
	png2sp1sprite ./sprites/bincat_sprites.png -i sprite_bincat -f 24 > bincat.asm

clothes:
	png2sp1sprite ./sprites/clothes_sprites.png -i sprite_clothes > clothes.asm
	png2sp1sprite ./sprites/clothes_sprites2.png -i sprite_clothes > clothes2.asm


udg:
	echo "Copy the vars to misifu.c code"
	png2udg ./background/udg_valla1.png
	png2udg ./background/udg_valla2.png
	png2udg ./background/udg_valla3.png
	png2udg ./background/udg_valla4.png
	png2udg ./background/cubo_down1.png
	png2udg ./background/cubo_down2.png
	png2udg ./background/cubo_down3.png
	png2udg ./background/cubo_middle1.png
	png2udg ./background/cubo_middle2.png
	png2udg ./background/cubo_middle3.png
	png2udg ./background/cubotop1.png
	png2udg ./background/cubotop2.png
	png2udg ./background/cubotop3.png
	png2udg ./background/udg_c.png
	png2udg ./background/udg_a.png
	png2udg ./background/udg_t.png
	png2udg ./background/udg_rope.png
	png2udg ./background/udg_win1.png
	png2udg ./background/udg_win2.png
	png2udg ./background/udg_win3.png
