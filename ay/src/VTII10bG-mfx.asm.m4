; modified for z88dk/z80asm and Gandalf

;Vortex Tracker II v1.0 PT3 player for ZX Spectrum
;(c)2004,2007 S.V.Bulba <vorobey@mail.khstu.ru>
;http://bulba.untergrund.net (http://bulba.at.kz)

;mFX edition by Intense
;WARNING: uses shadow registers HL',DE',BC' for stack output!
;Uncomment the 'LD HL,0x2758' line if used alongside BASIC

;Release number
define(`m4_Release', "7.1")

;Features
;--------
;-Can be compiled at any address (i.e. no need rounding ORG
; address).
;-Variables (VARS) can be located at any address (not only after
;code block).
;-INIT subroutine detects module version and rightly generates
; both note and volume tables outside of code block (in VARS).
;-Two portamento (spc. command 3xxx) algorithms (depending of
; module version).
;-New 1.XX and 2.XX special command behaviour (only for PT v3.7
; and higher).
;-Any Tempo value are accepted (including Tempo=1 and Tempo=2).
;-Fully compatible with Ay_Emul PT3 player codes.
;-See also notes at the end of this source code.

;Limitations
;-----------
;-Can run in RAM only (self-modified code is used).

;Warning!!! PLAY subroutine can crash if no module are loaded
;into RAM or INIT subroutine was not called before.

;Call MUTE or INIT one more time to mute sound after stopping
;playing 


;Test codes (commented)
;  CALL START
;  EI
;_LP  HALT
;  CALL START+5
;  XOR A
;  IN A,(0xFE)
;  CPL
;  AND 15
;  JR Z,_LP
;  JR START+8

defc TonA  = 0
defc TonB  = 2
defc TonC  = 4
defc Noise = 6
defc Mixer = 7
defc AmplA = 8
defc AmplB = 9
defc AmplC = 10
defc Env   = 11
defc EnvTp = 13

;Entry and other points
;START initialization
;INIT = START+3 initialization with module address in HL (0 = no song)
;PLAY = START+5 play one quark
;MUTE = START+8 mute
;SETUP = START+10 setup and status flags
;CrPsPtr = START+11 pointer to current position value in PT3 module;
;After INIT (START+11) points to Postion0-1 (optimization)

START:
   LD HL,0  ; no song
   JR INIT
   JP PLAY
   JR MUTE
SETUP: defb 0 ;set bit0 to 1, if you want to play without looping
        ;bit7 is set each time, when loop point is passed
        ;(Hikaru) Set BIT 1 before calling START+5 to push the AY register data
        ;         for the current frame into the stack.
        ;         Note that BIT 1 resets automatically at exit
CrPsPtr:  defw 0 

;Identifier
   defm "=VTII PT3 Player r.",m4_Release,"="

CHECKLP:  LD HL,SETUP
   SET 7,(HL)
   BIT 0,(HL)
   RET Z
   POP HL
   LD HL,DelyCnt
   INC (HL)
   LD HL,ChanA+CHP_NtSkCn
   INC (HL)
STOP:  XOR A
   LD H,A
   LD L,A
   LD (MODADDR),HL
   LD (MDADDR2),HL
MUTE:  XOR A
   LD H,A
   LD L,A
   LD (AYREGS+AmplA),A
   LD (AYREGS+AmplB),HL
   JP ROUT_A0

INIT:
;HL - AddressOfModule

   LD (MODADDR),HL
   LD (MDADDR2),HL
   PUSH HL
   LD DE,100
   ADD HL,DE
   LD A,(HL)
   LD (Delay),A
   PUSH HL
   POP IX
   ADD HL,DE
   LD (CrPsPtr),HL
   LD E,(IX+102-100)
   ADD HL,DE
   INC HL
   LD (LPosPtr),HL
   POP DE
   LD L,(IX+103-100)
   LD H,(IX+104-100)
   ADD HL,DE
   LD (PatsPtr),HL
   LD HL,169
   ADD HL,DE
   LD (OrnPtrs),HL
   LD HL,105
   ADD HL,DE
   LD (SamPtrs),HL
   LD HL,SETUP
   RES 7,(HL)

SMC_INIT_0:

   JR FIRST_TIME_INIT_0

   XOR A
   JP INIT_REGISTERS

FIRST_TIME_INIT_0:

   PUSH HL
   LD HL,0
   LD (SMC_INIT_0),HL
   POP HL

;note table data depacker
   LD DE,T_PACK
   LD BC,T1_+(2*49)-1
TP_0:  LD A,(DE)
   INC DE
   CP 15*2
   JR NC,TP_1
   LD H,A
   LD A,(DE)
   LD L,A
   INC DE
   JR TP_2
TP_1:  PUSH DE
   LD D,0
   LD E,A
   ADD HL,DE
   ADD HL,DE
   POP DE
TP_2:  LD A,H
   LD (BC),A
   DEC BC
   LD A,L
   LD (BC),A
   DEC BC
   SUB 0xF0 ;#F8*2
   JR NZ,TP_0

INIT_REGISTERS:

   LD HL,VARS
   LD (HL),A
   LD DE,VARS+1
   LD BC,VAR0END-VARS-1
   LDIR
   INC A
   LD (DelyCnt),A
   LD HL,0xF001 ;H - CHP_Volume, L - CHP_NtSkCn
   LD (ChanA+CHP_NtSkCn),HL
   LD (ChanB+CHP_NtSkCn),HL
   LD (ChanC+CHP_NtSkCn),HL

   LD HL,EMPTYSAMORN
   LD (AdInPtA),HL ;ptr to zero
   LD (ChanA+CHP_OrnPtr),HL ;ornament 0 is "0,1,0"
   LD (ChanB+CHP_OrnPtr),HL ;in all versions from
   LD (ChanC+CHP_OrnPtr),HL ;3.xx to 3.6x and VTII

   LD (ChanA+CHP_SamPtr),HL ;S1 There is no default
   LD (ChanB+CHP_SamPtr),HL ;S2 sample in PT3, so, you
   LD (ChanC+CHP_SamPtr),HL ;S3 can comment S1,2,3; see
                ;also EMPTYSAMORN comment

SMC_INIT_1:

   JR FIRST_TIME_INIT_1
   JP ROUT

FIRST_TIME_INIT_1:

   LD HL,0
   LD (SMC_INIT_1),HL

   LD A,(IX+13-100) ;EXTRACT VERSION NUMBER
   SUB 0x30
   JR C,L20
   CP 10
   JR C,L21
L20:   LD A,6
L21:   LD (Version),A
   PUSH AF
   CP 4
   LD A,(IX+99-100) ;TONE TABLE NUMBER
   RLA
   AND 7

;NoteTableCreator (c) Ivan Roshin
;A - NoteTableNumber*2+VersionForNoteTable
;(xx1b - 3.xx..3.4r, xx0b - 3.4x..3.6x..VTII1.0)

   LD HL,NT_DATA
   PUSH DE
   LD D,B
   ADD A,A
   LD E,A
   ADD HL,DE
   LD E,(HL)
   INC HL
   SRL E
   SBC A,A
   AND 0xA7 ;#00 (NOP) or #A7 (AND A)
   LD (L3),A
   EX DE,HL
   POP BC ;BC=T1_
   ADD HL,BC

   LD A,(DE)
   ADD A,T_ & 0x00FF
   LD C,A
   ADC A,T_/256
   SUB C
   LD B,A
   PUSH BC
   LD DE,NT_
   PUSH DE

   LD B,12
L1: PUSH BC
   LD C,(HL)
   INC HL
   PUSH HL
   LD B,(HL)

   PUSH DE
   EX DE,HL
   LD DE,23
   LD IXH,8

L2: SRL B
   RR C
L3: defb 0x19  ;AND A or NOP
   LD A,C
   ADC A,D  ;=ADC 0
   LD (HL),A
   INC HL
   LD A,B
   ADC A,D
   LD (HL),A
   ADD HL,DE
   DEC IXH
   JR NZ,L2

   POP DE
   INC DE
   INC DE
   POP HL
   INC HL
   POP BC
   DJNZ L1

   POP HL
   POP DE

   LD A,E
   CP TCOLD_1 & 0x00FF
   JR NZ,CORR_1
   LD A,0xFD
   LD (NT_+0x2E),A

CORR_1:   LD A,(DE)
   AND A
   JR Z,TC_EXIT
   RRA
   PUSH AF
   ADD A,A
   LD C,A
   ADD HL,BC
   POP AF
   JR NC,CORR_2
   DEC (HL)
   DEC (HL)
CORR_2:   INC (HL)
   AND A
   SBC HL,BC
   INC DE
   JR CORR_1

TC_EXIT:

   POP AF

;VolTableCreator (c) Ivan Roshin
;A - VersionForVolumeTable (0..4 - 3.xx..3.4x;
            ;5.. - 3.5x..3.6x..VTII1.0)

   CP 5
   LD HL,0x11
   LD D,H
   LD E,H
   LD A,0x17
   JR NC,M1
   DEC L
   LD E,L
   XOR A
M1:      LD (M2),A

   LD IX,VT_+16
   LD C,0x10

INITV2:  PUSH HL

   ADD HL,DE
   EX DE,HL
   SBC HL,HL

INITV1:  LD A,L
M2:      defb 0x7D
   LD A,H
   ADC A,0
   LD (IX),A
   INC IX
   ADD HL,DE
   INC C
   LD A,C
   AND 15
   JR NZ,INITV1

   POP HL
   LD A,E
   CP 0x77
   JR NZ,M3
   INC E
M3:      LD A,C
   AND A
   JR NZ,INITV2
   JP ROUT_A0

;pattern decoder
PD_OrSm:  LD (IX-12+CHP_Env_En),0
   CALL SETORN
   LD A,(BC)
   INC BC
   RRCA

PD_SAM:   ADD A,A
PD_SAM_:  LD E,A
   LD D,0
defc SamPtrs = _SamPtrs+1
_SamPtrs:
   LD HL,0x2121
   ADD HL,DE
   LD E,(HL)
   INC HL
   LD D,(HL)
defc MODADDR = _MODADDR+1
_MODADDR:
   LD HL,0  ;; 0x2121
   ADD HL,DE
   LD (IX-12+CHP_SamPtr),L
   LD (IX-12+CHP_SamPtr+1),H
   JR PD_LOOP

PD_VOL:   RLCA
   RLCA
   RLCA
   RLCA
   LD (IX-12+CHP_Volume),A
   JR PD_LP2
   
PD_EOff:  LD (IX-12+CHP_Env_En),A
   LD (IX-12+CHP_PsInOr),A
   JR PD_LP2

PD_SorE:  DEC A
   JR NZ,PD_ENV
   LD A,(BC)
   INC BC
   LD (IX-12+CHP_NNtSkp),A
   JR PD_LP2

PD_ENV:   CALL SETENV
   JR PD_LP2

PD_ORN:   CALL SETORN
   JR PD_LOOP

PD_ESAM:  LD (IX-12+CHP_Env_En),A
   LD (IX-12+CHP_PsInOr),A
   CALL NZ,SETENV
   LD A,(BC)
   INC BC
   JR PD_SAM_

PTDECOD: LD A,(IX-12+CHP_Note)
   LD (PrNote+1),A
   LD L,(IX-12+CHP_CrTnSl)
   LD H,(IX-12+CHP_CrTnSl+1)
   LD (PrSlide+1),HL

PD_LOOP:  LD DE,0x2010
PD_LP2:   LD A,(BC)
   INC BC
   ADD A,E
   JR C,PD_OrSm
   ADD A,D
   JR Z,PD_FIN
   JR C,PD_SAM
   ADD A,E
   JR Z,PD_REL
   JR C,PD_VOL
   ADD A,E
   JR Z,PD_EOff
   JR C,PD_SorE
   ADD A,96
   JR C,PD_NOTE
   ADD A,E
   JR C,PD_ORN
   ADD A,D
   JR C,PD_NOIS
   ADD A,E
   JR C,PD_ESAM
   ADD A,A
   LD E,A
   LD HL,SPCCOMS-0x20E0 ;+#FF20-#2000
   ADD HL,DE
   LD E,(HL)
   INC HL
   LD D,(HL)
   PUSH DE
   JR PD_LOOP

PD_NOIS:  LD (Ns_Base),A
   JR PD_LP2

PD_REL:   RES 0,(IX-12+CHP_Flags)
   JR PD_RES
   
PD_NOTE:  LD (IX-12+CHP_Note),A
   SET 0,(IX-12+CHP_Flags)
   XOR A

PD_RES:   LD (PDSP_+1),SP
   LD SP,IX
   LD H,A
   LD L,A
   PUSH HL
   PUSH HL
   PUSH HL
   PUSH HL
   PUSH HL
   PUSH HL
PDSP_: LD SP,0x3131

PD_FIN:   LD A,(IX-12+CHP_NNtSkp)
   LD (IX-12+CHP_NtSkCn),A
   RET

C_PORTM: RES 2,(IX-12+CHP_Flags)
   LD A,(BC)
   INC BC
;SKIP PRECALCULATED TONE DELTA (BECAUSE
;CANNOT BE RIGHT AFTER PT3 COMPILATION)
   INC BC
   INC BC
   LD (IX-12+CHP_TnSlDl),A
   LD (IX-12+CHP_TSlCnt),A
   LD DE,NT_
   LD A,(IX-12+CHP_Note)
   LD (IX-12+CHP_SlToNt),A
   ADD A,A
   LD L,A
   LD H,0
   ADD HL,DE
   LD A,(HL)
   INC HL
   LD H,(HL)
   LD L,A
   PUSH HL
PrNote:   LD A,0x3E
   LD (IX-12+CHP_Note),A
   ADD A,A
   LD L,A
   LD H,0
   ADD HL,DE
   LD E,(HL)
   INC HL
   LD D,(HL)
   POP HL
   SBC HL,DE
   LD (IX-12+CHP_TnDelt),L
   LD (IX-12+CHP_TnDelt+1),H
   LD E,(IX-12+CHP_CrTnSl)
   LD D,(IX-12+CHP_CrTnSl+1)
defc Version = _Version+1
_Version:
   LD A,0x3E
   CP 6
   JR C,OLDPRTM ;Old 3xxx for PT v3.5-
PrSlide:  LD DE,0x1111
   LD (IX-12+CHP_CrTnSl),E
   LD (IX-12+CHP_CrTnSl+1),D
OLDPRTM:  LD A,(BC) ;SIGNED TONE STEP
   INC BC
   EX AF,AF'
   LD A,(BC)
   INC BC
   AND A
   JR Z,NOSIG
   EX DE,HL
NOSIG: SBC HL,DE
   JP P,SET_STP
   CPL
   EX AF,AF'
   NEG
   EX AF,AF'
SET_STP:  LD (IX-12+CHP_TSlStp+1),A
   EX AF,AF'
   LD (IX-12+CHP_TSlStp),A
   LD (IX-12+CHP_COnOff),0
   RET

C_GLISS:  SET 2,(IX-12+CHP_Flags)
   LD A,(BC)
   INC BC
   LD (IX-12+CHP_TnSlDl),A
   AND A
   JR NZ,GL36
   LD A,(Version) ;AlCo PT3.7+
   CP 7
   SBC A,A
   INC A
GL36:  LD (IX-12+CHP_TSlCnt),A
   LD A,(BC)
   INC BC
   EX AF,AF'
   LD A,(BC)
   INC BC
   JR SET_STP

C_SMPOS:  LD A,(BC)
   INC BC
   LD (IX-12+CHP_PsInSm),A
   RET

C_ORPOS:  LD A,(BC)
   INC BC
   LD (IX-12+CHP_PsInOr),A
   RET

C_VIBRT:  LD A,(BC)
   INC BC
   LD (IX-12+CHP_OnOffD),A
   LD (IX-12+CHP_COnOff),A
   LD A,(BC)
   INC BC
   LD (IX-12+CHP_OffOnD),A
   XOR A
   LD (IX-12+CHP_TSlCnt),A
   LD (IX-12+CHP_CrTnSl),A
   LD (IX-12+CHP_CrTnSl+1),A
   RET

C_ENGLS:  LD A,(BC)
   INC BC
   LD (Env_Del),A
   LD (CurEDel),A
   LD A,(BC)
   INC BC
   LD L,A
   LD A,(BC)
   INC BC
   LD H,A
   LD (ESldAdd),HL
   RET

C_DELAY:  LD A,(BC)
   INC BC
   LD (Delay),A
   RET
   
SETENV:   LD (IX-12+CHP_Env_En),E
   LD (AYREGS+EnvTp),A
   LD A,(BC)
   INC BC
   LD H,A
   LD A,(BC)
   INC BC
   LD L,A
   LD (EnvBase),HL
   XOR A
   LD (IX-12+CHP_PsInOr),A
   LD (CurEDel),A
   LD H,A
   LD L,A
   LD (CurESld),HL
C_NOP: RET

SETORN:   ADD A,A
   LD E,A
   LD D,0
   LD (IX-12+CHP_PsInOr),D
defc OrnPtrs = _OrnPtrs+1
_OrnPtrs:
   LD HL,0x2121
   ADD HL,DE
   LD E,(HL)
   INC HL
   LD D,(HL)
defc MDADDR2 = _MDADDR2+1
_MDADDR2:
   LD HL,0  ;; 0x2121
   ADD HL,DE
   LD (IX-12+CHP_OrnPtr),L
   LD (IX-12+CHP_OrnPtr+1),H
   RET

;ALL 16 ADDRESSES TO PROTECT FROM BROKEN PT3 MODULES
SPCCOMS: defw C_NOP
   defw C_GLISS
   defw C_PORTM
   defw C_SMPOS
   defw C_ORPOS
   defw C_VIBRT
   defw C_NOP
   defw C_NOP
   defw C_ENGLS
   defw C_DELAY
   defw C_NOP
   defw C_NOP
   defw C_NOP
   defw C_NOP
   defw C_NOP
   defw C_NOP

CHREGS:   XOR A
   LD (Ampl),A
   BIT 0,(IX+CHP_Flags)
   PUSH HL
   JP Z,CH_EXIT
   LD (CSP_+1),SP
   LD L,(IX+CHP_OrnPtr)
   LD H,(IX+CHP_OrnPtr+1)
   LD SP,HL
   POP DE
   LD H,A
   LD A,(IX+CHP_PsInOr)
   LD L,A
   ADD HL,SP
   INC A
   CP D
   JR C,CH_ORPS
   LD A,E
CH_ORPS:  LD (IX+CHP_PsInOr),A
   LD A,(IX+CHP_Note)
   ADD A,(HL)
   JP P,CH_NTP
   XOR A
CH_NTP:   CP 96
   JR C,CH_NOK
   LD A,95
CH_NOK:   ADD A,A
   EX AF,AF'
   LD L,(IX+CHP_SamPtr)
   LD H,(IX+CHP_SamPtr+1)
   LD SP,HL
   POP DE
   LD H,0
   LD A,(IX+CHP_PsInSm)
   LD B,A
   ADD A,A
   ADD A,A
   LD L,A
   ADD HL,SP
   LD SP,HL
   LD A,B
   INC A
   CP D
   JR C,CH_SMPS
   LD A,E
CH_SMPS:  LD (IX+CHP_PsInSm),A
   POP BC
   POP HL
   LD E,(IX+CHP_TnAcc)
   LD D,(IX+CHP_TnAcc+1)
   ADD HL,DE
   BIT 6,B
   JR Z,CH_NOAC
   LD (IX+CHP_TnAcc),L
   LD (IX+CHP_TnAcc+1),H
CH_NOAC: EX DE,HL
   EX AF,AF'
   LD L,A
   LD H,0
   LD SP,NT_
   ADD HL,SP
   LD SP,HL
   POP HL
   ADD HL,DE
   LD E,(IX+CHP_CrTnSl)
   LD D,(IX+CHP_CrTnSl+1)
   ADD HL,DE
CSP_:  LD SP,0x3131
   EX (SP),HL
   XOR A
   OR (IX+CHP_TSlCnt)
   JR Z,CH_AMP
   DEC (IX+CHP_TSlCnt)
   JR NZ,CH_AMP
   LD A,(IX+CHP_TnSlDl)
   LD (IX+CHP_TSlCnt),A
   LD L,(IX+CHP_TSlStp)
   LD H,(IX+CHP_TSlStp+1)
   LD A,H
   ADD HL,DE
   LD (IX+CHP_CrTnSl),L
   LD (IX+CHP_CrTnSl+1),H
   BIT 2,(IX+CHP_Flags)
   JR NZ,CH_AMP
   LD E,(IX+CHP_TnDelt)
   LD D,(IX+CHP_TnDelt+1)
   AND A
   JR Z,CH_STPP
   EX DE,HL
CH_STPP: SBC HL,DE
   JP M,CH_AMP
   LD A,(IX+CHP_SlToNt)
   LD (IX+CHP_Note),A
   XOR A
   LD (IX+CHP_TSlCnt),A
   LD (IX+CHP_CrTnSl),A
   LD (IX+CHP_CrTnSl+1),A
CH_AMP:   LD A,(IX+CHP_CrAmSl)
   BIT 7,C
   JR Z,CH_NOAM
   BIT 6,C
   JR Z,CH_AMIN
   CP 15
   JR Z,CH_NOAM
   INC A
   JR CH_SVAM
CH_AMIN:  CP -15
   JR Z,CH_NOAM
   DEC A
CH_SVAM:  LD (IX+CHP_CrAmSl),A
CH_NOAM:  LD L,A
   LD A,B
   AND 15
   ADD A,L
   JP P,CH_APOS
   XOR A
CH_APOS:  CP 16
   JR C,CH_VOL
   LD A,15
CH_VOL:   OR (IX+CHP_Volume)
   LD L,A
   LD H,0
   LD DE,VT_
   ADD HL,DE
   LD A,(HL)
CH_ENV:   BIT 0,C
   JR NZ,CH_NOEN
   OR (IX+CHP_Env_En)
CH_NOEN:  LD (Ampl),A
   BIT 7,B
   LD A,C
   JR Z,NO_ENSL
   RLA
   RLA
   SRA A
   SRA A
   SRA A
   ADD A,(IX+CHP_CrEnSl) ;SEE COMMENT BELOW
   BIT 5,B
   JR Z,NO_ENAC
   LD (IX+CHP_CrEnSl),A
NO_ENAC:  LD HL,AddToEn
   ADD A,(HL) ;BUG IN PT3 - NEED WORD HERE.
         ;FIX IT IN NEXT VERSION?
   LD (HL),A
   JR CH_MIX
NO_ENSL: RRA
   ADD A,(IX+CHP_CrNsSl)
   LD (AddToNs),A
   BIT 5,B
   JR Z,CH_MIX
   LD (IX+CHP_CrNsSl),A
CH_MIX:   LD A,B
   RRA
   AND 0x48
CH_EXIT:  LD HL,AYREGS+Mixer
   OR (HL)
   RRCA
   LD (HL),A
   POP HL
   XOR A
   OR (IX+CHP_COnOff)
   RET Z
   DEC (IX+CHP_COnOff)
   RET NZ
   XOR (IX+CHP_Flags)
   LD (IX+CHP_Flags),A
   RRA
   LD A,(IX+CHP_OnOffD)
   JR C,CH_ONDL
   LD A,(IX+CHP_OffOnD)
CH_ONDL:  LD (IX+CHP_COnOff),A
   RET

PLAY:
   LD A,(MODADDR+1)
   OR A
   JP Z, ROUT_A0     ; if no song
   XOR A
   LD (AddToEn),A
   LD (AYREGS+Mixer),A
   DEC A
   LD (AYREGS+EnvTp),A
   LD HL,DelyCnt
   DEC (HL)
   JR NZ,PL2
   LD HL,ChanA+CHP_NtSkCn
   DEC (HL)
   JR NZ,PL1B
defc AdInPtA = _AdInPtA+1
_AdInPtA:
   LD BC,0x0101
   LD A,(BC)
   AND A
   JR NZ,PL1A
   LD D,A
   LD (Ns_Base),A
   LD HL,(CrPsPtr)
   INC HL
   LD A,(HL)
   INC A
   JR NZ,PLNLP
   CALL CHECKLP
defc LPosPtr = _LPosPtr+1
_LPosPtr:
   LD HL,0x2121
   LD A,(HL)
   INC A
PLNLP: LD (CrPsPtr),HL
   DEC A
   ADD A,A
   LD E,A
   RL D
defc PatsPtr = _PatsPtr+1
_PatsPtr:
   LD HL,0x2121
   ADD HL,DE
   LD DE,(MODADDR)
   LD (PSP_+1),SP
   LD SP,HL
   POP HL
   ADD HL,DE
   LD B,H
   LD C,L
   POP HL
   ADD HL,DE
   LD (AdInPtB),HL
   POP HL
   ADD HL,DE
   LD (AdInPtC),HL
PSP_:  LD SP,0x3131
PL1A:  LD IX,ChanA+12
   CALL PTDECOD
   LD (AdInPtA),BC

PL1B:  LD HL,ChanB+CHP_NtSkCn
   DEC (HL)
   JR NZ,PL1C
   LD IX,ChanB+12
defc AdInPtB = _AdInPtB+1
_AdInPtB:
   LD BC,0x0101
   CALL PTDECOD
   LD (AdInPtB),BC

PL1C:  LD HL,ChanC+CHP_NtSkCn
   DEC (HL)
   JR NZ,PL1D
   LD IX,ChanC+12
defc AdInPtC = _AdInPtC+1
_AdInPtC:
   LD BC,0x0101
   CALL PTDECOD
   LD (AdInPtC),BC

defc Delay = _Delay+1
_Delay:
PL1D:  LD A,0x3E
   LD (DelyCnt),A

PL2:   LD IX,ChanA
   LD HL,(AYREGS+TonA)
   CALL CHREGS
   LD (AYREGS+TonA),HL
   LD A,(Ampl)
   LD (AYREGS+AmplA),A
   LD IX,ChanB
   LD HL,(AYREGS+TonB)
   CALL CHREGS
   LD (AYREGS+TonB),HL
   LD A,(Ampl)
   LD (AYREGS+AmplB),A
   LD IX,ChanC
   LD HL,(AYREGS+TonC)
   CALL CHREGS
;  LD A,(Ampl) ;Ampl = AYREGS+AmplC
;  LD (AYREGS+AmplC),A
   LD (AYREGS+TonC),HL

   LD HL,(Ns_Base_AddToNs)
   LD A,H
   ADD A,L
   LD (AYREGS+Noise),A

defc AddToEn = _AddToEn+1
_AddToEn:
   LD A,0x3E
   LD E,A
   ADD A,A
   SBC A,A
   LD D,A
   LD HL,(EnvBase)
   ADD HL,DE
   LD DE,(CurESld)
   ADD HL,DE
   LD (AYREGS+Env),HL

   XOR A
   LD HL,CurEDel
   OR (HL)
   JR Z,ROUT_A0
   DEC (HL)
   JR NZ,ROUT
defc Env_Del = _Env_Del+1
_Env_Del:
   LD A,0x3E
   LD (HL),A
defc ESldAdd = _ESldAdd+1
_ESldAdd:
   LD HL,0x2121
   ADD HL,DE
   LD (CurESld),HL

ROUT:  XOR A
ROUT_A0: LD HL,SETUP
   BIT 1,(HL)
   JR NZ,RSTK
   LD DE,0xFFBF
   LD BC,0xFFFD
   LD HL,AYREGS
LOUT:  OUT (C),A
   LD B,E
   OUTI 
   LD B,D
   INC A
   CP 13
   JR NZ,LOUT
   OUT (C),A
   LD A,(HL)
   AND A
   RET M
   LD B,E
   OUT (C),A
   RET
RSTK:
   RES 1,(HL)
   LD (RSTKSP_+1),SP
   LD SP,AYREGS
   POP BC
   POP DE
   POP HL
   POP AF
   EXX
   POP BC
   POP DE
   POP HL
RSTKSP_:
   LD SP,0
   EX (SP),HL
   PUSH DE
   PUSH BC
   EXX
   PUSH AF
   PUSH HL
   PUSH DE
   PUSH BC
   ;LD HL,0x2758
   EXX
   JP (HL)



NT_DATA:  defb (T_NEW_0-T1_)*2
   defb TCNEW_0-T_
   defb (T_OLD_0-T1_)*2+1
   defb TCOLD_0-T_
   defb (T_NEW_1-T1_)*2+1
   defb TCNEW_1-T_
   defb (T_OLD_1-T1_)*2+1
   defb TCOLD_1-T_
   defb (T_NEW_2-T1_)*2
   defb TCNEW_2-T_
   defb (T_OLD_2-T1_)*2
   defb TCOLD_2-T_
   defb (T_NEW_3-T1_)*2
   defb TCNEW_3-T_
   defb (T_OLD_3-T1_)*2
   defb TCOLD_3-T_

T_:

TCOLD_0:  defb 0x00+1,0x04+1,0x08+1,0x0A+1,0x0C+1,0x0E+1,0x12+1,0x14+1
   defb 0x18+1,0x24+1,0x3C+1,0
TCOLD_1:  defb 0x5C+1,0
TCOLD_2:  defb 0x30+1,0x36+1,0x4C+1,0x52+1,0x5E+1,0x70+1,0x82,0x8C,0x9C
   defb 0x9E,0xA0,0xA6,0xA8,0xAA,0xAC,0xAE,0xAE,0
TCNEW_3:  defb 0x56+1
TCOLD_3:  defb 0x1E+1,0x22+1,0x24+1,0x28+1,0x2C+1,0x2E+1,0x32+1,0xBE+1,0
TCNEW_0:  defb 0x1C+1,0x20+1,0x22+1,0x26+1,0x2A+1,0x2C+1,0x30+1,0x54+1
   defb 0xBC+1,0xBE+1,0
defc TCNEW_1 = TCOLD_1
TCNEW_2:  defb 0x1A+1,0x20+1,0x24+1,0x28+1,0x2A+1,0x3A+1,0x4C+1,0x5E+1
   defb 0xBA+1,0xBC+1,0xBE+1

EMPTYSAMORN:
   defb 0
   defb 1,0,0x90 ;delete #90 if you don't need default sample

;first 12 values of tone tables (packed)

T_PACK:   defb 0x06EC*2/256,0xD8 ;#06EC*2
   defb 0x0755-0x06EC
   defb 0x07C5-0x0755
   defb 0x083B-0x07C5
   defb 0x08B8-0x083B
   defb 0x093D-0x08B8
   defb 0x09CA-0x093D
   defb 0x0A5F-0x09CA
   defb 0x0AFC-0x0A5F
   defb 0x0BA4-0x0AFC
   defb 0x0C55-0x0BA4
   defb 0x0D10-0x0C55
   defb 0x066D*2/256,0xDA ;#066D*2
   defb 0x06CF-0x066D
   defb 0x0737-0x06CF
   defb 0x07A4-0x0737
   defb 0x0819-0x07A4
   defb 0x0894-0x0819
   defb 0x0917-0x0894
   defb 0x09A1-0x0917
   defb 0x0A33-0x09A1
   defb 0x0ACF-0x0A33
   defb 0x0B73-0x0ACF
   defb 0x0C22-0x0B73
   defb 0x0CDA-0x0C22
   defb 0x0704*2/256,0x08 ;#0704*2
   defb 0x076E-0x0704
   defb 0x07E0-0x076E
   defb 0x0858-0x07E0
   defb 0x08D6-0x0858
   defb 0x095C-0x08D6
   defb 0x09EC-0x095C
   defb 0x0A82-0x09EC
   defb 0x0B22-0x0A82
   defb 0x0BCC-0x0B22
   defb 0x0C80-0x0BCC
   defb 0x0D3E-0x0C80
   defb 0x07E0*2/256,0xC0 ;#07E0*2
   defb 0x0858-0x07E0
   defb 0x08E0-0x0858
   defb 0x0960-0x08E0
   defb 0x09F0-0x0960
   defb 0x0A88-0x09F0
   defb 0x0B28-0x0A88
   defb 0x0BD8-0x0B28
   defb 0x0C80-0x0BD8
   defb 0x0D60-0x0C80
   defb 0x0E10-0x0D60
   defb 0x0EF8-0x0E10

;vars from here can be stripped
;you can move VARS to any other address

VARS:

;ChannelsVars
   ;STRUCT  CHP
;reset group
defc CHP_PsInOr = 0
defc CHP_PsInSm = 1
defc CHP_CrAmSl = 2
defc CHP_CrNsSl = 3
defc CHP_CrEnSl = 4
defc CHP_TSlCnt = 5
defc CHP_CrTnSl = 6 ;DW
defc CHP_TnAcc  = 8 ;DW
defc CHP_COnOff = 10
;reset group

defc CHP_OnOffD = 11

;IX for PTDECOD here (+12)
defc CHP_OffOnD = 12
defc CHP_OrnPtr = 13 ;DW
defc CHP_SamPtr = 15 ;DW
defc CHP_NNtSkp = 17
defc CHP_Note   = 18
defc CHP_SlToNt = 19
defc CHP_Env_En = 20
defc CHP_Flags  = 21
 ;Enabled - 0,SimpleGliss - 2
defc CHP_TnSlDl = 22
defc CHP_TSlStp = 23 ;DW
defc CHP_TnDelt = 25 ;DW
defc CHP_NtSkCn = 27
defc CHP_Volume = 28

defc CHP = CHP_Volume+1

ChanA: defs CHP
ChanB: defs CHP
ChanC: defs CHP

;GlobalVars
DelyCnt:  defb 0
CurESld:  defw 0
CurEDel:  defb 0
Ns_Base_AddToNs:
Ns_Base:  defb 0
AddToNs:  defb 0

AYREGS:

VT_:   defs 256 ;CreatedVolumeTableAddress

defc EnvBase = VT_+14

defc T1_ = VT_+16 ;Tone tables data depacked here

defc T_OLD_1 = T1_
defc T_OLD_2 = T_OLD_1+24
defc T_OLD_3 = T_OLD_2+24
defc T_OLD_0 = T_OLD_3+2
defc T_NEW_0 = T_OLD_0
defc T_NEW_1 = T_OLD_1
defc T_NEW_2 = T_NEW_0+24
defc T_NEW_3 = T_OLD_3

NT_:   defs 192 ;CreatedNoteTableAddress

;local var
defc Ampl = AYREGS+AmplC

defc VAR0END = VT_+16 ;INIT zeroes from VARS to VAR0END-1

VARSEND:

MDLADDR:

;Release 0 steps:
;11.Sep.2004 - Note tables creator
;12.Sep.2004 - Volume tables creator; INIT subroutine
;13.Sep.2004 - Play counters, position counters
;14.Sep.2004 - Patterns decoder subroutine
;15.Sep.2004 - Resting (no code)
;16.Sep.2004 - CHREGS subroutine; global debugging; 1st stable
;version was born
;17.Sep.2004 - Debugging and optimization. First release!
;Release 1 steps:
;20.Sep.2004 - local vars moved to code (selfmodified code
;smaller and faster)
;22.Sep.2004 - added mute sound entry at START+8; position
;pointer moved to START+11; added setup and status byte at
;START+10 noloop mode and loop passed flags added
;Release 2 steps:
;28.Sep.2004 - Optimization: code around CHREGS's volume and
;vibrato faster now; zeroing PD_RES through stack; Ton and Ampl
;moved from channel vars to global ones; first position selector
;removed from INIT; optimization for packers(Ivan Roshin method)
;Release 3 steps:
;2.Oct.2004 - optimization in INIT and PD_LOOP (thanks to Ivan
;Roshin)
;4.Oct.2004 - load delay from (hl) in INIT (2 bytes shorter)
;5.Oct.2004 - optimization in PD_LOOP (->PD_LP2)
;7.Oct.2004 - swaping some commands for better packing
;Release 4 steps:
;9.Oct.2004 - optimization around LD HL,SPCCOMS (thanks to Ivan
;Roshin); in PTDECOD swapped BC and DE to optimize C_PORTM;
;removed sam and orn len and loop channel vars; CHREGS totally
;optimized
;Release 5 steps:
;11.Oct.2004 - PD_OrSm and C_PORTM optimized; Ivan Roshin's
;volume tables creator algorithm (51 bytes shorter than mine)
;12.Oct.2004 - Ivan Roshin's note tables creator algorithm (74
;bytes shorter than mine)
;Release 6 steps:
;14.Oct.2004 - loop and next position calculations moved to INIT
;15.Oct.2004 - AdInPt moved to code
;19.Oct.2004 - Env_Del moved to code
;20.Oct.2004 - Version PUSH and POP (1 byte shorter, thanks to
;Ivan Roshin)
;22.Oct.2004 - Env_En moved from Flags' bit to byte (shorter and
;faster code)
;25.Oct.2004 - SETENV optimized
;29.Oct.2004 - Optimized around AddToEn (SBC A,A, thanks to Ivan
;Roshin)
;3.Nov.2004 - Note tables data was compressed; with depacker it
;is 9 bytes shorter than uncompressed (thanks to Ivan Roshin)
;4.Nov.2004 - default sample and ornament both are fixed now
;and placed into code block (6 bytes shorter)
;7.Nov.2004 - LD A,(Ns_Base):LD L,A changed to LD HL,(Ns_Base)
;(thanks to Dima Bystrov)
;9.Nov.2004 - Ns_Base and AddToNs are merged to Ns_Base_AddToNs;
;LD A,255 changed to DEC A (at start of PLAY); added ROUT_A0
;12.Nov.2004 - NtSkCn&Volume are merged (8 bytes smaller init);
;LD BC,T1_ changed to PUSH DE...POP BC in note table creator
;19.Dec.2004 - NT_DATA reorganized (6 bytes shorter, thanks to
;Ivan Roshin); C_PORTM and C_GLISS are merged via SET_STP (48
;tacts slower, but 8 bytes smaller, thanks to Ivan Roshin)
;Release 7 steps:
;29.Apr.2007 - SjAsm adaptation; new 1.xx and 2.xx
;interpretation for PT 3.7+.
;7.Sep.2017 - Modified by Hikaru/Intense: generalized ASM syntax
;for improved compatibility, added stack output (see SETUP byte)

;Tests in IMMATION TESTER V1.0 by Andy Man/POS (thanks to
;Himik's ZxZ for help):
;Module name/author  Min tacts   Max tacts   Average
;Spleen/Nik-O     1720     9256     5500
;Chuta/Miguel     1720     9496     5500
;Zhara/Macros     4536     8744     5500

;Size:
;Code block #676 bytes
;Variables #21D bytes (can be stripped)
;Size in RAM #676+#21D=#893 (2195) bytes

;Notes:
;Pro Tracker 3.4r can not be detected by header, so PT3.4r tone
;tables really used only for modules of 3.3 and older versions.
