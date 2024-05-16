extern const int pinData_Cronometro;
extern const int pinLatcha_Cronometro;
extern const int pinClock;
extern const int numero[];
void imprimir_encender_cronometro(int segundos) {
  int primer_digito_minutero = (segundos / 60) / 10;
  int segundo_digito_minutero = (segundos / 60) % 10;

  int primer_digito_segundero = (segundos % 60) / 10;
  int segundo_digito_segundero = (segundos % 60) % 10;

  

  // Led1 es el segundo decimal del minutero
  // Led2 es el primer decimal del minutero
  // Led3 es el segundo decimal del segundero
  // Led4 es el primer decimal de segundero


  // Envía los datos al 74HC595

  shiftOut(pinData_Cronometro, pinClock, MSBFIRST, numero[segundo_digito_segundero]);
  shiftOut(pinData_Cronometro, pinClock, MSBFIRST, numero[primer_digito_segundero]);
  digitalWrite(pinLatcha_Cronometro, HIGH);
  digitalWrite(pinLatcha_Cronometro, LOW);
}
