// 2 x 3 macro keyboard converted from CMStorm Switch tester.

#include "Keyboard.h"

uint8_t switch_pin[6] = { 2, 3, 4, 5, 6, 7 }; // arduino pin of switch.
char switch_key[6] = { (char)0xD7, (char) 0xD9, (char) 0xD8, (char) 0xD3, (char) 0xDA, (char)0xD6 }; // keyboard char of switch, map pin index.
uint8_t switch_reading[6]; // reading of 1 is up, reading of 0 is down
bool press_these[6];
bool switch_is_down[6];
uint8_t switch_down_count[6]; // switch continuous down state count.

void setup() {
  
  // Set pin 16 to high for LED.
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
  
  // Set all button pin state.
  for(uint8_t i = 0; i < 6; i++) {
    pinMode(switch_pin[i], INPUT_PULLUP);
  }
  Keyboard.begin();
}

void loop() {

    for(uint8_t i = 0; i < 6; i++) {
      
        // loop every pin current state and save to variable.
        switch_reading[i] = digitalRead(switch_pin[i]);
        press_these[i] = false;
        
        if (switch_reading[i] == 0 && !switch_is_down[i]) { // Button is now pressed down, and it was up before, add to press list.
            switch_is_down[i] = true;
            press_these[i] = true;
        } else if (switch_reading[i] == 1 && switch_is_down[i]) { // Button is now up, and it was down before, reset down and down status count.
            switch_is_down[i] = false;
            switch_down_count[i] = 0;
        } else if (switch_reading[i] == 0 && switch_is_down[i]) { // button is down, and it is holding down since before.
            if (switch_down_count[i] > 20) { // if its been n loop of down state, hold down state and output.
              press_these[i] = true;
            } else { // button hasn't hold long enough to continue register, up continuous state and not output yet.
              switch_down_count[i] += 1;
            }
        }
    }

    // press each key that's in the press_these list.
    for(uint8_t i = 0; i < 6; i++) {
        if (press_these[i]) {
            Keyboard.press(switch_key[i]);         
        }
    }
    delay(30);
    
    // release each key in the press_these list.
    for(uint8_t i = 0; i < 6; i++) {
        if (press_these[i]) {
            Keyboard.release(switch_key[i]);           
        }
    }
    delay(10);
}
