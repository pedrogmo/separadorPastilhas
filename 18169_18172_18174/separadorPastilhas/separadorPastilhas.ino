//Includes de bibliotecas
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Stepper.h>

//Objeto de bluetooth, comunicação entre arduino e appInventor
SoftwareSerial bluetooth(6,7);

//Declaração do servo
Servo servo;

//Declaração do motor de passo
Stepper passo(500, 8, 10, 9, 11);

//Constantes inteiras para funcionamento do programa, adiquiridas com base na montagem

const int anguloHelice1 = 300;
const int anguloHelice2 = 212;
const int valor_escuro = 700;
const int angulo_claro =  40;
const int angulo_escuro = 140;

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
  passo.setSpeed(45); //ativação do motor de passo
  servo.write(90);
}

void loop() 
{  
  passo.step(anguloHelice1); //motor passo gira para pegar um mm só e ler o seu valor
  delay(1000); 
  int valorSensor = analogRead(portaSensorLuz); //valor que o sensor de luz retorn
  delay(500);
  if (valorSensor > 600 && valorSensor < 800) //se estiver no intervalo em que há mm
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
    delay(500);
    passo.step(anguloHelice2); //motor passo gira para cair um mm na rampa      
    delay(100);
    int anguloHeliceTotal = anguloHelice1 + anguloHelice2;
    passo.step(-anguloHeliceTotal);
  }
  else //se não foi colocado mm

  {
    passo.step(-anguloHelice1); //passo volta à posição original
  }
  //servo e motor de passo voltam à posição original
  servo.write(90);
  delay(900);
}
