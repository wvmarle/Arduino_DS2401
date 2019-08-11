/*
The MIT License (MIT)

Copyright (c) 2016 Sindre Halbjørhus - sindre@ihemsedal.no

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef _DS2401_h
#define _DS2401_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <OneWire.h>

#define DS2401_READ_ROM_COMMAND   0x33
#define DS2401_FAMILY_CODE        0x01

#define DS2401_SUCCESS            0 
#define DS2401_CRC_FAIL           1
#define DS2401_NOT_DS2401         2
#define DS2401_NO_WIRE            3

class DS2401 {
public:
  DS2401(OneWire* _oneWire);
  uint8_t init();
  void getSerialNumber(uint8_t*);

private:
  OneWire* _wire;
  void GetData();
  void IsCRCValid();
  void DS2401Present();

  uint8_t _data[8];
  uint8_t _readSuccess;
};
#endif
