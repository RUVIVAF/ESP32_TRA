
/*
 * Ruiz Villalba Valentina Fabienne
 * Prueba motor con processing
 * Octubre 2020
 * ESP32 TRA 
 */


/*
 *--------------------------------------- 
 *          Pines y variables 
 * --------------------------------------
 */


 //Pines del motor
byte driver1 = 27;
byte driver2 = 26;
byte enable = 14;

char letra='a'; //--> Guarda el estado en que girará el motor o si estará prendido o apagado

// PWM propiedades

const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 255;


/*
 *------------------------------------ 
 *        Funciones principales
 *------------------------------------
 */
 
void setup() {
  Serial.begin(115200);
  
  pinMode(driver1,OUTPUT);
  pinMode(driver2,OUTPUT);
  pinMode(enable,OUTPUT);
  digitalWrite(enable,HIGH);

  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable, pwmChannel);
}


void loop() {

 // Recibir información de procesing
 
 if(Serial.available() != 0){
     letra = Serial.read();
  }
  
  turnOnOffMotor(letra);
  cambiaGiro(letra);
}

  
/*
 * Prende o apagaga el motor
 * std --> Indica el estado del motor :
 *      p - Prendido
 *      a - Apagado
 * Cuando se enciende el motor gira en sentido antihorario o a la izquierda
 */
void turnOnOffMotor( char std){
  if(std == 'p'){ //Gira a la izquierda
    ledcWrite(pwmChannel, dutyCycle);
    digitalWrite(driver1,LOW);
    digitalWrite(driver2,HIGH);
  }else if(std == 'a'){ // Motor apagado 
    digitalWrite(driver1,LOW);
    digitalWrite(driver2,LOW);
  }
}


/*
 * Cambia el sentido de giro del motor
 * 
 * giro --> Indica el sentido de giro del motor de la siguiente manera:
 *    l - Izquierda de la palabra left en inglés
 *         r - Derecha de la palabra right en inglés
 */
void cambiaGiro(char giro){
  if(giro == 'l'){
     ledcWrite(pwmChannel, dutyCycle);
     digitalWrite(driver1,LOW);
     digitalWrite(driver2,HIGH);
  }else if(giro == 'r'){
    ledcWrite(pwmChannel, dutyCycle);
    digitalWrite(driver1,HIGH);
    digitalWrite(driver2,LOW);
  }
}
