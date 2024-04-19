extern const int pinData_Cronometro;
extern const int pinLatcha_Cronometro;
extern const int pinClock;
extern const int numero[];

void imprimir_encender_cronometro(unsigned long milisegundos) {
  // Serial.print("milisegundos");
  // Serial.println(milisegundos);
  unsigned long segundos = milisegundos / 1000;

  unsigned long primer_digito_minutero = (segundos / 60) / 10;
  unsigned long segundo_digito_minutero = (segundos / 60) % 10;

  unsigned long primer_digito_segundero = (segundos % 60) / 10;
  unsigned long segundo_digito_segundero = (segundos % 60) % 10;

  unsigned long primer_digito_milisegundero = (milisegundos % 1000) / 10;
  unsigned long segundo_digito_milisegundero = (milisegundos % 1000) % 10;
  // Serial.print("Segundos");
  // Serial.println(segundos);
  // Serial.print("minutos");
  // Serial.print(primer_digito_minutero);
  // Serial.print(",");
  // Serial.println(segundo_digito_minutero);

  // Led1 es el segundo decimal del minutero
  // Led2 es el primer decimal del minutero
  // Led3 es el segundo decimal del segundero
  // Led4 es el primer decimal de segundero
  // Envía los datos al 74HC595

  // if (segundos < 60) {

  //   shiftOut(pinData_Cronometro, pinClock, MSBFIRST, numero[segundo_digito_milisegundero]);
  //   shiftOut(pinData_Cronometro, pinClock, MSBFIRST, numero[primer_digito_milisegundero]);
  //   shiftOut(pinData_Cronometro, pinClock, MSBFIRST, numero[segundo_digito_segundero]);
  //   shiftOut(pinData_Cronometro, pinClock, MSBFIRST, numero[primer_digito_segundero]);
  //   digitalWrite(pinLatcha_Cronometro, HIGH);
  //   digitalWrite(pinLatcha_Cronometro, LOW);
  // } else {

    shiftOut(pinData_Cronometro, pinClock, MSBFIRST, numero[segundo_digito_segundero]);
    shiftOut(pinData_Cronometro, pinClock, MSBFIRST, numero[primer_digito_segundero]);
    shiftOut(pinData_Cronometro, pinClock, MSBFIRST, numero[segundo_digito_minutero]);
    shiftOut(pinData_Cronometro, pinClock, MSBFIRST, numero[primer_digito_minutero]);
    digitalWrite(pinLatcha_Cronometro, HIGH);
    digitalWrite(pinLatcha_Cronometro, LOW);
  // }
}
