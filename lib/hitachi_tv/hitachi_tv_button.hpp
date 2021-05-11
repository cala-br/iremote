#ifndef HITACHI_TV_BUTTON_HPP_
#define HITACHI_TV_BUTTON_HPP_

enum class HitachiTVButton {
  NONE = 0,
  
  ZERO = 0x40,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE = 0x49,

  UP = 0x54,
  DOWN = 0x53,
  LEFT = 0x55,
  RIGHT = 0x56,
  
  POWER = 0x4C,
  HOME = 0x6E,
  OK = 0x75,
  BACK = 0x4A,
  EXIT = 0x65,
  MENU = 0x70,
  SELECT_INPUT = 0x78,
  
  MUTE = 0x4D,
  VOLUME_UP = 0x50,
  VOLUME_DOWN = 0x51,
  NEXT_CHANNEL = 0x60,
  PREVIOUS_CHANNEL = 0x61,
};

#endif // !HITACHI_TV_BUTTON_HPP_