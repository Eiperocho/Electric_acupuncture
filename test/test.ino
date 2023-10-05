#include <Arduino.h>
#include <SPI.h>
#include <stdio.h>
#include "LiquidCrystal_I2C.h"
#include "GyverHC595.h"


#define STCP 10 //pinCS 12
#define DS 11 //pinDT 14
#define SHCP 13 //pinCLK 11

#define SHIFTS 1
#define HC595_DELAY 0
#define ONE_SHIFT_DATA 8
#define ALL_DATA (SHIFTS * ONE_SHIFT_DATA)


GyverHC595<SHIFTS, HC_PINS> reg (STCP, DS, SHCP);
LiquidCrystal_I2C lcd (0x27, 16, 2);

uint16_t CURRENT_PIN = 0;
uint32_t TIMER = 0;
uint16_t OLD_PIN = 0;
bool FIRST = true;

void setup (){
	/*Init Serial*/
	Serial.begin (9600);
	while (!Serial);
	Serial.print ("Serial OK");

	/*Init LCD*/
	lcd.init ();
	lcd.backlight ();
	lcd.clear ();
	lcd.setCursor (1, 0);
	lcd.print ("by e64b");
	lcd.setCursor (2, 1);
	lcd.print ("Electric acu");
	delay (1000);
	lcd.clear ();

	/*Init reg*/
	reg.clearAll ();
	}

void loop (){

	/*We turn on the pins in turn in increments of 1 minute*/
	if (millis () - TIMER >= 60000){
		/*If we have reached the limit, we return to the beginning*/
		if (CURRENT_PIN == ALL_DATA){
			CURRENT_PIN = 0;
			}
		TIMER = millis ();
		for (CURRENT_PIN; CURRENT_PIN < ALL_DATA; CURRENT_PIN++){
			OLD_PIN = CURRENT_PIN;
			reg.set (CURRENT_PIN);
			if (CURRENT_PIN > 0){
				reg.clear (CURRENT_PIN - 1);
				}
			reg.update ();
			break;
			}
		}

	/*If the value has changed, we change it on the screen*/
	if ((OLD_PIN != CURRENT_PIN) or (FIRST)){
		FIRST = false;
		lcd.clear ();
		OLD_PIN = CURRENT_PIN;
		lcd.home ();
		lcd.print ("CURRENT PIN");
		lcd.print (' ');
		lcd.print (CURRENT_PIN + 1);
		lcd.setCursor (0, 1);
		lcd.print ("OF");
		lcd.print (' ');
		lcd.print (ALL_DATA + 1);
		}	
	}