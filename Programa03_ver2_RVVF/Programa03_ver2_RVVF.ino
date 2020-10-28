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
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

int motor2Pin1 = 33; 
int motor2Pin2 = 32; 
int enable2Pin = 12;


// PWM propiedades
int pwmFreq = 8000; 
int pwmChannel_A = 0;   
int pwmChannel_B = 0;  
int pwmRes = 8; //Resolución de 8 bits

//Variables de velocidad y dirección
    int vel_A = 255;  // Con un ciclo de trabajo  del 100%
    int vel_B = 255;  // Con un ciclo de trabajo  del 100%
    int dir_A= 0;
    int dir_B= 0;

// Variable que guardará el 'estado' del los motores.
char estado = 's'; //--> Inicialmente el valor de la variable es el de tenido.

/*
 *------------------------------------ 
 *        Funciones principales
 *------------------------------------
 */


void setup() {
    Serial.begin(115200);
    
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin,OUTPUT);

    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enabe2Pin,OUTPUT);
  
    ledcSetup(pwmChannel_A,pwmFreq,pwmRes);
    ledcSetup(pwmChannel_B,pwmFreq,pwmRes);

    //Mandar señal PWM al pin enable del puente h
    ledcAttachPin(enable1Pin,pwmChannel);
     ledcAttachPin(enable2Pin,pwmChannel);

    //Velocidad del motor
    ledcWrite(pwmChanne_A,vel);
    ledcWrite(pwmChannel_B,vel);
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
  dir_A = 0;
  dir_B = dir_A;
  digitalWrite(motor1Pin1,dir_A);
  digitalWrite(motor2Pin1,dir_B);
  dir_A = 1;
  dir_B = dir_A;
  digitalWrite(motor1Pin2,dir_A);
  digitalWrite(motor2Pin2,dir_B);
}

/*
 * Gira en sentido antihorario
 *  dir_A y dir_B = 1 y 0
 */

void atras(){
  dir_A = 1;
  dir_B = dir_A;
  digitalWrite(motor1Pin1,dir_A);
  digitalWrite(motor2Pin1,dir_B);
  dir_A = 0;
  dir_B = dir_A;
  digitalWrite(motor1Pin2,dir_A);
  digitalWrite(motor2Pin2,dir_B);
}


/*
 * Detiene el movimiento
 *  dir_A y dir_B = 0 y 0
 */
 
void detener(){
  dir_A = 0;
  dir_B = dir_B;
  digitalWrite(motor1Pin1,dir_A);
  digitalWrite(motor2Pin1,dir_B);
  digitalWrite(motor1Pin2,dir_A);
  digitalWrite(motor2Pin2,dir_B);
}


/*
 * Gira a la izquierda
 *  dir_A = 0 y 0
 *  dir_B = 0 y 1 
 */

void izquierda(){
  dir_A = 0;
  dir_B= dir_A;
  digitalWrite(motor1Pin1,dir_A);
  digitalWrite(motor1Pin2,dir_A);
  digitalWrite(motor2Pin1,dir_B);
  dir_B = 1;
  digitalWrite(motor2Pin2,dir_B);
 }

/*
 * Gira a la derecha
 *  dir_A = 0 y 1
 *  dir_B = 0 y 0
 */
void derecha(){
  dir_A = 0;
  digitalWrite(motor1Pin1,dir_A);
  dir_A = 1;
  digitalWrite(motor1Pin2,dir_A);
  
  dir_B = 0;
  digitalWrite(motor2Pin1,dir_B);
  digitalWrite(motor2Pin2,dir_B);
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
      detenido();
    }
 }
