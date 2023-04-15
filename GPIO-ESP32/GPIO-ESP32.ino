//#include "BlinkTimes.h"

// define pins for LED and push buttons
const int LED_PIN_2 = 2;
const int BUTTON_PIN_21 = 21;
const int BUTTON_PIN_22 = 22;
const int BUTTON_PIN_23 = 23;


unsigned long blinkTimes[4] = {
  1,   // On Sequence 1 (in second)
  11,   // Off Sequence 2 (in second)
  
  15,  // On Sequence 3 (in second)
  1,  // Off Sequence 4 (in second)
};


// define variables for LED state and blink interval
bool ledOn = false;
bool paused = false;


unsigned long lastBlinkTime = 0;
int blinkIndex = 0; // index to keep track of which blink time to use


void setup() {
  // initialize LED pin as output
  pinMode(LED_PIN_2, OUTPUT);

  // initialize button pins as inputs with pull-up resistors
  pinMode(BUTTON_PIN_21, INPUT_PULLUP);
  pinMode(BUTTON_PIN_22, INPUT_PULLUP);
  pinMode(BUTTON_PIN_23, INPUT_PULLUP);

  // start serial communication
  Serial.begin(9600);
}

void loop() {
  static unsigned long elapsedTime = 0;

  while (true) {
   
    // check if button 21 is pressed
    if (digitalRead(BUTTON_PIN_21) == LOW) {
      ledOn = true; // turn on LED
      paused = false; // resume blinking if previously paused
      blinkIndex = 0; // reset blink index to start from beginning of array
      digitalWrite(LED_PIN_2, HIGH); // turn on LED
      Serial.println("Button 21 pressed"); // output message to serial monitor
      delay(1000); // debounce delay
      elapsedTime = 0; // reset elapsed time
    }

    // check if button 22 is pressed
    if (digitalRead(BUTTON_PIN_22) == LOW) {
      ledOn = false; // turn off LED
      paused = true; // pause blinking
      digitalWrite(LED_PIN_2, LOW); // turn off LED
      Serial.println("Button 22 pressed"); // output message to serial monitor
      Serial.println("LED Stopped"); // output message to serial monitor
      delay(1000); // debounce delay
      elapsedTime = 0; // reset elapsed time
    }

    // check if button 23 is pressed
    if (digitalRead(BUTTON_PIN_23) == LOW) {
      paused = !paused; // toggle pause state
      if (paused) {
        Serial.println("LED paused"); // output message to serial monitor
        elapsedTime = (millis() - lastBlinkTime) / 1000; // calculate elapsed time
      } else {
        Serial.println("LED resumed"); // output message to serial monitor
        lastBlinkTime = millis() - (elapsedTime * 1000); // subtract elapsed time from current time
      }
      delay(1000); // debounce delay
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
      if (blinkIndex >= 4) {
        blinkIndex = 0; // reset blink index to start from beginning of array
      }
    }
  }
}
