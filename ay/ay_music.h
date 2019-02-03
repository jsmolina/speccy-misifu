#ifndef _AY_MUSIC
#define _AY_MUSIC

extern unsigned char music_module[];

extern unsigned char pcspeaker_module[];

extern unsigned char sweet_module[];

extern void ay_vt_init(const void *module_address) __z88dk_fastcall;
extern void ay_vt_mute(void);

#endif
