// For Raspberry Pi Pico
//
// midivel
//
#include "pico/stdlib.h"

// UART settings
#define UART_ID uart0
#define BAUD_RATE 31250
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define GPIO_FUNC_UART 2

// midi note-on command - binary 10010000
// ignore lower nibble which is midi-channel
#define MIDI_NOTE_ON 144

// function declarations
unsigned char midivel_rx();
void midivel_tx(unsigned char);

int main() {
	
	unsigned char midichar = 0; // midi character rx'd and/or to be tx'd

	// set UART speed.
	uart_init(UART_ID, BAUD_RATE);

	// set UART Tx and Rx pins
	gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
	gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

	// enable Tx and Rx fifos on UART
	uart_set_fifo_enabled(UART_ID, true);

	// disable cr/lf conversion on Tx
	uart_set_translate_crlf(UART_ID, false);

	// endless loop
	while(true){

		// read RX character
		midichar = midivel_rx();
		
		// test if midi-note-on command - high-nibble only
		if ((midichar & 240) == MIDI_NOTE_ON) {
			//Tx it
			midivel_tx(midichar);
			
			// get midi-note-on-key data
			midichar = midivel_rx();
			
			// check it is not a new midi command (highly unlikely)
			if (midichar < 128) {
				
				// Tx midi-note-on-key data
				midivel_tx(midichar);
				
				// get midi-note-on-velocity data
				midichar = midivel_rx();
			
				// check it is not a new midi command (highly unlikely)
				// nor midi-note-on-velocity-0 which is same as note-off
				if ((midichar < 128) && (midichar != 0)){
				
					// alter midi-velocity
					// simple example which sets mininum velocity
					// in the future I may use a mappng table
					if (midichar < 32) {midichar = 32;}

				}
			}
		}
		// Tx it - either modified velocity or anything else rx'd
		midivel_tx(midichar);
		
	} // endless loop
	return 0; // prittification, never happens
}

// function - get a midi character from UART - blocking
unsigned char midivel_rx(){
	while (!uart_is_readable(UART_ID)){
	}
	unsigned char midichar_fr = uart_getc (UART_ID);
	return midichar_fr;
}

//function - send a midi character to UART - blocking
void midivel_tx(unsigned char midichar_ft){
	
	while (!uart_is_writable(UART_ID)){
	}
	uart_putc(UART_ID, midichar_ft);
	return;
}
