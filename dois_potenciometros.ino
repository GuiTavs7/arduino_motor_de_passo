//O objetivo deste código é controlar a velocidade de giro do motor de passo e sua direção de acordo com os valores de dois potenciômetros!

// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Stepper.h>   //Biblioteca para controle de motor de passo

// ========================================================================================================
// --- MAPEAMENTO DE HARDWARE ---
#define   in1   8      //Entrada 1 do ULN2003 (digital)
#define   in2   9      //Entrada 2 do ULN2003 (digital)
#define   in3  10      //Entrada 3 do ULN2003 (digital)
#define   in4  11      //Entrada 4 do ULN2003 (digital)

// ========================================================================================================
// --- CONSTANTES AUXILIARES ---

const int stepsPerRevolution = 200;  // Aqui você altera o número de passos por revolução do motor
const int potPin_1 = A0; // Pino do potenciômetro 1 - Analógica 0
const int potPin_2 = A1; // Pino do potenciômetro 2 - Analógica 1

// ========================================================================================================
// --- DECLARAÇÃO DE OBJETOS ---

Stepper myStepper(stepsPerRevolution, in1,in3,in2,in4); //Criação do objeto motor de passo, atribuindo como argumentos da função o número de passos por revolução e as 4 entradas digitais da placa

// ========================================================================================================
// --- CONFIGURAÇÕES INICIAIS ---

void setup() 
{
  myStepper.setSpeed(160); // Use esta função para definir as rotações por minuto (RPM) do motor
  Serial.begin(9600); // Inicializa a comunicação serial com uma taxa de 9600 baud
  
} //Fim da função setup()

// ========================================================================================================

// --- LOOP INFINITO ---

void loop() 
{

  //CONFIGURAÇÕES DO PRIMEIRO POTENCIÔMETRO - CONTROLA A VELOCIDADE DO MOTOR

  int potValue_1 = analogRead(potPin_1);    // Lê o valor de 0 a 1023 do primeiro potenciômetro

  // 1) Mapeia o valor do potenciômetro para a velocidade do motor
  // 2) Neste caso estamos definindo que no valor 0 do potenciômetro o motor gira em 30 RPM (mínimo) e, no valor 1023 do potenciômetro o motor gira em 160 RPM (máximo)
  // 3) Altere os valores conforme necessário

  int motorSpeed = map(potValue_1, 0, 1023, 30, 160); 

  //Serial.println("Valor do primeiro potenciômetro: ");
  Serial.println(potValue_1); // Envia o valor lido para o monitor serial

  myStepper.setSpeed(motorSpeed); // Define a velocidade do motor em passos por minuto (PPM)

  //------------------------------------------------------------------------------------------------------------------------------//

  //CONFIGURAÇÕES DO SEGUNDO POTENCIÔMETRO - CONTROLA O SENTIDO DE GIRO / DIREÇÃO DO MOTOR - HORÁRIO OU ANTI-HORÁRIO

  int potValue_2 = analogRead(potPin_2); // Lê o valor de 0 a 1023 do segundo potenciômetro

  //Serial.println("Valor do segundo potenciômetro: ");
  Serial.println(potValue_2); // Envia o valor lido para o monitor serial

  //BLOCO CONDICIONAL PARA DETERMINAR A DIREÇÃO DO MOTOR

  if(potValue_2 <= 512){ // Se o valor analógico do segundo potenciômetro for menor ou igual 512 (aproximadamente a metade de 10223), o motor irá girar no sentido horário

    Serial.println("clockwise - sentido-horário");
    myStepper.step(-stepsPerRevolution); // Função que permite o giro do motor no sentido horário (basta retirar o sinal negativo para inverter o sentido)
  }
  else{ // Caso a condição acima não seja verdadeira, o motor irá girar no sentido anti-horário

    Serial.println("counterclockwise - sentido anti-horário"); // Enquanto a condição acima for verdadeira, o motor irá girar no sentido anti-horário 
    myStepper.step(stepsPerRevolution); // Função que permite o giro do motor no sentido anti-horário (basta acrescentar o sinal negativo para inverter o sentido)
  }

} // FIM FA FUNÇÃO loop()
