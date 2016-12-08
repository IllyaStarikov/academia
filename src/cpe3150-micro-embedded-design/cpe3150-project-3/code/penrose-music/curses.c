#include<uart.h>
#include<curses.h>
#include <REG932.h>

void addch(unsigned char value){
		uart_isr();
		uart_transmit(value);
		while(TI==0);
}

void clear_screen(){
	addch('\033');
	addch('[');
	addch('2');
	addch('J');
	zero_cursor();
}

void print_string(unsigned char string[]){
unsigned char i=0;
	while(string[i] != '\0'){
		addch(string[i]);
		i++;
	}

}
void cursor_jump(unsigned char jump, unsigned char direction){
	unsigned char i,escape[] = "\033[1A"; //automatically going up
	escape[2] = jump + '0';//convert y to char and replace default jump value 9 is max value
	switch(direction){ //Takes user entered direction and conversts escape string
		case 'U': 
			escape[3] = 'A'; 
			break;
		case 'D': 
			escape[3] = 'B'; 
			break;
		case 'L': 
			escape[3] = 'D';
			break;
		case 'R':
			escape[3] = 'C';
			break;
	}
	
	//prints escape ANSI escape sequence to putty
	for(i = 0; i< 4 ; i++){
		addch(escape[i]);
	}
}

void zero_cursor(){
	unsigned char i;
	addch('\r');
	for(i=0;i<10;i++){
		cursor_jump(8,'U');
	}
}

void move(unsigned char y, unsigned char x){
	unsigned char i;
	zero_cursor();
	for(i=0; i<x ; i++)
	{
		cursor_jump(1,'R');
	}
	for(i=0; i<y; i++){
		cursor_jump(1,'D');
	}
}

void save_cursor(){
	addch('\033');
	addch('[');
	addch('s');
}

void highlight(){
	addch('\033');
	addch('[');
	addch('5');
	addch('m');
}

void attroff(){
	addch('\033');
	addch('[');
	addch('0');
	addch('m');
}

void to_saved(){
	addch('\033');
	addch('[');
	addch('u');
}