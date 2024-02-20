

#include <esp_now.h>
#include <WiFi.h>
#include "sonido.h"



// Definimos los pines a los que se conectan los botones
const int botones[] = { 32, 33, 25, 26, 27, 14, 12, 17, 16, 19, 18, 5, 21, 22, 23, 4, 0, 15 };
const int numBotones = sizeof(botones) / sizeof(botones[0]);

// Definimos una variable para almacenar el estado anterior de cada botón
bool estadosAnteriores[numBotones] = { false };

// Definimos una variable para el tiempo de debounce (anti-rebote)
unsigned long tiempoDebounce = 50;
unsigned long ultimaLectura[numBotones] = { 0 };


//parte de la comunicacion
uint8_t valor_local, valor_visita, valor_falta_local, valor_falta_visita, estado_cronometro, tiempo_cronometro = 1, valor_periodo;
//int8_t a, b, c, d, e, f;
uint8_t estado_cronometro_basquet;
// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t direccion_tablero[] = { 0xD8, 0xBF, 0xC0, 0xE0, 0x78, 0x90 };        //direcion del ESP8266:  D8:BF:C0:E0:78:90
uint8_t direccion_cronometro_n1[] = { 0xCC, 0x50, 0xE3, 0xF3, 0x55, 0xC8 };  //direcion del ESP8266:  CC:50:E3:F3:55:C8
uint8_t direccion_cronometro_n2[] = { 0xFC, 0xF5, 0xC4, 0x81, 0x10, 0xCE };  //direcion del ESP8266:   FC:F5:C4:81:10:CE

// Structure example to send data
// Must match the receiver structure
typedef struct esctuctura_tablero {
  uint8_t a;
  uint8_t b;
  uint8_t c;
  uint8_t d;
  uint8_t e;
  uint8_t f;
  uint8_t g;
} esctuctura_tablero;

esctuctura_tablero dato_tablero;

typedef struct esctuctura_cronometro {
  uint8_t a;

} esctuctura_cronometro;
// Create a esctuctura_tablero called dato_tablero
esctuctura_cronometro dato_cronometro;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {

  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


void setup() {
  pinMode(BUZZER_PIN, OUTPUT);


  // Inicializamos los pines de los botones como entradas y activamos las resistencias de pull-up
  for (int i = 0; i < numBotones; i++) {
    pinMode(botones[i], INPUT);
  }

  // Inicializamos la comunicaciión serial para imprimir resultados
  Serial.begin(115200);
  Serial.println("Iniciando");
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer


  memcpy(peerInfo.peer_addr, direccion_tablero, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer for direccion_tablero");
    return;
  }

  // Register peer for direccion_cronometro_n1
  memcpy(peerInfo.peer_addr, direccion_cronometro_n1, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer for direccion_cronometro_n1");
    return;
  }

  // Register peer for direccion_cronometro_n2
  memcpy(peerInfo.peer_addr, direccion_cronometro_n2, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer for direccion_cronometro_n2");
    return;
  }




  sonidoIniciar();
  enviar_tablero();
}

void loop() {
  for (int i = 0; i < numBotones; i++) {
    // Leemos el estado actual del botón
    bool estadoBoton = digitalRead(botones[i]);

    // Comprobamos si ha pasado suficiente tiempo desde la última lectura
    if ((millis() - ultimaLectura[i]) > tiempoDebounce) {
      // Si el estado del botón ha cambiado desde la última lectura
      if (estadoBoton != estadosAnteriores[i]) {
        if (estadoBoton == LOW) {

          // El botón se ha presionado
          Serial.print("Botón en el pin ");
          Serial.print(botones[i]);
          Serial.println(" presionado.");

          switch (botones[i]) {

            //Tablero principal
            case 16:
              valor_local += 1;
              enviar_tablero();
              sonidoSubir();
              break;
            case 17:
              valor_local -= 1;
              enviar_tablero();
              sonidoBajar();
              break;
            case 15:
              valor_visita += 1;
              enviar_tablero();
              sonidoSubir();
              break;
            case 18:
              valor_visita -= 1;
              enviar_tablero();
              sonidoBajar();
              break;
            case 19:
              valor_falta_local += 1;
              enviar_tablero();
              sonidoSubir();
              break;
            case 21:
              valor_falta_visita += 1;
              enviar_tablero();
              sonidoSubir();
              break;
            case 23:
              estado_cronometro = 2;  //pausa
              enviar_tablero();
              estado_cronometro = 0;  //una ves enviado el valor se resea a 0 el estado
              Mi();
              break;
            case 32:
              estado_cronometro = 1;  //iniciar
              enviar_tablero();
              estado_cronometro = 0;  //una ves enviado el valor se resea a 0 el estado
              Do();
              break;
            case 33:
              estado_cronometro = 3;  //reiniciar
              enviar_tablero();
              estado_cronometro = 0;  //una ves enviado el valor se resea a 0 el estado
              Fa();
              break;
            case 4:
              valor_periodo += 1;
              enviar_tablero();
              sonidoSubir();
              break;
            case 5:
              valor_periodo -= 1;
              enviar_tablero();
              sonidoBajar();
              break;
            case 12:  //subir tiempo
              tiempo_cronometro += 1;
              enviar_tablero();
              sonidoSubir();
              break;
            case 27:  //bajar tiempo
              tiempo_cronometro -= 1;
              enviar_tablero();
              sonidoBajar();
              break;

            case 22:
              estado_cronometro_basquet = 3;
              enviar_cronometro(direccion_cronometro_n1);
              enviar_cronometro(direccion_cronometro_n2);
              estado_cronometro_basquet = 0;  //una ves enviado el valor se resea a 0 el estado
              sonidoBajar();
              break;
            case 26:
              estado_cronometro_basquet = 1;
              enviar_cronometro(direccion_cronometro_n1);
              enviar_cronometro(direccion_cronometro_n2);
              estado_cronometro_basquet = 0;  //una ves enviado el valor se resea a 0 el estado
              sonidoSubir();
              break;
            case 14:
              estado_cronometro_basquet = 2;
              enviar_cronometro(direccion_cronometro_n1);
              enviar_cronometro(direccion_cronometro_n2);
              estado_cronometro_basquet = 0;  //una ves enviado el valor se resea a 0 el estado
              sonidoSubir();


            default:
              // Manejar un valor no reconocido si es necesario
              break;
          }

          /*
            if (result == ESP_OK) {
            Serial.println("Sent with success");
            } else {
            Serial.println("Error sending the data");
            }
          */
        }
      }

      // Actualizamos el estado anterior y el tiempo de la última lectura
      estadosAnteriores[i] = estadoBoton;
      ultimaLectura[i] = millis();
    }
  }
}

void enviar_tablero() {

  valor_local = constrain(valor_local, 0, 199);
  valor_visita = constrain(valor_visita, 0, 199);
  valor_falta_local = constrain(valor_falta_local, 0, 9);
  valor_falta_visita = constrain(valor_falta_visita, 0, 9);
  valor_periodo = constrain(valor_periodo, 0, 9);
  tiempo_cronometro = constrain(tiempo_cronometro, 1, 19);
  dato_tablero.a = valor_local;
  dato_tablero.b = valor_visita;
  dato_tablero.c = valor_falta_local;
  dato_tablero.d = valor_falta_visita;
  dato_tablero.e = estado_cronometro;
  dato_tablero.f = tiempo_cronometro;
  dato_tablero.g = valor_periodo;
  esp_err_t result = esp_now_send(direccion_tablero, (uint8_t *)&dato_tablero, sizeof(dato_tablero));
}
void enviar_cronometro(const uint8_t *direccion) {
  dato_cronometro.a = estado_cronometro_basquet;
  esp_err_t result1 = esp_now_send(direccion_cronometro_n1, (uint8_t *)&dato_cronometro, sizeof(dato_cronometro));
  esp_err_t result2 = esp_now_send(direccion_cronometro_n2, (uint8_t *)&dato_cronometro, sizeof(dato_cronometro));
}
