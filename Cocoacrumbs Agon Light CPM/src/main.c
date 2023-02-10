#include <ez80.h>
#include <stdio.h>
//------------------------------------------------------------------------
#include "cpmload.h"
#include "sdcard.h"
//------------------------------------------------------------------------

void wait_ESP32(void) 
{
	INT ch = 0; 	

	while(ch != 27) 
    {
		ch = getch();
	}	
}

int main()
{ 
    init_hw();

    setbaud_UART0(384000);
    setstopbits_UART0(STOPBITS_1);
    
 	wait_ESP32();			        // Wait for the ESP32 to finish its bootup

    printf("\nLoading CP/M\n\n");

    /* Start CP/M */
    startCpm();    

    while(1)
        ;
}
