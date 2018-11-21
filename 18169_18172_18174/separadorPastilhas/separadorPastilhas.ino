#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial bluetooth;
Servo servo1;
Servo servo2;
const int portaServo1 = 5;
const int portaServo2 = 6;
const int anguloHelice = ;
const int valor_escuro = 550;
const int angulo_claro = ;
const int angulo_escuro = ;
const int portaSensorLuz = A0;
int contEscuro = 0;
int contClaro = 0;

void setup() 
{
  servo1.attach(portaServo1);
  servo2.attach(portaServo2);
}

void loop() 
{
  servo1.write(anguloHelice);
  delay(100);
  int valorSensor = analogRead(portaSensorLuz);
  if (valorSensor > valor_escuro)
  {
    servo2.write(angulo_escuro);
    contEscuro++;
  }
  else
  {
    servo2.write(angulo_claro);
    contClaro++;
  }
  bluetooth.print("");
  bluetooth.print(contClaros);
  bluetooth.print("|");
  bluetooth.print(contEscuros);
  delay(900);
}
