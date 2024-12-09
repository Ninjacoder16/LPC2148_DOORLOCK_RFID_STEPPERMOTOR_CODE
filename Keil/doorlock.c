#include<lpc214x.h>
#include<string.h>
#include "lcd4bit.h"
#include "steppermotor.h"
#include "armuart.h"

 char ID[6];
 char ID1[6]="BBBAAA";
 char D;
 
int main(){
	while(1){
	LCD_4BITINIT();
	cmd(0x80);
	name("SCAN your card");
		print(":RFID:");
	for(int i=0; i<7; i++){
	b=rx();
	tx(b);
	ID[i]=b;
	}
	
	if(!strncmp(ID, ID1, 6)){
	print("opned:");
	cmd(0xC0);
	name("Door Opened WlCM:");
  stepper_clock();
	delay(50);
	stepper_original();

  }
	else{
		print("Incorrect ID");
	  cmd(0xC0);
	  name("Incorrect ID:");
		delay(300);
	}
 }
}

