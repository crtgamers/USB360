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

#ifndef _XINPUTCONTROL_H_
#define _XINPUTCONTROL_H_

/* Includes: */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>

#include "Descriptors.h"

#include <LUFA/Drivers/USB/USB.h>

/* Tipo Define: */
/** Escriba definir para la estructura de informes HID del joystick, para crear y enviar informes HID a la PC host.
 * Esto refleja el diseño descrito para el host en el descriptor del informe HID, en Descriptors.c.
 */
typedef struct {
	uint8_t rid;
	uint8_t rsize;
	uint8_t digital_buttons_1;
	uint8_t digital_buttons_2;
	uint8_t lt;
	uint8_t rt;
	int l_x;
	int l_y;
	int r_x;
	int r_y;
	uint8_t reserved_1[6];
} USB_JoystickReport_Data_t;

extern USB_JoystickReport_Data_t gamepad_state;

/* Prototipos de funciones: */

void xbox_reset_pad_status(void);
void xbox_send_pad_state(void);
void xbox_reset_watchdog(void);
void xbox_init(bool watchdog);

void xbox_set_connect_callback(void (*callbackPtr)(void));
void xbox_set_disconnect_callback(void (*callbackPtr)(void));

// Botones digitales 1
#define XBOX_DPAD_UP		0x01
#define XBOX_DPAD_DOWN		0x02
#define XBOX_DPAD_LEFT		0x04
#define XBOX_DPAD_RIGHT		0x08
#define XBOX_START			0x10
#define XBOX_BACK			0x20
#define XBOX_LEFT_STICK		0x40
#define XBOX_RIGHT_STICK	0x80

// Botones Digitales 2
#define XBOX_LB		0x01
#define XBOX_RB		0x02
#define XBOX_HOME	0x04
#define XBOX_A		0x10
#define XBOX_B		0x20
#define XBOX_X		0x40
#define XBOX_Y		0x80

#endif

