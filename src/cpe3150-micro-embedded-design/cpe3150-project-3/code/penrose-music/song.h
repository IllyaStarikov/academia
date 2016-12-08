#ifndef SONG_H
#define SONG_H

sbit SPKR = P1^7;
sbit a = P2^0;
sbit b = P2^1;
sbit c = P2^2;
sbit d = P2^3;
sbit e = P2^4;
sbit f = P2^5;
sbit g = P2^6;
#define OSC_FREQ		7372800
#define MAX_DELAY      700 //(OSC_FREQ/10532)
#define TEMPO			95		/* Duration of a 64th note */

//Most of these note definitions were taken from the Simon 2 website
#define C2        ((OSC_FREQ/4)/65.41)  //0
#define Db2       ((OSC_FREQ/4)/69.30)  //1
#define D2        ((OSC_FREQ/4)/73.42)  //2
#define Eb2       ((OSC_FREQ/4)/77.78)  //3
#define E2        ((OSC_FREQ/4)/82.41)  //4
#define F2        ((OSC_FREQ/4)/87.31)  //5
#define Gb2       ((OSC_FREQ/4)/92.5)   //6
#define G2        ((OSC_FREQ/4)/98.00)  //7
#define Ab2       ((OSC_FREQ/4)/103.83) //8
#define A2        ((OSC_FREQ/4)/110.00) //9
#define Bb2       ((OSC_FREQ/4)/116.54) //10
#define B2        ((OSC_FREQ/4)/123.47) //11
#define C3				((OSC_FREQ/4)/130.81) //12
#define Db3				((OSC_FREQ/4)/138.59) //13
#define D3				((OSC_FREQ/4)/146.83) //14
#define Eb3				((OSC_FREQ/4)/155.56) //15
#define E3				((OSC_FREQ/4)/164.81) //16
#define F3				((OSC_FREQ/4)/174.61) //17
#define Gb3       ((OSC_FREQ/4)/185.00) //18
#define G3				((OSC_FREQ/4)/196.00) //19
#define Ab3				((OSC_FREQ/4)/207.65) //20
#define A3				((OSC_FREQ/4)/220.00) //21
#define Bb3				((OSC_FREQ/4)/233.08) //22
#define B3				((OSC_FREQ/4)/246.94) //23
#define C4				((OSC_FREQ/4)/261.63) //24
#define Db4				((OSC_FREQ/4)/277.18) //25
#define D4				((OSC_FREQ/4)/293.67) //26
#define Eb4				((OSC_FREQ/4)/311.13) //27
#define E4				((OSC_FREQ/4)/329.63) //28
#define F4				((OSC_FREQ/4)/349.23) //29
#define Gb4				((OSC_FREQ/4)/369.99) //30
#define G4				((OSC_FREQ/4)/392.00) //31
#define Ab4				((OSC_FREQ/4)/415.30) //32
#define A4				((OSC_FREQ/4)/440.00) //33
#define Bb4				((OSC_FREQ/4)/466.16) //34
#define B4				((OSC_FREQ/4)/493.88) //35
#define C5				((OSC_FREQ/4)/523.25) //36
#define Db5				((OSC_FREQ/4)/554.37) //37
#define D5				((OSC_FREQ/4)/587.33) //38
#define Eb5				((OSC_FREQ/4)/622.25) //39
#define E5				((OSC_FREQ/4)/659.26) //40
#define F5				((OSC_FREQ/4)/698.46) //41
#define Gb5				((OSC_FREQ/4)/739.99) //42
#define G5				((OSC_FREQ/4)/783.99) //43
#define Ab5				((OSC_FREQ/4)/830.61) //44
#define A5				((OSC_FREQ/4)/880.00) //45
#define Bb5				((OSC_FREQ/4)/932.33) //46
#define B5				((OSC_FREQ/4)/987.77) //47
#define C6				((OSC_FREQ/4)/1046.5) //48
#define Db6				((OSC_FREQ/4)/1108.7) //49
#define D6				((OSC_FREQ/4)/1174.7) //50
#define Eb6				((OSC_FREQ/4)/1244.5) //51
#define E6				((OSC_FREQ/4)/1318.5) //52
#define F6				((OSC_FREQ/4)/1396.9) //53
#define Gb6				((OSC_FREQ/4)/1480.0) //54
#define G6				((OSC_FREQ/4)/1568.0) //55
#define Ab6				((OSC_FREQ/4)/1661.2) //56
#define A6				((OSC_FREQ/4)/1760.0) //57
#define Bb6				((OSC_FREQ/4)/1864.7) //58
#define B6				((OSC_FREQ/4)/1975.5) //59
#define C7				((OSC_FREQ/4)/2093.0) //60
	
void playNote(char note, int noteType);
void playSong(char notes[], char lengths[], int numNotes);
void playConstantSong(char notes[], char length, int numNotes);
void delay1ms();
void delayms(int);

#endif SONG_H
