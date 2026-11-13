#include "splash.h"
#include "gui.h"
#include "constants.h"

// Geometry is 0.4 x the 640 x 360 film, centred above the version and tuner lines.
// Angles follow the TFT_eSPI arc convention: 0 at 6 o'clock, increasing clockwise.
static const int CX = 160;
static const int CY = 86;
static const int TRACK_R = 15, TRACK_IR = 13;     // thin circle the white dot rides on
static const int RING_R = 38, RING_IR = 23;       // green ring
static const int RING_CAP = 7;                    // round end of the green comet
static const int WRING_R = 17, WRING_IR = 7;      // white ring with the dark centre
static const int DOT_R = 5;                       // white dot that sweeps the ring
// How far (degrees) the rim of the round head reaches back into the band, see cometStep()
static const int CAP_BACK = 15, DOT_BACK = 35;
static const int ARC_W = 4;                       // half thickness of the white arcs
static const int ARC_MID_START = 44, ARC_MID = 48;
static const int PILL_MID_START = 50, PILL_MID = 64;
// Box of one pill, measured from the centre: the pills are drawn in a sprite of this size
// and placed in one go, so the move shows no intermediate erased state.
static const int PILL_DX = 41, PILL_W = 33, PILL_H = 58;
static const int RIPPLE_R_START = 42, RIPPLE_R_END = 64, RIPPLE_W = 4;
static const int TEXT_Y = 130, TEXT_GAP = 3;

// Timeline in ms; the film runs at 30 frames per second
static const uint32_t COMET_START = 0, COMET_LEN = 650;        // film frames 4 - 24
static const uint32_t SWEEP_START = 650, SWEEP_LEN = 350;      // frames 24 - 34
static const uint32_t ARCS_START = 1470, ARCS_LEN = 330;       // frames 48 - 58
static const uint32_t PILLS_START = 1870, PILLS_LEN = 460;     // frames 56 - 70
static const uint32_t RIPPLE_START = 2200, RIPPLE_LEN = 600;   // frames 66 - 84
static const uint32_t TEXT_START = 3000, TEXT_STEP = 50, TEXT_FADE = 200;  // frames 90 - 100
static const uint32_t SPLASH_END = 3800;

static uint16_t bg, ringTop, ringBottom, trackGreen, pillLeft, pillRight, rippleGreen;
static int cometHead, cometTail, sweepPos, arcsMid, pillMid, rippleR;
static uint16_t arcsCol, pillCol, rippleCol;
static const char textChars[] = "fmdx.org";
static const byte TEXT_LEN = sizeof(textChars) - 1;
static byte textFade[TEXT_LEN];
static int textX[TEXT_LEN];
static TFT_eSprite pillSprite = TFT_eSprite(&tft);

static void polar(float r, int angle, int &x, int &y) {
  float a = angle * DEG_TO_RAD;
  x = lroundf(CX - r * sinf(a));
  y = lroundf(CY + r * cosf(a));
}

// Mint at the top, yellow-green at the bottom, like the gradient in the film
static uint16_t ringColor(int angle) {
  uint8_t f = lroundf((1.0f - cosf(angle * DEG_TO_RAD)) * 127.5f);
  return tft.alphaBlend(f, ringTop, ringBottom);
}

static void drawRingSegment(int from, int to) {
  int s = from % 360, e = to % 360;
  if (s == e) return;
  tft.drawArc(CX, CY, RING_R, RING_IR, s, e, ringColor((from + to) / 2), bg, true);
}

static void drawFullRing() {
  for (int a = 0; a < 360; a += 15) drawRingSegment(a, a + 15);
}

static void drawRingCap(int angle) {
  int x, y;
  polar((RING_R + RING_IR) / 2.0f, angle % 360, x, y);
  tft.fillSmoothCircle(x, y, RING_CAP, ringColor(angle), bg);
}

static void drawArcs(int mid, uint16_t col) {
  tft.drawSmoothArc(CX, CY, mid + ARC_W, mid - ARC_W, 50, 130, col, bg, true);
  tft.drawSmoothArc(CX, CY, mid + ARC_W, mid - ARC_W, 230, 310, col, bg, true);
}

static void eraseArcs(int mid) {
  tft.drawArc(CX, CY, mid + ARC_W + 1, mid - ARC_W - 1, 42, 138, bg, bg, false);
  tft.drawArc(CX, CY, mid + ARC_W + 1, mid - ARC_W - 1, 222, 318, bg, bg, false);
}

// One pill with the part of the white arc that lies in front of it, via the sprite
static void drawPill(bool right, int mid, uint16_t col) {
  int sx = right ? CX + PILL_DX : CX - PILL_DX - PILL_W + 1;
  int sy = CY - PILL_H / 2;
  pillSprite.fillSprite(bg);
  pillSprite.drawSmoothArc(CX - sx, CY - sy, mid + 7, mid - 6, right ? 254 : 74, right ? 286 : 106, col, bg, true);
  pillSprite.drawSmoothArc(CX - sx, CY - sy, ARC_MID + ARC_W, ARC_MID - ARC_W, right ? 230 : 50, right ? 310 : 130, White, bg, true);
  pillSprite.pushSprite(sx, sy);
}

// Ring that only shows in the gaps above and below the arcs, as if it passes behind them
static void drawRipple(int r, uint16_t col, bool erase) {
  int outer = erase ? r + 1 : r, inner = erase ? r - RIPPLE_W : r - RIPPLE_W + 1;
  tft.drawArc(CX, CY, outer, inner, 140, 220, col, bg, !erase);
  tft.drawArc(CX, CY, outer, inner, 320, 40, col, bg, !erase);
}

// Green comet: a short dash runs clockwise from 6 o'clock and leaves the ring behind
static void cometStep(uint32_t t) {
  if (t < COMET_START || cometHead >= 420) return;
  int head = min((uint32_t)420, (t - COMET_START) * 420 / COMET_LEN);
  head -= head % 3;
  if (head == cometHead) return;
  int tail = constrain(head - 45, 0, 60);
  if (tail > cometTail) {
    if (cometTail == 0) tft.drawArc(CX, CY, RING_R + 1, RING_IR - 1, 340, 360, bg, bg, false);  // bulge of the start cap
    tft.drawArc(CX, CY, RING_R + 1, RING_IR - 1, cometTail, tail, bg, bg, false);
    cometTail = tail;
    if (tail == 60) {  // the tail stops here: give it a round end
      drawRingCap(60);
      drawRingSegment(60, 75);
    }
  }
  // Round head first, then the band up to the head on top of it: the anti-aliased
  // rim of the previous cap would otherwise stay behind inside the ring.
  if (head < 420) drawRingCap(head);
  drawRingSegment(cometHead < CAP_BACK ? 0 : cometHead - CAP_BACK, head);
  cometHead = head;
  if (head == 420) drawFullRing();
}

// The white dot appears on the thin circle, sweeps it and leaves the white ring behind
static void sweepStep(uint32_t t) {
  if (t < SWEEP_START || sweepPos >= 360) return;
  int pos = min((uint32_t)360, (t - SWEEP_START) * 360 / SWEEP_LEN);
  pos -= pos % 3;
  if (pos == sweepPos) return;
  if (pos < 360) {  // dot first, then the band on top of its rim, see cometStep
    int x, y;
    polar((WRING_R + WRING_IR) / 2.0f, pos, x, y);
    tft.fillSmoothCircle(x, y, DOT_R, White, bg);
  }
  if (pos > 0) tft.drawArc(CX, CY, WRING_R, WRING_IR, sweepPos < DOT_BACK ? 0 : sweepPos - DOT_BACK, pos, White, bg, true);
  if (pos == 360) tft.drawArc(CX, CY, WRING_R, WRING_IR, 0, 360, White, bg, true);
  sweepPos = pos;
}

// The white arcs slide out of the green ring while they brighten
static void arcsStep(uint32_t t) {
  if (t < ARCS_START) return;
  float p = min(1.0f, (t - ARCS_START) / (float)ARCS_LEN);
  int mid = ARC_MID_START + lroundf(p * (ARC_MID - ARC_MID_START));
  uint16_t col = tft.alphaBlend(128 + lroundf(p * 127), White, bg);
  if (mid == arcsMid && col == arcsCol) return;
  if (arcsMid && mid != arcsMid) eraseArcs(arcsMid);
  drawArcs(mid, col);
  arcsMid = mid;
  arcsCol = col;
  if (p >= 1.0f) drawFullRing();  // repairs the ring edge touched by the erasing
}

// The side pills slide out from behind the arcs and fade in
static void pillsStep(uint32_t t) {
  if (t < PILLS_START) return;
  float p = min(1.0f, (t - PILLS_START) / (float)PILLS_LEN);
  int mid = PILL_MID_START + lroundf(p * (PILL_MID - PILL_MID_START));
  uint16_t alpha = lroundf(sqrtf(p) * 255);
  if (mid == pillMid && alpha == pillCol) return;
  if (!pillMid) {
    pillSprite.setColorDepth(16);
    pillSprite.createSprite(PILL_W, PILL_H);
  }
  drawPill(false, mid, tft.alphaBlend(alpha, pillLeft, bg));
  drawPill(true, mid, tft.alphaBlend(alpha, pillRight, bg));
  pillMid = mid;
  pillCol = alpha;
  if (p >= 1.0f) pillSprite.deleteSprite();
}

// A faint ring expands outwards and fades away
static void rippleStep(uint32_t t) {
  if (t < RIPPLE_START || rippleR < 0) return;
  float p = min(1.0f, (t - RIPPLE_START) / (float)RIPPLE_LEN);
  int r = RIPPLE_R_START + lroundf(p * (RIPPLE_R_END - RIPPLE_R_START));
  uint16_t col = tft.alphaBlend(lroundf((1.0f - p) * 255), rippleGreen, bg);
  if (r == rippleR && col == rippleCol) return;
  if (rippleR) drawRipple(rippleR, bg, true);
  if (p >= 1.0f) {
    rippleR = -1;  // done
    return;
  }
  drawRipple(r, col, false);
  rippleR = r;
  rippleCol = col;
}

// fmdx.org appears letter by letter, each fading in; the domain part in the logo green
static void textStep(uint32_t t) {
  for (byte k = 0; k < TEXT_LEN; k++) {
    uint32_t start = TEXT_START + k * TEXT_STEP;
    if (t < start || textFade[k] >= 4) continue;
    byte step = min((uint32_t)4, (t - start) * 4 / TEXT_FADE + 1);
    if (step == textFade[k]) continue;
    uint16_t col = tft.alphaBlend(step * 64 - 1, k < 4 ? White : pillLeft, bg);
    tftPrint(ALEFT, String(textChars[k]), textX[k], TEXT_Y, col, bg, 16);
    textFade[k] = step;
  }
}

void SplashIntro() {
  bg = BackgroundColor;
  ringTop = tft.color565(165, 211, 152);
  ringBottom = tft.color565(193, 219, 131);
  trackGreen = tft.color565(160, 212, 150);
  pillLeft = tft.color565(205, 222, 123);
  pillRight = tft.color565(162, 210, 153);
  rippleGreen = tft.color565(90, 110, 90);
  cometHead = cometTail = arcsMid = pillMid = rippleR = 0;
  sweepPos = -1;  // the dot is not there yet
  arcsCol = pillCol = rippleCol = 0;
  memset(textFade, 0, sizeof(textFade));

  // Letter positions: the text is centred with a little extra spacing between the glyphs
  int width = -TEXT_GAP;
  for (byte k = 0; k < TEXT_LEN; k++) width += tftTextWidth(String(textChars[k]), 16) + TEXT_GAP;
  int left = CX - width / 2;
  for (byte k = 0; k < TEXT_LEN; k++) {
    textX[k] = left;
    left += tftTextWidth(String(textChars[k]), 16) + TEXT_GAP;
  }

  tft.drawArc(CX, CY, TRACK_R, TRACK_IR, 0, 360, trackGreen, bg, true);
  drawRingCap(0);
}

void SplashPlay() {
  uint32_t t0 = millis();
  tft.setViewport(0, 36, 320, 114, false);  // keeps the ripple off the title and the version line
  for (;;) {
    uint32_t t = millis() - t0;
    if (t >= SPLASH_END) break;
    cometStep(t);
    sweepStep(t);
    arcsStep(t);
    pillsStep(t);
    rippleStep(t);
    textStep(t);
    delay(1);
  }
  tft.resetViewport();
}
