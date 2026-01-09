#include <Stepper.h>

// Constantes arbitrárias (podem ser alteradas quando for efetuado o teste físico)
const int stepPin = 4;
const int dirPin = 5;

const int delay = 800;

const int passosParaMover = 400

void setup() {
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, HIGH);

  Serial.println("Arduino pronto para rotação");

}

void loop() {
  if (Serial.available() > 0){
    char comando = Serial.read();

    if (comando = 'R') {
      moverMotor(passosParaMover);

      // avisar ao Qt que o movimento acabou com o sinal 'K' (OK)
      // TO-DO: implementar esse 'handhsake' no codigo qt
      Serial.print('P');
    }
  }
}

void moverMotor(int passos){
  for (int i=0; i < passos; i++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(800);
  }
}
