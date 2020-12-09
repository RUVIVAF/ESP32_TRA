/*
 * Ruiz Villalba Valentina Fabienne
 * Prueba programa 06 con Cytron MDD10A 
 * --> Uso de encoders / Giro y ángulo / lectura haciendo uso de interrupciones
 * --> Tipo de control Locked-Antiphase PWM
 * Noviembre 2020
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

//Pin interrupción --> Señal encoder motor A
int pinIntA = 21;

//Pin interrupción --> Señal encoder motor A2
int pinIntA2 = 3;

//Numero de cuentas de revolución (pulsos del encoder)*(Relación de reducción) 
// Como son dos canales se tomo los pulsos de los dos encoders
int numRev = 4752;

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
  
// Variable que hará el conteo del cambio en los dos canales
int contA = 0;
int contA2 = 0;

//ángulo
float angle = 0;


/*
 *------------------------------------ 
 *        Funciones principales
 *------------------------------------
 */


void setup() {
    Serial.begin(115200);
    
    pinMode(DIR_A, OUTPUT);
    pinMode(DIR_B, OUTPUT);

    ledcAttachPin(DIR_A,pwmChannel_A);  // --> Derecha
    ledcAttachPin(DIR_B,pwmChannel_B);  // --> Izquierda
        
    ledcSetup(pwmChannel_A,pwmFreq,pwmRes);
    ledcSetup(pwmChannel_B,pwmFreq,pwmRes);

    //Se define el pin con interrupción de acuerdo a -->  attachInterrupt(GPIOPin, ISR, Mode) <--
     attachInterrupt(pinIntA, isrA, RISING);
} 

void loop() {
  contRevol();
}


/*
 *---------------------------------------------
 *                  Funciones
 *--------------------------------------------
 */


/*
 * Función de interrupción ISR (Interrupt Service Routine)
 * Si los contadores son distintos significa que el giro es en sentido horario y si
 * contA y contB son iguales indica un giro en sentido antihorario
 */
 
void isrA(){
  if (digitalRead(pinIntA2) == 1){
    angle = (contA*360)/numRev;
    Serial.println("El motor gira en sentido antihorario");
    contaA ++;
  }else if(digitalRead(pinIntA2) == 0){
    contA --;
    angle = (contA*360)/numRev;
  }
    Serial.print("El ángulo es: ");
    Serial.println(angle);
    Serial.println("--------------------------------------------");
 }


/*
 * Giro en sentido antihorario  
 */
 
void mov_CCW(){
  ledcWrite(pwmChannel_A, vel_1);
}

/*
 * Giro en sentido horario
 */
 
void mov_CW(){
  ledcWrite(pwmChannel_A, vel_2);
}

/*
 * Detiene el movimiento
 *  
 */
void detener(){
  ledcWrite(pwmChannel_A,vel_Stop);
}


/*
 * Detiene al motor a una revolución 
 */

 void contRevol(){
    if(angle < 360){
      mov_CCW();
     }else if(angle >= 360){
      detener();
      delay(1000);
      mov_CW();
     }else if(angle <= 0){
      detener();
      contA = 0;
     }
 }


 
