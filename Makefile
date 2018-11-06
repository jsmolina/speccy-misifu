VT_SOUND_LIB_SDCC_IY := ./ay

compile:
	zcc +zx -v -startup=31 -DWFRAMES=3 -clib=sdcc_iy -Cz--screen=screen.scr -SO3 --max-allocs-per-node200000 @zproject.lst -pragma-include:zpragma.inc -o misifu -L$(VT_SOUND_LIB_SDCC_IY) -lvt_sound -create-app
	echo "Done"

develop:
	zcc +zx -v -clib=sdcc_iy -Cz--screen=screen.scr -startup=31 -DWFRAMES=3 -O3 @zproject.lst -o misifu -pragma-include:zpragma.inc -L$(VT_SOUND_LIB_SDCC_IY) -lvt_sound -create-app
	echo "Done"

sprites: prota dogsprites bincat clothes auxiliar

prota:
	png2sp1sprite ./sprites/cat_sprites.png -i sprite_protar -f 32 > ./build/protar.asm

dogsprites:
	png2sp1sprite ./sprites/dog_sprites.png -i sprite_dog -f 32 > ./build/dogr.asm

bincat:
	png2sp1sprite ./sprites/bincat_sprites.png --bit -i sprite_bincat > ./build/bincat.asm

clothes:
	png2sp1sprite ./sprites/clothes_sprites.png --bit -i sprite_clothes  -f 64 > ./build/clothes.asm
	png2sp1sprite ./sprites/clothes_sprites2.png --bit -i sprite_clothes2 -f 40 > ./build/clothes2.asm

auxiliar:
	png2sp1sprite ./sprites/auxiliar.png --bit -i auxiliar -f 32 > ./build/auxiliar.asm

fence:
	@png2udg ./background/udg_valla1.png
	@png2udg ./background/udg_valla2.png
	@png2udg ./background/udg_valla3.png
	@png2udg ./background/udg_valla4.png
	@png2udg ./background/udg_c.png
	@png2udg ./background/udg_a.png
	@png2udg ./background/udg_t.png

cubo:
	@png2udg ./background/cubo_down1.png
	@png2udg ./background/cubo_down2.png
	@png2udg ./background/cubo_down3.png
	@png2udg ./background/cubo_middle1.png
	@png2udg ./background/cubo_middle2.png
	@png2udg ./background/cubo_middle3.png
	@png2udg ./background/cubotop1.png
	@png2udg ./background/cubotop2.png
	@png2udg ./background/cubotop3.png

windows:
	echo "Copy the vars to misifu.c code"
	@png2udg ./background/udg_rope.png
	@png2udg ./background/udg_win1.png
	@png2udg ./background/udg_win2.png
	@png2udg ./background/udg_win3.png

mouse:
	@png2udg ./background/hole_empty.png
	@png2udg ./background/hole_mouse.png

cheese:
	@png2udg ./background/curtain.png
	@png2udg ./background/cheese2.png

wall:
	@png2udg ./background/wall1.png
	@png2udg ./background/wall2.png
	@png2udg ./background/wall3.png
	@png2udg ./background/wall4.png

hearts:
	@png2udg ./background/heart1.png
	@png2udg ./background/heart2.png
	@png2udg ./background/cupid11.png
	@png2udg ./background/cupid12.png
	@png2udg ./background/cupid13.png
	@png2udg ./background/cupid21.png
	@png2udg ./background/cupid22.png
	@png2udg ./background/cupid23.png
	@png2udg ./background/cupid31.png
	@png2udg ./background/cupid32.png
	@png2udg ./background/cupid33.png

heavencat:
	@png2udg ./background/catheaven1.png
	@png2udg ./background/catheaven2.png

numbers:
	@png2udg ./background/udg_0.png
	@png2udg ./background/udg_1.png
	@png2udg ./background/udg_2.png
	@png2udg ./background/udg_3.png
	@png2udg ./background/udg_4.png
	@png2udg ./background/udg_5.png
	@png2udg ./background/udg_6.png
	@png2udg ./background/udg_7.png
	@png2udg ./background/udg_8.png
	@png2udg ./background/udg_9.png