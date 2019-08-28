#include "linearFade.h"

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
  Serial.print("Remember, these are slow transitions. Don't expect dithering and rainbow wipes.");
  //values: R, G, B, W, R2, G2, B2, W2, transition duration in seconds, hold duration in seconds.
  doubleColorFade(246, 106, 4, 20, 216, 218, 26, 0, 60, 120);
  doubleColorFade(56, 229, 158, 0, 216, 218, 26, 0, 90, 200);
  doubleColorFade(78, 6, 160, 0, 90, 30, 255, 0, 200, 200);
  doubleColorFade(216, 218, 26, 0, 150, 30, 246, 106, 600, 200);
  doubleColorFade(255, 0, 0, 120, 216, 218, 26, 0, 200, 200);
  doubleColorFade(0, 0, 0, 0, 2, 1, 0, 0, 2, 1);

  ledState = 0;

}
