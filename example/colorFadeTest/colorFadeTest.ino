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
  Serial.println("Remember, these are slow transitions. Don't expect a bunch of rainbow wipes.");
  //values: R, G, B, W, transition duration in seconds, hold duration in seconds.
  colorFade(246, 106, 4, 20, 60, 180); //Orange
  colorFade(56, 229, 158, 0, 90, 120); //turquoise
  colorFade(78, 6, 160, 0, 150, 600); //lavender
  colorFade(216, 218, 26, 0, 500, 100); //yellow
  colorFade(255, 0, 0, 120, 800, 100);// Pink
  colorFade(0, 0, 0, 0, 2, 1); //Fade to black

  ledState = 0;

}
