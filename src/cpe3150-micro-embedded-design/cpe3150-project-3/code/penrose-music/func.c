#include<REG932.h>
#include<song.h>
#include<func.h>

void keyboard(){
unsigned char run = 1;
	P2M2 = 0;
	while(run){
		if(!SW1){
			while(!SW1);
			led1 = 0;
			playNote(24, 4);
			led1 = 1;
		}
		else if(!SW2){
			while(!SW2);
			led2 = 0;
			playNote(26, 4);
			led2 = 1;
		}
		else if(!SW3){
			while(!SW3);
			led3 = 0;
			playNote(28, 4);
			led3 = 1;
		}
		else if(!SW4){
			while(!SW4);
			led4 = 0;
			playNote(29, 4);
			led4 = 1;
		}
		else if(!SW5){
			while(!SW5);
			led5 = 0;
			playNote(31, 4);
			led5 = 1;
		}
		else if(!SW6){
			while(!SW6);
			led6 = 0;
			playNote(33, 4);
			led6 = 1;
		}
		else if(!SW7){
			while(!SW7);
			led7 = 0;
			playNote(35, 4);
			led7 = 1;
		}
		else if(!SW8){
			while(!SW8);
			led8 = 0;
			playNote(36, 4);
			led8 = 1;
		}
		if(!SW9){
			while(!SW8);
			run =0;
		}
	}
				SW1 = 1;
				SW2 = 1;
				SW3 = 1;
				SW4 = 1;
				SW5 = 1;
				SW6 = 1;
				SW7 = 1;
				SW8 = 1;
				SW9 = 1;
	P2M2 = 0xFF;
}

void counter(){
unsigned char run = 1;
P2= 0x3f;
while(run){
if(!SW2)
	{
		while(!SW2);
		incrementCounter();
		delayms(10);		
	}
	if(!SW8)
	{
		while(!SW8);
		decrementCounter();
		delayms(10);
	}
 	if(!SW6){
 		while(!SW6);
		run = 0;
	 }
 }
}

void incrementCounter()
{
	switch(P2)
	{
		case 0x3f:
			P2 = 0x06;
		  break;
		case 0x06:
			P2 = 0x5B;
			break;
		case 0x5B:
			P2 = 0x4F;
			break;
		case 0x4F:
			P2 = 0x66;
			break;
		case 0x66:
			P2 = 0x6D;
			break;
		case 0x6D:
			P2 = 0x7D;
			break;
		case 0x7D:
			P2 = 0x07;
			break;
		case 0x07:
			P2 = 0x7F;
			break;
		case 0x7F:
			P2 = 0x6F;
			break;
		case 0x6F:
			P2 = 0x3F;
			break;
	}
}

void decrementCounter()
{
	switch(P2)
	{
		case 0x06:
			P2 = 0x3f;
		  break;
		case 0x5B:
			P2 = 0x06;
			break;
		case 0x4F:
			P2 = 0x5B;
			break;
		case 0x66:
			P2 = 0x4F;
			break;
		case 0x6D:
			P2 = 0x66;
			break;
		case 0x7D:
			P2 = 0x6D;
			break;
		case 0x07:
			P2 = 0x7D;
			break;
		case 0x7F:
			P2 = 0x07;
			break;
		case 0x6F:
			P2 = 0x7F;
			break;
		case 0x3F:
			P2 = 0x6F;
			break;
	}
}
