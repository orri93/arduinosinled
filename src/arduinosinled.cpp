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

void SinLed::fullcycle(const unsigned long& delayms, const uint8_t& count, const float& at) {
  if (at >= 0.0F) {
    at_ = at;
  }
  while (at < FDS_LED_SIN_MAXIMUM_AT) {
    outputsin();
    if (delayms > 0) {
      delay(delayms);
    }
    at_ += step_;
  }
  at_ = 0.0;
}

void SinLed::outputsin() {
  analogWrite(pin_, (int)(sin(at_) * 127.5 + 127.5));
}

}


