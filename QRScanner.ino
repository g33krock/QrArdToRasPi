
#include <Wire.h>
#include <string.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 4); // TX, RX

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo counterServo;

int pos = 0;

const int buttonPinOne = 9;
const int buttonPinTwo = 10;
const int buttonPinThree = 11;

int buttonSelected = 0;

int increment = 18;
int hitInt;

int buttonStateOne;
int buttonStateTwo;
int buttonStateThree;

String inputString;
String inputArray[9];

String hitString;

void setup()
{
  counterServo.attach(12);
  counterServo.write(pos);
  pinMode(buttonPinOne, INPUT);
  pinMode(buttonPinTwo, INPUT);
  pinMode(buttonPinThree, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.print("Arduino Barcode scanner");
  delay(1000);
  display.clearDisplay();
}

void loop()
{
  buttonStateOne = digitalRead(buttonPinOne);
  buttonStateTwo = digitalRead(buttonPinTwo);
  buttonStateThree = digitalRead(buttonPinThree);

  if (buttonStateOne == HIGH) {
    // turn LED on:
    buttonSelected = 1;
  }
  if (buttonStateTwo == HIGH) {
    // turn LED on:
    buttonSelected = 2;
  }
  if (buttonStateThree == HIGH) {
    // turn LED on:
    buttonSelected = 3;
  }


  if (mySerial.available())
  {
    display.setCursor(0, 0);
    //Serial.println("[");

    while (mySerial.available())
    {
      char input = mySerial.read();
      Serial.print(input);

      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print(input);
      display.display();
      delay(5);
    }
    String input = String(input);
    String inputString = input;
    inputString.trim();
    int index = 0;
    char *inputArray[10];
    inputArray[index] = strtok(inputString.c_str(), ",");
    while (inputArray[index] != NULL) {
      index++;
      inputArray[index] = strtok(NULL, ",");
      display.print(String(inputArray[index]));
    }
  }
  hitString = inputArray[4];
  //hitInt = int(hitString);
//  if (pos >= 180) {
//    pos = 0;
//  } else {
//    int newPos = (hitInt * increment) + pos;
//    pos = newPos;
//  }
//  counterServo.write(pos);
//  Serial.println("," + String(buttonSelected));
//  //Serial.println("]");
//  display.print("," + String(buttonSelected) + hitString);
//  display.display();
//  display.clearDisplay();
}
//}
