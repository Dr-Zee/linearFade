#include "linearFade.h"

uint8_t ledState = 0;

void setup () {
  strip.begin ();
  strip.show ();
  strip.setBrightness (255);
}

void loop () {
  if (ledState == 0) {
    runLED();
  }
}

// reset function
int reset(){
  strip.clear();
}

/**
** LED function
**/
int runLED() {

  ledState = 1;
  Serial.print(" ");
  Serial.println("Remember, these are slow transitions. Don't expect a bunch of rainbow wipes.");

  /**
   * Color fade
   * values: R, G, B, W, transition duration in seconds, hold duration in seconds.
   */
  colorFade(246, 106, 4, 20, 60, 180); //Orange
  colorFade(56, 229, 158, 0, 90, 120); //turquoise
  colorFade(78, 6, 160, 0, 150, 600); //lavender
  colorFade(216, 218, 26, 0, 500, 100); //yellow
  colorFade(255, 0, 0, 120, 800, 100);// Pink
  colorFade(0, 0, 0, 0, 2, 1); //Fade to black

  /**
   * Double Color fade
   * values: R, G, B, W, R2, G2, B2, W2, transition duration in seconds, hold duration in seconds.
   * uncomment to run
   */
  //doubleColorFade(246, 106, 4, 20, 216, 218, 26, 0, 60, 120);
  //doubleColorFade(56, 229, 158, 0, 216, 218, 26, 0, 90, 200);
  //doubleColorFade(78, 6, 160, 0, 90, 30, 255, 0, 200, 200);
  //doubleColorFade(216, 218, 26, 0, 150, 30, 246, 106, 600, 200);
  //doubleColorFade(255, 0, 0, 120, 216, 218, 26, 0, 200, 200);
  //doubleColorFade(0, 0, 0, 0, 2, 1, 0, 0, 2, 1);

  ledState = 0;

}
