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

const int anguloPasso1 = -512;
const int anguloPasso2 = -200;
const int valor_escuro = 700;
const int angulo_claro =  40;
const int angulo_escuro = 140;

//Contadores de pastilhas claras e escuras
int contEscuro = 0;
int contClaro = 0;

void setup() 
{
  servo.attach(5); //ativação do servo
  passo.setSpeed(60); //ativação do motor de passo
  servo.write(90);
}

void loop()                
{  
  passo.step(anguloPasso1); //motor passo gira para pegar um mm só e ler o seu valor
  delay(500); 
  int valorSensor = analogRead(A0); //valor que o sensor de luz retorn
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
    passo.step(anguloPasso2); //motor passo gira para cair um mm na rampa      
    delay(500);
    int anguloPassoTotal = anguloPasso1 + anguloPasso2;
    passo.step(-anguloPassoTotal);
  }
  else //se não foi colocado mm
  {
    passo.step(-anguloPasso1); //passo volta à posição original
  }
  //servo e motor de passo voltam à posição original
  servo.write(90);
  delay(900);
}
