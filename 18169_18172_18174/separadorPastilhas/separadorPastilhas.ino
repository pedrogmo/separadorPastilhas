#include <Servo.h>
#include <SoftwareSerial.h>
#include <Stepper.h>
SoftwareSerial bluetooth(10,11);
Servo servo1;
const int stepPerRevolution = 500;
Stepper passo(stepPerRevolution, 8, 10, 9, 11);
const int portaServo1 = 5;
const int anguloHelice = 10;
const int valor_escuro = 550;
const int angulo_claro = 10;
const int angulo_escuro = -(angulo_claro);
const int branco = 10;
const int portaSensorLuz = A0;
int contEscuro = 0;
int contClaro = 0;

void setup() 
{
  servo1.attach(portaServo1);
  passo.setSpeed(60);
}

void loop() 
{
  servo1.write(anguloHelice);
  delay(100);
  int valorSensor = analogRead(portaSensorLuz);
  if (!(valorSensor > branco - 10 && valorSensor < branco + 10))
  {
    if (valorSensor > valor_escuro)
    {
      passo.step(angulo_escuro); //anti-horário
      contEscuro++;
    }
    else
    {
      passo.step(angulo_claro); //horário
      contClaro++;
    }
    bluetooth.print("");
    bluetooth.print(contClaro);
    bluetooth.print("|");
    bluetooth.print(contEscuro);
  }
  servo.write(0);
  delay(900);
}
