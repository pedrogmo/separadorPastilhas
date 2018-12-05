//Includes de bibliotecas
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Stepper.h>

//Objeto de bluetooth, comunicação entre arduino e appInventor
SoftwareSerial bluetooth(6,7);

//Declaração do servo
Servo servo;

//Declaração do motor de passo
const int stepPerRevolution = 500;
Stepper passo(stepPerRevolution, 8, 10, 9, 11);

//Constantes inteiras para funcionamento do programa, adiquiridas com base na montagem

const int anguloHelice1 = 10;
const int anguloHelice2 = 10;
const int valor_escuro = 550;
const int angulo_claro = 0;
const int angulo_escuro = 0;
const int valor_branco = 10;

//Porta analógica do sensor de luz
const int portaSensorLuz = A0;

//Porta do servo motor
const int portaServo1 = 5;

//Contadores de pastilhas claras e escuras
int contEscuro = 0;
int contClaro = 0;

void setup() 
{
  servo.attach(portaServo1); //ativação do servo
  passo.setSpeed(60); //ativação do motor de passo
}

void loop() 
{
  if (bluetooth.read() == 'L') //Se for para ligar
  {
    passo.step(anguloHelice1); //motor passo gira para pegar um mm só e ler o seu valor
    delay(100); 
    int valorSensor = analogRead(portaSensorLuz); //valor que o sensor de luz retorna
    passo.step(anguloHelice2); //motor passo gira para cair um mm na rampa
    if (!(valorSensor > valor_branco - 10 && valorSensor < valor_branco + 10)) //se não estiver no intervalo onde a cor é branca
    {
      if (valorSensor > valor_escuro) //se for escuro
      {
        servo.write(angulo_escuro); //servo gira anti-horário, ângulo escuro
        contEscuro++; //contEscuro aumenta
      }
      else //mm claro
      {
        servo.write(angulo_claro); //servo gira horário, ângulo claro
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
    int anguloHeliceTotal = anguloHelice1 + anguloHelice2;
    passo.step(-anguloHeliceTotal);
    delay(900);
  }
  else
  {
    contClaro = 0;
    contEscuro = 0;
  }
}
