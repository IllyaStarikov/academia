;*******************************************************************
;   P89LPC932 Special Function Registers
;*******************************************************************
;
;******* System ****************
ACC	    DATA	0xE0
B	    DATA	0xF0
SP	    DATA	0x81
DPL	    DATA	0x82
DPH	    DATA	0x83
RSTSRC	DATA	0xDF
PCON	DATA	0x87
PCONA	DATA	0xB5
PSW	    DATA	0xD0
DIVM	DATA	0x95
TRIM	DATA	0x96
AUXR1	DATA	0xA2
;------- Bit Addressable -------
CY	    BIT	    0xD7
AC	    BIT	    0xD6
F0	    BIT	    0xD5
RS1	    BIT	    0xD4
RS0	    BIT	    0xD3
OV	    BIT	    0xD2
F1	    BIT	    0xD1
P	    BIT	    0xD0
XTAL1	BIT	    0xB1
XTAL2	BIT	    0xB0
;******* Ports *****************
P0	    DATA	0x80
P0M1	DATA	0x84
P0M2	DATA	0x85
PT0AD	DATA	0xF6
P1	    DATA	0x90
P1M1	DATA	0x91
P1M2	DATA	0x92
P2	    DATA	0xA0
P2M1	DATA	0xA4
P2M2	DATA	0xA5
P3	    DATA	0xB0
P3M1	DATA	0xB1
P3M2	DATA	0xB2
;******* EEPROM ****************
DEECON	DATA	0xF1
DEEDAT	DATA	0xF2
DEEADR	DATA	0xF3
;******* Keypad ****************
KBMASK	DATA	0x86
KBPATN	DATA	0x93
KBCON	DATA	0x94
;------- Bit Addressable -------
KB0	    BIT	    0x80
KB1	    BIT	    0x81
KB2	    BIT	    0x82
KB3	    BIT	    0x83
KB4	    BIT	    0x84
KB5	    BIT	    0x85
KB6	    BIT	    0x86
KB7	    BIT	    0x87
;******* Comparators ***********
CMP1	DATA	0xAC
CMP2	DATA	0xAD
;------- Bit Addressable -------
CMP1O   BIT     0x86
CMPREF  BIT     0x85
CIN1A   BIT     0x84
CIN1B   BIT     0x83
CIN2A   BIT     0x82
CIN2B   BIT     0x81
CMP2O   BIT     0x80
;******* Serial Port ***********
SCON	DATA	0x98
SBUF	DATA	0x99
SADDR	DATA	0xA9
SADEN	DATA	0xB9
SSTAT	DATA	0xBA
BRGCON	DATA	0xBD
BRGR0	DATA	0xBE
BRGR1	DATA	0xBF
;------- Bit Addressable -------
FE	    BIT	    0x9F
SM0	    BIT	    0x9F
SM1	    BIT	    0x9E
SM2	    BIT	    0x9D
REN	    BIT	    0x9C
TB8	    BIT	    0x9B
RB8	    BIT	    0x9A
TI	    BIT	    0x99
RI	    BIT	    0x98
RxD	    BIT	    0x91
TxD	    BIT	    0x90
;******* SPI *******************
SPSTAT	DATA	0xE1
SPCTL	DATA	0xE2
SPDAT	DATA	0xE3
;------- Bit Addressable -------
SPICLK	BIT	    0xA5
SS	    BIT	    0xA4
MISO	BIT	    0xA3
MOSI	BIT	    0xA2
;******* IIC *******************
I2CON	DATA	0xD8
I2STAT	DATA	0xD9
I2DAT	DATA	0xDA
I2ADR	DATA	0xDB
I2SCLL	DATA	0xDC
I2SCLH	DATA	0xDD
;------ Bit Addressable --------
I2EN	BIT	    0xDE
STA	    BIT	    0xDD
STO	    BIT	    0xDC
SI	    BIT	    0xDB
AA	    BIT	    0xDA
CRSEL	BIT	    0xD8
SDA	    BIT	    0x93
SCL	    BIT	    0x92
;******* Timers ****************
TPCR2L	DATA	0xCA
TPCR2H	DATA	0xCB
TCON	DATA	0x88
TMOD	DATA	0x89
TL0	    DATA	0x8A
TH0	    DATA	0x8C
TL1	    DATA	0x8B
TH1	    DATA	0x8D
TL2	    DATA	0xCC
TH2	    DATA	0xCD
TAMOD	DATA	0x8F
;------- Bit Addressable -------
TF1	    BIT	    0x8F
TR1	    BIT	    0x8E
TF0	    BIT	    0x8D
TR0	    BIT	    0x8C
IE1	    BIT	    0x8B
IT1	    BIT	    0x8A
IE0	    BIT	    0x89
IT0	    BIT	    0x88
PLLEN	BIT	    0xCF
HLTRN	BIT	    0xCE
HLTEN	BIT	    0xCD
ALTCD	BIT	    0xCC
ALTAB	BIT	    0xCB
TDIR2	BIT	    0xCA
TMOD21	BIT	    0xC9
TMOD20	BIT	    0xC8
T1	    BIT	    0x87
T0	    BIT	    0x92
;******* Capture/Compare Unit **
CCCRA	DATA	0xEA
CCCRB	DATA	0xEB
CCCRC	DATA	0xEC
CCCRD	DATA	0xED
TCR20	DATA	0xC8
TCR21	DATA	0xF9
TICR2	DATA	0xC9
TISE2	DATA	0xDE
TIFR2	DATA	0xE9
TOR2L	DATA	0xCE
TOR2H	DATA	0xCF
;******* Input Capture *********
ICRAL	DATA	0xAA
ICRAH	DATA	0xAB
ICRBL	DATA	0xAE
ICRBH	DATA	0xAF
;------- Bit Addressable -------
ICA	    BIT	    0xA7
ICB	    BIT	    0xA0
;******* Output Compare ********
OCRAL	DATA	0xEE
OCRAH	DATA	0xEF
OCRBL	DATA	0xFA
OCRBH	DATA	0xFB
OCRCL	DATA	0xFC
OCRCH	DATA	0xFD
OCRDL	DATA	0xFE
OCRDH	DATA	0xFF
;------- Bit Addressable -------
OCD	    BIT	    0xA1
OCC	    BIT	    0x97
OCB	    BIT	    0x96
OCA	    BIT	    0xA6
;******* Watchdog **************
WFEED1	DATA	0xC2
WFEED2	DATA	0xC3
WDL	    DATA	0xC1
WDCON	DATA	0xA7
;******* Real Time Clock *******
RTCL	DATA	0xD3
RTCH	DATA	0xD2
RTCCON	DATA	0xD1
;******* Interrupts ************
IEN0	DATA	0xA8
IEN1	DATA	0xE8
IP0	    DATA	0xB8
IP0H	DATA	0xB7
IP1	    DATA	0xF8
IP1H	DATA	0xF7
;------- Bit Addressable -------
EA	    BIT	    0xAF
EWDRT	BIT	    0xAE
EBO	    BIT	    0xAD
ES	    BIT	    0xAC
ESR	    BIT	    0xAC
ET1	    BIT	    0xAB
EX1	    BIT	    0xAA
ET0	    BIT	    0xA9
EX0	    BIT	    0xA8
EIEE	BIT	    0xEF
EST	    BIT	    0xEE
ECCU	BIT	    0xEC
ESPI	BIT	    0xEB
EC	    BIT	    0xEA
EKBI	BIT	    0xE9
EI2C	BIT	    0xE8
PWDRT	BIT	    0xBE
PB0	    BIT	    0xBD
PS	    BIT	    0xBC
PSR	    BIT	    0xBC
PT1	    BIT	    0xBB
PX1	    BIT	    0xBA
PT0	    BIT	    0xB9
PX0	    BIT	    0xB8
PIEE	BIT	    0xFF
PST	    BIT	    0xFE
PCCU	BIT	    0xFC
PSPI	BIT	    0xFB
PCL     BIT	    0xFA
PKBI	BIT	    0xF9
PI2C	BIT	    0xF8
RST	    BIT	    0x95
INT1	BIT	    0x94
INT0	BIT	    0x93















