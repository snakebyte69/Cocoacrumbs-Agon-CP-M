/*
 * Title:			Minimal example code using UART0 on a eZ80F92 to talk with the ESP32 video terminal
 * Author:			Cocoacrumbs
 * Created:			13/07/2022
 * Last Updated:	13/07/2022
 *
 * Info:            This code does not use the C Runtime nor the ZSL libraries.
 */

#include <eZ80.h>
#include <stdio.h>

#define UART_BPS             384000
#define UART_DATA_BITS       8
#define UART_PARITY          0
#define UART_STOP_BITS       1

#define LCTL_DLAB            (unsigned char)0x80
#define LSR_THRE             (unsigned char)0x20
#define LSR_DR               (unsigned char)0x01
 
#define SetLCTL(d, p, s)     UART0_LCTL = ((d-5)&3) | (((s-1)&1)<<2) | (p&3)

#define LF                   '\n'
#define CR                   '\r'
 
extern long SysClkFreq;
char        device_name[]   = "eZ80F92";


void uart_init(void) 
{ 
    unsigned short int  i;
    unsigned short      brg;

    brg = SysClkFreq/(16 * UART_BPS);
 
    PD_ALT2 = 0x03;
    PD_ALT1 = 0x00;
    PD_DDR  = 0xEB;
    PD_DR   = 0x00;
	
	// enable serial driver
    PB_DR   = 0x40;
    PB_ALT2 = 0x00;
    PB_ALT1 = 0x00;
    PB_DDR  = 0xBF;

    UART0_LCTL  |= LCTL_DLAB;
    UART0_BRG_L  = (brg & (unsigned short)0x00FF);
    UART0_BRG_H  = (brg & (unsigned short)0xFF00) >> (unsigned short)8;
    UART0_LCTL  &= ~LCTL_DLAB;
    UART0_FCTL   = 0x07;	// eZ80F91 date codes 0611 and after requires disabling FIFO.
    SetLCTL(UART_DATA_BITS, UART_PARITY, UART_STOP_BITS);
} /* end uart_init */


int putch(int ch)
{
    while ((UART0_LSR & LSR_THRE) == (unsigned char)0);
    UART0_THR = ch;
    if (ch == LF)
    {
        while ((UART0_LSR & LSR_THRE) == (unsigned char)0);
        UART0_THR = CR;
    }
    return (ch);
} /* end putch */


int getch(void)
{
    while ((UART0_LSR & LSR_DR) == (unsigned char)0);
    return (UART0_RBR);
} /* end getch */


void printString(char* str)
{
    while (*str != 0)
    {
        putch(*str);
        str++;
    } /* end while */
} /* end printString */


int main()
{
    int ch;

    uart_init();

    printString("\n");
    printString("Hello from the eZ80F92 talking to the ESP32.\n");
    printString("Using UART0 @ 384000 baud / 8N1\n");
 
    while (1)
    {   
        ch = getch();
        putch(ch);
        if (ch == '\r')
        {
			putch( '\n' ) ;
        } /* end if */
    } /* end while */
    return 0;
} /* end main */
