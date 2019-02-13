#include <Arduino.h>
#include <Sprites.h>
#include <Print.h>
#include "Font5x7.h"

#define FONT5x7_WIDTH 5
#define FONT5x7_HEIGHT 8


const uint8_t PROGMEM font_images[] = {
5, 8,

0x00, 0x00, 0x00, 0x00, 0x00,	//' '
0x00, 0x74, 0x6d, 0x74, 0x00,	//'!' potions
0x40, 0x40, 0x40, 0x40, 0x40,	//' " ' underscore
0x55, 0x2a, 0x55, 0x2a, 0x55,	//'#' corridor
0x04,0x2E,0x6B,0x3A,0x10,	//'$'
0x7f, 0x43, 0x7f, 0x41, 0x7f,	//'%' stairs
0x6a, 0x57, 0x67, 0x57, 0x6e,	//'&' wall horizontal
0x00, 0x60, 0x60, 0x00, 0x00,	//' ' ' replaces PERIOD (.)
0x70, 0x7a, 0x77, 0x0a, 0x70,	//'(' tombstone
0x08, 0x10, 0x5f, 0x10, 0x08,	//')' weapon
0x22, 0x08, 0x5d, 0x08, 0x22,	//'*' gold coin
0x7e, 0x41, 0x41, 0x41, 0x7e,	//'+' door
0x06, 0x09, 0x29, 0x52, 0x2c,	//',' amulet of Yendor
0x00, 0x08, 0x08, 0x08, 0x00,	//'-'
0x00, 0x00, 0x00, 0x40, 0x20,	//'.' floor
0x02, 0x00, 0x7d, 0x00, 0x02,	//'/' staff
0x3E,0x7F,0x41,0x7F,0x3E,	//'0'
0x00,0x42,0x7F,0x7F,0x40,	//'1'
0x62,0x71,0x59,0x4F,0x46,	//'2'
0x22,0x41,0x49,0x7F,0x36,	//'3'
0x18,0x14,0x7E,0x7F,0x10,	//'4'
0x2F,0x4F,0x49,0x79,0x31,	//'5'
0x3E,0x7F,0x49,0x79,0x30,	//'6'
0x01,0x61,0x79,0x1F,0x07,	//'7'
0x36,0x7F,0x49,0x7F,0x36,	//'8'
0x06,0x4F,0x49,0x7F,0x3E,	//'9'
0x18, 0x35, 0x3e, 0x3d, 0x18,	//':' food
0x00, 0x36, 0x36, 0x00, 0x00,	//';' replaces ' : '
0x00, 0x40, 0x38, 0x18, 0x00,	//'<' virgule
0x10, 0x2a, 0x45, 0x2a, 0x10,	//'=' ring
0x1c, 0x7f, 0x3e, 0x1c, 0x08,	//'>' pointer
0x08, 0x5c, 0x2e, 0x17, 0x0a,	//'?' scroll
0x01, 0x02, 0x64, 0x1f, 0x76,	//'@' character
0x7E,0x7F,0x09,0x7F,0x7E,	//'A'
0x7F,0x7F,0x49,0x7F,0x36,	//'B'
0x3E,0x7F,0x41,0x41,0x22,	//'C'
0x7F,0x7F,0x41,0x7F,0x3E,	//'D'
0x7F,0x7F,0x49,0x49,0x41,	//'E'
0x7F,0x7F,0x09,0x09,0x01,	//'F'
0x3E,0x7F,0x41,0x79,0x7A,	//'G'
0x7F,0x7F,0x08,0x7F,0x7F,	//'H'
0x00,0x41,0x7F,0x7F,0x41,	//'I'
0x41,0x41,0x7F,0x3F,0x01,	//'J'
0x7F,0x7F,0x1C,0x36,0x63,	//'K'
0x7F,0x7F,0x40,0x40,0x40,	//'L'
0x7F,0x7E,0x0C,0x7E,0x7F,	//'M'
0x7F,0x7E,0x1C,0x3F,0x7F,	//'N'
0x3E,0x7F,0x41,0x7F,0x3E,	//'O'
0x7F,0x7F,0x09,0x0F,0x06,	//'P'
0x3E,0x7F,0x61,0x3F,0x5E,	//'Q'
0x7F,0x7F,0x09,0x7F,0x76,	//'R'
0x26,0x4F,0x49,0x79,0x32,	//'S'
0x00,0x01,0x7F,0x7F,0x01,	//'T'
0x3F,0x7F,0x40,0x7F,0x3F,	//'U'
0x1F,0x3F,0x60,0x3F,0x1F,	//'V'
0x7F,0x3F,0x10,0x3F,0x7F,	//'W'
0x77,0x7F,0x08,0x7F,0x77,	//'X'
0x03,0x7F,0x78,0x07,0x03,	//'Y'
0x71,0x79,0x4D,0x47,0x43,	//'Z'
0x1f, 0x3f, 0x7b, 0x3f, 0x1f,	//'[' armour
0x70, 0x7a, 0x77, 0x0a, 0x70,	//'\'tombstone
0x00, 0x41, 0x41, 0x7f, 0x3e,	//']' bracket right
0x3e, 0x7f, 0x41, 0x41, 0x00,	//'^' bracket left
0x4d, 0x3a, 0x16, 0x3a, 0x4d,	//'_' Trap
0x00, 0x6f, 0x6f, 0x00, 0x00,	//'`' exclamation mark
0x20,0x74,0x54,0x7C,0x78,	//'a'
0x7F,0x7F,0x44,0x7C,0x38,	//'b'
0x38,0x7C,0x44,0x44,0x28,	//'c'
0x38,0x7C,0x44,0x7F,0x7F,	//'d'
0x38,0x7C,0x54,0x5C,0x18,	//'e'
0x00,0x04,0x7E,0x7F,0x05,	//'f'
0x18,0xBC,0xA4,0xFC,0x7C,	//'g'
0x7F,0x7F,0x08,0x78,0x70,	//'h'
0x00,0x44,0x7D,0x7D,0x40,	//'i'
0x80,0x80,0xFD,0x7D,0x00,	//'j'
0x7F,0x7F,0x38,0x6C,0x44,	//'k'
0x00,0x41,0x7F,0x7F,0x40,	//'l'
0x7C,0x78,0x10,0x78,0x7C,	//'m'
0x7C,0x7C,0x04,0x7C,0x78,	//'n'
0x38,0x7C,0x44,0x7C,0x38,	//'o'
0xFC,0xFC,0x24,0x3C,0x18,	//'p'
0x18,0x3C,0x24,0xFC,0xFC,	//'q'
0x7C,0x7C,0x08,0x04,0x04,	//'r'
0x08,0x5C,0x54,0x74,0x20,	//'s'
0x00,0x04,0x7E,0x7E,0x04,	//'t'
0x3C,0x7C,0x40,0x7C,0x7C,	//'u'
0x1C,0x3C,0x40,0x3C,0x1C,	//'v'
0x7C,0x3C,0x10,0x3C,0x7C,	//'w'
0x6C,0x7C,0x10,0x7C,0x6C,	//'x'
0x1C,0xBC,0xA0,0xFC,0x7C,	//'y'
0x44,0x64,0x74,0x5C,0x4C,	//'z'
0x1f, 0x3b, 0x71, 0x3b, 0x1f,	//'{' Armour Rustproof
0x00, 0x77, 0x77, 0x77, 0x00,	//'|' wall vertical
0x06, 0x01, 0x59, 0x0f, 0x06,	//'}' question mark
0x20, 0x10, 0x08, 0x04, 0x02,	//'~' slash

};


Font5x7::Font5x7(uint8_t lineSpacing) {

  _lineHeight = lineSpacing;
  _letterSpacing = 1;

  _cursorX = _cursorY = _baseX = 0;
  _textColor = 1;

}

size_t Font5x7::write(uint8_t c) {

  if (c == '\n')      { _cursorX = _baseX; _cursorY += _lineHeight; }
  else {

    printChar(c, _cursorX, _cursorY);
    _cursorX += FONT5x7_WIDTH + _letterSpacing;

  }

  return 1;

}

void Font5x7::printChar(const char c, const int8_t x, int8_t y) {

  int8_t idx = -1;

  ++y;

  switch (c) {
    
    case 32 ... 126:
      idx = c - 32;
      break;
      
//    case 123:
//      idx = 63;
//      break;
      
//    case 124:
//      idx = 64;
//      break;

//    case 125:
//      idx = 65;
//      break;

  }

  if (idx > -1) {
    
    if (_textColor == WHITE) {
      Sprites::drawOverwrite(x, y, font_images, idx);
    }
    else {
      Sprites::drawErase(x, y, font_images, idx);
    }

  }

}

void Font5x7::setCursor(const int8_t x, const int8_t y) {
  _cursorX = _baseX = x;
  _cursorY = y;
}

void Font5x7::setTextColor(const uint8_t color){
  _textColor = color;
}

void Font5x7::setHeight(const uint8_t color){
  _lineHeight = color;
}
