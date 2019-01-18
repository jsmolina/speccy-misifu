VT_SOUND_LIB_SDCC_IY := ./ay
# ./bas2tap -a loader.bas
compile:
	zcc +zx -v -startup=31 -DWFRAMES=3 -clib=sdcc_iy -Cz--screen=screen.scr -SO3 --max-allocs-per-node200000 @zproject.lst -pragma-include:zpragma.inc -o misifu -create-app
	echo "Done"

develop:
	zcc +zx -v -clib=sdcc_iy -Cz--screen=screen.scr -startup=31 -DWFRAMES=3 -O3 @zproject.lst -o misifu -pragma-include:zpragma.inc -create-app
	echo "Done"

sprites: prota dogsprites bincat clothes auxiliar protaswim

prota:
	png2sp1sprite ./sprites/cat_sprites.png -i sprite_protar -f 32 > ./build/protar.asm

protaswim:
	png2sp1sprite ./sprites/cat_swimsprites.png --bit -i sprite_swim -f 32 > ./build/protaswim.asm

dogsprites:
	png2sp1sprite ./sprites/dog_sprites.png -i sprite_dog -f 32 > ./build/dogr.asm

bincat:
	png2sp1sprite ./sprites/bincat_sprites.png --bit -i sprite_bincat -f 24 > ./build/bincat.asm

clothes:
	@png2udg ./background/udg_clothes11.png
	@png2udg ./background/udg_clothes12.png
	@png2udg ./background/udg_clothes21.png
	@png2udg ./background/udg_clothes22.png
	@png2udg ./background/udg_boot.png
	@png2udg ./background/udg_boot2.png

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

chair:
	@png2udg ./background/udg_sillaL.png
	@png2udg ./background/udg_sillaR.png
	@png2udg ./background/udg_sillaLM.png
	@png2udg ./background/udg_sillaRM.png

table:
	@png2udg ./background/mesatop.png
	@png2udg ./background/mesapata.png
	@png2udg ./background/mesaside.png

fish:
	@png2udg ./background/udg_fishtank1.png
	@png2udg ./background/udg_fishtank2.png

water:
	@png2udg ./background/udg_watertop.png
	@png2udg ./background/udg_fish.png
	@png2udg ./background/udg_fishL.png
	@png2udg ./background/udg_eel.png

spider:
	@png2udg ./background/udg_spiderplant11.png
	@png2udg ./background/udg_spiderplant12.png
	@png2udg ./background/udg_spiderplant21.png
	@png2udg ./background/udg_spiderplant22.png
	@png2udg ./background/udg_spidershelfleft.png
	@png2udg ./background/udg_spidershelfright.png
	@png2udg ./background/udg_spiderempty.png
	@png2udg ./background/udg_spiderbook.png
	@png2udg ./background/udg_spiderbook2.png

bird:
	@png2udg ./background/udg_birdcage1.png
	@png2udg ./background/udg_birdcage2.png

dog:
	@png2udg ./background/udg_dog1.png
	@png2udg ./background/udg_dog1m.png
	@png2udg ./background/udg_dog2.png
	@png2udg ./background/udg_dogmilk.png
