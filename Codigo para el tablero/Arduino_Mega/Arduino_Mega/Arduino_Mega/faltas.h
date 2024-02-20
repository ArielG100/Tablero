extern const int pinClock;
extern const int numero[];
// Constrantes del faltas  local
extern const int pinData_faltas_local;
extern const int pinLatcha_faltas_local;

// Constrantes del faltas  visita
extern const int pinData_faltas_visita;
extern const int pinLatcha_faltas_visita;


void imprimir_faltas_local(int valor) {
  shiftOut(pinData_faltas_local, pinClock, MSBFIRST, numero[valor]);
  digitalWrite(pinLatcha_faltas_local, HIGH);
  digitalWrite(pinLatcha_faltas_local, LOW);
}

void imprimir_faltas_visita(int valor) {

  shiftOut(pinData_faltas_visita, pinClock, MSBFIRST, numero[valor]);
  digitalWrite(pinLatcha_faltas_visita, HIGH);
  digitalWrite(pinLatcha_faltas_visita, LOW);
}
