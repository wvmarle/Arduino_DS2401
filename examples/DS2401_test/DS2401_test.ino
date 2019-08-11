/*
 Name:		DS2401_test.ino
 Author:	Wouter van Marle
*/

#include <OneWire.h>
#include "DS2401.h"

const uint8_t ONE_WIRE_PIN = 2;                             // Set this to match the pin your device is connected to.

OneWire oneWire(ONE_WIRE_PIN);

DS2401 ds24(&oneWire);

void setup() {
	Serial.begin(115200);
	Serial.print("Reading DS2401 on pin ");
	Serial.println(ONE_WIRE_PIN);

  uint8_t result = ds24.init();
  if (result == DS2401_SUCCESS) {
		Serial.println(F("DS2401 read successfully."));
		Serial.print(F("Serial number (6 bytes): "));
		uint8_t serialNumber[6];
		ds24.getSerialNumber(serialNumber);
		for (uint8_t i = 0; i < 6; i++) {
		  Serial.print(serialNumber[i], HEX);
		  Serial.print(F(" "));
    }
	}
	else if (result == DS2401_CRC_FAIL) {
	  Serial.println(F("ERROR: data CRC check failed."));
	}
	else if (result == DS2401_NOT_DS2401) {
	  Serial.println(F("ERROR: found device is not a DS2401."));
	}
	else if (result == DS2401_NO_WIRE) {
	  Serial.println(F("ERROR: OneWire interface not working properly."));
	}
}

void loop() {
}
