extern const int pinClock;
extern const int numero[];
// Constrantes del marcador  local
extern const int pinData_marcador_local;
extern const int pinLatcha_marcador_local;
extern const int pin_3er_decimal_local;

// Constrantes del marcador  visita
extern const int pinData_marcador_visita;
extern const int pinLatcha_marcador_visita;
extern const int pin_3er_decimal_visita;

void imprimir_marcador_local(int valor) {
  int digito1, digito2, digito3;
  // Extraer los dígitos
  digito1 = valor / 100;        // Divide por 100 para obtener el primer dígito
  digito2 = (valor / 10) % 10;  // Divide por 10 y toma el residuo para obtener el segundo dígito
  digito3 = valor % 10;         // Obtiene el tercer dígito como el residuo
  if (digito1 == 1) {
    digitalWrite(pin_3er_decimal_local, HIGH);
  } else {
    digitalWrite(pin_3er_decimal_local, LOW);
  }
  shiftOut(pinData_marcador_local, pinClock, MSBFIRST, numero[digito2]);
  shiftOut(pinData_marcador_local, pinClock, MSBFIRST, numero[digito3]);

  digitalWrite(pinLatcha_marcador_local, HIGH);
  digitalWrite(pinLatcha_marcador_local, LOW);
}

void imprimir_marcador_visita(int valor) {
  int digito1, digito2, digito3;
  // Extraer los dígitos
  digito1 = valor / 100;        // Divide por 100 para obtener el primer dígito
  digito2 = (valor / 10) % 10;  // Divide por 10 y toma el residuo para obtener el segundo dígito
  digito3 = valor % 10;         // Obtiene el tercer dígito como el residuo
  if (digito1 == 1) {
    digitalWrite(pin_3er_decimal_visita, HIGH);
  } else {
    digitalWrite(pin_3er_decimal_visita, LOW);
  }
  shiftOut(pinData_marcador_visita, pinClock, MSBFIRST, numero[digito2]);
  shiftOut(pinData_marcador_visita, pinClock, MSBFIRST, numero[digito3]);

  digitalWrite(pinLatcha_marcador_visita, HIGH);

  digitalWrite(pinLatcha_marcador_visita, LOW);
}
