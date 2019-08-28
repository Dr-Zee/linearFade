#include <Adafruit_NeoPixel.h>
/**
* Define Neopixel strip
*/
//NeoPixel setup
const uint8_t LED = 9;
uint8_t ledState = 0;

#define LED_COUNT 20
#define BRIGHTNESS 50
#define LED_PIN LED
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);


/**
 * ColorFade
 * Takes R, G, B, W, fade duration in seconds, time to hold on color in seconds.
 * colorFade(255, 0, 0, 180, 5, 40);
 */

//volatile ints to store color data between runs. More accurate than getPixelColor.
volatile uint8_t curr_r = 0;
volatile uint8_t curr_g = 0;
volatile uint8_t curr_b = 0;
volatile uint8_t curr_w = 0;

void colorFade(uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint32_t d, uint32_t t) {

  //convert seconds to milliseconds
  d = d * 1000;
  t = t * 1000;

  unsigned long waitTimer = 0;

  //pixel timers
  uint32_t rPT = 0;
  uint32_t gPT = 0;
  uint32_t bPT = 0;
  uint32_t wPT = 0;

  //rgbw steps
  uint32_t rS = 0;
  uint32_t gS = 0;
  uint32_t bS = 0;
  uint32_t wS = 0;

  //Get the number of steps needed for each pixel transition then divide the fade duration to get step length.
  if (r > curr_r) rS = d / (r - curr_r); else rS = d / (curr_r - r);
  if (g > curr_g) gS = d / (g - curr_g); else gS = d / (curr_g - g);
  if (b > curr_b) bS = d / (b - curr_b); else bS = d / (curr_b - b);
  if (w > curr_w) wS = d / (w - curr_w); else wS = d / (curr_w - w);

  //if the old and new values are different
  if((curr_r != r) || (curr_g != g) || (curr_b != b) || (curr_w != w)) {

    //enter the transition loop
    while ((curr_r != r) || (curr_g != g) || (curr_b != b) || (curr_w != w)){

      //if the elapsed time is greater than the step duration
      if (millis() - rPT >= rS) {

        //increment or decrement the pixel value
        if (curr_r < r) curr_r++; else if (curr_r > r) curr_r--;

        //and reset the pixel timer
        rPT = millis();
      }
      if (millis() - gPT >= gS) {
        if (curr_g < g) curr_g++; else if (curr_g > g) curr_g--;
        gPT = millis();
      }
      if (millis() - bPT >= bS) {
        if (curr_b < b) curr_b++; else if (curr_b > b) curr_b--;
        bPT = millis();
      }
      if (millis() - wPT >= wS) {
        if (curr_w < w) curr_w++; else if (curr_w > w) curr_w--;
        wPT = millis();
      }

      //Write to the strip
      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(strip.gamma8(curr_r), strip.gamma8(curr_g), strip.gamma8(curr_b), strip.gamma8(curr_w))); // Set white
      }
      strip.show();
    }
  }

  //if all the values match
  if ((curr_r == r) && (curr_g == g) && (curr_b == b) && (curr_w == w)) {

    //set the timer
    waitTimer = millis();

    //and go into the hold loop
    while ((curr_r == r) && (curr_g == g) && (curr_b == b) && (curr_w == w)){

      //if hold time isn't past, stay in loop
      if((millis() - waitTimer) <= t) {
      } else {
        break;
      }
    }
  }
}

/**
 * doubleColorFade
 * Takes R, G, B, W, R2, G2, B2, W2, fade duration in seconds, time to hold on color in seconds.
 * colorFade(255, 0, 0, 180, 213, 45, 234, 0, 5, 40);
 */

//volatile ints to store color data between runs. More accurate than getPixelColor.
volatile uint8_t curr_r1 = 0;
volatile uint8_t curr_g1 = 0;
volatile uint8_t curr_b1 = 0;
volatile uint8_t curr_w1 = 0;

volatile uint8_t curr_r2 = 0;
volatile uint8_t curr_g2 = 0;
volatile uint8_t curr_b2 = 0;
volatile uint8_t curr_w2 = 0;

void doubleColorFade(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t w1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t w2, uint32_t d, uint32_t t) {

  //convert seconds to milliseconds
  d = d * 1000;
  t = t * 1000;

  //divide the strip in half
  uint8_t halfStrip = strip.numPixels() / 2;
  uint8_t firstHalf = halfStrip;
  uint8_t lastHalf = halfStrip;

  //if the led count is odd, give the extra pixel to the first half
  //flip if needed
  if ((halfStrip & 1) != 0) firstHalf += 1;

  unsigned long waitTimer1 = 0;

  //First half rgbw pixel timers
  uint32_t rPT1 = 0;
  uint32_t gPT1 = 0;
  uint32_t bPT1 = 0;
  uint32_t wPT1 = 0;

  //second half rgbw pixel timers
  uint32_t rPT2 = 0;
  uint32_t gPT2 = 0;
  uint32_t bPT2 = 0;
  uint32_t wPT2 = 0;

  //first half rgbw steps
  uint32_t rS1 = 0;
  uint32_t gS1 = 0;
  uint32_t bS1 = 0;
  uint32_t wS1 = 0;

  //second half rgbw steps
  uint32_t rS2 = 0;
  uint32_t gS2 = 0;
  uint32_t bS2 = 0;
  uint32_t wS2 = 0;

  //Get the number of steps needed for each pixel transition then divide the fade duration to get step length for first half of string.
  if (r1 > curr_r1) rS1 = d / (r1 - curr_r1); else rS1 = d / (curr_r1 - r1);
  if (g1 > curr_g1) gS1 = d / (g1 - curr_g1); else gS1 = d / (curr_g1 - g1);
  if (b1 > curr_b1) bS1 = d / (b1 - curr_b1); else bS1 = d / (curr_b1 - b1);
  if (w1 > curr_w1) wS1 = d / (w1 - curr_w1); else wS1 = d / (curr_w1 - w1);

  //Same for second half of string.
  if (r2 > curr_r2) rS2 = d / (r2 - curr_r2); else rS2 = d / (curr_r2 - r2);
  if (g2 > curr_g2) gS2 = d / (g2 - curr_g2); else gS2 = d / (curr_g2 - g2);
  if (b2 > curr_b2) bS2 = d / (b2 - curr_b2); else bS2 = d / (curr_b2 - b2);
  if (w2 > curr_w2) wS2 = d / (w2 - curr_w2); else wS2 = d / (curr_w2 - w2);

    //if the old and new values are different
   if((curr_r1 != r1) || (curr_g1 != g1) || (curr_b1 != b1) || (curr_w1 != w1) || (curr_r2 != r2) || (curr_g2 != g2) || (curr_b2 != b2) || (curr_w2 != w2)) {

    //enter the transition loop
    while ((curr_r1 != r1) || (curr_g1 != g1) || (curr_b1 != b1) || (curr_w1 != w1) || (curr_r2 != r2) || (curr_g2 != g2) || (curr_b2 != b2) || (curr_w2 != w2)){

      //if the elapsed time is greater than the step duration
      if (millis() - rPT1 >= rS1) {

        //increment or decrement the pixel value
        if (curr_r1 < r1) curr_r1++; else if (curr_r1 > r1) curr_r1--;

        //and reset the pixel timer
        rPT1 = millis();
      }
      if (millis() - gPT1 >= gS1) {
        if (curr_g1 < g1) curr_g1++; else if (curr_g1 > g1) curr_g1--;
        gPT1 = millis();
      }
      if (millis() - bPT1 >= bS1) {
        if (curr_b1 < b1) curr_b1++; else if (curr_b1 > b1) curr_b1--;
        bPT1 = millis();
      }
      if (millis() - wPT1 >= wS1) {
        if (curr_w1 < w1) curr_w1++; else if (curr_w1 > w1) curr_w1--;
        wPT1 = millis();
      }
      if (millis() - rPT2 >= rS2) {
        if (curr_r2 < r2) curr_r2++; else if (curr_r2 > r2) curr_r2--;
        rPT2 = millis();
      }
      if (millis() - gPT2 >= gS2) {
        if (curr_g2 < g2) curr_g2++; else if (curr_g2 > g2) curr_g2--;
        gPT2 = millis();
      }
      if (millis() - bPT2 >= bS2) {
        if (curr_b2 < b2) curr_b2++; else if (curr_b2 > b2) curr_b2--;
        bPT2 = millis();
      }
      if (millis() - wPT2 >= wS2) {
        if (curr_w2 < w2) curr_w2++; else if (curr_w2 > w2) curr_w2--;
        wPT2 = millis();
      }

      //Write to the first half of the strip
      for(int i=0; i<firstHalf; i++) {
        strip.setPixelColor(i, strip.Color(strip.gamma8(curr_r1), strip.gamma8(curr_g1), strip.gamma8(curr_b1), strip.gamma8(curr_w1))); // Set white
      }

      //Write to the second half of the strip
      for(int j=firstHalf; j<lastHalf + firstHalf; j++) {
        strip.setPixelColor(j, strip.Color(strip.gamma8(curr_r2), strip.gamma8(curr_g2), strip.gamma8(curr_b2), strip.gamma8(curr_w2))); // Set white
      }
      strip.show();
    }
  }

  //if all the values match
  if ((curr_r1 == r1) && (curr_g1 == g1) && (curr_b1 == b1) && (curr_w1 == w1) && (curr_r2 == r2) && (curr_g2 == g2) && (curr_b2 == b2) && (curr_w2 == w2)) {

    //set the timer
    waitTimer1 = millis();

    //and go into the hold loop
    while ((curr_r1 == r1) && (curr_g1 == g1) && (curr_b1 == b1) && (curr_w1 == w1) && (curr_r2 == r2) && (curr_g2 == g2) && (curr_b2 == b2) && (curr_w2 == w2)){

      //if hold time isn't past, stay in loop
      if((millis() - waitTimer1) <= t) {
      } else {
        break;
      }
    }
  }
}
