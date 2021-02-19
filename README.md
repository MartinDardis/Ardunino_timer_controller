# Timer control with LCD

Temporizador programable via USB. Posee 2 modos de funcionamiento
* **Temporizado:** Cuenta regresiva desde el tiempo seteado. El tiempo puede ser cambiado desde la interfaz serial
* **Manual**: Activado constante hasta accionar el pulsador de encendido

## Configuracion Inicial

La cantidad de minutos que cuenta el modo temporizado se encuentra guardado en la EEPROM. Al cargar el programa este puede poseer cualquier valor distinto al deseado por esto **DEBE CONFIGURARSE EN EL PRIMER INICIO**, de la siguiente manera luego de haberse cargado el programa a ARDUINO.

1. Ejecutar una coneccion SERIAL. ( Puede usarse el mismo IDE de ARDUINO CTRL+MAY+M o el interprete preferido por el usuario)
2. Ingresar la letra **U** para entrar al modo USB, se podra ver en la pantalla LCD el mensaje 'MODO USB'.
3. Ingresar `3` para entrar la configuracion.
4. Ingresar el tiempo deseado en MINUTOS.
5. El tiempo deseado sera memorizado quedando seteado para proximos inicios.

## Screenshots

![](https://github.com/MartinDardis/timer_pump_arduino/blob/master/DOCS/serial_init.png "Init message")

![](https://github.com/MartinDardis/timer_pump_arduino/blob/master/DOCS/serial_menu.png "Serial Menu")

## Hardware

|Cant|Item|
|---|---|
|1|Arduino Nano|
|1|LCD Display 16x21|
|1|Relay 12v 40 AMP|
|1|LM7805|
|1|LM7812|
|1|TIP41|
|-|Various Capacitor and resistor|
|-|Pertinax PCB|

