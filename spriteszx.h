// sprites.h

extern unsigned char sprite_negro [];
extern unsigned char sprite_cubo [];
extern unsigned char sprite_moneda [];
extern unsigned char sprite_prota1 [];
extern unsigned char sprite_prota2 [];
extern unsigned char sprite_protajump [];
extern unsigned char sprite_protajumpleft [];
extern unsigned char sprite_protajumpright [];
extern unsigned char sprite_prota4 [];
extern unsigned char sprite_prota5 [];
extern unsigned char sprite_malo1 [];
extern unsigned char sprite_malo2 [];
extern unsigned char sprite_fight1 [];
extern unsigned char sprite_fight2 [];
extern unsigned char sprite_arbol [];

extern unsigned char fondov_x16 [];
extern unsigned char fondoh_x16 [];

#asm
	._sprite_negro
	DEFB	  0,  0,  0,  0,  0,  0,  0,  0
	DEFB	0,  0,  0, 0,0,  0,  0,0
	DEFB	0,  0,  0,0, 0,  0,0,0
	DEFB	 0,0,0,0, 0,0,0,0
	DEFB	  0,0,0,0,  0,0,0,0
	DEFB	  0,0,0,0,  0,0,0,0
	DEFB	  0,0, 0,  0,  0,0, 0,  0
	DEFB	  0, 0,  0,  0,  0, 0,  0,  0
	DEFB	 0, 0, 0, 0, 0, 0, 0, 0

	._sprite_cubo
	defb 255,255,128,1,128,1,128,1,128,1,128,1,128,1,128,1
	defb 128,1,128,1,128,1,128,1,128,1,128,1,128,1,255,255
	defb 12,13,14,15

	._sprite_moneda
	defb 0,0,3,192,12,48,19,200
	defb 47,244,44,52,91,218,80,122
	defb 80,122,91,218,44,52,47,244
	defb 19,200,12,48,3,192,0,0
	defb 71,70,70,6

	._sprite_prota1
	DEFB	  0,  0,  0,  0,  0,  0,  0,  0
	DEFB	128,  0,  0, 96,128,  0,  0,112
	DEFB	240,  0,  0,252, 24,  1,241,246
	DEFB	 14,127,255,255, 14,127,255,255
	DEFB	  7,255,255,254,  7,255,255,252
	DEFB	  0,255,255,128,  0,255,255,128
	DEFB	  0,126, 15,  0,  0,112, 14,  0
	DEFB	  0, 24,  7,  0,  0, 24,  7,  0
	DEFB	 71, 71, 71, 71, 71, 71, 71, 71


	._sprite_prota2
	DEFB	  0,  0,  0,  0, 16,  0,  0,  0
	DEFB	224,  0,  0, 64,224,  0,  0, 64
	DEFB	128,  0,  1,240,224,  7,227,236
	DEFB	120,127,255,254, 31,255,255,252
	DEFB	 31,255,255,252,  7,254,127,240
	DEFB	  3,248,  7,192,  7,112,  6, 96
	DEFB	  7,112, 28, 96,  7,112, 28, 96
	DEFB	  3,152,  0, 48,  0,  0,  0,  0
	DEFB	 71, 71, 71, 71, 71, 71, 71, 71

	._sprite_protajump
    DEFB	  0,  0,230,  0,  0,  3,255,  0
	DEFB	  0,  3,255,  0,  0,  7,255,128
	DEFB	  0, 23,255, 96,  0, 49,248,224
	DEFB	  0, 31,255,192,  0, 23,255,192
	DEFB	  1,175,254,  0,  7,239,248,  0
	DEFB	  7,127,248,  0,  0, 31,254,  0
	DEFB	  0, 31,252,  0,  0, 63,254,  0
	DEFB	  0, 62, 15,  0,  0,240,  3,128
	DEFB	  0, 71, 71,  7, 71, 71, 71,  7

	._sprite_protajumpleft
    DEFB	 16,112,  0,  0, 31,248,  0,  0
	DEFB	 31,248,  0,  0,111,190,  0,  0
	DEFB	 31,248,  0,  0, 31,248,  0,  0
	DEFB	  3,255,128,  0, 31,255,240,  0
	DEFB	243,255,252, 15,243,255,252, 15
	DEFB	 15,129,255,255, 28,  1,255,192
	DEFB	 28,  1,255,192,  0,  0,126,112
	DEFB	  0,  0, 14,  0,  0,  0, 14,  0
	DEFB	 71, 71, 71,  0, 71, 71, 71, 71

    ._sprite_protajumpright
    DEFB	  0,  0, 14,  8,  0,  0, 31,248
	DEFB	  0,  0, 31,248,  0,  0,125,246
	DEFB	  0,  0, 31,248,  0,  0, 31,248
	DEFB	  0,  1,255,192,  0, 15,255,248
	DEFB	240, 63,255,207,240, 63,255,207
	DEFB	255,255,129,240,  3,255,128, 56
	DEFB	  3,255,128, 56, 14,126,  0,  0
	DEFB	  0,112,  0,  0,  0,112,  0,  0
	DEFB	  0, 71, 71, 71, 71, 71, 71, 71


	._sprite_prota4
    DEFB	  0,  0,  0,  0,  0,  0,  0,  0
	DEFB	  6,  0,  0,  1, 14,  0,  0,  1
	DEFB	 63,  0,  0, 15,111,143,128, 24
	DEFB	255,255,254,112,255,255,254,112
	DEFB	127,255,255,224, 63,255,255,224
	DEFB	  1,255,255,  0,  1,255,255,  0
	DEFB	  0,240,126,  0,  0,112, 14,  0
	DEFB	  0,224, 24,  0,  0,224, 24,  0
	DEFB	 71, 71, 71, 71, 71, 71, 71, 71

    ._sprite_prota5
    DEFB	  0,  0,  0,  0,  0,  0,  0,  8
	DEFB	  2,  0,  0,  7,  2,  0,  0,  7
	DEFB	 15,128,  0,  1, 55,199,224,  7
	DEFB	127,255,254, 30, 63,255,255,248
	DEFB	 63,255,255,248, 15,254,127,224
	DEFB	  3,224, 31,192,  6, 96, 14,224
	DEFB	  6, 56, 14,224,  6, 56, 14,224
	DEFB	 12,  0, 25,192,  0,  0,  0,  0
	DEFB	 71, 71, 71, 71, 71, 71, 71, 71


	._sprite_malo1
	DEFB	  0,234,138,  0,  7, 16,  1,  0
	DEFB	 15, 16,  2,112,121,  0,  1,240
	DEFB	255,  8,128,240,255, 48,  0,248
	DEFB	111,  0,  0,254, 37,  0,  0,246
	DEFB	 32,255,253,251,  8,127,253,249
	DEFB	 13,157,254,243, 15, 14,124,242
	DEFB	  6,  7,129,224,  0,  1,195,192
	DEFB	  0,  0,195,  0,  0,  0,  0,  0
	DEFB	 65, 73, 73, 65, 65, 65, 65, 65

	._sprite_malo2
	DEFB	  0,  1,138,  0,  0,  7,  1,  0
	DEFB	  7,239,  2,102, 31,223,  1,243
	DEFB	 31,255,  0,241,115,239,  0,251
	DEFB	255,255,192,254,255,255,128,248
	DEFB	 63,239,255,248,175,255,127,188
	DEFB	255,254,254, 60,109,175,224, 30
	DEFB	 12, 60,  0,  7,  0,240,  0,  3
	DEFB	  0, 96,  0,  0,  0,  0,  0,  0
	DEFB	 65, 65, 73, 65, 65, 65, 65, 65

	._sprite_arbol
	defb 7,255,192,31,255,176,63,255
	defb 232,127,255,244,127,255,252,255
	defb 255,254,255,255,250,255,255,244
	defb 255,255,250,255,255,244,255,255
	defb 250,127,255,252,127,255,212,63
	defb 254,232, 27,213,176,6,170,192
	defb 3,137,128,1,219,0,0,126
	defb 0,0,62,0,0,28,0,0
	defb 28,0,0,60,0,0,126,0
	defb 68,68,4,68,68,4,66,66
	defb 66

	._sprite_fight1
    DEFB	136,  0,128,136,  0, 15,  0,  0
	DEFB	  0,251,240,192, 51, 65, 87, 60
	DEFB	 63, 63, 63,204,252,221,205,204
	DEFB	255,243,255,255,119, 81, 85,119
	DEFB	255,255,255,204,205, 93, 77,112
	DEFB	 51,207,207,240, 63,117,117, 64
	DEFB	191,255, 63,136,  2, 17,214,  0
	DEFB	  0, 12,176, 32,  0,  0,  0,  0
	DEFB	  7,  7,  7,  7,  7,  7,  7,  7

	._sprite_fight2
    DEFB	  0,  0,  0,128,  0,  0,  0, 48
	DEFB	  0,  0,  0,128,192,  0,  0,  0
	DEFB	 32,  0,195,  0, 12, 48, 48,192
	DEFB	  0,128,  0,128,  0, 12, 64,  0
	DEFB	  3,  2, 48,224,  1, 12,  0, 12
	DEFB	  0,  0,  0,192,  0,192,  0, 64
	DEFB	  3,  0,194,  0, 12,  6, 12,  0
	DEFB	  0,  0,  0,  0,  0,  0,  0,  0
	DEFB	  7,  7,  7,  7,  7,  7,  7,  7

	._fondov_x16
	defb 0,0,0,0,0,0,0,0
	defb 0,0,0,0,0,0,0,0
	defb 0,0

	._fondoh_x16
	defb 0,0,0,0,0,0,0,0
	defb 0,0,0,0,0,0,0,0
	defb 0,0
#endasm