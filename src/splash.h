#ifndef SPLASH_H
#define SPLASH_H

// Boot animation: the FM-DX logo is built up the same way as the PlutoRadio splash
// film, but drawn with the TFT_eSPI smooth graphics instead of a stored video, so it
// costs no flash. SplashIntro() draws the first frame (shown while the backlight ramps
// up), SplashPlay() runs the animation and returns when it has finished.
void SplashIntro();
void SplashPlay();

#endif
