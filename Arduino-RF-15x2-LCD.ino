/* Demonstration sketch for PCF8574T I2C LCD Backpack 
Uses library from https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads GNU General Public License, version 3 (GPL-3.0) */
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <NewRemoteReceiver.h>
 
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack

//variables
int Temp;
char bar = 'O';

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

byte smiley[8] = //icon for bar
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
  lcd.clear();
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
 lcd.createChar(1,termometru);
 lcd.createChar(2,picatura);
 lcd.createChar(3,barchar);
 lcd.createChar(4,smiley);
 lcd.setCursor(0, 0);
 lcd.print("Booting..");
 shutdown(bar,16);
 lcd.setBacklight(LOW);
}
 
void loop()
{
}



void rfstart(NewRemoteCode receivedCode) {

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
lcd.setCursor(4, 1);
  lcd.write(1);
  lcd.setCursor(5, 1);
  lcd.print(Temp);
  lcd.setCursor(7, 1);
  lcd.print((char)223); //degree sign
  lcd.print("C");
  NewRemoteReceiver::enable();
}
if (receivedCode.address == 22 && receivedCode.unit == 2 && receivedCode.switchType == 0) //Unit 22, ID 2, OFF
    {
      NewRemoteReceiver::disable();
lcd.clear();
  lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("Night mode");
  shutdown(bar,16);
  lcd.clear();
  lcd.setCursor(0, 0);
      lcd.print("Switching on air");
  lcd.setCursor(0, 1); 
  air(bar,16);
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("BYE");
      lcd.setCursor(7, 1);
      lcd.write(4);
      delay (10000);
      lcd.setBacklight(LOW);
      NewRemoteReceiver::enable();
    }
}
void shutdown(int led, int times) //Unit 66 ID 7 Off Blink
{
  lcd.setCursor(0, 1);
 for (int i=0; i< times; i++)
 {
  lcd.write(3);
  delay (1000);
 }
}
void air(int led, int times) //Unit 66 ID 7 Off Blink
{
  lcd.setCursor(0, 1);
 for (int i=0; i< times; i++)
 {
  lcd.write(3);
  delay (2750);
 }
}

