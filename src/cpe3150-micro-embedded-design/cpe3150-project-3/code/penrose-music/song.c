#include <reg932.h>
#include <song.h>

unsigned int *p_per;
code unsigned int quarterNote = TEMPO * 4, eighthNote = TEMPO*2, sixteenthNote = TEMPO, halfNote = TEMPO * 8, wholeNote = TEMPO*16;
code unsigned int period[] = {C2, Db2, D2, Eb2, E2, F2, Gb2, G2, Ab2, A2, Bb2, B2,
						      C3, Db3, D3, Eb3, E3, F3, Gb3, G3, Ab3, A3, Bb3, B3,
	                                  C4, Db4, D4, Eb4, E4, F4, Gb4, G4, Ab4, A4, Bb4, B4,
	                                  C5, Db5, D5, Eb5, E5, F5, Gb5, G5, Ab5, A5, Bb5, B5,
	                                  C6, Db6, D6, Eb6, E6, F6, Gb6, G6, Ab6, A6, Bb6, B6,
	                                  C7};
void clk( void ) interrupt 3 using 1
{
    TH1=-(*p_per)>>8;
    TL1=-(*p_per)&0x0ff;
    SPKR = ~SPKR;
}		

void playConstantSong(char notes[], char length, int numNotes)
{
    int i, j;
	for(i = 0; i < numNotes; i++)
	{
		playNote(notes[i], length);

		if (SW7 == 0) {
			length/=2;
			delayms(40);
		}
		else if(SW9 == 0)
		{
			length*=2;
			delayms(40);
		}
	    else if (SW1 == 0) {
			while(SW1==0);
			delayms(10);
			break;
		}

		j = 0;
	}
}

void playSong(char notes[], char lengths[], int numNotes)
{
	int i;
	for(i = 0; i < numNotes; i++)
	{
		playNote(notes[i], lengths[i]);
	}
}
						
void playNote(char note, int noteType)
{
	int i;
	int length;
	p_per = &period[note];
	switch (noteType)
	{
		case 1:
			length = wholeNote;
			break;
		case 2:
			length = halfNote;
			break;
		case 4:
			length = quarterNote;
			break;
		case 8:
			length = eighthNote;
			break;
		case 16:
			length = sixteenthNote;
			break;
	}
	TH1=-(*p_per)>>8;
  	TL1=-(*p_per)&0x0ff;
	ET1=1;
	TR1=1;

	delayms(length);
	TR1 = 0;
	delayms(4);
}

void delayms(int numMS)
{
	int i;
	for(i = 0; i < numMS; i++)
	{
		delay1ms();
	}
}

void delay1ms()
{
		TH0=-0x0E;
    TL0=-0x66;
		TR0 = 1;
		while(TF0 == 0);
		TR0 = 0;
		TF0 = 0;
}
