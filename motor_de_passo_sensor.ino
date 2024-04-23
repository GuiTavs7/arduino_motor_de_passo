#include <Stepper.h>   //Biblioteca para controle de motor de passo

#define   in1   8      //Entrada 1 do ULN2003 (digital)
#define   in2   9      //Entrada 2 do ULN2003 (digital)
#define   in3  10      //Entrada 3 do ULN2003 (digital)
#define   in4  11      //Entrada 4 do ULN2003 (digital)

const int stepsPerRevolution = 2038;  // Aqui você altera o número de passos por revolução do motor

Stepper myStepper(stepsPerRevolution, in1,in3,in2,in4); 

int analogPin = 3;
int valor = 0;

void setup() {

  Serial.begin(9600);
  myStepper.setSpeed(12); // Use esta função para definir as rotações por minuto (RPM) do motor - 12 = mais adequado

}

void loop() {
  
  valor = analogRead(analogPin); // Guarda na variável a leitura analógica do pino do sensor

  Serial.println(valor); // Printa no serial monitor o valor 

  if(valor>900){
      Serial.println("\n LUMINOSIDADE BAIXA - SENTIDO ANTI-HORÁRIO! \n");
      myStepper.step(stepsPerRevolution); // Função que permite o giro do motor no sentido anti-horário (basta acrescentar o sinal negativo para inverter o sentido)
  }
  else{
      Serial.println("\n LUMINOSIDADE ALTA - SENTIDO HORÁRIO! \n");
      myStepper.step(-stepsPerRevolution); //Função que permite o giro do motor no sentido horário
  }

}
