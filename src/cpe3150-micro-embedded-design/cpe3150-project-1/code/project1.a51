	#include<reg932.inc>
	
	RANDREG EQU 0X20
		
	CSEG AT 0
	
	MOV R2, #0
	MOV P3M1, #00H
    MOV P3M2, #00H
    MOV P2M1, #00H
    MOV P2M2, #00H
    MOV P1M1, #00H
    MOV P1M2, #00H
    MOV P0M1, #00H
    MOV P0M2, #00H
				
MAIN:
	JB P2.0, NO_DEC

WAIT1:
	JNB P2.0, WAIT1
	DEC R2
	CJNE R2, #0FFH, LED
	ACALL BEEP 
	MOV R2, #15
	SJMP LED

NO_DEC:
	JB P0.1, MAIN

WAIT2:
	JNB P0.1, WAIT2
	INC R2
	CJNE R2, #16, LED
	ACALL BEEP
	MOV R2, #0
	SJMP LED
	
LED:
	MOV A, R2
	CPL A
	RRC A
	MOV P0.6, C
	RRC A
	MOV P2.7, C
	RRC A
	MOV P0.5, C
	RRC A
	MOV P2.4, C
	SJMP MAIN
	
	
; this mostly came from trial and error
; and seeing what sounded good for a beep
; reference canvas tutorial for this
BEEP: 
	MOV R0, #100
S1:	CPL P1.7
	ACALL SDELAY
	DJNZ R0, S1
	
	RET
	
SDELAY: 
	MOV R1, #100
D1: MOV R2, #10
D2: DJNZ R2, D2
	DJNZ R1, D1
	RET


; note this a port from http://pjrc.com/tech/8051/rand.asm
; returns a random value in the A register from 0 to 9, inclusive.
; note needs a seed value (equated at the top)
RNG:
	MOV	A, RANDREG
	JNZ	RAND8B
	CPL	A
	MOV	RANDREG, A
RAND8B:	ANL	A, #10111000B
	MOV	C, PSW.0
	MOV	A, RANDREG
	RLC	A
	MOV	RANDREG, A
	MOV B, #10D
	DIV AB
	MOV A, B

	RET
	
	
	END
