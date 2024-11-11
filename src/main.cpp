#include <Arduino.h>
#include <LiquidCrystal.h>

#define MINUTE 60000
#define BEEP_TIME 100

int sensorPin = A0;
int sensorValue = 0;
int speakerPin = 6;
int beat = 0;
int pitch = 0;
// initialize the library with the numbers of the interface pins
// modified for Metro Explorers Guide
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void bpm(char str[], int ms);

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.println("");
  // lcd.autoscroll();
  pinMode(speakerPin, OUTPUT);
}

void loop()
{
  char str[5];

  if (beat == 1)
  {
    pitch = 200;
  }
  else
  {
    pitch = 100;
  }

  lcd.setCursor(0, 0);
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0, 1023, 250, 1500);

  bpm(str, sensorValue);
  lcd.print(str);
  lcd.setCursor(0, 1);
  lcd.print("4/4");
  tone(speakerPin, pitch, BEEP_TIME);
  beat = (beat + 1) % 4;
  delay(sensorValue);
  lcd.clear();
}

void bpm(char str[], int ms)
{
  int base = MINUTE / ms;
  int remainder = MINUTE % ms;
  int decimal = (remainder * 10) / ms;
  sprintf(str, "%i.%i", base, remainder);
}
