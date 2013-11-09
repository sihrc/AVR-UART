#define F_CPU (1000000L)
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdlib.h>

/* TEST CODE - UART
        Initializes the UART controller and sends out sporadic debug messages.
*/

// Set up the LIN/UART Controller
// RX on 12
// TX on 2

// Scale down to 9600 baud (bits per sec)
// LDIV[11..0] = ( 8,000,000 / 32 x BAUD ) - 1
// 
void initUART(void) {
    LINCR = _BV(LENA) | _BV(LCONF1) | _BV(LCMD2) | _BV(LCMD0);
    LINBRR = 0x0C; //0b00001100
}

void UART_putChar(char c) {
    while(LINSIR & _BV(LTXOK)); // controller is busy
    LINDAT = c;
}

int main (void) {
    DDRD &= ~(_BV(PD4)); // set pin 12 for input
    DDRD |= _BV(PD3); // set pin 2 for output

    sei(); // enable global interrupts    
    initUART(); // intitialize button interrupts

    for (;;) {
        // spit out debug messages forever
        UART_putChar('a');
        _delay_ms(50);
    }

    return(0);
}

