#include<lpc214x.h>
void lcd_int(void);
void delay(int m);
void cmd( int a );
void Data( int b );
void name( char *ptr);
void LCD_4BITINIT(void);

void LCD_4BITINIT(void){
	PINSEL2 =0X00000000;         //Declaring the IO pins port1
  IODIR1 = 0X0007F0000;        //
	lcd_int();
}

void lcd_int(void){
	cmd(0x02);            
	cmd(0x28);
	cmd(0x01);
	cmd(0x0F); 
	cmd(0x06);	
	cmd(0x80); 
	delay(1);
}

void cmd( int a ){
	 IOCLR1 = 0X007F0000;          // 0.16 to 0.23 OUTPUT datalines RS=0.14 EN=0.15;
	 int b = a>>4;
	 IOSET1=(b<<19);
	 IOCLR1=(1<<16);  //0X00FF8000  //RS
	 IOSET1=(1<<18);  //0X00FF8000  //EN
	 delay(1);
	 IOCLR1=(1<<18);  //0X00FF8000
	 delay(1);
	
	 IOCLR1 = 0X007F0000;          // 0.16 to 0.23 OUTPUT datalines RS=0.14 EN=0.15;
	 IOSET1=(a<<19);
	 IOCLR1=(1<<16);  //0X00FF8000   //RS
	 IOSET1=(1<<18);  //0X00FF8000   //EN
	 delay(1);
	 IOCLR1=(1<<18);  //0X00FF8000
	 delay(1);
}

void Data( int b ){
	 IOCLR1 = 0X007F0000; 
	 int a = b>>4;                            //higher bits of a
	 IOSET1=(a<<19);
	 IOSET1=(1<<16);  //0X00FF8000
	 IOSET1=(1<<18);  //0X00FF8000
	 delay(1);
	 IOCLR1=(1<<18);  //0X00FF8000
	 delay(1);
	
	 IOCLR1 = 0X007F0000;          // 0.16 to 0.23 OUTPUT datalines RS=0.14 EN=0.15;
	 IOSET1=(b<<19);
	 IOSET1=(1<<16);  //0X00FF8000
	 IOSET1=(1<<18);  //0X00FF8000
	 delay(1);
	 IOCLR1=(1<<18);  //0X00FF8000
	 delay(1);
	
	
}

void delay(int m){
int i;
for(i=0; i<12300*m; i++);
}

void name( char *ptr){
	unsigned int i;
	for(i=0; *ptr!='\0'; i++){
	  Data(*ptr++);
	}
}
