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

// Scale down to 2400 baud (bits per sec)
// LDIV[11..0] = ( 8,000,000 / 32 x BAUD ) - 1
// 
void initUART(void) {
    LINCR = _BV(SWRES) | _BV(LENA) | _BV(LCMD2) | _BV(LCMD0);
    LINBRR = 0x0C; //0b00001100
}

int UART_putChar(char c) {
    LINDAT = c;
    return(0);
    // int i = 0;
    // while((LINSIR & _BV(LBUSY)) && (i<1000) ){ ++i; } // controller is busy
    
    // if (LINSIR & _BV(LBUSY)) {
    //     LINDAT = c;
    //     return(0);
    // } else {
    //     return(-1);
    // }
}

int main (void) {
    DDRD &= ~(_BV(PD4)); // set pin 12 for input
    DDRD |= _BV(PD3); // set pin 2 for output

    DDRB |= _BV(PB7);

    sei(); // enable global interrupts    
    initUART(); // intitialize button interrupts

    int status = 0;
    for (;;) {
        // spit out debug messages forever
        status = UART_putChar('a');
        PORTB ^= _BV(PB7);
        _delay_ms(500);
    }

    return(0);
}

