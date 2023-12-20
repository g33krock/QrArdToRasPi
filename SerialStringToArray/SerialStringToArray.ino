#include <Wire.h>
#include <string.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define MAX_DATA_POINTS 10
int dataArray[MAX_DATA_POINTS];

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.print("Arduino Barcode scanner");
  delay(1000);
  display.clearDisplay();
}

void loop() {
  if (Serial.available() > 0) { 
    String data = Serial.readStringUntil('\n'); 
    Serial.println(data);
    int dataIndex = 0;
    String currentValue = "";
    for (int i = 0; i < data.length(); i++) {
      if (data[i] != ',') {
        currentValue += data[i]; 
        //        Serial.println(currentValue);
      } else {
        dataArray[dataIndex] = currentValue.toInt(); 
        dataIndex++;
        currentValue = ""; 
        //        Serial.println(currentValue);
      }
    }
    // add the last value to the array
    dataArray[dataIndex] = currentValue.toInt();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    switch (dataArray[0]) {
      case 1:
        display.print("Player: Warrior");
        break;
      case 2:
        display.print("Player: Priest");
        break;
      case 3:
        display.print("Player: Rogue");
        break;
      case 4:
        display.print("Player: Wizard");
        break;
      case 5:
        display.print("Player: Paladin");
        break;
    }
    display.display();
  }
}
