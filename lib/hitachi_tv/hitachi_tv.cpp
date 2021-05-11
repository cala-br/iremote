#include "hitachi_tv.hpp"


HitachiTV::HitachiTV(byte irPin)
  : _ir({irPin}) 
{}

void HitachiTV::begin() {
  _ir.begin();
}

void HitachiTV::send(HitachiTVButton button) {
  const int data = 
    static_cast<int>(button);
  
  _ir.sendRC5(data);
}