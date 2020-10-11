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

USB_JoystickReport_Data_t gamepad_state;


void (*padUSBConnectEventCallback)(void) = NULL;

void (*padUSBDisconnectEventCallback)(void) = NULL;

/** Controlador de eventos para el evento USB_Connect. Esto indica que el dispositivo está enumerando a través de los LED de estado y
 * inicia la tarea USB de la biblioteca para comenzar el proceso de enumeración y administración de USB.
 */
void EVENT_USB_Device_Connect(void) {
	if(padUSBConnectEventCallback)
		padUSBConnectEventCallback();
}

/** Controlador de eventos para el evento USB_Disconnect. Esto indica que el dispositivo ya no está conectado a un host a través de
 * los LED de estado y detiene la gestión de USB y las tareas de informes del joystick.
 */
void EVENT_USB_Device_Disconnect(void) {
	if(padUSBDisconnectEventCallback)
		padUSBDisconnectEventCallback();
}

/** Controlador de eventos para el evento USB_ConfigurationChanged. Esto se activa cuando el host establece la configuración actual
 * del dispositivo USB después de la enumeración: se configuran los puntos finales del dispositivo y se inicia la tarea de informes del joystick.
 */
void EVENT_USB_Device_ConfigurationChanged(void) {
	/* Configurar el punto final del informe HID */
	Endpoint_ConfigureEndpoint(JOYSTICK_EPADDR_IN, EP_TYPE_INTERRUPT, 20, 1);
	Endpoint_ConfigureEndpoint((ENDPOINT_DIR_IN | 3), EP_TYPE_INTERRUPT, 32, 1);
}

/** Controlador de eventos para el evento USB_ControlRequest. Se utiliza para capturar y procesar solicitudes de control enviadas a
 * el dispositivo del host USB antes de pasar las solicitudes de control no gestionadas a la biblioteca para su procesamiento
 * internamente.
 */
void EVENT_USB_Device_ControlRequest(void) {
	/* Manejar solicitudes específicas de clase HID */
	switch (USB_ControlRequest.bRequest) {
	case HID_REQ_GetReport:
		if (USB_ControlRequest.bmRequestType
				== (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE)) {
			Endpoint_ClearSETUP();

			/* Escriba los datos del informe en el punto final de control */
			Endpoint_Write_Control_Stream_LE(&gamepad_state, 20);
			Endpoint_ClearOUT();
		}

		break;
	}
}

/** Función para gestionar la generación y transmisión de informes HID al host. */
void HID_Task(void) {
	/* El dispositivo debe estar conectado y configurado para que se ejecute la tarea */
	if (USB_DeviceState != DEVICE_STATE_Configured)
		return;

	/* Seleccione el punto final del informe del joystick */
	Endpoint_SelectEndpoint(JOYSTICK_EPADDR_IN);

	/* Verifique si el host está listo para otro paquete */
	if (Endpoint_IsINReady()) {
		/* Escribir datos de informe de joystick */
		Endpoint_Write_Stream_LE(&gamepad_state, 20, NULL);

		/* Finalice la transferencia de flujo para enviar el último paquete */
		Endpoint_ClearIN();
	}
}

void xbox_reset_pad_status(void) {
	memset(&gamepad_state, 0x00, sizeof(USB_JoystickReport_Data_t));

	gamepad_state.rsize = 20;
}

void xbox_send_pad_state(void) {
	HID_Task();
	USB_USBTask();
}

void xbox_reset_watchdog(void) {
	wdt_reset();
}

void xbox_init(bool watchdog) {
	if (watchdog) {
		wdt_enable(WDTO_2S);
	} else {
		wdt_disable();
	}

	xbox_reset_pad_status();

	USB_Init();

	sei();
}

void xbox_set_connect_callback(void (*callbackPtr)(void)) {
	padUSBConnectEventCallback = callbackPtr;
}

void xbox_set_disconnect_callback(void (*callbackPtr)(void)) {
	padUSBDisconnectEventCallback = callbackPtr;
}

