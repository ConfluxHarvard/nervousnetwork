// CONFIG
// strip50: pin8, pin9
// strip100: pin10, pin11, pin12
// ring: pin6

#include <Adafruit_NeoPixel.h>
#define STRIPPIN100_3 12 // input pin Neopixel strip is attached to
#define STRIPPIN100_2 11
#define STRIPPIN100_1 10
#define STRIPPIN50_2 9
#define STRIPPIN50_1 8

#define RINGPIN 6 // input pin Neopixel ring is attached to
#define STRIP50_NUMPIXELS 50 // number of neopixels in strip50
#define STRIP100_NUMPIXELS 100 // number of neopixels in strip100
#define RINGNUMPIXELS 12 // number of neopixels in ring

// NEOPIXEL SETUP
Adafruit_NeoPixel pixelStrip50_1 = Adafruit_NeoPixel(STRIP50_NUMPIXELS, STRIPPIN50_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelStrip50_2 = Adafruit_NeoPixel(STRIP50_NUMPIXELS, STRIPPIN50_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelStrip100_1 = Adafruit_NeoPixel(STRIP100_NUMPIXELS, STRIPPIN100_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelStrip100_2 = Adafruit_NeoPixel(STRIP100_NUMPIXELS, STRIPPIN100_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelStrip100_3 = Adafruit_NeoPixel(STRIP100_NUMPIXELS, STRIPPIN100_3, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel pixelStrip50_16 = Adafruit_NeoPixel(STRIP100_NUMPIXELS, STRIPPIN6, NEO_GRB + NEO_KHZ800);


Adafruit_NeoPixel pixelRing = Adafruit_NeoPixel(RINGNUMPIXELS, RINGPIN, NEO_GRB + NEO_KHZ800);
int delayval = 20; // timing delay in milliseconds
int baseRedColor = 20;
int baseGreenColor = 0;
int baseBlueColor = 30;
float redColor;
float blueColor;
float greenColor;
int offColor = 0;
bool beat = false;
float heartrate_avg = 0;
float heartrates[10];
int index = 0;

// PULSE SETUP
int const PULSE_SENSOR_PIN = 0;
int Signal;                // Store incoming ADC data. Value can range from 0-1024
int Threshold = 550;       // Determine which Signal to "count as a beat" and which to ignore.
bool beating = false;

// Storing state
int STRIP50_state[50];
int STRIP100_state[100];

void setup() {
  // Initialize the NeoPixel library.
  Serial.begin(9600);
  pixelStrip50_1.begin();
  pixelStrip50_2.begin();
  pixelStrip100_1.begin();
  pixelStrip100_2.begin();
  pixelStrip100_3.begin();
  pixelRing.begin();
  for (int i = 0; i < STRIP50_NUMPIXELS; i++) {
  STRIP50_state[i] = 0;
  }
  for (int i = 0; i < STRIP100_NUMPIXELS; i++) {
  STRIP100_state[i] = 0;
  }
  clearColors();
  showPixels();
}

void loop() {
  if (index % 10 == 0) {
    for (int i = 0; i < 10; i++) {
      heartrate_avg = heartrate_avg + heartrates[i];
    }
    heartrate_avg = heartrate_avg / 10;

    if (heartrate_avg > 500) {
    redColor = baseRedColor * (heartrate_avg - 500) / 50;
    blueColor = baseBlueColor * (heartrate_avg - 500) / 50;
    greenColor = baseGreenColor * (heartrate_avg - 500) / 50;
    }
    else {
      redColor = baseRedColor;
      blueColor = baseBlueColor;
      greenColor = baseGreenColor;
    }
    
  } 
  
  Signal = analogRead(PULSE_SENSOR_PIN); // Read the sensor value
  
  heartrates[index % 10] = Signal;
  
  push(STRIP50_state, 0, 50);
  push(STRIP100_state, 0, 100);

  if (beating == true && Signal < Threshold) {
      for (int i=0; i < RINGNUMPIXELS; i++) {
//        Serial.print("");
//        pixelRing.setPixelColor(i, pixelRing.Color(offColor, offColor, offColor));
      }
      beating = false;
  }
  if (Signal > Threshold) {
      if (beating == false) {
        for (int i=0; i < RINGNUMPIXELS; i++) {
          pixelRing.setPixelColor(i, pixelRing.Color(redColor, greenColor, blueColor));
        }
      }

    addPulse();
    beating = true;
  }

  for (int i=0; i < STRIP50_NUMPIXELS; i++) {
    Serial.print(STRIP50_state[i]);
  }
  Serial.println();
  for (int i=0; i < STRIP50_NUMPIXELS; i++) {
        if (STRIP50_state[i] == 1) {
          pixelStrip50_1.setPixelColor(i, pixelStrip50_1.Color(redColor, greenColor, blueColor));
          pixelStrip50_2.setPixelColor(i, pixelStrip50_2.Color(redColor, greenColor, blueColor));
      }
      else {
          pixelStrip50_1.setPixelColor(i, pixelStrip50_1.Color(offColor, offColor, offColor));
          pixelStrip50_2.setPixelColor(i, pixelStrip50_2.Color(offColor, offColor, offColor));
      }
  }
  for (int i=0; i < STRIP100_NUMPIXELS; i++) {
     if (STRIP100_state[i] == 1) {
        pixelStrip100_1.setPixelColor(i, pixelStrip100_1.Color(redColor, greenColor, blueColor));
        pixelStrip100_2.setPixelColor(i, pixelStrip100_2.Color(redColor, greenColor, blueColor));
        pixelStrip100_3.setPixelColor(i, pixelStrip100_3.Color(redColor, greenColor, blueColor));
     }
     else {
        pixelStrip100_1.setPixelColor(i, pixelStrip100_1.Color(offColor, offColor, offColor));
        pixelStrip100_2.setPixelColor(i, pixelStrip100_2.Color(offColor, offColor, offColor));
        pixelStrip100_3.setPixelColor(i, pixelStrip100_3.Color(offColor, offColor, offColor));
     }
    }
    
    showPixels();
  delay(delayval);
  index ++;

}

void addPulse() {

  STRIP50_state[0]=1;
  STRIP100_state[0]=1;

//  if (beatcount == 3) {
//    beating = false;
//  }
}

void push(int arr[], int new_value, int array_length) {
  for (int i = array_length-1; i > -1; i--) {
    if (i == 0) {
      arr[i] = new_value;
    }
    else {
      arr[i] = arr[i - 1];
    }
  }
}

void showPixels() {
    pixelStrip50_1.show();
    pixelStrip50_2.show();
    pixelStrip100_1.show();
    pixelStrip100_2.show();
    pixelStrip100_3.show();
    pixelRing.show();
}

void clearColors() {
    for (int i=0; i < STRIP50_NUMPIXELS; i++) {
      pixelStrip50_1.setPixelColor(i, pixelStrip50_1.Color(offColor, offColor, offColor));
      pixelStrip50_2.setPixelColor(i, pixelStrip50_2.Color(offColor, offColor, offColor));
    }
    for (int i=0; i < STRIP100_NUMPIXELS; i++) {
      pixelStrip100_1.setPixelColor(i, pixelStrip100_1.Color(offColor, offColor, offColor));
      pixelStrip100_2.setPixelColor(i, pixelStrip100_2.Color(offColor, offColor, offColor));
      pixelStrip100_3.setPixelColor(i, pixelStrip100_3.Color(offColor, offColor, offColor));
    }
    for (int i=0; i < RINGNUMPIXELS; i++) {
    pixelRing.setPixelColor(i, pixelRing.Color(offColor, offColor, offColor));
    }
}
