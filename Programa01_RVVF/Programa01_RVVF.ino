
/*
 * Ruiz Villalba Valentina Fabienne
 * Prueba programa 01 con puente H
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

// PWM propiedades
int pwmFreq = 8000; //Periodo de 8ms
int pwmChannel = 0;   
int pwmRes = 8; //Resolución de 8 bits (2^8 = 254)

//Variables de velocidad y dirección
    int vel = 255;  // Con un ciclo de trabajo  del 100%
    int dir= 0;
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
  
    ledcSetup(pwmChannel,pwmFreq,pwmRes);

    //Mandar señal PWM al pin enable del puente h
    ledcAttachPin(enable1Pin,pwmChannel);

    //Velocidad del motor
    ledcWrite(pwmChannel,vel);
}


void loop() {
  adelante();
  delay(1000);
  detener();
  delay(500);
  atras();
  delay(1000);
  detener();
}


/*
 * Gira en sentido horario
 *  Dir = 0 y 1
 */
 
void adelante(){
  Serial.println("Adelante");
  digitalWrite(motor1Pin1,dir);
   dir = 1;
  digitalWrite(motor1Pin2,dir);
}

/*
 * Gira en sentido antihorario
 *  Dir = 1 y 0
 */

void atras(){
  dir = 1;
  Serial.println("Atrás");
  digitalWrite(motor1Pin1,dir);
  dir = 0;
  digitalWrite(motor1Pin2,dir);
}

void detener(){
  dir = 0;
  Serial.println("Detenido");
  digitalWrite(motor1Pin1,dir);
  digitalWrite(motor1Pin2,dir);
}
