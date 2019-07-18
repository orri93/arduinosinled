/*
  Demo: How to use the simple MAX485-library for the max485 EIA-485 driver IC from Maxim Integrated.
  Copyright 2016 Stefan Thema (swarkn), http://do-it-neat.com <swarkn@do-it-neat.com>
  
  Upload this Sketch on your Arduino/Genuino Uno or Nano to use it  as a EIA-485 receiving slave device.
  This sketch outputs received data to the serial USB-port.
*/

#include <arduinosinled.h>

#define PIN_LED_1 5
#define PIN_LED_2 6

#ifdef PIN_LED_1
fds::SinLed sinled1(PIN_LED_1);
#endif
#ifdef PIN_LED_2
fds::SinLed sinled2(PIN_LED_2);
#endif

void setup() {
#ifdef PIN_LED_1
  sinled1.initialize();
#endif  
#ifdef PIN_LED_2
  sinled2.initialize(6);
  sinled2.setat(PI);
#endif  
} 

void loop() {
#ifdef PIN_LED_1
  sinled1.cycle();
#endif  
#ifdef PIN_LED_2
  sinled2.cycle();
#endif  

}
