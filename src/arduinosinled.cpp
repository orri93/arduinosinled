#include "arduinosinled.h"

namespace fds {

SinLed::SinLed(const uint8_t& pin, const float& step) :
  pin_(pin),
  at_(0.0F),
  step_(step) {
}

void SinLed::initialize(const uint8_t& ledstartupcount, const int& delayms) {
  pinMode(pin_, OUTPUT);
  for (uint8_t n = 0; n < ledstartupcount; n++) {
    digitalWrite(pin_, HIGH);
    delay(delayms);
    digitalWrite(pin_, LOW);
    delay(delayms);
  }
}

void SinLed::setat(const float& at) {
  at_ = at;
}

void SinLed::setstep(const float& step) {
  step_ = step;
}

void SinLed::cycle() {
  outputsin();
  at_ = at_ < FDS_LED_SIN_MAXIMUM_AT ? at_ + step_ : 0.0;
}

void SinLed::fullcycle(const uint8_t& count, const unsigned long& delayms, const float& at) {
  if (at >= 0.0F) {
    at_ = at;
  }
  for(uint8_t i = 0; i < count; i++) {
    while (at_ < FDS_LED_SIN_MAXIMUM_AT) {
      outputsin();
      if (delayms > 0) {
        delay(delayms);
      }
      at_ += step_;
    }
    at_ = 0.0;
  }
  analogWrite(pin_, LOW);
}

void SinLed::outputsin() {
  analogWrite(pin_, (int)(sin(at_) * 127.5 + 127.5));
}

}


