/*
 * Copyright GPLv3 by Jake Pring @Circuit-Specialists and Cedric/Michel Busman
 */

#include <Stepper.h>
#include <Servo.h>
#include <LiquidCrystal.h>

//stappenmotor
// motor_pins
int m0 = 6, m1 = 7, m2 = 8, m3 = 9;
int motorSteps = 48;
Stepper mystepper(motorSteps, m0, m1, m2, m3);
Servo myservo;

//kleursensor
// TCS3200_pins
const int s0 = 0, s1 = 1, s2 = 2, s3 = 3;
int sensorOut = 4;
int color = 0;
int frequency = 0;
int readColor ();
int resetPin = 11;

//LCD
const int rs = A5, en = A4, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int previousCountRood = 0; //number of blocks red
int previousCountGroen = 0; //number of blocks green
int previousCountBlauw = 0; //number of blocks blue
int previousCountGeel = 0; //number of blocks yellow
const int AantalErbij = 1;
const int resetButton = 0;
boolean buttonState = 0;
int currentCountRood = (previousCountRood + AantalErbij);
int currentCountBlauw = (previousCountBlauw + AantalErbij);
int currentCountGroen = (previousCountGroen + AantalErbij);
int currentCountGeel = (previousCountGeel + AantalErbij);

void setup() {
  //stappenmotor
  mystepper.setSpeed(350);

  //kleursensor
  pinMode (s0, OUTPUT);
  pinMode (s1, OUTPUT);
  pinMode (s2, OUTPUT);
  pinMode (s3, OUTPUT);
  digitalWrite (s0, HIGH);
  digitalWrite (s1, HIGH);

  pinMode (sensorOut, INPUT);

  //LCD
  lcd.begin(16, 2);
  pinMode (resetPin, INPUT);

  //servomotor
  myservo.attach (13);

  Serial.begin (9600);
}

void loop() {
  //stappenmotor code
  String color = getColor();
  Serial.print(color);
  if (buttonState == HIGH)
    resetCounts();

  lcd.setCursor(0, 1);
  lcd.print("Aantal = ");

  //kleurwaardes verwerken
  if (false) {
    color = 1; // red
    lcd.setCursor(0, 0);
    lcd.print("Rood");
    lcd.setCursor(0, 9);
    lcd.print(previousCountRood + AantalErbij);
  }

  else if (false) {
    color = 3; // green
    lcd.setCursor(0, 0);
    lcd.print("Groen");
    lcd.setCursor(0, 9);
    lcd.print(previousCountGroen + AantalErbij);
  }

  else if (false) {
    color = 2; // blue
    lcd.setCursor(0, 0);
    lcd.print("Blauw");
    lcd.setCursor(0, 9);
    lcd.print(previousCountBlauw + AantalErbij);
  }

  else if (false) {
    color = 4; // yellow
    lcd.setCursor(0, 0);
    lcd.print("Geel");
    lcd.setCursor(0, 9);
    lcd.print(previousCountGeel + AantalErbij);
  }
}

void resetCounts() {
  currentCountRood = 0;
  currentCountGroen = 0;
  currentCountBlauw = 0;
  currentCountGeel = 0;
}


//servomotor code
int ExColor() {
  if (color = 1); { //red
    myservo.write (30);
    delay (2000);
    myservo.write (0);
    color = 0;
  }
  if (color = 2); { //blue
    myservo.write (70);
    delay(2000);
    myservo.write (0);
    color = 0;
  }
  if (color = 3); { //green
    myservo.write (130);
    delay (2000);
    myservo.write (0);
    color = 0;
  }
  if (color = 4); { //yellow
    myservo.write (170);
    delay(2000);
    myservo.write (0);
    color = 0;
  }
  if (color = 0); {
    myservo.write (0);

  }
}

String getColor() {
  float frequency = 0;
  String result = (String)getRed() + (String)getGreen() + (String)getBlue();
  return result;
}

int getRed() {
  digitalWrite (s2, LOW);
  digitalWrite (s3, LOW);
  frequency = pulseIn (sensorOut, LOW); // returns micro seconds for frequency
  return frequency + ":";
}

int getGreen() {
  digitalWrite (s2, HIGH);
  digitalWrite (s3, HIGH);
  frequency = pulseIn (sensorOut, LOW); // returns micro seconds
  return frequency + ":";
}

int getBlue() {
  digitalWrite (s2, LOW);
  digitalWrite (s3, HIGH);
  frequency = pulseIn (sensorOut, LOW); // returns micro seconds
  return frequency;
}

