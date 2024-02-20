#include <ESP8266WiFi.h>
#include <espnow.h>
#include "encender_cronometro.h"
typedef struct struct_message {
  uint8_t a;
} struct_message;

struct_message myData;

const int numero[] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111 };

const int pinClock = 3;   // Pin de reloj para los shift registers
const int pinData_Cronometro = 5;    // Pin de datos para los shift register
const int pinLatcha_Cronometro = 6;  // Pin de latch para los shift registers

unsigned long cronometro = 0;  // Duración del reloj de arena en milisegundos
unsigned long inicio = 0;
bool reset = false;



void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Valor:");
  Serial.println(myData.a);
  (myData.a == 1)&&(duration = 24,paused_time = 0, timer_active = false);
  (myData.a == 2)&&(duration = 14,paused_time = 0, timer_active = false);
  (myData.a == 3)&&(timer_active && ((paused_time = millis() - start_time), timer_active = false));
}
void setup() {
  Serial.begin(115200);
  //Configuracion de la libreria esepnow y comprovacion de error al conectar
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error inicializando ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

}

void loop() {
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
