#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <SSD1306Wire.h>
#include <Arduino.h>
#include "Adeept_Ultrasonic_For_ESP32.h"
#include "Adeept_Servo_For_ESP32.h"
#include <VK16K33.h>

#define ADDRESS 0x71
#define LED_COUNT 7
#define LED_PIN   32
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// OLED pin definition.
#define SDA   13
#define SCL   14
SSD1306Wire OLED_display(0x3c, SDA, SCL);

float distance;

VK16K33 matrix = VK16K33();
byte x_array[][8] = {//Put the data into the left LED matrix
  0x00,0x18,0x24,0x00,0x00,0x04,0x03,0x00,
  0x00,0x10,0x28,0x44,0x00,0x00,0x00,0x00,
};

byte y_array[][8] = {//Put the data into the right LED matrix
  0x00,0x18,0x24,0x00,0x00,0x20,0xC0,0x00,
  0x00,0x08,0x14,0x22,0x00,0x00,0x00,0x00,
};

void setup() {
  Serial.begin(115200);//Open the serial port and set the baud rate to 115200
  strip.begin();
  strip.show();
  strip.setBrightness(50);
  OLED_display.init(); // Initialize the OLED.
  OLED_display.flipScreenVertically();  // The screen flips 180° to display.
  Ultrasonic_Setup();  //Ultrasonic module initialization.
  matrix.init(ADDRESS, SDA, SCL);
  matrix.setBrightness(15);


  PCA9685_Setup();       //Initializes the chip that controls the servo
  Servo_1_Angle(90); //Set servo 1 Angle
  Servo_2_Angle(90); //Set servo 2 Angle
  //Servo_0_Angle(90); //Set servo 2 Angle
  delay(1000);


    OLED_display.clear();  // clear screen.
  OLED_display.setFont(ArialMT_Plain_16);  // set font size 10,16,24.
    OLED_display.drawString(26, 10, "DIEGOOZ");
    OLED_display.setFont(ArialMT_Plain_10);
    OLED_display.drawString(30,35,"Test Program");
  OLED_display.setFont(ArialMT_Plain_10);
  OLED_display.drawString(10,50,"YouTube @PixelsSquad");
  OLED_display.display(); // display characters.
    delay(5000);
}


void loop() {

  drawLogo();
  rainbow(10);
  usdistance();
  matrixdisplay();
  moveservos();
}

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
   // delay(wait);
   delay(2);
  }
}

void drawLogo()
{
  OLED_display.clear();  // clear screen.
  OLED_display.setFont(ArialMT_Plain_16);  // set font size 10,16,24.
    OLED_display.drawString(20, 10, "ESP32 Car");
    OLED_display.setFont(ArialMT_Plain_10);
    OLED_display.drawString(10,26,"Diegooz Test Program");
    OLED_display.setFont(ArialMT_Plain_10);
    OLED_display.drawString(20,50,"www.adeept.com");
      distance = Get_Sonar();  // get ultrasonic distance value.
  Serial.print("Distance: " + String(distance) + " cm\n");//Print ultrasonic distance
  OLED_display.setFont(ArialMT_Plain_10);
  OLED_display.drawString(16,37,"Distance: " + String(distance) + " cm\n");
  OLED_display.display(); // display characters.

  /* (x, y, "string"), x, y are the coordinate axes, 
     (30, 30) means that the initial position is 30, 30 from the upper left corner. 
     string: The string that starts to be displayed at the initial position.
    */   
    
} 

void usdistance()
{

  }

void matrixdisplay()
{ 
  int count = sizeof(x_array) / sizeof(x_array[0]);
  for (int i = 0; i < count; i++) {
    matrix.showStaticArray(x_array[i], y_array[i]);
    delay(200);
  }
  }

void moveservos()
{ 

    // Servo 1 
   Servo_Sweep(1, 180, 0);
     delay(1000);
   Servo_Sweep(1, 0, 180);
     delay(1000);
  // Servo 2 
  Servo_Sweep(2, 0, 90);
  Servo_Sweep(2, 90, 180);
  Servo_Sweep(2, 180, 90);
  
  // Servo 3 
  Servo_Sweep(3, 90, 0);
  Servo_Sweep(3, 0, 180);
  Servo_Sweep(3, 180, 90);
  }
  
