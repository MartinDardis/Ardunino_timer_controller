#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "config.h"


bool estado_manual = false;
bool modo_timmer = false;
int min_activo_tempo;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void imprimir_mensaje(char codigo,int tiempo);
void imprimir_serial_lcd_restant(int i);
void configuracion_usb();
void menu_serial();



void setup(){
  lcd.begin(16, 2);
  pinMode(PIN_LED_SALIDA,OUTPUT);
  digitalWrite(PIN_LED_SALIDA,LED_ENCENDIDO);
  lcd.print("Inicializando");
  Serial.begin(9600);
  pinMode(PIN_SALIDA,OUTPUT);
  digitalWrite(PIN_SALIDA,LIBERADO);
  pinMode(PULS_MANUAL,INPUT_PULLUP);
  pinMode(PULS_INICIAR_TEMPO,INPUT_PULLUP);
  delay(2000);
  lcd.clear();
  EEPROM.get(TIME_SET_MEM,min_activo_tempo);
  lcd.print("LISTO");
  Serial.println("Iniciado. Para modo usb ingrese U ...");
}


void loop (){
  if (Serial.available()>0){
      String read_s = Serial.readString();
      if(read_s[0] == MODO_USB || read_s[0] == MODO_USB_MAY)
      menu_serial();
  }
  if ( (digitalRead(PULS_INICIAR_TEMPO)== PRESIONADO || modo_timmer) && estado_manual==false){
    while(digitalRead(PULS_INICIAR_TEMPO)== PRESIONADO);
    Serial.println("Modo TIMER, presione x para cancelar");
    if(modo_timmer) modo_timmer = false;
    int tiempo_total = min_activo_tempo*60;
    digitalWrite(PIN_LED_SALIDA,LED_ENCENDIDO);
    imprimir_mensaje(MOTOR_ENCENDIDO,0);
    digitalWrite(PIN_SALIDA,ACCIONADO);
    for(long int i=min_activo_tempo*60; i>0 ;i--,i--){
      imprimir_serial_lcd_restant(i);
      delay(1000);
      if(digitalRead(PULS_MANUAL) == PRESIONADO || Serial.readString()[0] == CANCELAR )
        i=0;
     }
    digitalWrite(PIN_SALIDA,LIBERADO);
    imprimir_mensaje(MOTOR_APAGADO,0);
    digitalWrite(PIN_LED_SALIDA,LED_APAGADO);
    while(digitalRead(PULS_MANUAL)== PRESIONADO);
    delay(500);
 }
  if (digitalRead(PULS_MANUAL)== PRESIONADO){
    if(estado_manual==false){
      Serial.println("Modo MANUAL ACTIVADO");
      imprimir_mensaje(MOTOR_ENCENDIDO,0);
      digitalWrite(PIN_LED_SALIDA,LED_ENCENDIDO);
      digitalWrite(PIN_SALIDA,ACCIONADO);
      estado_manual=true;
    }
    else{
      Serial.println("Modo MANUAL DESACTIVADO");
      digitalWrite(PIN_SALIDA,LIBERADO);
      imprimir_mensaje(MOTOR_APAGADO,0);
      digitalWrite(PIN_LED_SALIDA,LED_APAGADO);
      estado_manual=false;
    }
    while(digitalRead(PULS_MANUAL)== PRESIONADO);
    delay(500);
 }


}

void imprimir_mensaje(char codigo,int min_activo_tempo){// E:encendido T:tiempo A:apagado C:limpiar 
  lcd.clear();
  if (codigo == MOTOR_ENCENDIDO)
    lcd.print("Motor encendido");
  else if (codigo == IMPRIMIR_TIEMPO){
    lcd.print("Temporizador en min_activo_tempo = ");
    lcd.write(min_activo_tempo);
  }
  else if (codigo == MOTOR_APAGADO)
    lcd.print("Motor Apagado");
  else if(codigo == LIMPIAR_PANTALLA)
    lcd.clear();
 
}

void imprimir_serial_lcd_restant(int i){
      char restante[10];
      sprintf(restante,"%d:%d\0",i/60,i%60);
      Serial.println(restante);
      lcd.setCursor(0,1);
      lcd.print("     " );
      lcd.setCursor(0,1);
      lcd.print(restante);
      //lcd.setCursor(0,1);
      //lcd.print(i);
}

void configuracion_usb(){
  Serial.println("Modo configuracion USB");
  bool salir = false;
  Serial.println("Ingrese un nuevo tiempo de temporizado (en minutos)");
  while( !salir ){
    if( Serial.available()>0){
      String string_time = Serial.readString();
      int new_time = string_time.toInt();
      if(new_time > 0){
        Serial.print("Cambiado con exito a "+string_time+"."+" Guardando cambio!\n");
        Serial.print("");
        min_activo_tempo = new_time;
        EEPROM.update(TIME_SET_MEM,new_time);
        salir = true;
      }
      else{
        Serial.println("Valor Incorrecto");
      }
    }
  }
  delay(2000);
}

void menu_serial(){
  int opcion = 0;
  Serial.print("\n");
  Serial.print(" Elija una opcion\n");
  Serial.print(" 1 -> Activar\n 2 -> Desactivar\n 3 -> Configurar\n 4 -> Ver configuracion actual\n 5 -> MODO TIMER\n 6 -> VERSION\n 7 -> Salir\n");
  Serial.print("\n");
  lcd.clear();
  lcd.print("Modo USB");
  digitalWrite(PIN_LED_SALIDA,LED_ENCENDIDO);
  while(Serial && opcion != 7){
    lcd.setCursor(0,1);
    if(Serial.available()>0){
      String input = Serial.readString();
      opcion = input.toInt();
      if (opcion < 1 || opcion > 7)
        opcion = 0;
      }
     if(opcion == 1 && estado_manual == false){
      Serial.println("Modo MANUAL ACTIVADO");
      lcd.print("MOTOR ENCENDIDO");
      digitalWrite(PIN_SALIDA,ACCIONADO);
      estado_manual=true;
    }
     else if (opcion == 2 && estado_manual == true){
      Serial.println("Modo MANUAL DESACTIVADO");
      digitalWrite(PIN_SALIDA,LIBERADO);
      lcd.print("MOTOR   APAGADO");
      estado_manual=false;
     }
     else if (opcion == 3){
      configuracion_usb();
      opcion = 0;
     }
     else if ( opcion == 4){
      char buff [200];
      sprintf(buff,"La configuracion actual es de %d minutos\n",min_activo_tempo);
      Serial.println(buff);
      opcion = 0;
     }
     else if ( opcion == 5){
      modo_timmer = true;
      opcion = 7;
     }else if ( opcion == 6){
      Serial.println("VERSION 2.0");
      opcion = 7; 
     }
  }
  digitalWrite(PIN_LED_SALIDA,LED_APAGADO);
  Serial.println("Para volver al modo USB ingrese un U");
}
