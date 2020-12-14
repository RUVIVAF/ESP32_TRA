
/*
 * Primer programa programa base para ReMBotcon Cytron MDD10A 
 * --> Control del movimiento de los motores de cada sistema.
 * --> Tipo de control Locked-Antiphase PWM
 * Diciemnbre 2020
 * ESP32 TRA 
 */


/*
 *---------------------------------------------------------------------------------------
 *                                Pines y variables 
 * --------------------------------------------------------------------------------------
 */

/*
 * C.T < 50% --> Giro en sentido horario
 * C.T = 50% --> Detenido
 * C.T > 50% --> Giro en sentido antihorario
 * 
 * Nota: Se recomienda no tomar los valores máximos (0, 255)
 */
//DEFINICION DE VARIABLES DE VELOCIDAD
//CONSIDERANDO CW--->VEL>127
//CONSIDERANDO CCW--->VEL<127

int VEL_CW = 190; //50%
int VEL_CCW = 63; //50%
int VEL_STOP = 127; //SE DETIENE LOS MOTORES

//DEFINICION DE PINES PARA MOTORES

//---------------------------------------LOCOMOCION-------------------------------------
//PIN (PUEDEN CAMBIAR)
int ML_1 = 1;
int ML_2 = 2;
int ML_3 = 3;
int ML_4 = 4;

//CANALES PARA LOCOMOCION (EN PRINCIPIO NO SE MUEVEN)
int CML_1 = 1;
int CML_2 = 2;
int CML_3 = 3;
int CML_4 = 4;

//---------------------------------------YAW-------------------------------------
//PIN (PUEDEN CAMBIAR)
// YAW DELANTERO
int MY_1 = 5;
// YAW TRASERO
int MY_2 = 6;

//CANALES PARA YAW (EN PRINCIPIO NO SE MUEVEN)
//YAW DELANTERO
int CMY_1 = 5;
//YAW TRASERO
int CMY_2 = 6;

//---------------------------------------ROLL-------------------------------------
//PIN (PUEDEN CAMBIAR)
//ROLL DELANTERO
int MRO_1 = 7;
//ROLL TRASERO
int MRO_2 = 8;

//CANALES PARA ROLL (EN PRINCIPIO NO SE MUEVEN)
//ROLL DELANTERO
int CMRO_1 = 7;
//ROLL TRASERO
int CMRO_2 = 8;

//---------------------------------------BALANCEO-------------------------------------
//PIN (PUEDEN CAMBIAR)
//EJE X
int MBX = 9;
//EJE Y
int MBY = 10;

//CANALES PARA BALANCEO (EN PRINCIPIO NO SE MUEVEN)
//ROLL DELANTERO
int CMBX = 9;
//ROLL TRASERO
int CMBY = 10;


/*
 *-----------------------------------------------------------------------------------
 *                           Funciones principales
 *-----------------------------------------------------------------------------------
 */

void setup() {
  //DEFINCION DE CANALES PARA LOS DIFERENTES SISTEMAS
  //---------------------------------------LOCOMOCION-------------------------------------
  ledcAttachPin(ML_1,CML_1);
  ledcAttachPin(ML_2,CML_2);
  ledcAttachPin(ML_3,CML_3);
  ledcAttachPin(ML_4,CML_4);

  //---------------------------------------YAW-------------------------------------
  //YAW DELANTERO
  ledcAttachPin(MY_1,CMY_1);
  //YAW TRASERO
  ledcAttachPin(MY_2,CMY_2);

  //---------------------------------------ROLL-------------------------------------
  //ROLL DELANTERO
  ledcAttachPin(MRO_1,CMRO_1);
  //ROLL TRASERO
  ledcAttachPin(MRO_2,CMRO_2);

  //---------------------------------------BALANCEO-------------------------------------
  //EJE X
  ledcAttachPin(MBX,CMBX);
  //EJE Y
  ledcAttachPin(MBY,CMBY);

 
  //DEFINCION DE PARAMETROS PARA LOS CANALES (MISMOS PARAMETROS PARA TODOS LOS CANALES)
  //---------------------------------------LOCOMOCION-------------------------------------
  ledcSetup(CML_1,8000,8);
  ledcSetup(CML_2,8000,8);
  ledcSetup(CML_3,8000,8);
  ledcSetup(CML_4,8000,8);

  //---------------------------------------YAW-------------------------------------
  //YAW DELANTERO
  ledcSetup(CMY_1,8000,8);
  //YAW TRASERO
  ledcSetup(CMY_2,6000,8);
  
  //---------------------------------------ROLL-------------------------------------
  //ROLL DELANTERO
  ledcSetup(CMRO_1,8000,8);
  //ROLL TRASERO
  ledcSetup(CMRO_2,8000,8);
  //---------------------------------------BALANCEO-------------------------------------
  //EJE X
  ledcSetup(CMBX,8000,8);
  //EJE Y
  ledcSetup(CMBY,8000,8);
  
  //SE INICIA COMUNICACION SERIAL
  Serial.begin(115200);
}

//-------------------------------------------MAIN LOOP-----------------------------------------------
void loop() {
  if (Serial.available())
  {
    char dato = Serial.read();
    //------------------------LOCOMOCION-------------------------------
    if (dato=='Q' || dato=='A' || dato=='Z')
    {
      LOCOMOCION(dato);
    }
    
    //---------------------------YAW-----------------------------------
    if (dato=='W' || dato=='E' || dato=='R' || dato=='S' || dato=='D' || dato=='F')
    {
      YAW(dato);
    }

    //---------------------------ROLL-----------------------------------
    if (dato=='I' || dato=='O' || dato=='P' || dato=='K' || dato=='L' || dato=='Ñ')
    {
      ROLL(dato);
    }

    //---------------------------BALANCEO-----------------------------------
    if (dato=='Y' || dato=='N' || dato=='G' || dato=='J' || dato=='H')
    {
      BALANCEO(dato);
    }
  }

}


/*
 *-------------------------------------------------------------------------------------------
 *                            Funciones de movimiento y giro 
 *-------------------------------------------------------------------------------------------
 */

//------------------------------------------LOCOMOCION---------------------------------------
void LOCOMOCION(char letra)
{
  if (letra=='Q') // 4 LLANTAS HACIA ADELANTE
  {
    ledcWrite(CML_1,VEL_CW);
    ledcWrite(CML_2,VEL_CCW);
    ledcWrite(CML_3,VEL_CW);
    ledcWrite(CML_4,VEL_CCW);
    Serial.println('El Robot se mueve hacia delante');
  }
  if (letra=='A') // 4 LLANTAS SE DETIENEN
  {
    ledcWrite(CML_1,VEL_STOP);
    ledcWrite(CML_2,VEL_STOP);
    ledcWrite(CML_3,VEL_STOP);
    ledcWrite(CML_4,VEL_STOP);
    Serial.println('El Robot se detiene');
  }
  if (letra=='Z') // 4 LLANTAS HACIA ATRAS
  {
    ledcWrite(CML_1,VEL_CCW);
    ledcWrite(CML_2,VEL_CW);
    ledcWrite(CML_3,VEL_CCW);
    ledcWrite(CML_4,VEL_CW);
    Serial.println('El Robot se mueve hacia atras');
  }
}


//------------------------------------------YAW---------------------------------------
void YAW(char letra)
{
//  --------------------------------YAW_DELANTERO---------------------------------------
  if (letra=='W') // YAW DELANTERO GIRA EN SENTIDO ANTIHORARIO
  {
    ledcWrite(CMY_1,VEL_CCW);
    Serial.println('YAW delantero gira en sentido antihorario');
  }
  if (letra=='E') // YAW DELANTERO SE DETIENE
  {
    ledcWrite(CMY_1,VEL_STOP);
    Serial.println('YAW delantero se detiene');
  }
  if (letra=='R') // YAE DELANTERO GIRA EN SENTIDO HORARIO
  {
    ledcWrite(CMY_1,VEL_CW);
    Serial.println('YAW delantero gira en sentido horario');
  }
//  --------------------------------YAW_TRASERO---------------------------------------
  if (letra=='S') // YAW TRASERO GIRA EN SENTIDO ANTIHORARIO
  {
    ledcWrite(CMY_2,VEL_CCW);
    Serial.println('YAW trasero gira en sentido antihorario');
  }
  if (letra=='D') // YAW TRASERO SE DETIENE
  {
    ledcWrite(CMY_2,VEL_STOP);
    Serial.println('YAW trasero se detiene');
  }
  if (letra=='F') // YAW TRASERO GIRA EN SENTIDO HORARIO
  {
    ledcWrite(CMY_2,VEL_CW);
    Serial.println('YAW trasero gira en sentido horario');
  }
}




//------------------------------------------ROLL---------------------------------------
void ROLL(char letra)
{
//  --------------------------------ROLL_DELANTERO---------------------------------------
  if (letra=='I') // ROLL DELANTERO GIRA EN SENTIDO ANTIHORARIO
  {
    ledcWrite(CMRO_1,VEL_CCW);
    Serial.println('ROLL delantero gira en sentido antihorario');
  }
  if (letra=='O') // ROLL DELANTERO SE DETIENE
  {
    ledcWrite(CMRO_1,VEL_STOP);
    Serial.println('ROLL delantero se detiene');
  }
  if (letra=='P') // ROLL DELANTERO GIRA EN SENTIDO HORARIO
  {
    ledcWrite(CMRO_1,VEL_CW);
    Serial.println('ROLL trasero gira en sentido horario');
  }
//  --------------------------------ROLL_TRASERO---------------------------------------
  if (letra=='K') // ROLL TRASERO GIRA EN SENTIDO ANTIHORARIO
  {
    ledcWrite(CMRO_2,VEL_CCW);
    Serial.println('ROLL trasero gira en sentido antihorario');
  }
  if (letra=='L') // ROLL TRASERO SE DETIENE
  {
    ledcWrite(CMRO_2,VEL_STOP);
    Serial.println('ROLL delantero se detiene');
  }
  if (letra=='Ñ') // ROLL TRASERO GIRA EN SENTIDO HORARIO
  {
    ledcWrite(CMRO_2,VEL_CW);
    Serial.println('ROLL trasero gira en sentido horario');
  }
}



//-----------------------------------------BALANCEO---------------------------------------
void BALANCEO(char letra)
{
//  --------------------------------EJE X---------------------------------------
  if (letra=='Y') // MOTOR DE X IMPULSA EL MECANISMO HACIA DELANTE
  {
    ledcWrite(CMBX,VEL_CW);
    Serial.println('Motor de X impulsa hacia delante el mecanismo');
  }
  if (letra=='N') // MOTOR DE X IMPULSA EL MECANISMO HACIA ATRAS
  {
    ledcWrite(CMBX,VEL_CCW);
    Serial.println('Motor de X impulsa hacia atras el mecanismo');
  }
//  --------------------------------EJE Y---------------------------------------
  if (letra=='G') // MOTOR DE Y IMPULSA EL MECANISMO HACIA DELANTE
  {
    ledcWrite(CMBY,VEL_CW);
    Serial.println('Motor de Y impulsa hacia delante el mecanismo');
  }
  if (letra=='J') // MOTOR DE Y IMPULSA EL MECANISMO HACIA ATRAS
  {
    ledcWrite(CMBY,VEL_CCW);
    Serial.println('Motor de Y impulsa hacia atras el mecanismo');
  }
//----------------------------MOTORES_SE_DETIENEN-------------------------------
  if (letra=='H') // MOTORES DE BALANCEO SE DETIENEN
  {
    ledcWrite(CMBX,VEL_STOP);
    ledcWrite(CMBY,VEL_STOP);
    Serial.println('Motores de balanceo se detienen');
  }
}
