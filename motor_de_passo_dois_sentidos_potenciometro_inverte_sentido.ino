#include <Stepper.h>

const int stepsPerRevolution = 64;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

int potPin = A0; // Pino analógico onde o potenciômetro está conectado
int potValue;    // Variável para armazenar o valor do potenciômetro

void setup() {
  myStepper.setSpeed(450);
  Serial.begin(9600); // Inicializa a comunicação serial com uma taxa de 9600 baud
}

void loop() {
  // Lê o valor do potenciômetro
  potValue = analogRead(potPin);

  Serial.println(potValue); // Envia o valor lido para o monitor serial
  
  delay(100); // Aguarda um curto período de tempo para evitar leituras muito rápidas

  // Determina o sentido de rotação com base no valor do potenciômetro
  if (potValue < 512) {
    // Gira o motor no sentido anti-horário se o valor do potenciômetro for menor que 512
    for (int i = 0; i < 50; i++) {
      myStepper.step(stepsPerRevolution);
    }
  } else {
    // Gira o motor no sentido horário se o valor do potenciômetro for maior ou igual a 512
    for (int i = 0; i < 50; i++) {
      myStepper.step(-stepsPerRevolution);
    }
  }
}
