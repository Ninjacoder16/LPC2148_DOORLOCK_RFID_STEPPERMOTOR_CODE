#include<lpc214x.h>

void tx(char a);
char rx(void);
void display_uart( char *p);
void pll(void);
void init_uart(void);
void start(char *p);
void print( char *pi);
void print1( char pi);

// UART Transmission and Reception Buffers
char b;

// UART Initialization Function
void init_uart()
{    
	  PINSEL0 = 0x00000005;
    U0LCR = 0x83;  // Set DLAB bit in LCR (Line Control Register)
    U0DLL = 0x86;  // Load value to DLL (Divisor Latch Low Byte) for 9600 baud
    U0DLM = 0x01;  // Load value to DLM (Divisor Latch High Byte)
    U0LCR = 0x03;  // Reset DLAB bit (8-bit word length, no parity, 1 stop bit)
}

// UART Transmit Function
void tx(char a)
{
    U0THR = a;  // Load the character into Transmit Holding Register
    // Wait for THR (Transmit Holding Register) to be empty before sending another character
    while ((U0LSR & (1 << 5)) == 0);  // Wait for the THRE (Transmit Holding Register Empty) bit
}

// UART Receive Function
 char rx(void)
{
    // Wait for data to be available in the Receive Holding Register
    while ((U0LSR & (1 << 0)) == 0);  // Wait for DR (Data Ready) bit to be set
    b = U0RBR;  // Read received byte from Receive Buffer Register
    return b;
}

// PLL Configuration Function to set system clock to 60 MHz
void pll(void)
{
    PLL0CON = 0x00;  // Disable PLL0
    PLL0CFG = 0x24;  // Set the PLL multiplier and divider to get 60 MHz
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;
    // Wait for PLL to lock
    while ((PLL0STAT & (1 << 10)) == 0);
    PLL0CON = 0x03;  // Enable PLL0 and connect PLL0 output
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;
    VPBDIV = 0x01;  // Set the VPB (Peripheral Clock) divider to 1 (60 MHz)
}

// Function to display a string via UART

void start(char *p)
{
    PINSEL0 = 0x00000005;  // Enable UART0 TX (P0.0) and RX (P0.1)
    pll();                 // Configure PLL to 60 MHz system clock
    init_uart();           // Initialize UART0 with the required configuration
	  //display_uart("Hello aarti");
}

void print(char *pi)
{
    PINSEL0 = 0x00000005;  // Enable UART0 TX (P0.0) and RX (P0.1)
    pll();                 // Configure PLL to 60 MHz system clock
    init_uart();           // Initialize UART0 with the required configuration
    while (*pi != '\0')  // Loop through the string until null terminator
    {
        tx(*pi++);  // Transmit each character of the string
    }

}
