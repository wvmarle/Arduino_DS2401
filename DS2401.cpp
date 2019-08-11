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

#include "DS2401.h"

/*
The DS2401 returns 64 bits (8 bytes) of data:
8 bit family code
48 bit serial number
8 bit CRC
*/

DS2401::DS2401(OneWire* _oneWire) {
  _wire = _oneWire;
  _readSuccess = false;
}

uint8_t DS2401::init() {
  if (_wire->reset()) {
    _wire->write(DS2401_READ_ROM_COMMAND);
    for (uint8_t i = 0; i < 8; i++) {                       // Read 8 bytes of data.
      _data[i] = _wire->read();
    }
    if (_data[0] == DS2401_FAMILY_CODE) {                   // Check the device family code.
      uint8_t crcCalc = _wire->crc8(_data, 7);              // Calculate CRC.
      if (crcCalc == _data[7]) {                            // Check the CRC.
        _readSuccess = DS2401_SUCCESS;                      // All checked out; data read successfully.
      }
      else {
        _readSuccess = DS2401_CRC_FAIL;
      }
    }
    else {
      _readSuccess = DS2401_NOT_DS2401;
    }
  }
  else {
    _readSuccess = DS2401_NO_WIRE;
  }
  return _readSuccess;
}

void DS2401::getSerialNumber(uint8_t *serialNumber) {
  if (_readSuccess == DS2401_SUCCESS) {
    for (uint8_t i = 0; i < 5; i++) {
      serialNumber[i] = _data[i+1];
    }
  }
}
