#ifndef HITACHI_TV_HPP_
#define HITACHI_TV_HPP_

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "hitachi_tv_button.hpp"

class HitachiTV {
public:
  HitachiTV(byte irPin);

  void begin();
  void send(HitachiTVButton button);
private:
  IRsend _ir;
};

#endif // !HITACHI_TV_HPP_