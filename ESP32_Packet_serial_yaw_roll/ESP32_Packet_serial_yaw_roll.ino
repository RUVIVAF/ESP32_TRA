
/*
 * Uso de tarjeta RoboClaw para motores del mecanismo de Yaw y Roll
 * Enero 2020
 * ESP32 TRA 
 */


/*
 *--------------------------------------- 
 *          Pines y variables 
 * --------------------------------------
 */
 

#include <RoboClaw.h>

RoboClaw roboclaw(&Serial2, 10000);
#define address 0x80


/*
 *------------------------------------ 
 *        Funciones principales
 *------------------------------------
 */


void setup() {

  //Comunicación serie con tarjeta
  roboclaw.begin(38400);

  //Comunicación serie computadora 
  Serial.begin(115200);
  
}



void loop() {
  char dato = Serial.read();
  menu(dato);
}


/*
 *---------------------------------------------
 *                  Funciones
 *--------------------------------------------
 */

void menu(char dato){
  if(Serial.available()){
    if (dato=='I' || dato=='O' || dato=='P' || dato=='K' || dato=='L' || dato=='X')
    {
      ROLL(dato);
    }
  }
 }

void ROLL(char letra)
{
//  --------------------------------ROLL_DELANTERO---------------------------------------
  if (letra=='I') // ROLL DELANTERO GIRA EN SENTIDO ANTIHORARIO
  {
    roboclaw.ForwardM1(address, 32);
    Serial.println("ROLL delantero gira en sentido antihorario");
  }
  if (letra=='O') // ROLL DELANTERO SE DETIENE
  {
    roboclaw.ForwardM1(address, 0);
    Serial.println("ROLL delantero se detiene");
  }
  if (letra=='P') // ROLL DELANTERO GIRA EN SENTIDO HORARIO
  {
    roboclaw.ForwardM1(address, 96);
    Serial.println("ROLL trasero gira en sentido horario");
  }
//  --------------------------------ROLL_TRASERO---------------------------------------
  if (letra=='K') // ROLL TRASERO GIRA EN SENTIDO ANTIHORARIO
  {
    roboclaw.ForwardM2(address, 32);
    Serial.println("ROLL trasero gira en sentido antihorario");
  }
  if (letra=='L') // ROLL TRASERO SE DETIENE
  {
    roboclaw.ForwardM2(address, 0);
    Serial.println("ROLL trasero se detiene");
  }
  if (letra=='X') // ROLL TRASERO GIRA EN SENTIDO HORARIO
  {
    roboclaw.ForwardM2(address, 96);
    Serial.println("ROLL trasero gira en sentido horario");
  }
}





 
