#include "hitachi_tv.hpp"
#include <map>

using TVButton = HitachiTVButton;


HitachiTV::HitachiTV(byte irPin)
  : _ir({irPin}) 
{}

void HitachiTV::begin() {
  _ir.begin();
}

void HitachiTV::send(TVButton button) {
  const int data = 
    static_cast<int>(button);
  
  _ir.sendRC5(data);
}


TVButton HitachiTV::asButton(const String& raw) {
  const bool isNumber = raw[0] >= '0' && raw[0] <= '9';
  return isNumber
    ? getNumberCode(raw)
    : getButtonCode(raw);
}


TVButton HitachiTV::getButtonCode(const String& button) {
  static std::map<String, TVButton> buttons = {
    { "up", TVButton::UP },
    { "down", TVButton::DOWN },
    { "left", TVButton::LEFT },
    { "right", TVButton::RIGHT },
    { "power", TVButton::POWER },
    { "home", TVButton::HOME },
    { "ok", TVButton::OK },
    { "back", TVButton::BACK },
    { "exit", TVButton::EXIT },
    { "menu", TVButton::MENU },
    { "select_input", TVButton::SELECT_INPUT },
    { "mute", TVButton::MUTE },
    { "volume_up", TVButton::VOLUME_UP },
    { "volume_down", TVButton::VOLUME_DOWN },
    { "next_channel", TVButton::NEXT_CHANNEL },
    { "previous_channel", TVButton::PREVIOUS_CHANNEL },
  };

  const auto result = buttons.find(button);
  return result == buttons.end()
    ? TVButton::NONE
    : result->second;
}

TVButton HitachiTV::getNumberCode(const String& rawNumber) {
  const int number = rawNumber.toInt();
  const int button = (int)TVButton::ZERO + number;

  return button >= 0 && button <= 9
    ? TVButton(button)
    : TVButton::NONE;
}