extern const int pinClock;
extern const int numero[];
extern const int pinData_periodo;
extern const int pinLatcha_periodo;



void imprimir_periodo(int valor) {
  shiftOut(pinData_periodo, pinClock, MSBFIRST, numero[valor]);
  digitalWrite(pinLatcha_periodo, HIGH);
  digitalWrite(pinLatcha_periodo, LOW);
}
