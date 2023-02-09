/*
 * Title:           AGON VPD for CP/M
 * Author:          Koenraad Van Nieuwenhove (Cocoacrumbs)
 * Created:         05/08/2022
 * Last Updated:    05/08/2022
 *
 * Modinfo:
 * xx/yy/zzzz:		
 */

#include "fabgl.h"
#include "HardwareSerial.h"

#define DEBUG 0

#define ESPSerial Serial2

#define UART_BR     384000
#define UART_NA     -1
#define UART_TX     2
#define UART_RX     34
#define UART_RTS    13 // The ESP32 RTS pin
#define UART_CTS    14 // The ESP32 CTS pin

#define GPIO_ITRP   17 // VSync Interrupt Pin - for reference only

fabgl::PS2Controller    PS2Controller;
fabgl::VGA16Controller  DisplayController;
fabgl::Terminal         Terminal;

void setup()
{
    // Serial.begin(115200); delay(500); Serial.write("\n\n\n"); // DEBUG ONLY
    disableCore0WDT(); // Disable the watchdog timers
    delay(100);        // Crashes without this delay
    disableCore1WDT();

    ESPSerial.begin(UART_BR, SERIAL_8N1, UART_RX, UART_TX);
    ESPSerial.setRxBufferSize(1024);

    PS2Controller.begin(PS2Preset::KeyboardPort0, KbdMode::CreateVirtualKeysQueue);

    DisplayController.begin();
    DisplayController.setResolution(VGA_640x480_60Hz);

    Terminal.begin(&DisplayController);

    Terminal.enableCursor(true);
}

// Handle the keyboard
void do_keyboard()
{
    fabgl::Keyboard *kb = PS2Controller.keyboard();
    bool isKeyDown;

    if (kb->virtualKeyAvailable() > 0)
    {
        fabgl::VirtualKey vk = kb->getNextVirtualKey(&isKeyDown, 20);
        if (isKeyDown)
        {
            int a = kb->virtualKeyToASCII(vk);

            if (a != -1)
            {
                ESPSerial.write(a);
            }
        }
    }
}

void boot_screen()
{
    Terminal.write("\e[40;92m"); // background: black, foreground: green
    Terminal.write("\e[2J");     // clear screen
    Terminal.write("\e[1;1H");   // move cursor to 1,1

    Terminal.write("AGON VPD Alternate Version 0.0.2 for CP/M\r\n");
    Terminal.write("Hit escape key to load CP/M\r\n\n");
    ESPSerial.write(27);
}

void loop()
{
    boot_screen();

    while (1)
    {
        do_keyboard();
        if (ESPSerial.available() > 0)
        {
            byte c = ESPSerial.read();
            Terminal.write(c);
        }
    }
}
