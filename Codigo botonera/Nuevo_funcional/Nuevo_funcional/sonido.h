#define BUZZER_PIN 2

void sonidoSubir() {
  tone(BUZZER_PIN, 440, 200);  // Frecuencia: La, Duración: 200ms
  delay(250);                  // Pequeña pausa entre los sonidos
  noTone(BUZZER_PIN);          // Detener el zumbador
}

void sonidoBajar() {
  tone(BUZZER_PIN, 293.66, 200);  // Frecuencia: Re, Duración: 200ms
  delay(250);                     // Pequeña pausa entre los sonidos
  noTone(BUZZER_PIN);             // Detener el zumbador
}

void sonidoIniciar() {
;
  tone(BUZZER_PIN, 440, 200);
  tone(BUZZER_PIN, 293.66, 200);
  noTone(BUZZER_PIN);  // Detener el zumbador
}


void Do() {
  tone(BUZZER_PIN, 261.63, 200);  // Do
}
void Mi() {
  tone(BUZZER_PIN, 329.63, 200);  // Mi
}

void Fa() {

  tone(BUZZER_PIN, 349.23, 400);  // Fa
}