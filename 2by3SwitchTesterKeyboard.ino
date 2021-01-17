// 2 x 3 macro keyboard converted from CMStorm Switch tester.
#include <EEPROM.h>
#include "Keyboard.h"

/**
 * Pin Key map:
 * 2 - bottom right key  - Right Arrow
 * 3 - bottom center key - Down Arrow
 * 4 - bottom left key   - Left Arrow
 * 5 - top left key      - Page Up
 * 6 - top center key    - Up Arrow
 * 7 - top right key     - Page Down
 * 16 - LED 5v output
 */
uint8_t switch_pin[6] = { 2, 3, 4, 5, 6, 7 }; // arduino pin of switch.
char switch_key[6] = { (char)0xD7, (char) 0xD9, (char) 0xD8, (char) 0xD3, (char) 0xDA, (char)0xD6 }; // keyboard char of switch, map pin index.
uint8_t switch_reading[6]; // reading of 1 is up, reading of 0 is down
bool press_these[6];
bool switch_is_down[6];
uint8_t switch_down_count[6]; // switch continuous down state count.
int led_pin = 16; // LED 5v pin
unsigned long last_input_received = millis(); // last input recieved millsecond.
unsigned long led_time_out_milsec = 600000; // 10 mins then led will turn off automatically
int default_led_status = 1; // default led status (on by default).

void setup() {
  
  pinMode(led_pin, OUTPUT);
  int led_stored_val = EEPROM.read(0); // read EEPROM 0 value. this address is used for LED on off setting.
  if (led_stored_val != 0 && led_stored_val != 1) { // check if EEPROM 0 doesn't have valid value, write default (on).
    EEPROM.write(0,default_led_status);
  } else {
    default_led_status = led_stored_val; // load EEPROM 0 value to default_led_status
  }
  digitalWrite(led_pin, default_led_status);
  for(uint8_t i = 0; i < 6; i++) {  // Set all button pin state.
    pinMode(switch_pin[i], INPUT_PULLUP);
  }
  Keyboard.begin();
}

void loop() {
    for(uint8_t i = 0; i < 6; i++) {
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
    if (press_these[3] && press_these[5]) { // If button on top left and top right are pressed together, then toggle default LED lighting
      default_led_status = default_led_status ? 0 : 1;
      EEPROM.write(0,default_led_status);
    } else { 
      for(uint8_t i = 0; i < 6; i++) { // press each key that's in the press_these list.
          if (press_these[i]) {
              last_input_received = millis(); // update last input received timer.
              Keyboard.press(switch_key[i]);         
          }
      }
      if ((millis() - last_input_received) >= led_time_out_milsec) { // if there hasn't been a key press in led_time_out_milsec.
        digitalWrite(led_pin, LOW);
      } else {
        digitalWrite(led_pin, default_led_status);
      }
      delay(30);
      
      for(uint8_t i = 0; i < 6; i++) { // release each key in the press_these list.
          if (press_these[i]) {
              Keyboard.release(switch_key[i]);           
          }
      }
      delay(10);
    }
}
