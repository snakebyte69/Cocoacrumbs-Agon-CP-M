//
// Title:	        Agon Video BIOS - Function prototypes
// Author:        	Dean Belfield
// Created:       	05/09/2022
// Last Updated:	05/09/2022
//
// Modinfo:

#pragma once

#define	ESPSerial Serial2

#define USE_HWFLOW				1		// Flow Control: 1 = enable hardware flow control to eZ80

#define UART_BR					384000
#define UART_NA					-1
#define UART_TX					2
#define UART_RX					34
#define UART_RTS  	 		 	13 		// The ESP32 RTS pin (eZ80 CTS)
#define UART_CTS  	  			14		// The ESP32 CTS pin (eZ80 RTS)

#define UART_RX_SIZE			256		// The RX buffer size
#define UART_RX_THRESH			128		// Point at which RTS is toggled

#define GPIO_ITRP				17		// VSync Interrupt Pin - for reference only

#define PACKET_GP				0		// General poll data
#define PACKET_KEYCODE			1		// Keyboard data
#define PACKET_CURSOR			2		// Cursor positions
#define PACKET_SCRCHAR			3		// Character read from screen
#define PACKET_SCRPIXEL			4		// Pixel read from screen
#define PACKET_AUDIO			5		// Audio acknowledgement
#define PACKET_MODE				6		// Get screen dimensions

#define AUDIO_CHANNELS			3		// Number of audio channels
#define PLAY_SOUND_PRIORITY 	3		// Sound driver task priority with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE	0
#else
#define ARDUINO_RUNNING_CORE	1
#endif

// Function Prototypes
//
void debug_log(const char *format, ...);