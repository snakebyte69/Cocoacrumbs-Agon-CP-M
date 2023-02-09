//----------------------------------------------------------------------------
// Copyright (c) 2018, Christopher D. Farrar
//----------------------------------------------------------------------------
#include "kbhit.h"
//----------------------------------------------------------------------------
#include "agonLight.h"
//----------------------------------------------------------------------------
extern UCHAR FifoEmpty( FIFO *f );
extern UCHAR g_mode_UART0;
extern FIFO g_RxFIFO_UART0;
//----------------------------------------------------------------------------
UCHAR kbhit_UART0( VOID )
{
	if( INTERRUPT == g_mode_UART0 )									//! The interrupt mode to be used.
	{
		if( FifoEmpty( &g_RxFIFO_UART0 ) )							//! FIFO is empty.
		{
			UART0_SPR = UART_ERR_RECEIVEFIFOEMPTY ;					//! Update SPR register.
			return 0 ;
		}
		else														//! A keyboard stroke detected!
		{
			return 1 ;
		}
	}
	else															//! The polling mode to be used.
	{
		return ( TRUE == (UART0_LSR & UART_LSR_DATA_READY) ) ;		//! Find it reading line status register.
	}
}
//----------------------------------------------------------------------------


/*!
 * \brief Detect keyboard from default UART.
 *
 * This API detects for any keystrokes from the default UART. If a keystroke is detected
 * this function returns a 1 else returns 0. The API returns immediately
 * without blocking both when the uart is configured to work in poll mode and in the
 * interrupt mode. Also note that the API does not read the data but only returns
 * the status. However, this function will return a 0xFF if FIFO has an error in it.
 * When it returns 0xFF error code, the application can use geterr_UART() to know the
 * exact error that occurred.
 */
UCHAR kbhit( VOID )
{
	return kbhit_UART0() ;
}//! end of kbhit()

/*! End of File */


