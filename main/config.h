#ifndef CONFIG_H
#define CONFIG_H


// DISPLAY PIN
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
#define TIME_SET_MEM 0

#define PIN_SALIDA 3
#define ACCIONADO HIGH
#define LIBERADO LOW

#define PIN_LED_SALIDA 13
#define LED_ENCENDIDO HIGH
#define LED_APAGADO LOW

#define PRESIONADO LOW
#define PULS_MANUAL 4
#define PULS_INICIAR_TEMPO 5

#define MOTOR_ENCENDIDO 'E'
#define MOTOR_APAGADO 'A'
#define IMPRIMIR_TIEMPO 'T'
#define LIMPIAR_PANTALLA 'C'
#define CANCELAR 'x'
#define MODO_USB 'u'
#define MODO_USB_MAY 'U'

#endif
