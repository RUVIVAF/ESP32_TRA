const uint8_t button = 14;
int numberKeyPresses = 0;
bool pressed = false;

const uint8_t led_stop = 2;

//--------------------------------------------

void isr() {
  numberKeyPresses += 1;
  pressed = true;
}

//---------------------------------------

void setup() {
  Serial.begin(115200);
  
  pinMode(button, INPUT_PULLUP);
  pinMode(led_stop, OUTPUT);
  
  attachInterrupt(button, isr, FALLING);
}

//-----------------------------------------

void loop() {
  if (pressed) {
      Serial.printf("Button has been pressed %u times\n", numberKeyPresses);
      pressed = false;
  }
  
  if (numberKeyPresses>10){
    detachInterrupt(button);
    Serial.println("Interrupt Detached!");  
    digitalWrite(led_stop, HIGH);
  }
  
}
