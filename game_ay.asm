;; AY CONTROL

SECTION data_arch

PUBLIC _ay_fx_bank
PUBLIC _ay_fx_command
PUBLIC _ay_fx_command_param

PUBLIC _ay_song_bank
PUBLIC _ay_song_command
PUBLIC _ay_song_command_param

_ay_fx_command:          defb 0   ; fx command communicated to isr
_ay_fx_bank:             defb 6   ; bank currently playing fx is in
_ay_fx_command_param:    defw 0

_ay_song_command:        defb 0   ; song command communicated to isr
_ay_song_bank:           defb 3   ; bank currently playing song is in
_ay_song_command_param:  defw 0

;; AY EFFECT FUNCTIONS

SECTION code_user

PUBLIC _ay_fx_play
PUBLIC _ay_fx_stop

; void ay_fx_play(unsigned char bank, void *effect)

_ay_fx_play:

IF __SDCC

   pop hl
   dec sp
   pop de
   ex (sp),hl

ENDIF

IF __SCCZ80

   pop af
   pop hl
   pop de
   push af
   ld d,e

ENDIF

ay_fx_play:

   ; hl = song address
   ;  d = bank

   ld (_ay_fx_command_param),hl

   ld e,$04                    ; NEW command
   ld (_ay_fx_command),de

   ret

_ay_fx_stop:

   ld a,$02                    ; STOP command
   ld (_ay_fx_command),a

   ret

;; AY SONG FUNCTIONS

SECTION code_user

PUBLIC _ay_song_play
PUBLIC _ay_song_stop

; void ay_song_play(unsigned char flag, unsigned char bank, void *song)

_ay_song_play:

IF __SDCC

   pop hl
   pop de
   ex (sp),hl

ENDIF

IF __SCCZ80

   pop af
   pop hl
   pop bc
   pop de
   push af
   ld d,c

ENDIF

ay_song_play:

   ; hl = song address
   ;  d = bank
   ;  e = 0 to repeat, 1 to not repeat

   ld (_ay_song_command_param),hl

   ld a,e
   and $01                     ; keep loop bit
   or $04                      ; add NEW command
   ld e,a

   ld (_ay_song_command),de
   ret

_ay_song_stop:

   ld a,$02                    ; STOP command
   ld (_ay_song_command),a
   ret

;; AY MISC FUNCTIONS

SECTION code_user

PUBLIC _ay_is_playing
PUBLIC _ay_reset

_ay_reset:

   call _ay_song_stop
   jp _ay_fx_stop

EXTERN _GLOBAL_ZX_PORT_7FFD
EXTERN mfx_mfxptr, vtii_modaddr

_ay_is_playing:

   ; exit:  l = bit 0 set if song playing, bit 1 set if fx playing

   ld a,(_ay_fx_bank)
   or $10                      ; select 48k rom

   ld bc,$7ffd

   di

   out (c),a

   ld hl,(mfx_mfxptr+1)        ; current effect position

   ld a,(_ay_song_bank)
   or $10                      ; select 48k rom

   out (c),a

   ld a,(vtii_modaddr+1)       ; msb of current song position
   ld l,a

   ld a,(_GLOBAL_ZX_PORT_7FFD)
   out (c),a                   ; restore bank

   ei

   inc l
   dec l
   jr z, no_song
   ld l,1

no_song:

   ld a,h
   or a
   jr z, no_effect
   ld a,$02

no_effect:

   or l
   ld l,a

   ret
