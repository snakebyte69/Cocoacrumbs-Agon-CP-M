//------------------------------------------------------------------------
// Copyright (c) 2019, Christopher D. Farrar
//------------------------------------------------------------------------
// I here grant permission to any and all to copy and use this software for
// any purpose as long as my copyright message is retained.
//------------------------------------------------------------------------
#include <ez80.h>
#include <stdio.h>
//------------------------------------------------------------------------
#include "cpmload.h"
#include "sdcard.h"
//------------------------------------------------------------------------

void wait_ESP32(void) {
	INT ch = 0; 	
	while(ch != 27) {
		ch = getch();
	}	
}

int main()
{ 
    init_hw();

    setbaud_UART0(384000);
    setstopbits_UART0(STOPBITS_1);

 	wait_ESP32();			// Wait for the ESP32 to finish its bootup

    printf("Hi there CP/M!\n");

    // while(1)
    //     ;    

    /* Start CP/M */
    for ( ; ; )
    {
        startCpm();
    }

    return 0;
}
//------------------------------------------------------------------------
















