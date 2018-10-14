;; AY RELATED FOR BANK_6

; OWN COPY OF VTII PLAYER

; This bank exports the player entry addresses
; which are the same for all banks' copies

SECTION BANK_6_VTII

PUBLIC vtii_init
PUBLIC vtii_play
PUBLIC vtii_stop
PUBLIC vtii_setup
PUBLIC vtii_modaddr

defc vtii_init  = INIT
defc vtii_play  = PLAY
defc vtii_stop  = STOP
defc vtii_setup = SETUP
defc vtii_modaddr = MODADDR

INCLUDE "src/VTII10bG-mfx.asm"

; OWN COPY OF MFXPLAYER

; This bank exports the mfx entry addresses
; which are the same for all banks' copies

SECTION BANK_6_MFX

PUBLIC mfx_init
PUBLIC mfx_add
PUBLIC mfx_playm
PUBLIC mfx_playe
PUBLIC mfx_mfxptr

defc mfx_init  = MFXINIT
defc mfx_add   = MFXADD
defc mfx_playm = MFXPLAYM
defc mfx_playe = MFXPLAYE
defc mfx_mfxptr = mfxPtr

INCLUDE "src/mfx.asm"

; SONGS & EFFECTS IN THIS BANK
SECTION BANK_6_AUDIO

PUBLIC _ay_song_06_alleycat
_ay_song_06_alleycat:
   BINARY "songs/alley_cat.pt3"
