; void ay_vt_init(const void *module_address) __z88dk_fastcall

SECTION code_crt_common

PUBLIC _ay_vt_init

EXTERN VT_INIT
EXTERN asm_z80_push_di, asm0_z80_pop_ei
EXTERN enable_bank_n, restore_bank_0

_ay_vt_init:

   call asm_z80_push_di
   
   push ix
   push iy

   ld a,0x80
   ld i,a                      ; point I at uncontended bank

   ex de,hl                    ; de = module address
   
   ld a,6
   call enable_bank_n          ; bank 6 in top 16k, stack moved
   
   ex de,hl                    ; hl = module address
   call VT_INIT
   
   call restore_bank_0         ; bank 0 in top 16k, stack restored

   ld a,0xd0
   ld i,a                      ; restore I

   pop iy
   pop ix
   
   jp asm0_z80_pop_ei


; void ay_vt_mute(void)

SECTION code_crt_common

PUBLIC _ay_vt_mute

EXTERN VT_MUTE
EXTERN asm_z80_push_di, asm0_z80_pop_ei
EXTERN enable_bank_n, restore_bank_0

_ay_vt_mute:

   call asm_z80_push_di

   ld a,0x80
   ld i,a                      ; point I at uncontended bank

   ld a,6
   call enable_bank_n          ; bank 6 in top 16k, stack moved
   
   call VT_MUTE
   
   call restore_bank_0         ; bank 0 in top 16k, stack restored

   ld a,0xd0
   ld i,a                      ; restore I

   jp asm0_z80_pop_ei
