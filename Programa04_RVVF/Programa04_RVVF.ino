/*
 * Ruiz Villalba Valentina Fabienne
 * Prueba programa 04 con Cytron MDD10A 
 * --> Uso de encoders / lectura haciendo uso de interrupciones
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

//Pin interrupción 

int pinInt = 21;

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
  
// Variable que hará el conteo del cambio en los endoders
int cont = 0;

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
     attachInterrupt(pinInt, isr, RISING);
    
}


void loop() {
  Serial.println(cont);
  Serial.println("-----------------------------");
  movDerecha();
}


/*
 *---------------------------------------------
 *                  Funciones
 *--------------------------------------------
 */


/*
 * Giro del motor de la derecha
 *  
 */
 
void movDerecha(){
  ledcWrite(pwmChannel_A, vel_1);
}


/*
 * Función de interrupción ISR (Interrupt Service Routine)
 */

 void isr(){
  cont += 1; 
 }
