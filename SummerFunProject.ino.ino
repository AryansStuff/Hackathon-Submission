/*
 This project was made by Aryan Sinha for the Summer Fun Hackathon by Eagle Stem
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// set up a constant for the button
const int switchPin = 6;
const int selectPin = 7;

int currentLine = 1;

const int buzzerPin = 9;

// variable to hold the value of the button
int switchState = 0;
int selectState = 0;
// variable to hold previous value of the button
int prevSwitchState = 0;
int prevSelectState = 0;
// Variable to hold which test the patient would like to take
String test;
//Variable to hold lines
int Lines = 2;
int i = 0;

int hits = 0;

bool inMainMenu = true;

bool inHearTest = false;

//Funcs and stuff
void setup()
{
  // set up the number of columns and rows on the LCD
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  // set up the switch pin as an input
  pinMode(switchPin, INPUT_PULLUP);

  // Print a message to the LCD.
  lcd.print("Tests:");

  delay(1000);
}

void loop()
{
  if(inMainMenu)
  {
     //Button Stuff
    if (currentLine == 1)
    {
      lcd.setCursor(0, 2);
      lcd.print("Ear Test");
    }
    else if (currentLine == 2)
    {
      lcd.setCursor(0, 2);
      lcd.print("Eye Test");
    }
    
    // check the status of the switch
    switchState = digitalRead(switchPin);
  
    // compare the switchState to its previous state
    if (switchState == LOW)
    {
  
      if (currentLine < Lines)
      {
        currentLine += 1;
  
      } 
      else if (currentLine == Lines)
      {
        currentLine -= 1;  
      }
    }
    selectState = digitalRead(selectPin);
    
    if (selectState >= prevSelectState)
    {
      if (selectState == LOW)
       {
         if (currentLine == 2)
         {
            inMainMenu = false;
            inHearTest = true;
         }
       } 
    }
    prevSelectState = selectState;

  }

  else if (inHearTest == true)
  {
    lcd.clear();
    lcd.home();
    lcd.print("Hello! Welcome to the hearing test!");
    lcd.setCursor(0, 2);
    lcd.print("To play just press button 2 each time you hear a sound");
    delay(1000);
    lcd.clear();
    lcd.home();
    lcd.print("Starting now!");

    tone(buzzerPin, 1000);
    delay(100);
    selectState = digitalRead(selectPin);
    if (selectState == LOW)
    {
       hits += 1;
    } 
    delay(750);
    noTone(buzzerPin);
    delay(1250);
    tone(buzzerPin, 500);
    delay(100);
    if (selectState == LOW)
    {
       hits += 1;
    } 
    delay(750);
    noTone(buzzerPin);

    lcd.clear();
    lcd.home();
    if (hits == 2)
    {
      lcd.print("Good Job!");
      delay(1000);
    }
    else if (hits == 1)
    {
      lcd.print("you got"+ String(hits) +"out of 2")  ;
      delay(1000);
    }
    else
    {
      lcd.print("please get an eye checkup");
      delay(1000);
    }
    inHearTest = false;
    inMainMenu = true;
    delay(1000);
  }
  
}
