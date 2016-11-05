#include <reg932.inc>
	CSEG AT 200H // find a safe place to pace db values
NOTES: db 64,21, 64,21, 64,20, 64,18, 64,18, 64,20, 64,21, 64,24, 64,27, 64,27, 64,24, 64,21, 64,21, 64,24, 64,24
	
	CSEG AT 0
	setb PSW.3
	mov p2m1,#0  			
start:   			
mov c,p2.0  		
SONG: mov DPTR, #200H
mov R0,#0FH
read_NOTES: clr A
	movc A, @A+DPTR
	mov R1, A
	clr A
	INC DPTR
	movc A, @A+DPTR
	mov R6, A
	lcall play_NOTE
	lcall pause
	inc DPTR
	DJNZ R0, read_NOTES
ret

play_NOTE: 
	mov 0c, R6
	mov 0b, R1
	mov R3, #20
	time_loop1:
	mov R7, #10
	time_loop2:
	mov R1, 0b
	freq_loop1:
	mov R6, 0c
	freq_loop0:nop
	djnz R6, freq_loop0
	djnz R1, freq_loop1
	cpl P1.7
	djnz R7, time_loop2
	djnz R3, time_loop1
ret

pause:
  mov R3, #30
  time1: mov R7, #20
  time2: nop
  djnz R7, time2
  djnz R3, time1
ret
DONE:
END
