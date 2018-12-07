#include <Stepper.h>
Stepper passo(500, 8, 10, 9, 11);
const int valor = 50;

void setup() {
  // put your setup code here, to run once:
  passo.setSpeed(45); //ativação do motor de passo
  passo.step(valor);
  //delay(1000);
  //passo.step(-valor);
}
void loop() {
  // put your main code here, to run repeatedly: 
}
