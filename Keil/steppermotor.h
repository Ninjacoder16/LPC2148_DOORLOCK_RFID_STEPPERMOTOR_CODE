#include<lpc214x.h>
#define Switch (1<<16)

void switch_control(void);
void stepper_clock(void);
void stepper_original(void);
void stepper_init(void);
void delay_ms(int j);

void delay_ms(int j)
{
    int x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);    /* loop to generate 1 milisecond delay with Cclk = 60MHz */
	}
}

void stepper_init(void){
	  PINSEL0|= 0x00000000;                         // Setting pin P0.1 of LPC2148 as PWM3
	  IODIR0|=  0x000000F0;		
}

void stepper_clock(void){
		stepper_init();

  for(int i=0; i<12; i++){
		IOSET0|=0x00000010;
		IOCLR0|=0x000000E0;
		delay_ms(100);
    IOSET0|=0x00000020;
		IOCLR0|=0x000000D0;
		delay_ms(100);
    IOSET0|=0x00000040;
		IOCLR0|=0x000000B0;
		delay_ms(100);
    IOSET0|=0x00000080;
		IOCLR0|=0x00000070;
		delay_ms(100);
	}
}
void stepper_original(void){
		stepper_init();

	 for(int i=0; i<12; i++){
	  IOSET0|=0x00000080;
		IOCLR0|=0x00000070;
		delay_ms(100);
    IOSET0|=0x00000040;
		IOCLR0|=0x000000B0;
		delay_ms(100);
    IOSET0|=0x00000020;
		IOCLR0|=0x000000D0;
		delay_ms(100);
		IOSET0|=0x00000010;
		IOCLR0|=0x000000E0;
		delay_ms(100);
	 }
	 
}

void switch_control(void){
	if((IOPIN1&Switch)){
	IOCLR1|=  0x00020000;	
  }
	else{
	IOSET1|=  0x00020000;	
	stepper_clock();
	}
}

void open_60(void){        // YOU CAN USE THIS FUNCTION IF angle is 60 in proteus for stepper motor
	stepper_init();
//for(int i=0; i<1; i++){
		delay_ms(100);
		IOSET0|=0x00000010;
		IOCLR0|=0x000000E0;
		delay_ms(100);
    IOSET0|=0x00000020;
		IOCLR0|=0x000000D0;
		//delay_ms(100);
    //IOSET0|=0x00000040;
		//IOCLR0|=0x000000B0;
		//delay_ms(100);
    //IOSET0|=0x00000080;
		//IOCLR0|=0x00000070;
 
//}
}

void original_60(void){        // YOU CAN USE THIS FUNCTION IF angle is 60 in proteus for stepper motor
	stepper_init();
//for(int i=0; i<1; i++){
		IOSET0|=0x00000080;
		IOCLR0|=0x00000070;
		delay_ms(80);
    IOSET0|=0x00000040;
		IOCLR0|=0x000000B0;
		delay_ms(80);
    IOSET0|=0x00000020;
		IOCLR0|=0x000000D0;
		delay_ms(80);
		IOSET0|=0x00000010;
		IOCLR0|=0x000000E0;

   // IOSET0|=0x00000010;
		//IOCLR0|=0x000000E0;
		//delay_ms(100);
    //IOSET0|=0x00000040;
		//IOCLR0|=0x000000B0;
		//delay_ms(100);
    //IOSET0|=0x00000080;
		//IOCLR0|=0x00000070;
		//delay_ms(100);
 
//}
}
