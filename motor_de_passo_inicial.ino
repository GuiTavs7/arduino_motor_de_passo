// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <Stepper.h>   //biblioteca para controle de motor de passo

// ========================================================================================================
// --- Mapeamento de Hardware ---
#define   in1   8      //entrada 1 do ULN2003
#define   in2   9      //entrada 2 do ULN2003
#define   in3  10      //entrada 3 do ULN2003
#define   in4  11      //entrada 4 do ULN2003

// ========================================================================================================
// --- Constantes Auxiliares ---
const int stepsPerRevolution = 200;  // aqui você altera o número de passos por revolução do motor

// ========================================================================================================
// --- Declaração de Objetos ---
Stepper myStepper(stepsPerRevolution, in1,in3,in2,in4); 


// ========================================================================================================
// --- Configurações Iniciais ---

void setup() 
{
    // use esta função para definir as rotações por minuto (RPM) do motor
  myStepper.setSpeed(160);
  
} //end setup

// ========================================================================================================
// --- Loop Infinito ---

void loop() 
{
  
  //motor girando no sentido horário

  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(1000); //define o tempo de 1 segundo de espera para girar no outro sentido
  
  //motor girando no sentido anti-horário

  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1000); //define o tempo de 1 segundo de espera para girar no outro sentido

} //end loop


 
  













