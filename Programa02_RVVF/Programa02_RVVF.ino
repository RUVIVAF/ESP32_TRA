
/*
 * Ruiz Villalba Valentina Fabienne
 * Prueba programa 02 con puente H
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

int motor2Pin1 = 25; 
int motor2Pin2 = 33; 
int enable2Pin = 12;


// PWM propiedades
int pwmFreq = 8000; //Periodo de 8ms
int pwmChannel_A = 0;   
int pwmChannel_B = 0;  
int pwmRes = 8; //Resolución de 8 bits (2^8 = 254)

//Variables de velocidad y dirección
    int vel_A = 255;  // Con un ciclo de trabajo  del 100%
    int vel_B = 255;  // Con un ciclo de trabajo  del 100%
    int dir_A= 0;
    int dir_B= 0;
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
    pinMode(enable2Pin,OUTPUT);
  
    ledcSetup(pwmChannel_A,pwmFreq,pwmRes);
    ledcSetup(pwmChannel_B,pwmFreq,pwmRes);

    //Mandar señal PWM al pin enable del puente h
    ledcAttachPin(enable1Pin,pwmChannel_A);
     ledcAttachPin(enable2Pin,pwmChannel_B);

    //Velocidad del motor
    ledcWrite(pwmChannel_A,vel_A);
    ledcWrite(pwmChannel_B,vel_B);
}


void loop() {
  adelante();
  derecha();
  detener();
  atras();
  izquierda();
  detener();
}


/*
 * Gira en sentido horario
 *  dir_A y dir_B = 0 y 1
 */
 
void adelante(){
  Serial.println("Adelante");
  digitalWrite(motor1Pin1,dir_A);
  digitalWrite(motor2Pin1,dir_B);
  dir_A = 1;
  dir_B = dir_A;
  digitalWrite(motor1Pin2,dir_A);
  digitalWrite(motor2Pin2,dir_B);
  delay(1000);
}

/*
 * Gira en sentido antihorario
 *  dir_A y dir_B = 1 y 0
 */

void atras(){
  dir_A = 1;
  dir_B = dir_A;
  Serial.println("Atrás");
  digitalWrite(motor1Pin1,dir_A);
  digitalWrite(motor2Pin1,dir_B);
  dir_A = 0;
  dir_B = dir_A;
  digitalWrite(motor1Pin2,dir_A);
  digitalWrite(motor2Pin2,dir_B);
  delay(1000);
}


/*
 * Detiene el movimiento
 *  dir_A y dir_B = 0 y 0
 */
 
void detener(){
  dir_A = 0;
  dir_B = dir_B;
  Serial.println("Detenido");
  digitalWrite(motor1Pin1,dir_A);
  digitalWrite(motor2Pin1,dir_B);
  delay(500);
}


/*
 * Gira a la izquierda
 *  dir_A = 0 y 0
 *  dir_B = 0 y 1 
 */

void izquierda(){
  dir_A = 0;
  dir_B= dir_A;
  Serial.println("Izquierda");
  digitalWrite(motor1Pin1,dir_A);
  digitalWrite(motor1Pin2,dir_A);
  digitalWrite(motor2Pin1,dir_B);
  
  dir_B = 1;
  digitalWrite(motor2Pin2,dir_B);
  delay(1000);
 }

/*
 * Gira a la derecha
 *  dir_A = 0 y 1
 *  dir_B = 0 y 0
 */
 
void derecha(){
  Serial.println("Derecha");
  dir_A = 0;
  digitalWrite(motor1Pin1,dir_A);
  dir_A = 1;
  digitalWrite(motor1Pin2,dir_A);
  
  dir_B = 0;
  digitalWrite(motor2Pin1,dir_B);
  digitalWrite(motor2Pin2,dir_B);
  delay(1000);
  }
