# Extremely Slow Linear Fade
## Arduino sketch For sk6812 RGBW NeoPixels

Requires the [Adafruit_NeoPixel library](https://github.com/adafruit/Adafruit_NeoPixel).

Two linear fade functions that interpolate steps between 2 colors over a predefined transition period, then hold on that color(s) for another predefined period before exiting loop.

Made with the intention of creating extremely slow even linear fades over long periods of time.

Functions break out each rgbw value, compare with the previously set color, get the number of steps needed to transition each pixel, then get a step duration that will spread the steps evenly across the fade. Then on each step duration, the appropriate pixel value increments/decrements until all colors are reached by transition duration end.

Functions are surprisingly accurate given that they're not using floats. a 15 minute transition will finish only off by 200-300 milliseconds. For my purposes this is a perfectly fine margin of error. 

Also works for brief transitions, but due to being int values, interpolation breaks down as the duration goes ~< 2-3 seconds. Transition still occurs, but if the duration steps are too small, the < 1 rounding errors compound and you get a very fast fade.

### colorFade
R, G, B, W, fade duration in seconds, time to hold on color in seconds.

The function below will fade a strip from off to pink over 15 minutes, then hold on that color for 30 minutes.

```colorFade(255, 0, 0, 180, 900, 1800);```

Followed by this function, the strip will fade from pink above to a pastel turquoise over 5 minutes, then hold for 30 minutes.

```colorFade(0, 255, 255, 90, 300, 1800);```

Followed by this function, the strip will fade from pastel turquoise to black over 30 seconds.

```colorFade(0, 0, 0, 0, 30, 1);```

### doubleColorFade
R, G, B, W, R2, G2, B2, W2, fade duration in seconds, time to hold on color in seconds.

Takes two R, G, B, W values, puts the first on the first half of the strip and the second on the second half. it then transitions each half between colors and holds for a predefined period.

The function below will transition the first half of the strip from off to orange, and the second half from off to turquoise. Both transitions will happen over 3 minutes and hold for 5.

```doubleColorFade(246, 106, 4, 20, 216, 218, 26, 0, 180, 300);```

Followed by this function, the strip will fade from orange and turquoise above to a turquoise and yellow over 5 minutes, then hold for 5 minutes.

```doubleColorFade(56, 229, 158, 0, 216, 218, 26, 0, 300, 300);```

Followed by this function, the strip will fade from turquoise and yellow to black over 30 seconds.

```doubleColorFade(0, 0, 0, 0, 0, 0, 0, 0, 30, 1);```
