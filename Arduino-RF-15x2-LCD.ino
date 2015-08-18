/* Arduino-RF-15x2-LCD 
 *  A simple sketch for my aquarium temperature https://github.com/incmve/Arduino-RF-15x2-LCD
Uses library from https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads or https://github.com/pkourany/LiquidCrystal_V1.2.1 GNU General Public License, version 3 (GPL-3.0) */
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <NewRemoteReceiver.h>
 
LiquidCrystal_I2C  lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // I2c 0x27 or 0x20
//variables
int Temp;


// create characters
 byte termometru[8] = //icon for termometer
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

byte picatura[8] = //icon for water droplet 
{
    B00100,
    B00100,
    B01010,
    B01010,
    B10001,
    B10001,
    B10001,
    B01110,
};

byte barchar[8] = //icon for bar
{
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};

byte smiley[8] = //icon for Smiley
{
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

void setup()
{
  // activate RF receiver
   NewRemoteReceiver::init(0, 2, rfstart);
  // activate LCD module
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.clear(); // clear LCD
//  lcd.setBacklightPin(3,POSITIVE); //TEST
  lcd.setBacklight(HIGH);
 lcd.createChar(1,termometru);
 lcd.createChar(2,picatura);
 lcd.createChar(3,barchar);
 lcd.createChar(4,smiley);
 lcd.setCursor(0, 0);
 lcd.print("Booting..");
 shutdown(16);
 lcd.setBacklight(LOW);
}
 
void loop()
{
}



void rfstart(NewRemoteCode receivedCode) {
 interrupts();

 
  if (receivedCode.address == 22 && receivedCode.unit == 1 && receivedCode.switchType == 2) //Unit 22, ID 2, DIM 0-15
    {
      lcd.clear();
      lcd.setBacklight(HIGH);
      Temp = receivedCode.dimLevel;
    // Disable the receiver
    NewRemoteReceiver::disable();
lcd.setCursor(4, 1);
  lcd.write(1);
  lcd.setCursor(5, 1);
  lcd.print(Temp);
  lcd.setCursor(7, 1);
  lcd.print((char)223); //degree sign
  lcd.print("C");
  NewRemoteReceiver::enable();
}

if (receivedCode.address == 22 && receivedCode.unit == 2 && receivedCode.switchType == 2) //Unit 22, ID 2, DIM 0-15*2
    {
      lcd.clear();
      lcd.setBacklight(HIGH);
      Temp = receivedCode.dimLevel * 2;
    // Disable the receiver
    NewRemoteReceiver::disable();
      lcd.setCursor(2, 0);
      lcd.print("Water temp.");
lcd.setCursor(4, 1);
  lcd.write(1);
  lcd.setCursor(6, 1);
  lcd.print(Temp);
  lcd.setCursor(8, 1);
  lcd.print((char)223); //degree sign
  lcd.print("C");
  NewRemoteReceiver::enable();
}

if (receivedCode.address == 22 && receivedCode.unit == 3 && receivedCode.switchType == 1) //Unit 22, ID 2, OFF
 {
   lcd.clear();
  lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Night mode");
  shutdown(16);
  lcd.clear();
  lcd.setCursor(0, 0);
      lcd.print("Switching on air");
  lcd.setCursor(0, 1); 
  air(16);
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("BYE");
      lcd.setCursor(7, 1);
      lcd.write(4);
      delay (10000);
      lcd.setBacklight(LOW);
  }
    
  
}
void shutdown(int times) //loading bar
{
  lcd.setCursor(0, 1);
 for (int i=0; i< times; i++)
 {
  lcd.write(3);
  delay (1000);
 }
}
void air(int times) //Loading bar
{
  lcd.setCursor(0, 1);
 for (int i=0; i< times; i++)
 {
  lcd.write(3);
  delay (2750);
 }
}

