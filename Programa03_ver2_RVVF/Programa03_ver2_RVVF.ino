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
int DIR_A = 27; 
int DIR_B = 26;
int PWM_A= 14;
int PWM_B= 12;

// PWM propiedades
int pwmFreq = 8000; 
int pwmChannel_A = 0;   
int pwmChannel_B = 1;  
int pwmRes = 8; //Resolución de 8 bits

/*
//Variables de velocidad y dirección
    int vel_A = 255;  // Con un ciclo de trabajo  del 100%
    int vel_B = 255;  // Con un ciclo de trabajo  del 100%
    int dir_A= 0;
    int dir_B= 0;*/

// Variable que guardará el 'estado' del los motores.
char estado = 's'; //--> Inicialmente el valor de la variable es el de tenido.

/*
 *------------------------------------ 
 *        Funciones principales
 *------------------------------------
 */


void setup() {
    Serial.begin(115200);
    
    pinMode(PWM_A, OUTPUT);
    pinMode(PWM_B, OUTPUT);
 

    pinMode(DIR_A, OUTPUT);
    pinMode(DIR_B, OUTPUT);

    digitalWrite(PWM_A,HIGH);
    digitalWrite(PWM_B,HIGH);

    ledcSetup(pwmChannel_A,pwmFreq,pwmRes);
    ledcSetup(pwmChannel_B,pwmFreq,pwmRes);

   
    ledcAttachPin(DIR_A,pwmChannel_A);
    ledcAttachPin(DIR_B,pwmChannel_B);
}


void loop() {
  estado = Serial.read();
  movimiento(estado);

}


/*
 * Gira en sentido horario
 *  dir_A y dir_B = 0 y 1
 */
 
void adelante(){
  ledcWrite(DIR_A, 127);
  ledcWrite(DIR_B, 225); 
}

/*
 * Gira en sentido antihorario
 *  dir_A y dir_B = 1 y 0
 */

void atras(){
  ledcWrite(DIR_A, 225);
  ledcWrite(DIR_B, 127); 
}


/*
 * Detiene el movimiento
 *  dir_A y dir_B = 0 y 0
 */
 
void detener(){
  ledcWrite(DIR_A, 225);
  ledcWrite(DIR_B, 225);
}


/*
 * Gira a la izquierda
 *  dir_A = 0 y 0
 *  dir_B = 0 y 1 
 */

void izquierda(){
  //¿?
  ledcWrite(DIR_A, 225);
  ledcWrite(DIR_B, 225);
 }

/*
 * Gira a la derecha
 *  dir_A = 0 y 1
 *  dir_B = 0 y 0
 */
void derecha(){
  //¿?
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
