# CMStormSwitchTesterMacroKeyboard

Convert a CMStorm (CoolerMaster) Key Switch Tester into a macro keyboard using an Arduino Pro Micro.

![image](https://github.com/MingyaoLiu/CMStormSwitchTesterMacroKeyboard/blob/main/image.png)

## Hardware

My GMMK has a very awkward arrow key set up, and there is no way to change FN key map for me to use the bottom right 4 key for arrow key.

I was thinking how I could get arrow key, then I remembered I had a CMStorm key switch tester from massdrop, and why not just build a keyboard from it?

I looked up what I would need, for a control board my mind went to arduino from the start, turns out sparkfun made a tiny micro usb version of Leonardo with ATmega32u4 called sparkfun pro micro, with USB keyboard HID native support. What a god sent.

Size wise it is basically perfect. The CMStorm key switch tester has 4 plastic pillar inside for support, but they must have last minute changed the switch mount plate to steel, so the 4 support is absolutely useless (not a mechanical engineer, don't quote me on this).

Cut them off with a plier, drill hole on the center back of the inner case, slightly cut off part of the outter case, micro usb port fit right in.

I decided to have the pro micro face down in the case, to lower the micro usb port, and better prevent shorting. Use hot glue to secure the pro micro inside the case after you done all the wire run.

For the switches I bent the copper feet just a little bit, because the copper feet is actually taller than the plastic shell. And for each switch, 1 of the feet is always softer than the other, I used the softer feet for ground, and harder feet for data pin (again not an electrical engineer, someone correct me).

I coated all naked wire and solder joint with nail polisher twice after i finished soldering, special thank to Rosy for the nail polisher. I dried it making sure the switches are facing upwards, so no nail polish could drip inside the switch while drying.

LED hot glued to be more secure, but the inside is quite tight with all the wires jamming together, so no chance of moving at all. Be careful with hot glue might stick out and cause clearance issue inside the case. (mostly between the led and the pro micro)

Be careful the switch is not pushed with too much force inside, it could pop out. the clearance is quite good just be aware because once you closed the case, it's hard to open again.


## Software

I took some inspiration from a template someone shared on the internet. However the template doesn't have many of the feature I wanted, for example holding a right arrow key should be able to make it travel continuously, and led control is not there.

My code support:
1. Assign key to each button
2. Long press will register key press continuously after a second or so
3. Press top left and top right key together will toggle LED
4. LED time out after 10 mins
5. LED on/off default status is saved to EEPROM

Arduino file contains detailed commenting, please read before use.

LED timer unsigned long may overflow after you left it on for 100 days or so, but in theory the overflow will not cause any issue and it will be reseted to 0 after overflow.

## Schema

Schema draw on fritzing, button is the switch.

![schema](https://github.com/MingyaoLiu/CMStormSwitchTesterMacroKeyboard/blob/main/Untitled%20Sketch_bb.png)

![schema2](https://github.com/MingyaoLiu/CMStormSwitchTesterMacroKeyboard/blob/main/Untitled%20Sketch_schem.png)

## BOM

Arduino Pro Micro -------------- $7 CAD

Key Switch x6 ------------------ $6 CAD

Key cap x6 ------------------ $6 CAD

CMStorm Switch Tester ---------- $20 CAD (comes with switch and translucent cap)

Total -------------------------- $27 CAD + ($12 CAD - cap&switch)

## After thought

This is one successful project. What I would improve next time:
1. Better soldering. Wasn't so mindful when doing it, i was on call with my mom and getting criticized for holding my soldering iron like chopstick every 30 seconds. End up burnt a hole in my mousepad too.
2. Run WS2812B led strip inside the case instead of led bulb. led bulb is too big, and individual address will require 6 more wire which is just clutter hell inside the case. In comparison, WS2812B can be individually addressed and only need 3 wires and a resistor. Based on my measurement, the 60 LED/m WS2812B strip should have the led exactly match the position of the switch, making it a no brainer. I don't have any 5V strip on hand that's why I couldn't do it. I have ordered some 5v 5M 5050SMD WS2812B 300LED strip for my next project. 30 bucks for 5m.
3. better wiring. I would get maget wires, they are thin, easy to burn off part of the shell, and non conductive. But i didn't have any, I'm ordering some NOW.
4. USB-C. I really want USB-C, but couldn't find any cheap board with it. The pro micro I got from amazon are chinese clones of sparkfun, 22 bucks for 3. (again canadian dollar). The sparkfun USB-C version of this is 30 CAD for 1.
5. QMK firmware. There should be something that can be done with QMK.
6. Just buy from aliexpress. new one with the same feature are around 25 CAD.

