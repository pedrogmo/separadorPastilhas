//Includes de bibliotecas
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Stepper.h>

//Objeto de bluetooth, comunicação entre arduino e appInventor
SoftwareSerial bluetooth(6,7);

//Declaração do servo
Servo servo1;

//Declaração do motor de passo
Stepper passo(stepPerRevolution, 8, 10, 9, 11);

//Constantes inteiras para funcionamento do programa, adiquiridas com base na montagem
const int stepPerRevolution = 500;
const int portaServo1 = 5;
const int anguloHelice = 10;
const int valor_escuro = 550;
const int angulo_claro = 10;
const int angulo_escuro = -(angulo_claro);
const int valor_branco = 10;

//Porta analógica do sensor de luz
const int portaSensorLuz = A0;

//Contadores de pastilhas claras e escuras
int contEscuro = 0;
int contClaro = 0;

void setup() 
{
  servo1.attach(portaServo1); //ativação do servo
  passo.setSpeed(60); //ativação do motor de passo
}

void loop() 
{
  servo1.write(anguloHelice); //servo gira para pegar um mm só
  delay(100); 
  int valorSensor = analogRead(portaSensorLuz); //valor que o sensor de luz retorna
  if (!(valorSensor > valor_branco - 10 && valorSensor < valor_branco + 10)) //se não estiver no intervalo onde a cor é branca
  {
    if (valorSensor > valor_escuro) //se for escuro
    {
      passo.step(angulo_escuro); //motor de passo gira anti-horário, ângulo escuro
      contEscuro++; //contEscuro aumenta
    }
    else //mm claro
    {
      passo.step(angulo_claro); //gira horário, ângulo claro
      contClaro++; //contClaro aumenta
    }
    //Aqui são printados os valores dos contadores pelo bluetooth
    bluetooth.print("");
    bluetooth.print(contClaro);
    bluetooth.print("|");
    bluetooth.print(contEscuro);
  }
  //servo e motor de passo voltam à posição original
  servo.write(0);
  passo.step(0);
  delay(900);
}
