#ifndef _FDS_ARDUINO_LIBRARY_SIN_LED_1_H_
#define _FDS_ARDUINO_LIBRARY_SIN_LED_1_H_


#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#ifndef FDS_LED_SIN_COUNT_IN_STARTUP
#define FDS_LED_SIN_COUNT_IN_STARTUP     3
#endif

#ifndef FDS_LED_SIN_DELAY_IN_STARTUP
#define FDS_LED_SIN_DELAY_IN_STARTUP   500
#endif

#ifndef FDS_LED_SIN_HEARTBEAT_STEPS
#define FDS_LED_SIN_HEARTBEAT_STEPS 0.001F
#endif

#ifndef FDS_LED_SIN_MAXIMUM_AT
#define FDS_LED_SIN_MAXIMUM_AT TWO_PI
#endif


namespace fds {

class SinLed {
public:
  /* pin must be PWM */
  SinLed(const uint8_t& pin, const float& step = FDS_LED_SIN_HEARTBEAT_STEPS);

  void initialize(
    const uint8_t& ledstartupcount = FDS_LED_SIN_COUNT_IN_STARTUP,
    const int& delayms = FDS_LED_SIN_DELAY_IN_STARTUP);

  void setat(const float& at);
  void setstep(const float& step);

  void cycle();
  void fullcycle(const unsigned long& delay = 0, const uint8_t& count = 1, const float& at = -1.0);

private:
  int pin_;
  float at_;
  float step_;

  void outputsin();
};

}

#endif
