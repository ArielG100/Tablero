

#include <ESP8266WiFi.h>
#include <espnow.h>


// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  uint8_t a;
  // uint8_t b;
  // uint8_t c;
  // uint8_t d;
  // uint8_t e;
  // uint8_t f;
  // uint8_t g;
} struct_message;

uint8_t dato = 0; 

uint8_t valor_local, valor_visita, valor_falta_local, valor_falta_visita, estado_cronometro, tiempo_cronometro, valor_periodo;
// Create a struct_message called myData
struct_message myData;

// Funcion que se ejecuta cuando se reciben datos de la botonera y se envian al arduino
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  // Recibe los valores de la botonera y los muestra en el serial
  memcpy(&myData, incomingData, sizeof(myData));
  /*Serial.print("valor_local: ");
    Serial.println(myData.a);
    Serial.print("valor_visita: ");
    Serial.println(myData.b);
    Serial.print("valor_falta_local: ");
    Serial.println(myData.c);
    Serial.print("valor_falta_visita: ");
    Serial.println(myData.d);
    Serial.print("estado_cronometro: ");
    Serial.println(myData.e);
    Serial.print("valor_periodo: ");
    Serial.println(myData.f);
  */
  // Asigna el valor que recibe de la botonera a variables para enviar
  dato = myData.a;
  switch (dato) {
    case 1:
      valor_local = constrain(valor_local + 1, 0, 199);
      break;
    case 2:
      valor_local = constrain(valor_local - 1, 0, 199);
      break;
    case 3:
      valor_visita = constrain(valor_visita + 1, 0, 199);
      break;
    case 4:
      valor_visita = constrain(valor_visita - 1, 0, 199);
      break;
    case 5:
      valor_falta_local = constrain(valor_falta_local + 1, 0, 9);
      break;
    case 6:
      valor_falta_visita = constrain(valor_falta_visita + 1, 0, 9);
      break;
    case 7:
      // Acción para pausar
      estado_cronometro = 2;
      break;
    case 8:
      // Acción para iniciar
      estado_cronometro = 1;
      break;
    case 9:
      // Acción para reiniciar
      estado_cronometro = 3;
      break;
    case 10:
      valor_periodo = constrain(valor_periodo + 1, 0, 9);
      break;
    case 11:
      valor_periodo = constrain(valor_periodo - 1, 0, 9);
      break;
    case 12:
      tiempo_cronometro = constrain(tiempo_cronometro + 1, 1, 19);
      break;
    case 13:
      tiempo_cronometro = constrain(tiempo_cronometro - 1, 1, 19);
      break;
    default:
      // Acción por defecto si dato no coincide con ningún caso
      break;
  }
  dato = 0;
  // valor_visita = myData.b;
  // valor_falta_local = myData.c;
  // valor_falta_visita = myData.d;
  // estado_cronometro = myData.e;
  // tiempo_cronometro = myData.f;
  // valor_periodo = myData.g;


  // valor_local = constrain(valor_local, 0, 199);
  // valor_visita = constrain(valor_visita, 0, 199);
  // valor_falta_local = constrain(valor_falta_local, 0, 9);
  // valor_falta_visita = constrain(valor_falta_visita, 0, 9);
  // valor_periodo = constrain(valor_periodo, 0, 9);

  // Envía las variables al Arduino Mega
  Serial.print(valor_local);
  Serial.print(",");
  Serial.print(valor_visita);
  Serial.print(",");
  Serial.print(valor_falta_local);
  Serial.print(",");
  Serial.print(valor_falta_visita);
  Serial.print(",");
  Serial.print(estado_cronometro);  // 1 star 2 stop 3 reset
  Serial.print(",");
  Serial.print(tiempo_cronometro);
  Serial.print(",");
  Serial.print(valor_periodo);
  Serial.println();
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  valor_local = 0;
  valor_visita = 0;
  valor_falta_local = 0;
  valor_falta_visita = 0;
  estado_cronometro = 0;
  tiempo_cronometro = 0;
  valor_periodo = 0;
  //espSerial.begin(9600);  // Configura la velocidad de transmisión (baud rate)

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
