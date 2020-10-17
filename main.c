/*
*
* USB360: Interfaz USB que emula control de Xbox 360 para Pro Micro originales o piratas 
*
* Copyright (c) 2020
* Bruno Freitas - bruno@brunofreitas.com
* Jon Wilson    - degenatrons@gmail.com
* Kevin Mackett - kevin@sharpfork.com
* Bastian Aguirre - crtgamers.cl
*
* Este programa es software gratuito: puedes redistribuirlo y / o modificar
* bajo los términos de la Licencia Pública General GNU publicada por
* Free Software Foundation, ya sea la versión 3 de la Licencia, o
* (a su elección) cualquier versión posterior.
*
* Este programa se distribuye con la esperanza de que sea útil,
* pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita de
* COMERCIABILIDAD o APTITUD PARA UN PROPÓSITO PARTICULAR. Ver el
* Licencia pública general GNU para más detalles.
*
* Debería haber recibido una copia de la Licencia Pública General GNU
* junto con este programa. Si no, vea <http://www.gnu.org/licenses/>.
*/

#include "XInputControl.h"
#include "util.h"

void setup_pins(void);

int main(void) {
	uint8_t pad_select, pad_start, pad_up, pad_down, pad_left, pad_right, pad_a, pad_x, pad_b, pad_y, pad_xbox, pad_l3, pad_r3, pad_l, pad_r, pad_lt, pad_rt;

	// Set clock @ 16Mhz
	CPU_PRESCALE(0);

	// Disable JTAG
	bit_set(MCUCR, 1 << JTD);
	bit_set(MCUCR, 1 << JTD);

	// Setup pins
	setup_pins();

	// Init XBOX pad emulation
	xbox_init(true);

	// Pins polling and gamepad status updates
	for (;;) {
		xbox_reset_watchdog();

		pad_select =  !bit_check(PIND, 2);
		pad_start =  !bit_check(PIND, 3);
		pad_up = !bit_check(PIND, 1);
		pad_down = !bit_check(PIND, 0);
		pad_left = !bit_check(PIND, 4);
		pad_right = !bit_check(PINC, 6);
		pad_y = !bit_check(PIND, 7);
		pad_b = !bit_check(PINE, 6);
		pad_x = !bit_check(PINB, 4);
		pad_a = !bit_check(PINB, 5);

		pad_xbox = !bit_check(PINF, 5);
		pad_l3 =  !bit_check(PINF, 6);
		pad_r3 =  !bit_check(PINF, 7);
		pad_l =  !bit_check(PINB, 2);
		pad_r =  !bit_check(PINB, 6);
		pad_lt = !bit_check(PINB, 1);
		pad_rt = !bit_check(PINB, 3);
		
		/**pad_left_analog_x = pad_left_analog_y = pad_right_analog_x = pad_right_analog_y = 0x7F;
 
		if(!bit_check(PINF, 4)) {
			pad_right_analog_y = 0x00;
		} else if(!bit_check(PINF, 5)) {
			pad_right_analog_y = 0xFF;
		}

		if(!bit_check(PINF, 4)) {
			pad_right_analog_x = 0x00;
		} else if(!bit_check(PINF, 5)) {
			pad_right_analog_x = 0xFF;
		}
		if(!bit_check(PINF, 4)) {
			pad_left_analog_y = 0x00;
		} else if(!bit_check(PINF, 5)) {
			pad_left_analog_y = 0xFF;
		}
		if(!bit_check(PINF, 4)) {
			pad_left_analog_x = 0x00;
		} else if(!bit_check(PINF, 5)) {
			pad_left_analog_x = 0xFF;
		}		*/

		pad_up    ? bit_set(gamepad_state.digital_buttons_1, XBOX_DPAD_UP)    : bit_clear(gamepad_state.digital_buttons_1, XBOX_DPAD_UP);
		pad_down  ? bit_set(gamepad_state.digital_buttons_1, XBOX_DPAD_DOWN)  : bit_clear(gamepad_state.digital_buttons_1, XBOX_DPAD_DOWN);
		pad_left  ? bit_set(gamepad_state.digital_buttons_1, XBOX_DPAD_LEFT)  : bit_clear(gamepad_state.digital_buttons_1, XBOX_DPAD_LEFT);
		pad_right ? bit_set(gamepad_state.digital_buttons_1, XBOX_DPAD_RIGHT) : bit_clear(gamepad_state.digital_buttons_1, XBOX_DPAD_RIGHT);

		pad_start  ? bit_set(gamepad_state.digital_buttons_1, XBOX_START)       : bit_clear(gamepad_state.digital_buttons_1, XBOX_START);
		pad_select ? bit_set(gamepad_state.digital_buttons_1, XBOX_BACK)        : bit_clear(gamepad_state.digital_buttons_1, XBOX_BACK);
		pad_l3     ? bit_set(gamepad_state.digital_buttons_1, XBOX_LEFT_STICK)  : bit_clear(gamepad_state.digital_buttons_1, XBOX_LEFT_STICK);
		pad_r3     ? bit_set(gamepad_state.digital_buttons_1, XBOX_RIGHT_STICK) : bit_clear(gamepad_state.digital_buttons_1, XBOX_RIGHT_STICK);

		pad_a ? bit_set(gamepad_state.digital_buttons_2, XBOX_A)    : bit_clear(gamepad_state.digital_buttons_2, XBOX_A);
		pad_b ? bit_set(gamepad_state.digital_buttons_2, XBOX_B)  : bit_clear(gamepad_state.digital_buttons_2, XBOX_B);
		pad_x ? bit_set(gamepad_state.digital_buttons_2, XBOX_X)  : bit_clear(gamepad_state.digital_buttons_2, XBOX_X);
		pad_y ? bit_set(gamepad_state.digital_buttons_2, XBOX_Y) : bit_clear(gamepad_state.digital_buttons_2, XBOX_Y);

		pad_l ? bit_set(gamepad_state.digital_buttons_2, XBOX_LB)    : bit_clear(gamepad_state.digital_buttons_2, XBOX_LB);
		pad_r ? bit_set(gamepad_state.digital_buttons_2, XBOX_RB)    : bit_clear(gamepad_state.digital_buttons_2, XBOX_RB);
		pad_xbox  ? bit_set(gamepad_state.digital_buttons_2, XBOX_HOME)  : bit_clear(gamepad_state.digital_buttons_2, XBOX_HOME);

		gamepad_state.lt = pad_lt * 0xFF;
		gamepad_state.rt = pad_rt * 0xFF;

		/**
		if(pad_start && pad_select) {
			bit_set(gamepad_state.digital_buttons_2, XBOX_HOME);
		} else {
			bit_clear(gamepad_state.digital_buttons_2, XBOX_HOME);
		}

		gamepad_state.l_x = pad_left_analog_x * 257 + -32768;
		gamepad_state.l_y = pad_left_analog_y * -257 + 32767;
		gamepad_state.r_x = pad_right_analog_x * 257 + -32768;
		gamepad_state.r_y = pad_right_analog_y * -257 + 32767;
		*/

		xbox_send_pad_state();
	}
}

void setup_pins(void) {

	// Setup pins
	bit_clear(DDRF, 1 << 7);
	bit_set(PORTF, 1 << 7);

	bit_clear(DDRF, 1 << 6);
	bit_set(PORTF, 1 << 6);

	bit_clear(DDRF, 1 << 5);
	bit_set(PORTF, 1 << 5);

	bit_clear(DDRF, 1 << 4);
	bit_set(PORTF, 1 << 4);

	bit_clear(DDRF, 1 << 1);
	bit_set(PORTF, 1 << 1);

	bit_clear(DDRF, 1 << 0);
	bit_set(PORTF, 1 << 0);

	bit_clear(DDRB, 1 << 3);
	bit_set(PORTB, 1 << 3);

	bit_clear(DDRB, 1 << 1);
	bit_set(PORTB, 1 << 1);

	bit_clear(DDRD, 1 << 6);
	bit_set(PORTD, 1 << 6);

	bit_clear(DDRB, 1 << 7);
	bit_set(PORTB, 1 << 7);

	bit_clear(DDRB, 1 << 6);
	bit_set(PORTB, 1 << 6);

	bit_clear(DDRB, 1 << 5);
	bit_set(PORTB, 1 << 5);

	bit_clear(DDRB, 1 << 4);
	bit_set(PORTB, 1 << 4);

	bit_clear(DDRE, 1 << 6);
	bit_set(PORTE, 1 << 6);

	bit_clear(DDRD, 1 << 7);
	bit_set(PORTD, 1 << 7);

	bit_clear(DDRC, 1 << 6);
	bit_set(PORTC, 1 << 6);

	bit_clear(DDRD, 1 << 4);
	bit_set(PORTD, 1 << 4);

	bit_clear(DDRD, 1 << 0);
	bit_set(PORTD, 1 << 0);

	bit_clear(DDRD, 1 << 1);
	bit_set(PORTD, 1 << 1);

	bit_clear(DDRD, 1 << 2);
	bit_set(PORTD, 1 << 2);

	bit_clear(DDRD, 1 << 3);
	bit_set(PORTD, 1 << 3);

	bit_clear(DDRB, 1 << 0);
	bit_set(PORTB, 1 << 0);

	bit_clear(DDRB, 1 << 2);
	bit_set(PORTB, 1 << 2);

	bit_clear(DDRC, 1 << 7);
	bit_set(PORTC, 1 << 7);
}
