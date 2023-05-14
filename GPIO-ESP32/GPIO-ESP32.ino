#include "BlinkTimes.h"

// define pins for LED and push buttons
const int MOTOR = 3;  //connect motor to pin 3 
const int START_BUTTON_PIN_2 = 2;  //connect start push button to pin 2.
const int STOP_BUTTON_PIN_9 = 9;  //connect stop push button to pin 9.
const int P_R_BUTTON_PIN_4 = 4;  //connect pause/resume push button to pin 4.

const int START_LED_PIN_5 = 5;  //connect start led button to pin 5.
const int STOP_LED_PIN_6 = 6;  //connect stop led button to pin 6.
const int P_R_LED_PIN_8 = 8;   //connect pause/resume led button to pin 8.
const int STATUS_LED_PIN_7 = 7;  //connect status led button to pin 7


// define variables for LED state and blink interval
bool ledOn = false;
bool paused = false;
int lastButton = 0;



unsigned long lastBlinkTime = 0;
int blinkIndex = 0; // index to keep track of which blink time to use


void setup() {
  // initialize LED pin as output
  pinMode(MOTOR, OUTPUT);

  // initialize button pins as inputs with pull-up resistors
  pinMode(START_BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(STOP_BUTTON_PIN_9, INPUT_PULLUP);
  pinMode(P_R_BUTTON_PIN_4, INPUT_PULLUP);

  pinMode(START_LED_PIN_5, OUTPUT);
  pinMode(STOP_LED_PIN_6, OUTPUT);
  pinMode(P_R_LED_PIN_8, OUTPUT);
  pinMode(STATUS_LED_PIN_7, OUTPUT);



  // start serial communication
  Serial.begin(9600);
}

void loop() {
          lastBlinkTime = millis(); // initialize last blink time to current time

  static unsigned long elapsedTime = 0;

  while (true) {
   
    // check if button 21 is pressed
    if (digitalRead(START_BUTTON_PIN_2) == LOW) {
        lastButton = 21;
        ledOn = true;
        paused = false; // resume blinking if previously paused
        blinkIndex = 0; // reset blink index to start from beginning of array
        digitalWrite(MOTOR, HIGH); // turn on LED
        digitalWrite(STATUS_LED_PIN_7, HIGH); // turn on LED19
        Serial.println("Button 21 pressed"); // output message to serial monitor
        delay(1000); // debounce delay
        elapsedTime = 0; // reset elapsed time
        lastBlinkTime = millis(); // initialize last blink time to current time
    }

    // check if button 22 is pressed
    if (digitalRead(STOP_BUTTON_PIN_9) == LOW) {
        lastButton = 22;
        ledOn = false; // turn off LED
        paused = true; // pause blinking
        digitalWrite(MOTOR, LOW); // turn off LED
        digitalWrite(STATUS_LED_PIN_7, LOW); // turn off LED19
        Serial.println("Button 22 pressed"); // output message to serial monitor
        Serial.println("MOTOR Stopped"); // output message to serial monitor
        delay(1000); // debounce delay
        elapsedTime = 0; // reset elapsed time
    }

    // check if button 23 is pressed
    if (digitalRead(P_R_BUTTON_PIN_4) == LOW) {
      lastButton = 23;
      digitalWrite(STATUS_LED_PIN_7, HIGH); // turn on LED19
      paused = !paused; // toggle pause state
      if (paused) {
        Serial.println("MOTOR paused"); // output message to serial monitor

         if (digitalRead(MOTOR)== HIGH){
        digitalWrite(MOTOR, LOW);
        }
        
        elapsedTime = (millis() - lastBlinkTime) / 1000; // calculate elapsed time
//        digitalWrite(MOTOR, LOW);
      } else {

        if (digitalRead(MOTOR)== LOW){
        digitalWrite(MOTOR, HIGH);
        }
                lastButton = 233;

        Serial.println("MOTOR resumed"); // output message to serial monitor
        lastBlinkTime = millis() - (elapsedTime * 1000); // subtract elapsed time from current time
//        digitalWrite(MOTOR, HIGH);
      }
      delay(1000); // debounce delay
    }

    switch (lastButton) {
  case 21:
    digitalWrite(START_LED_PIN_5, ledOn);
    digitalWrite(STOP_LED_PIN_6, LOW);
    digitalWrite(P_R_LED_PIN_8, LOW);
    break;
  case 22:
    digitalWrite(START_LED_PIN_5, LOW);
    digitalWrite(STOP_LED_PIN_6, HIGH); // turn on STOP_LED_PIN_6
    digitalWrite(P_R_LED_PIN_8, LOW);
    break;
  case 23:
    digitalWrite(START_LED_PIN_5, LOW);
    digitalWrite(STOP_LED_PIN_6, LOW);
    digitalWrite(P_R_LED_PIN_8, HIGH);
    
    break;
  case 233:
    digitalWrite(START_LED_PIN_5, ledOn);
    digitalWrite(STOP_LED_PIN_6, LOW); // turn on STOP_LED_PIN_6
    digitalWrite(P_R_LED_PIN_8, LOW);
    break;
  default:
    digitalWrite(START_LED_PIN_5, ledOn);
    digitalWrite(STOP_LED_PIN_6, LOW);
    digitalWrite(P_R_LED_PIN_8, LOW);
    break;
}


    // blink LED according to on/off times if not paused
    if (!paused && (millis() - lastBlinkTime) >= (blinkTimes[blinkIndex] * 1000)) {
      lastBlinkTime = millis();
      if (ledOn) {
        digitalWrite(MOTOR, !digitalRead(MOTOR)); // toggle MOTOR
        Serial.println(digitalRead(MOTOR) ? "MOTOR off" : "MOTOR on"); // output LED state to serial monitor
        
      }
      Serial.print("Time (sec): "); // output blink time to serial monitor
      Serial.println(blinkTimes[blinkIndex]);
      elapsedTime = 0; // reset elapsed time
      blinkIndex++; // increment blink index to move to next blink time
      if (blinkIndex >= 24) {
        blinkIndex = 0; // reset blink index to start from beginning of array
      }
    }
  }
}
