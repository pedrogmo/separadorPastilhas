#include <Stepper.h>
Stepper passo(500, 8, 10, 9, 11);

void setup() {
  // put your setup code here, to run once:
  passo.setSpeed(45); //ativação do motor de passo
}

void loop() {
  // put your main code here, to run repeatedly:
  passo.step(512);
}