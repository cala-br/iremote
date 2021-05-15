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

  static HitachiTVButton asButton(const String& raw);
private:
  IRsend _ir;
  
  static HitachiTVButton getButtonCode(const String& button);
  static HitachiTVButton getNumberCode(const String& rawNumber);
};

#endif // !HITACHI_TV_HPP_