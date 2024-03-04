//O objetivo deste código é controlar a velocidade de giro do motor de passo de acordo com o valor do potenciômetro!

// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Stepper.h>   //Biblioteca para controle de motor de passo

// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   in1   8      //Entrada 1 do ULN2003 (digital)
#define   in2   9      //Entrada 2 do ULN2003 (digital)
#define   in3  10      //Entrada 3 do ULN2003 (digital)
#define   in4  11      //Entrada 4 do ULN2003 (digital)

// ========================================================================================================
// --- Constantes Auxiliares ---
const int stepsPerRevolution = 200;  // Aqui você altera o número de passos por revolução do motor
const int potPin = A0; // Pino do potenciômetro - Analógica 0

// ========================================================================================================
// --- Declaração de Objetos ---
Stepper myStepper(stepsPerRevolution, in1,in3,in2,in4); //Criação do objeto motor de passo, atribuindo como argumentos da função o número de passos por revolução e as 4 entradas digitais da placa

// ========================================================================================================
// --- Configurações Iniciais ---

void setup() 
{
  myStepper.setSpeed(160); // Use esta função para definir as rotações por minuto (RPM) do motor
  Serial.begin(9600); // Inicializa a comunicação serial com uma taxa de 9600 baud
  
} //Fim da função setup()

// ========================================================================================================
// --- Loop Infinito ---

void loop() 
{
  int potValue = analogRead(potPin);    // Lê o valor do potenciômetro

  // Mapeia o valor do potenciômetro para a velocidade do motor
  // Neste caso estamos definindo que no valor 0 do potenciômetro o motor gira em 30 RPM (mínimo) e, no valor 1023 do potenciômetro o motor gira em 160 RPM (máximo)
  int motorSpeed = map(potValue, 0, 1023, 30, 160); // Altere os valores conforme necessário

  Serial.println(potValue); // Envia o valor lido para o monitor serial

  // Define a velocidade do motor em passos por minuto (PPM)
  myStepper.setSpeed(motorSpeed);
  
  //Motor girando no sentido horário

  Serial.println("clockwise");
  myStepper.step(-stepsPerRevolution); //Função que permite o giro do motor no sentido horário
  delay(1000); //Define o tempo de 1 segundo de espera para girar no outro sentido
  
  //Motor girando no sentido anti-horário

  Serial.println("counterclockwise");
  myStepper.step(stepsPerRevolution); // Função que permite o giro do motor no sentido anti-horário (basta acrescentar o sinal negativo para inverter o sentido)
  delay(1000); //Define o tempo de 1 segundo de espera para girar no outro sentido

} //Fim da função loop()

// ========================================================================================================

// OBSERVAÇÃO IMPORTANTE: Você pode comentar um dos blocos de giro em um dos sentidos para observar o motor girando apenas no sentido horário ou anti-horário, assim
//                        ficará fácil visualizar a mudança de velocidade


 
  













