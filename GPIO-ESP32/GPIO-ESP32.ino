#include "BlinkTimes.h"

// define pins for LED and push buttons
const int LED_PIN_2 = 3;  //connect motor to pin 3 
const int BUTTON_PIN_21 = 2;  //connect start push button to pin 2.
const int BUTTON_PIN_22 = 9;  //connect stop push button to pin 9.
const int BUTTON_PIN_23 = 4;  //connect pause/resume push button to pin 4.

const int LED_PIN_15 = 5;  //connect start led button to pin 5.
const int LED_PIN_4 = 6;  //connect stop led button to pin 6.
const int LED_PIN_5 = 8;   //connect pause/resume led button to pin 8.
const int LED_PIN_19 = 7;  //connect status led button to pin 7.


// define variables for LED state and blink interval
bool ledOn = false;
bool paused = false;
int lastButton = 0;



unsigned long lastBlinkTime = 0;
int blinkIndex = 0; // index to keep track of which blink time to use


void setup() {
  // initialize LED pin as output
  pinMode(LED_PIN_2, OUTPUT);

  // initialize button pins as inputs with pull-up resistors
  pinMode(BUTTON_PIN_21, INPUT_PULLUP);
  pinMode(BUTTON_PIN_22, INPUT_PULLUP);
  pinMode(BUTTON_PIN_23, INPUT_PULLUP);

  pinMode(LED_PIN_15, OUTPUT);
  pinMode(LED_PIN_4, OUTPUT);
  pinMode(LED_PIN_5, OUTPUT);
  pinMode(LED_PIN_19, OUTPUT);



  // start serial communication
  Serial.begin(9600);
}

void loop() {
          lastBlinkTime = millis(); // initialize last blink time to current time

  static unsigned long elapsedTime = 0;

  while (true) {
   
    // check if button 21 is pressed
    if (digitalRead(BUTTON_PIN_21) == LOW) {
        lastButton = 21;
        ledOn = true;
        paused = false; // resume blinking if previously paused
        blinkIndex = 0; // reset blink index to start from beginning of array
        digitalWrite(LED_PIN_2, HIGH); // turn on LED
        digitalWrite(LED_PIN_19, HIGH); // turn on LED19
        Serial.println("Button 21 pressed"); // output message to serial monitor
        delay(1000); // debounce delay
        elapsedTime = 0; // reset elapsed time
        lastBlinkTime = millis(); // initialize last blink time to current time
    }

    // check if button 22 is pressed
    if (digitalRead(BUTTON_PIN_22) == LOW) {
        lastButton = 22;
        ledOn = false; // turn off LED
        paused = true; // pause blinking
        digitalWrite(LED_PIN_2, LOW); // turn off LED
        digitalWrite(LED_PIN_19, LOW); // turn off LED19
        Serial.println("Button 22 pressed"); // output message to serial monitor
        Serial.println("LED Stopped"); // output message to serial monitor
        delay(1000); // debounce delay
        elapsedTime = 0; // reset elapsed time
    }

    // check if button 23 is pressed
    if (digitalRead(BUTTON_PIN_23) == LOW) {
      lastButton = 23;
      digitalWrite(LED_PIN_19, HIGH); // turn on LED19
      paused = !paused; // toggle pause state
      if (paused) {
        Serial.println("LED paused"); // output message to serial monitor
        elapsedTime = (millis() - lastBlinkTime) / 1000; // calculate elapsed time
      } else {
                lastButton = 233;

        Serial.println("LED resumed"); // output message to serial monitor
        lastBlinkTime = millis() - (elapsedTime * 1000); // subtract elapsed time from current time
      }
      delay(1000); // debounce delay
    }

    switch (lastButton) {
  case 21:
    digitalWrite(LED_PIN_15, ledOn);
    digitalWrite(LED_PIN_4, LOW);
    digitalWrite(LED_PIN_5, LOW);
    break;
  case 22:
    digitalWrite(LED_PIN_15, LOW);
    digitalWrite(LED_PIN_4, HIGH); // turn on LED_PIN_4
    digitalWrite(LED_PIN_5, LOW);
    break;
  case 23:
    digitalWrite(LED_PIN_15, LOW);
    digitalWrite(LED_PIN_4, LOW);
    digitalWrite(LED_PIN_5, HIGH);
    break;
  case 233:
    digitalWrite(LED_PIN_15, ledOn);
    digitalWrite(LED_PIN_4, LOW); // turn on LED_PIN_4
    digitalWrite(LED_PIN_5, LOW);
    break;
  default:
    digitalWrite(LED_PIN_15, ledOn);
    digitalWrite(LED_PIN_4, LOW);
    digitalWrite(LED_PIN_5, LOW);
    break;
}


    // blink LED according to on/off times if not paused
    if (!paused && (millis() - lastBlinkTime) >= (blinkTimes[blinkIndex] * 1000)) {
      lastBlinkTime = millis();
      if (ledOn) {
        digitalWrite(LED_PIN_2, !digitalRead(LED_PIN_2)); // toggle LED
        Serial.println(digitalRead(LED_PIN_2) ? "LED off" : "LED on"); // output LED state to serial monitor
        
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
