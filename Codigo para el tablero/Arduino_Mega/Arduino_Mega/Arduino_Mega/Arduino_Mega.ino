//#include <SoftwareSerial.h>

#include "encender_cronometro.h"
#include "faltas.h"
#include "marcador.h"
#include "periodo.h"
int contador = 2400;
//SoftwareSerial megaSerial(15, 14);  // RX, TX (Configura los pines RX y TX según corresponda)

uint8_t valor_local, valor_visita, valor_falta_local, valor_falta_visita, estado_cronometro, tiempo_cronometro, valor_periodo;
const int numero[] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111 };
const int pinClock = 4;


//constantes del cronometro
const int pinData_Cronometro = 22;
const int pinLatcha_Cronometro = 23;


// Constrantes del marcador  local
const int pinData_marcador_local = 24;
const int pinLatcha_marcador_local = 25;
const int pin_3er_decimal_local = 26;

// Constrantes del marcador  visita
const int pinData_marcador_visita = 27;
const int pinLatcha_marcador_visita = 28;
const int pin_3er_decimal_visita = 29;

// Constrantes del faltas  local
const int pinData_faltas_local = 30;
const int pinLatcha_faltas_local = 31;

// Constrantes del faltas  visita
const int pinData_faltas_visita = 32;
const int pinLatcha_faltas_visita = 33;

//Constantes de periodo
const int pinData_periodo = 34;
const int pinLatcha_periodo = 35;

//variables para el cronometro


unsigned long tiempo_inicial_recibido;
unsigned long valor_cronometro_inicial;

bool timer_active = false;
unsigned long start_time;
unsigned long paused_time = 0;
unsigned long duration = 0;  // Duración del reloj de arena en milisegundos

void setup() {
  //Serial.begin(9600);      // Configura la velocidad de transmisión (baud rate) para el monitor serial
  // megaSerial.begin(9600);  // Configura la velocidad de transmisión (baud rate) para la comunicación con el ESP8266
  Serial.begin(9600);
  pinMode(pinClock, OUTPUT);

  pinMode(pinData_Cronometro, OUTPUT);
  pinMode(pinLatcha_Cronometro, OUTPUT);

  pinMode(pinData_marcador_local, OUTPUT);
  pinMode(pinLatcha_marcador_local, OUTPUT);
  pinMode(pin_3er_decimal_local, OUTPUT);

  pinMode(pinData_marcador_visita, OUTPUT);
  pinMode(pinLatcha_marcador_visita, OUTPUT);
  pinMode(pin_3er_decimal_visita, OUTPUT);

  pinMode(pinData_faltas_local, OUTPUT);
  pinMode(pinLatcha_faltas_local, OUTPUT);

  pinMode(pinData_faltas_visita, OUTPUT);
  pinMode(pinLatcha_faltas_visita, OUTPUT);
  pinMode(pinData_periodo, OUTPUT);
  pinMode(pinLatcha_periodo, OUTPUT);

}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');  
    sscanf(data.c_str(), "%hhu,%hhu,%hhu,%hhu,%hhu,%hhu,%hhu", &valor_local, &valor_visita, &valor_falta_local, &valor_falta_visita, &estado_cronometro, &tiempo_cronometro, &valor_periodo);

    if (estado_cronometro != 1 && tiempo_cronometro != valor_cronometro_inicial) {
      // Este bloque de código se ejecutará si estado_cronometro no es igual a 1
      // y si estado_cronometro no es igual a valor_cronometro_inicial
      valor_cronometro_inicial = tiempo_cronometro;
      tiempo_inicial_recibido = tiempo_cronometro * 300000;
      imprimir_encender_cronometro(tiempo_inicial_recibido / 1000);
      duration = tiempo_inicial_recibido;
      Serial.print("duration: ");
      Serial.println(duration);
      timer_active = false;
    }

    if (estado_cronometro == 1) {
      // Iniciar el cronómetro primer boton
      // Start the timer
      Serial.println("Estado_1");
      if (!timer_active) {
        start_time = millis() - paused_time;
        timer_active = true;
      }
    } else if (estado_cronometro == 2) {
      // Pausar el cronómetro segundo boton
      if (timer_active) {
        paused_time = millis() - start_time;
        timer_active = false;
      }

    } else if (estado_cronometro == 3) {
      //reiniciar tercer  boton
      // Reset the timer to 10 minutes
      duration = tiempo_inicial_recibido;
      paused_time = 0;
      timer_active = false;
      imprimir_encender_cronometro(tiempo_inicial_recibido / 1000);
    }




    imprimir_faltas_local(valor_falta_local);
    imprimir_faltas_visita(valor_falta_visita);
    imprimir_marcador_local(valor_local);
    imprimir_marcador_visita(valor_visita);
    imprimir_periodo(valor_periodo);
  }
  if (timer_active) {
    unsigned long currentTime = millis();                  // Tiempo actual
    unsigned long elapsedTime = currentTime - start_time;  // Tiempo transcurrido desde el inicio

    // Comprobar si el tiempo transcurrido es menor que la duración del reloj de arena
    if (elapsedTime < duration) {
      // Imprimir el tiempo restante en segundos
      unsigned long remainingTime = (duration - elapsedTime) / 1000;  // Convertir a segundos

      Serial.print("Tiempo restante: ");
      Serial.print(remainingTime);
      Serial.println(" segundos");
      imprimir_encender_cronometro(remainingTime);
    } else {
      // El reloj de arena ha terminado
      Serial.println("El reloj de arena ha terminado.");
      imprimir_encender_cronometro(0);
      timer_active = false;
      // Aquí puedes realizar cualquier acción que desees cuando el reloj de arena termine.
    }
  }
}