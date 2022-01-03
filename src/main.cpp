#include "Arduino.h"
#include "SPI.h"
#include "max6675.h"
#include "LiquidCrystal_I2C.h"
#include "Wire.h"
#include "SoftWire.h"




// Default connection is using software SPI, but comment and uncomment one of
// the two examples below to switch between software SPI and hardware SPI:

// Example creating a thermocouple instance with software SPI on any three
// digital IO pins.
#define DO   18
#define CS   19
#define CLK  20
MAX6675 thermocouple(CLK, CS, DO);

// SoftWire softwire(PB7,PB6);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);  // set the LCD address to 0x38, 0x27, or 0x3F
// 0x27 was working addrss with the other module. 
// LiquidCrystal_I2C lcd(0x38, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);



void setup() {
  Serial.begin(9600);

  Wire.setSCL(PB6);
  Wire.setSDA(PB7);

  Wire.begin();
  // Wire.beginTransmission(0x27);

  // wait for MAX chip to stabilize
  delay(500);

  lcd.begin(16, 2);

  lcd.home();
  lcd.print("Let's check");
  lcd.setCursor(0, 1);
  lcd.print("the temperature");
  delay(1000);
}

void loop() {

  lcd.clear();
  lcd.home();
  // basic readout test, just print the current temp
   int incoming = 0;
   double temp = thermocouple.readFahrenheit();
   if (isnan(temp)) {
     lcd.print("bad reading!");
    //  Serial.println("Something wrong with thermocouple!");
   } else {
     lcd.printf("%3.2f degrees F", temp);
    //  incoming = Serial.read();
    //  Serial.println(temp);
   }

   delay(250);
}
