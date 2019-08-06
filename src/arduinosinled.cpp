#include "arduinosinled.h"

namespace fds {

SinLed::SinLed(const uint8_t& pin, const float& step) :
  pin_(pin),
  at_(0.0F),
  step_(step) {
}

void SinLed::initialize(const uint8_t& ledstartupcount, const int& delayms) {
  pinMode(pin_, OUTPUT);
  uint16_t step = 0xff / ledstartupcount;
  uint8_t led = step;
  for (uint8_t n = 0; n < ledstartupcount; n++) {
    analogWrite(pin_, led);
    delay(delayms);
    digitalWrite(pin_, LOW);
    delay(delayms);
    led = min(led + step, 0x00ff);
  }
}

void SinLed::setat(const float& at) {
  at_ = at;
}

void SinLed::setstep(const float& step) {
  step_ = step;
}

uint8_t SinLed::cycle(const uint8_t& max) {
  uint8_t value = outputsin(max);
  at_ = at_ < FDS_LED_SIN_MAXIMUM_AT ? at_ + step_ : 0.0;
  return value;
}

void SinLed::fullcycle(const uint8_t& count, const unsigned long& delayms, const float& at, const uint8_t& max) {
  if (at >= 0.0F) {
    at_ = at;
  }
  for(uint8_t i = 0; i < count; i++) {
    while (at_ < FDS_LED_SIN_MAXIMUM_AT) {
      outputsin(max);
      if (delayms > 0) {
        delay(delayms);
      }
      at_ += step_;
    }
    at_ = 0.0;
  }
  analogWrite(pin_, LOW);
}

uint8_t SinLed::outputsin(const uint8_t& max) {
  float half = static_cast<double>(max) / 2.0;
  uint8_t value = static_cast<uint8_t>(sin(at_) * half + half);
  analogWrite(pin_, value);
  return value;
}

}


