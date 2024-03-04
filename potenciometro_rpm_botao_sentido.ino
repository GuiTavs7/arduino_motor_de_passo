//O objetivo deste código é controlar a velocidade de giro do motor de passo de acordo com o valor do potenciômetro!
//Além disso, quando o botão for pressionado, o sentido de rotação do motor deverá ser alterado!

// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Stepper.h>   //Biblioteca para controle de motor de passo
#include <Button.h> //Biblioteca para funcionamento de botões

// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   in1   8      //Entrada 1 do ULN2003 (digital)
#define   in2   9      //Entrada 2 do ULN2003 (digital)
#define   in3  10      //Entrada 3 do ULN2003 (digital)
#define   in4  11      //Entrada 4 do ULN2003 (digital)
#define buttonPin 2 //Entrada 2 - Botão (digital)

// ========================================================================================================
// --- Constantes Auxiliares ---
const int stepsPerRevolution = 200;  // Aqui você altera o número de passos por revolução do motor
const int potPin = A0; // Pino do potenciômetro - Analógica 0

// ========================================================================================================
// --- Declaração de Objetos ---
Stepper myStepper(stepsPerRevolution, in1,in3,in2,in4); //Criação do objeto motor de passo, atribuindo como argumentos da função o número de passos por revolução e as 4 entradas digitais da placa

Button button(buttonPin); // Cria um objeto Button associado ao pino do botão

// ========================================================================================================
// --- Configurações Iniciais ---

void setup() 
{
  myStepper.setSpeed(160); // Use esta função para definir as rotações por minuto (RPM) do motor
  pinMode(buttonPin, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up interno
  Serial.begin(9600); // Inicializa a comunicação serial com uma taxa de 9600 baud
  button.begin(); // Inicializa o botão
  
} //Fim da função setup()

// ========================================================================================================
// --- Loop Infinito ---

void loop() 
{
  int potValue = analogRead(potPin);    // Lê o valor do potenciômetro

  // 1) Mapeia o valor do potenciômetro para a velocidade do motor
  // 2) Neste caso estamos definindo que no valor 0 do potenciômetro o motor gira em 30 RPM (mínimo) e, no valor 1023 do potenciômetro o motor gira em 160 RPM (máximo)
  // 3) Altere os valores conforme necessário
  int motorSpeed = map(potValue, 0, 1023, 30, 160); 

  Serial.println(potValue); // Envia o valor lido para o monitor serial

  myStepper.setSpeed(motorSpeed); // Define a velocidade do motor em passos por minuto (PPM)

  // LOOP DO BOTÃO

  button.read(); // Atualiza o estado do botão, isto é, verifica se o botão está sendo pressionado ou não

  // Verifica se o botão foi pressionado
  if (button.pressed()) {
    Serial.println("Botão pressionado!");

    while (digitalRead(buttonPin) == LOW) { //Enquanto o botão estiver sendo pressionado, isto é, o sinal digital estiver como LOW
      Serial.println("counterclockwise"); // Enquanto a condição acima for verdadeira, o motor irá girar no sentido anti-horário 
      myStepper.step(stepsPerRevolution); // Função que permite o giro do motor no sentido anti-horário (basta acrescentar o sinal negativo para inverter o sentido)
   }
  } //Fim do LOOP -- OU SEJA, O BOTÃO FOI LIBERADO

  // Verifica se o botão foi liberado

  //if (button.released()) -- Verifique que esta linha foi comentada por ser desnecessária e está aqui apenas para fins didáticos

    Serial.println("Botão liberado!");
    Serial.println("clockwise - sentido-horário");
    myStepper.step(-stepsPerRevolution); // Função que permite o giro do motor no sentido horário (basta retirar o sinal negativo para inverter o sentido)
  //}
  
}

//OBSERVAÇÃO IMPORTANTE: FOI UTILIZADO NO HARDWARE UM BOTÃO DE FIM DE CURSO, ISTO É, UM BOTÃO QUE PERMITE DUAS CARACTERÍSTICAS:
//                       1) NC - NORMAL CLOSED - NORMAL FECHADO - CIRCUITO NORMALMENTE FECHADO - AO PRESSIONAR O BOTÃO O MOTOR GIRA NO SENTIDO HORÁRIO - ABRE O CIRCUITO
//                       2) NO - NORMAL OPEN - NORMAL ABERTO - CIRCUITO NORMALMENTE ABERTO - AO PRESSIONAR O BOTÃO O MOTOR GIRA NO SENTIDO ANTI-HORÁRIO - FECHA O CIRCUITO
