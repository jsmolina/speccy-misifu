;; AY RELATED FOR BANK_3

; OWN COPY OF VTII PLAYER

SECTION BANK_3_VTII

INCLUDE "src/VTII10bG-mfx.asm"

; OWN COPY OF MFXPLAYER

SECTION BANK_3_MFX

INCLUDE "src/mfx.asm"

; SONGS & EFFECTS IN THIS BANK

SECTION BANK_3_AUDIO

PUBLIC _ay_song_03_alleycat
_ay_song_03_alleycat:
   BINARY "songs/alley_cat.pt3"
