/*
 This project was made by Aryan Sinha for the Summer Fun Hackathon by Eagle Stem
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte c[8] = 
{
  B00000,
  B00000,
  B01111,
  B10000,
  B10000,
  B10000,
  B01111,
  B00000
};
byte h[8] = 
{
  B00000,
  B01000,
  B01000,
  B01110,
  B01010,
  B01010,
  B00000,
  B00000
};
byte e[8] =
{
  B00000,
  B00000,
  B00111,
  B01001,
  B01111,
  B01000,
  B01111,
  B00000
};

byte s[8] = 
{
  B00000,
  B00111,
  B01000,
  B00111,
  B00001,
  B01111,
  B00000,
  B00000
};






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

bool inEyeTest = false;

bool EyeTestIsDone = false;

bool HearTestIsDone = false;

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
  lcd.print("Configuring ...");

  delay(1000);
}

void loop()
{
  if(inMainMenu)
  {
    lcd.clear();
    lcd.home();
    lcd.print("Ear Test (1)");
    lcd.setCursor(0, 2);
    lcd.print("Eye Test (2)");
    delay(1000);
    
    // check the status of the switch
    switchState = digitalRead(switchPin);
  
    // compare the switchState to its previous state
    if (switchState == LOW)
    {
      inMainMenu = false;
      inHearTest = true;
    }
    selectState = digitalRead(selectPin);
    
    if (selectState >= prevSelectState)
    {
      if (selectState == LOW)
       {
        if (!EyeTestIsDone)
        {
          inMainMenu = false;
          inEyeTest = true;
          delay(1000);
        }
        if (EyeTestIsDone)
        {
          inMainMenu = false;
          inHearTest = true;
          delay(1000); 
        }
        if (HearTestIsDone)
        {
          lcd.clear();
          lcd.home();
          lcd.print("No more required tests, you may unplug now.");
        }

       } 
    }



  }

  if (inHearTest == true)
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
      lcd.print("please get a checkup");
      delay(1000);
    }
    inHearTest = false;
    inMainMenu = true;
    delay(1000);
    lcd.clear();
    hits = 0;
    HearTestIsDone = true;
  }
  if (inEyeTest)
  {
    lcd.clear();
    lcd.home();
    lcd.print("Choose the right");
    lcd.setCursor(0, 2);
    lcd.print("Answer Choice");
    delay(100);
    lcd.clear();
    lcd.home();
    lcd.print("Like if I said Peg");
    lcd.setCursor(0, 2);
    lcd.print("pick peg");
    delay(1000);
    lcd.clear();
    lcd.home();
    lcd.print("you ready?");
    delay(1000);
    lcd.clear();
    lcd.home();
    lcd.print("1. I like dogs");
    delay(1000);
    lcd.clear();
    lcd.print("(1) L Ilke Bogs");
    lcd.setCursor(0, 2);
    lcd.print("(2) I Like Dogs");
    delay(1000);
    selectState = digitalRead(selectPin);
    switchState = digitalRead(switchPin);
    if (selectState == LOW)
    {
      lcd.print("Correct! You Passed");
      delay(1000);
      inEyeTest = false;
      inMainMenu = true;
    }
    if (switchState == LOW)
    {
      lcd.print("You Failed");
      delay(1000);
      inEyeTest = false;
      inMainMenu = true;
    }
    else
    {
      lcd.clear();
      lcd.home();
      lcd.print("you chose nothing");
      delay(1000);
      inEyeTest = false;
      inMainMenu = true;
      EyeTestIsDone = true;
    }
  }
  
}
