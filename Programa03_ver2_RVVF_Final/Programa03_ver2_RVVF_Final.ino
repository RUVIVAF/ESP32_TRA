/*
 * Ruiz Villalba Valentina Fabienne
 * Prueba programa 03 con Cytron MDD10A 
 * --> Tipo de control Locked-Antiphase PWM
 * Octubre 2020
 * ESP32 TRA 
 */


/*
 *--------------------------------------- 
 *          Pines y variables 
 * --------------------------------------
 */
 
//Pines del motor
int DIR_A = 17; //---> Derecho
int DIR_B = 16; //---> Izquierdo


// PWM propiedades
int pwmFreq = 8000; 
int pwmChannel_A = 0;   
int pwmChannel_B = 1;  
int pwmRes = 8; //Resolución de 8 bits


//Variables de velocidad y dirección

/*
 * C.T < 50% --> Giro en sentido horario
 * C.T = 50% --> Detenido
 * C.T > 50% --> Giro en sentido antihorario
 * 
 * Nota: Se recomienda no tomar los valores máximos (0, 255)
 */

    int vel_1 = 190;  
    int vel_2 = 64;  
    int vel_Stop=127;
  
// Variable que guardará el estado del los motores.
char estado = 's'; //--> Inicialmente el valor de la variable es el de tenido.

/*
 *------------------------------------ 
 *        Funciones principales
 *------------------------------------
 */


void setup() {
    Serial.begin(115200);
    
    pinMode(DIR_A, OUTPUT);
    pinMode(DIR_B, OUTPUT);

    ledcAttachPin(DIR_A,pwmChannel_A);
    ledcAttachPin(DIR_B,pwmChannel_B);
    
    ledcSetup(pwmChannel_A,pwmFreq,pwmRes);
    ledcSetup(pwmChannel_B,pwmFreq,pwmRes);
}


void loop() {
  estado = Serial.read();
  movimiento(estado);

}


/*
 *-------------------------------------------
 *        Funciones de movimiento y giro 
 *------------------------------------------
 */


/*
 * Gira en sentido horario
 *  
 */
 
void adelante(){
  ledcWrite(pwmChannel_A, vel_1);
  ledcWrite(pwmChannel_B, vel_2); 
}

/*
 * Gira en sentido antihorario
 *  
 */

void atras(){
  ledcWrite(pwmChannel_A,vel_2);
  ledcWrite(pwmChannel_B,vel_1); 
}


/*
 * Detiene el movimiento
 *  
 */
 
void detener(){
  ledcWrite(pwmChannel_A,vel_Stop);
  ledcWrite(pwmChannel_B,vel_Stop);
}


/*
 * Gira a la izquierda
 *  
 */

void izquierda(){
  
  ledcWrite(pwmChannel_A,vel_1);
  ledcWrite(pwmChannel_B,vel_1);
 }

/*
 * Gira a la derecha
 *  dir_A = 0 y 1
 *  dir_B = 0 y 0
 */
 
void derecha(){
  ledcWrite(pwmChannel_A,vel_2);
  ledcWrite(pwmChannel_B,vel_2);
 }


/*
 * Cambia el moviemiento de los motores
 * _estado --> Indica el estado del motor
 *    Adelante --> w
 *    Derecha --> d
 *    Atrás --> x
 *    Izquierda --> a 
 *    Detenido --> s
 */

void movimiento(char _estado){
  if (_estado == 'w'){
      Serial.println("Moviendo adelante");
      adelante();
    }else if(_estado == 'd'){
     Serial.println("Moviendo a la derecha");
      derecha();
    }else if(_estado == 'x'){
      Serial.println("Moviendo hacia atrás");
      atras();
    }else if(_estado == 'a'){
      Serial.println("Moviendo a la izquierda");
      izquierda();
    }else if(_estado == 's'){
      Serial.println("Movimiento detenido");
      detener();
    }
 }
