int somatoria = 0;
int maiorValor = 0;
int menorValor = 0;
int meuCont = 0;
 
 void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(200);
  int valorSensor = analogRead(A0);
  meuCont++;
  Serial.print("|");
  somatoria += valorSensor;
  if (valorSensor > maiorValor) maiorValor = valorSensor;
  if (valorSensor < menorValor) menorValor = valorSensor;
  if (meuCont == 30)
  {
    int media = somatoria / meuCont;
    Serial.println();
    Serial.print("Media: ");
    Serial.println(media);
    Serial.print("Maior valor: ");
    Serial.println(maiorValor);
    Serial.print("Menor valor: ");
    Serial.println(menorValor);
    meuCont = 0;
  }
}
