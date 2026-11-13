#include "games.h"
#include "gui.h"
#include "constants.h"
#include "audiocues.h"
#include <EEPROM.h>

extern int rotary;
extern void tftReplace(int8_t offset, const String & textold, const String & text, int16_t x, int16_t y, int color, int smoothcolor, int background, uint8_t fontsize);

// ============================================================================ shared
static byte knobPin, modePin, bwPin, bandPin;
static const byte SOUND_LEVEL = 5;  // -5 dB, like the beeps of the radio
static uint16_t frameInner;         // the inner line of the frames, from the theme

static void sfx(uint16_t ms, uint16_t hz) {
  radio.tone(ms, -SOUND_LEVEL, hz);
  if (radio.mute) radio.setMute();
}

static void sfxFame() { sfx(60, 784); sfx(60, 988); sfx(60, 1175); sfx(60, 1568); sfx(150, 2093); }

// A push, waited out with a little debounce
static bool pressed(byte pin) {
  if (digitalRead(pin) == HIGH) return false;
  delay(20);
  while (digitalRead(pin) == LOW) delay(10);
  delay(20);
  return true;
}

// Waits for a push on the knob (true) or on MODE (false)
static bool waitForKnob() {
  for (;;) {
    if (pressed(modePin)) return false;
    if (pressed(knobPin)) return true;
    delay(10);
  }
}

// A box in the middle of the screen for the messages
static void box(const String &title, const String &line1, const String &line2) {
  tft.fillRoundRect(40, 66, 240, 112, 8, BackgroundColor);
  tft.drawRoundRect(40, 66, 240, 112, 8, FrameColor);
  tft.drawRoundRect(42, 68, 236, 108, 7, frameInner);
  tftPrint(ACENTER, title, 160, 78, PrimaryColor, PrimaryColorSmooth, 28);
  tftPrint(ACENTER, line1, 160, 122, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(ACENTER, line2, 160, 146, ActiveColor, ActiveColorSmooth, 16);
}

// A block with a bevel, the look of the tetris pieces and the icons
static void bevel(int x, int y, int size, uint16_t color) {
  tft.fillRect(x, y, size, size, color);
  uint16_t light = tft.alphaBlend(110, White, color), dark = tft.alphaBlend(120, 0x0000, color);
  tft.drawFastHLine(x, y, size, light);
  tft.drawFastVLine(x, y, size, light);
  tft.drawFastHLine(x, y + size - 1, size, dark);
  tft.drawFastVLine(x + size - 1, y, size, dark);
}

// ---------------------------------------------------------------- hall of fame
// Five scores with three initials, kept in the EEPROM in 6 bytes each
static const byte SCORES = 5, NAME_LEN = 3;

struct HallOfFame {
  int eeBase;
  struct {
    uint16_t score;
    char name[NAME_LEN + 1];
  } entry[SCORES];

  void load() {
    for (byte i = 0; i < SCORES; i++) {
      int base = eeBase + i * 6;
      entry[i].score = EEPROM.readUShort(base);
      bool valid = entry[i].score != 0xFFFF;
      for (byte c = 0; c < NAME_LEN; c++) {
        char ch = EEPROM.readByte(base + 2 + c);
        if (ch != ' ' && (ch < 'A' || ch > 'Z')) valid = false;
        entry[i].name[c] = ch;
      }
      entry[i].name[NAME_LEN] = 0;
      if (!valid) {  // a new EEPROM, or garbage
        entry[i].score = 0;
        strcpy(entry[i].name, "---");
      }
    }
  }

  void save() {
    for (byte i = 0; i < SCORES; i++) {
      int base = eeBase + i * 6;
      EEPROM.writeUShort(base, entry[i].score);
      for (byte c = 0; c < NAME_LEN; c++) EEPROM.writeByte(base + 2 + c, entry[i].name[c]);
    }
    EEPROM.commit();
  }

  int rankOf(uint16_t score) {
    for (byte i = 0; i < SCORES; i++) if (score > entry[i].score) return i;
    return -1;
  }

  // Three letters, chosen with the knob
  void enterName(char *name) {
    static const char letters[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const byte count = sizeof(letters) - 1;
    byte idx[NAME_LEN] = {1, 1, 1};
    byte slot = 0;
    bool cursor = true;
    tft.fillRoundRect(40, 66, 240, 112, 8, BackgroundColor);
    tft.drawRoundRect(40, 66, 240, 112, 8, PrimaryColor);
    tft.drawRoundRect(42, 68, 236, 108, 7, frameInner);
    tftPrint(ACENTER, "HIGH SCORE!", 160, 74, PrimaryColor, PrimaryColorSmooth, 28);
    tftPrint(ACENTER, "Turn: letter   Push: next", 160, 152, ActiveColor, ActiveColorSmooth, 16);
    rotary = 0;
    for (;;) {
      for (byte i = 0; i < NAME_LEN; i++) {
        int x = 130 + i * 30;
        tft.fillRect(x - 12, 108, 24, 40, BackgroundColor);
        tftPrint(ACENTER, String(letters[idx[i]]), x, 110, i == slot ? PrimaryColor : ActiveColor, i == slot ? PrimaryColorSmooth : ActiveColorSmooth, 28);
        if (i == slot && cursor) tft.fillRect(x - 10, 144, 20, 2, PrimaryColor);
      }
      uint32_t until = millis() + 250;
      bool changed = false;
      while (millis() < until && !changed) {
        if (rotary) {
          idx[slot] = (idx[slot] + (rotary < 0 ? 1 : count - 1)) % count;
          rotary = 0;
          sfx(12, 1200);
          cursor = true;
          changed = true;
        } else if (pressed(knobPin)) {
          sfx(30, 1500);
          slot++;
          cursor = true;
          changed = true;
        } else if (pressed(modePin)) {
          slot = NAME_LEN;
          changed = true;
        } else {
          delay(5);
        }
      }
      if (slot >= NAME_LEN) break;
      if (!changed) cursor = !cursor;
    }
    for (byte i = 0; i < NAME_LEN; i++) name[i] = letters[idx[i]];
    name[NAME_LEN] = 0;
  }

  // Fanfare, name entry and the place in the table, or -1 when the score is too low
  int enter(uint16_t score) {
    int rank = rankOf(score);
    if (rank < 0) return -1;
    sfxFame();
    char name[NAME_LEN + 1];
    enterName(name);
    for (int i = SCORES - 1; i > rank; i--) entry[i] = entry[i - 1];
    entry[rank].score = score;
    strcpy(entry[rank].name, name);
    save();
    return rank;
  }

  void draw(int x, int y, int lineHeight) {
    for (byte i = 0; i < SCORES; i++) {
      int ly = y + i * lineHeight;
      tftPrint(ALEFT, String(i + 1) + ".", x, ly, ActiveColor, ActiveColorSmooth, 16);
      tftPrint(ALEFT, entry[i].name, x + 24, ly, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(ARIGHT, entry[i].score ? String(entry[i].score) : "", x + 112, ly, PrimaryColor, PrimaryColorSmooth, 16);
    }
  }
};

static HallOfFame snakeFame = {EE_SNAKE_SCORES};
static HallOfFame tetrisFame = {EE_TETRIS_SCORES};
static HallOfFame tefmanFame = {EE_TEFMAN_SCORES};
static HallOfFame invadersFame = {EE_INVADERS_SCORES};

// ============================================================================ snake
namespace snake {

// Playfield of 30 x 20 cells of 10 px, framed, with the scores above it
static const byte CELL = 10, COLS = 30, ROWS = 20;
static const int FX = 10, FY = 30;              // top left of the field
static const int CELLS = COLS * ROWS;
static const byte FOODS_PER_LEVEL = 5;
static const byte BONUS_LIFE = 40;               // steps a bonus stays
static const byte WALLS_FROM_LEVEL = 3, WALLS_PER_LEVEL = 4;

enum { UP, RIGHT, DOWN, LEFT };
enum { FREE, SNAKE, WALL };

// The snake is a ring of cells, the head at the front
static byte bodyX[CELLS], bodyY[CELLS];
static int head, length;
static byte grid[COLS][ROWS];
static byte dir, turnQueue[2], turnCount;
static byte foodX, foodY, bonusX, bonusY, bonusLeft, bonusCount;
static byte grow, foods, level;
static uint16_t score;
static uint32_t stepInterval;
static uint16_t bgA, bgB, scaleA, scaleB, headRim, wallDark, leafGreen, stemBrown;
static uint16_t scoreShown, bestShown;
static byte levelShown;

static void sfxStart()    { sfx(40, 523); sfx(40, 659); sfx(60, 784); }
static void sfxEat()      { sfx(25, min(2000, 700 + 15 * length)); }
static void sfxBonusIn()  { sfx(20, 1500); sfx(20, 1900); }
static void sfxBonusEat() { sfx(30, 784); sfx(30, 988); sfx(30, 1175); sfx(50, 1568); }
static void sfxLevel()    { sfx(40, 1047); sfx(60, 1568); }
static void sfxWalls()    { sfx(60, 180); sfx(60, 150); }
static void sfxPause()    { sfx(30, 600); }
static void sfxDead()     { sfx(250, 120); }

// Steering is relative to the snake: clockwise turns right. Two turns can be queued,
// so a quick left-left U-turn works at any speed.
static void readKnob() {
  if (rotary == 0) return;
  if (turnCount < 2) turnQueue[turnCount++] = rotary < 0 ? RIGHT : LEFT;
  rotary = 0;
}

// ---------------------------------------------------------------- drawing
static int px(byte x) { return FX + x * CELL; }
static int py(byte y) { return FY + y * CELL; }
static uint16_t cellBg(byte x, byte y) { return (x + y) & 1 ? bgB : bgA; }

static void clearCell(byte x, byte y) {
  tft.fillRect(px(x), py(y), CELL, CELL, cellBg(x, y));
}

static void drawFrame(uint16_t color) {
  tft.drawRect(FX - 3, FY - 3, COLS * CELL + 6, ROWS * CELL + 6, color);
  tft.drawRect(FX - 1, FY - 1, COLS * CELL + 2, ROWS * CELL + 2, frameInner);
}

// Ring index k of the snake: scales in two tones, the tail tapered
static void drawSegment(int k) {
  int tail = (head - length + 1 + CELLS) % CELLS;
  byte x = bodyX[k], y = bodyY[k];
  uint16_t color = k & 1 ? scaleA : scaleB;
  if (k == tail) {
    clearCell(x, y);
    tft.fillRoundRect(px(x) + 2, py(y) + 2, CELL - 4, CELL - 4, 3, color);
  } else {
    tft.fillRoundRect(px(x), py(y), CELL, CELL, 3, color);
  }
}

static void drawHead(byte x, byte y) {
  int x0 = px(x), y0 = py(y);
  tft.fillRoundRect(x0, y0, CELL, CELL, 4, PrimaryColor);
  tft.drawRoundRect(x0, y0, CELL, CELL, 4, headRim);
  int ex1 = x0 + 2, ey1 = y0 + 2, ex2 = x0 + 6, ey2 = y0 + 6;  // the eyes
  int dx = 0, dy = 0;  // the pupils look ahead
  switch (dir) {
    case UP:    ey2 = ey1; break;
    case DOWN:  ey1 = ey2; dy = 1; break;
    case LEFT:  ex2 = ex1; break;
    case RIGHT: ex1 = ex2; dx = 1; break;
  }
  tft.fillRect(ex1, ey1, 2, 2, White);
  tft.fillRect(ex2, ey2, 2, 2, White);
  tft.drawPixel(ex1 + dx, ey1 + dy, bgA);
  tft.drawPixel(ex2 + dx, ey2 + dy, bgA);
}

static void drawApple(byte x, byte y) {
  int cx = px(x) + 5, cy = py(y) + 5;
  tft.fillCircle(cx, cy, 4, SignificantColor);
  tft.drawPixel(cx - 2, cy - 2, White);
  tft.fillRect(cx, cy - 5, 1, 2, stemBrown);
  tft.fillRect(cx + 1, cy - 5, 2, 1, leafGreen);
}

static void drawBonus() {
  clearCell(bonusX, bonusY);
  if (bonusLeft < 10 && bonusCount & 1) return;  // nearly gone: blinks
  int cx = px(bonusX) + 5, cy = py(bonusY) + 5, r = 2 + bonusCount % 3;  // pulses
  tft.fillCircle(cx, cy, r, PrimaryColor);
  tft.drawFastVLine(cx, cy - r, 2 * r + 1, cellBg(bonusX, bonusY));
  tft.drawFastHLine(cx - r, cy, 2 * r + 1, cellBg(bonusX, bonusY));
  tft.drawPixel(cx, cy, PrimaryColor);
}

static void drawBonusBar() {
  int w = 300L * bonusLeft / BONUS_LIFE;
  tft.fillRect(FX, FY + ROWS * CELL + 5, w, 3, PrimaryColor);
  tft.fillRect(FX + w, FY + ROWS * CELL + 5, 300 - w, 3, BackgroundColor);
}

static void drawWall(byte x, byte y) {
  int x0 = px(x), y0 = py(y);
  tft.fillRect(x0, y0, CELL, CELL, FrameColor);
  tft.drawFastHLine(x0, y0 + 4, CELL, wallDark);  // bricks
  tft.drawFastHLine(x0, y0 + 9, CELL, wallDark);
  tft.drawFastVLine(x0 + 6, y0, 4, wallDark);
  tft.drawFastVLine(x0 + 2, y0 + 5, 4, wallDark);
}

// The score line is drawn once per screen; afterwards only a changed value is replaced,
// old text in the background colour first, so nothing else blinks
static void drawBestLabel(uint16_t best, int color, int smooth) {
  tftPrint(ARIGHT, "BEST", FX + 300 - 10 - tftTextWidth(String(best), 16), 4, color, smooth, 16);
}

static void drawScoreLine() {
  tft.fillRect(0, 2, 320, 22, BackgroundColor);
  tftPrint(ALEFT, "SCORE", FX, 4, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(ALEFT, String(score), FX + 58, 4, PrimaryColor, PrimaryColorSmooth, 16);
  tftPrint(ACENTER, "LEVEL " + String(level), 160, 4, SecondaryColor, SecondaryColorSmooth, 16);
  tftPrint(ARIGHT, String(snakeFame.entry[0].score), FX + 300, 4, PrimaryColor, PrimaryColorSmooth, 16);
  drawBestLabel(snakeFame.entry[0].score, ActiveColor, ActiveColorSmooth);
  scoreShown = score;
  levelShown = level;
  bestShown = snakeFame.entry[0].score;
}

static void updateScores() {
  uint16_t best = snakeFame.entry[0].score;
  if (score != scoreShown) {
    tftReplace(ALEFT, String(scoreShown), String(score), FX + 58, 4, PrimaryColor, PrimaryColorSmooth, BackgroundColor, 16);
    scoreShown = score;
  }
  if (level != levelShown) {
    tftReplace(ACENTER, "LEVEL " + String(levelShown), "LEVEL " + String(level), 160, 4, SecondaryColor, SecondaryColorSmooth, BackgroundColor, 16);
    levelShown = level;
  }
  if (best != bestShown) {  // the label moves with the width of the number
    drawBestLabel(bestShown, BackgroundColor, BackgroundColor);
    tftReplace(ARIGHT, String(bestShown), String(best), FX + 300, 4, PrimaryColor, PrimaryColorSmooth, BackgroundColor, 16);
    drawBestLabel(best, ActiveColor, ActiveColorSmooth);
    bestShown = best;
  }
}

static void drawField() {
  tft.fillScreen(BackgroundColor);
  drawFrame(FrameColor);
  for (byte x = 0; x < COLS; x++) {
    for (byte y = 0; y < ROWS; y++) {
      if (grid[x][y] == WALL) drawWall(x, y); else clearCell(x, y);
    }
  }
}

static void drawSnake() {
  for (int i = 0, k = head; i < length; i++, k = (k + CELLS - 1) % CELLS) {
    if (i) drawSegment(k); else drawHead(bodyX[k], bodyY[k]);
  }
}

static void redrawAll() {
  drawField();
  drawScoreLine();
  drawSnake();
  drawApple(foodX, foodY);
  if (bonusLeft) {
    drawBonus();
    drawBonusBar();
  }
}

static void flashFrame() {
  for (byte n = 0; n < 2; n++) {
    drawFrame(PrimaryColor);
    delay(70);
    drawFrame(FrameColor);
    delay(70);
  }
}

// ---------------------------------------------------------------- game
// A free cell, away from the food and the bonus. Worked out in locals: the result may
// be foodX and foodY themselves, which the check compares against.
static void freeCell(byte &outX, byte &outY, bool awayFromHead) {
  byte x, y;
  do {
    x = random(COLS);
    y = random(ROWS);
  } while (grid[x][y] != FREE || (x == foodX && y == foodY) || (bonusLeft && x == bonusX && y == bonusY) ||
           (awayFromHead && abs(x - bodyX[head]) < 4 && abs(y - bodyY[head]) < 4));
  outX = x;
  outY = y;
}

static void addWalls() {
  for (byte n = 0; n < WALLS_PER_LEVEL; n++) {
    byte x, y;
    freeCell(x, y, true);
    grid[x][y] = WALL;
    drawWall(x, y);
  }
  sfxWalls();
}

static void newGame() {
  memset(grid, FREE, sizeof(grid));
  length = 4;
  dir = RIGHT;
  turnCount = 0;
  for (int i = 0; i < length; i++) {  // the tail is the oldest cell, the head the newest
    bodyX[i] = COLS / 2 - 4 + i;
    bodyY[i] = ROWS / 2;
    grid[bodyX[i]][bodyY[i]] = SNAKE;
  }
  head = length - 1;
  grow = 0;
  foods = 0;
  level = 1;
  score = 0;
  bonusLeft = 0;
  bonusCount = 0;
  stepInterval = 160;
  foodX = foodY = 255;
  freeCell(foodX, foodY, true);
  redrawAll();
  rotary = 0;
}

// The snake dissolves from the tail to the head, with falling tones
static void dissolve() {
  int tail = (head - length + 1 + CELLS) % CELLS;
  uint16_t wait = constrain(1200 / length, 3, 40);
  byte every = length / 10 + 1;
  for (int i = 0, k = tail; i < length; i++, k = (k + 1) % CELLS) {
    tft.fillRoundRect(px(bodyX[k]), py(bodyY[k]), CELL, CELL, 3, SignificantColor);
    delay(wait);
    clearCell(bodyX[k], bodyY[k]);
    if (i % every == 0) sfx(15, 900 - 700L * i / length);
  }
  sfxDead();
}

// One step; false when the snake dies
static bool step() {
  if (turnCount) {  // a turn from the queue, never straight back
    byte turn = turnQueue[0];
    turnQueue[0] = turnQueue[1];
    turnCount--;
    dir = turn == RIGHT ? (dir + 1) % 4 : (dir + 3) % 4;
  }
  int x = bodyX[head], y = bodyY[head];
  switch (dir) {
    case UP:    y--; break;
    case DOWN:  y++; break;
    case LEFT:  x--; break;
    case RIGHT: x++; break;
  }
  if (x < 0 || x >= COLS || y < 0 || y >= ROWS) return false;

  // The tail leaves first unless the snake grows, so chasing it is allowed
  int tail = (head - length + 1 + CELLS) % CELLS;
  if (grow) {
    grow--;
    length++;
  } else {
    grid[bodyX[tail]][bodyY[tail]] = FREE;
    clearCell(bodyX[tail], bodyY[tail]);
    tail = (tail + 1) % CELLS;
    drawSegment(tail);  // the new tail tapers
  }
  if (grid[x][y] != FREE) return false;

  drawSegment(head);  // the old head is body now
  head = (head + 1) % CELLS;
  bodyX[head] = x;
  bodyY[head] = y;
  grid[x][y] = SNAKE;
  drawHead(x, y);

  if (x == foodX && y == foodY) {
    score += 10;
    grow += 1;
    foods++;
    sfxEat();
    freeCell(foodX, foodY, false);
    drawApple(foodX, foodY);
    if (foods % FOODS_PER_LEVEL == 0) {
      level++;
      stepInterval = max((uint32_t)60, stepInterval - 12);
      sfxLevel();
      flashFrame();
      if (level >= WALLS_FROM_LEVEL) addWalls();
      if (!bonusLeft) {  // a bonus to go with the new level
        freeCell(bonusX, bonusY, false);
        bonusLeft = BONUS_LIFE;
        bonusCount = 0;
        drawBonus();
        sfxBonusIn();
      }
    }
    updateScores();
  } else if (bonusLeft && x == bonusX && y == bonusY) {
    score += 50;
    grow += 3;
    bonusLeft = 0;
    sfxBonusEat();
    updateScores();
    drawBonusBar();
  }

  if (bonusLeft) {  // the bonus pulses and runs out
    bonusLeft--;
    bonusCount++;
    if (bonusLeft == 0) clearCell(bonusX, bonusY); else drawBonus();
    drawBonusBar();
  }
  return true;
}

// Plays until the snake dies (true) or MODE is pressed (false)
static bool play() {
  uint32_t next = millis() + stepInterval;
  for (;;) {
    readKnob();
    if (pressed(modePin)) return false;
    if (pressed(knobPin)) {
      sfxPause();
      box("PAUSED", "Push the knob", "to go on");
      while (!pressed(knobPin)) {
        if (pressed(modePin)) return false;
        delay(10);
      }
      redrawAll();
      rotary = 0;
      next = millis() + stepInterval;
    }
    if (millis() >= next) {
      next += stepInterval;
      if (!step()) return true;
    }
    delay(2);
  }
}

// Title, the hall of fame and a little snake that eats its way along the bottom.
// Returns true for a push on the knob, false for MODE.
static bool startScreen() {
  tft.fillScreen(BackgroundColor);
  drawFrame(FrameColor);
  tftPrint(ACENTER, "SNAKE", 160, 36, PrimaryColor, PrimaryColorSmooth, 28);
  tftPrint(ACENTER, "HALL OF FAME", 160, 72, SecondaryColor, SecondaryColorSmooth, 16);
  snakeFame.draw(104, 92, 18);
  tftPrint(ACENTER, "Turn: steer   Push: start   MODE: back", 160, 190, ActiveColor, ActiveColorSmooth, 16);

  // The demo snake lives on the bottom row
  const byte row = ROWS - 1, demoLen = 7;
  int demoHead = 12;
  byte apple = 20;
  dir = RIGHT;
  for (byte x = 0; x < COLS; x++) clearCell(x, row);
  uint32_t next = millis();
  for (;;) {
    if (pressed(modePin)) return false;
    if (pressed(knobPin)) return true;
    if (millis() >= next) {
      next += 110;
      clearCell((demoHead - demoLen + COLS) % COLS, row);
      tft.fillRoundRect(px(demoHead), py(row), CELL, CELL, 3, demoHead & 1 ? scaleA : scaleB);
      demoHead = (demoHead + 1) % COLS;
      if (demoHead == apple) {
        sfx(15, 1200);
        apple = (apple + 7 + random(10)) % COLS;
        if (apple == demoHead) apple = (apple + 3) % COLS;
      }
      drawHead(demoHead, row);
      drawApple(apple, row);
    }
    delay(5);
  }
}

static void gameOver() {
  dissolve();
  int rank = snakeFame.enter(score);
  updateScores();
  if (rank >= 0) box("GAME OVER", "Score " + String(score) + ", place " + String(rank + 1), "Push the knob to play again");
  else box("GAME OVER", "Score " + String(score), "Push the knob to play again");
}

static void run() {
  bgA = BackgroundColor;
  bgB = tft.alphaBlend(22, FrameColor, BackgroundColor);
  scaleA = SecondaryColor;
  scaleB = tft.alphaBlend(170, SecondaryColor, BackgroundColor);
  headRim = tft.alphaBlend(110, White, PrimaryColor);
  wallDark = tft.alphaBlend(120, BackgroundColor, FrameColor);
  leafGreen = tft.color565(60, 180, 60);
  stemBrown = tft.color565(120, 80, 30);
  if (!startScreen()) return;
  for (;;) {
    sfxStart();
    newGame();
    if (!play()) break;  // MODE during the game
    gameOver();
    if (!waitForKnob()) break;
  }
}

}  // namespace snake

// ============================================================================ tetris
namespace tetris {

// Playfield of 10 x 20 cells of 10 px in the middle, level and lines on the left,
// the next piece, score and best on the right
static const byte CELL = 10, COLS = 10, ROWS = 20;
static const int FX = 110, FY = 20;
static const int NEXT_X = 234, NEXT_Y = 42;      // preview box

// The seven pieces as 4 x 4 bitmaps, one per rotation, in the classic colours
static const uint16_t shapes[7][4] = {
  {0x0F00, 0x2222, 0x00F0, 0x4444},  // I
  {0x6600, 0x6600, 0x6600, 0x6600},  // O
  {0x4E00, 0x4640, 0x0E40, 0x4C40},  // T
  {0x6C00, 0x4620, 0x06C0, 0x8C40},  // S
  {0xC600, 0x2640, 0x0C60, 0x4C80},  // Z
  {0x8E00, 0x6440, 0x0E20, 0x44C0},  // J
  {0x2E00, 0x4460, 0x0E80, 0xC440}   // L
};
static const uint16_t colors[7] = {0x07FF, 0xFFE0, 0x901F, 0x07E0, 0xF800, 0x21BF, 0xFD20};

static byte field[COLS][ROWS];  // 0 empty, else piece + 1
static byte cur, rot, nextPiece;
static int cx, cy, ghostY;
static uint16_t score, lines;
static byte level;
static uint32_t interval;
static uint16_t scoreShown, bestShown, linesShown;
static byte levelShown;
static uint16_t ghostColor;

static void sfxMove()   { sfx(8, 500); }
static void sfxRotate() { sfx(12, 900); }
static void sfxLock()   { sfx(20, 220); }
static void sfxDrop()   { sfx(30, 160); }
static void sfxLines(byte n) {
  if (n == 4) { sfx(40, 1047); sfx(40, 1319); sfx(40, 1568); sfx(80, 2093); }
  else for (byte i = 0; i < n; i++) sfx(40, 1000 + 200 * i);
}
static void sfxLevel()  { sfx(40, 1047); sfx(60, 1568); }
static void sfxStart()  { sfx(40, 523); sfx(40, 659); sfx(60, 784); }
static void sfxPause()  { sfx(30, 600); }

static bool cellBit(byte piece, byte r, byte row, byte col) {
  return (shapes[piece][r] >> (15 - (row * 4 + col))) & 1;
}

static int px(int x) { return FX + x * CELL; }
static int py(int y) { return FY + y * CELL; }

static bool fits(byte piece, byte r, int x, int y) {
  for (byte row = 0; row < 4; row++) {
    for (byte col = 0; col < 4; col++) {
      if (!cellBit(piece, r, row, col)) continue;
      int fx = x + col, fy = y + row;
      if (fx < 0 || fx >= COLS || fy >= ROWS) return false;
      if (fy >= 0 && field[fx][fy]) return false;
    }
  }
  return true;
}

// ---------------------------------------------------------------- drawing
static void drawBlock(int x, int y, uint16_t color) {
  if (y < 0) return;
  bevel(px(x), py(y), CELL, color);
}

static void eraseBlock(int x, int y) {
  if (y < 0) return;
  tft.fillRect(px(x), py(y), CELL, CELL, BackgroundColor);
}

static void drawGhostBlock(int x, int y) {
  if (y < 0) return;
  tft.drawRect(px(x) + 1, py(y) + 1, CELL - 2, CELL - 2, ghostColor);
}

static int landingY() {
  int y = cy;
  while (fits(cur, rot, cx, y + 1)) y++;
  return y;
}

static void showPiece() {
  ghostY = landingY();
  for (byte row = 0; row < 4; row++) {
    for (byte col = 0; col < 4; col++) {
      if (!cellBit(cur, rot, row, col)) continue;
      if (ghostY != cy) drawGhostBlock(cx + col, ghostY + row);
    }
  }
  for (byte row = 0; row < 4; row++) {
    for (byte col = 0; col < 4; col++) {
      if (cellBit(cur, rot, row, col)) drawBlock(cx + col, cy + row, colors[cur]);
    }
  }
}

static void hidePiece() {
  for (byte row = 0; row < 4; row++) {
    for (byte col = 0; col < 4; col++) {
      if (!cellBit(cur, rot, row, col)) continue;
      eraseBlock(cx + col, ghostY + row);
      eraseBlock(cx + col, cy + row);
    }
  }
}

static void drawFrame() {
  tft.drawRect(FX - 3, FY - 3, COLS * CELL + 6, ROWS * CELL + 6, FrameColor);
  tft.drawRect(FX - 1, FY - 1, COLS * CELL + 2, ROWS * CELL + 2, frameInner);
}

static void drawField() {
  for (byte x = 0; x < COLS; x++) {
    for (byte y = 0; y < ROWS; y++) {
      if (field[x][y]) drawBlock(x, y, colors[field[x][y] - 1]); else eraseBlock(x, y);
    }
  }
}

static void drawNext() {
  tft.fillRect(NEXT_X, NEXT_Y, 40, 40, BackgroundColor);
  for (byte row = 0; row < 4; row++) {
    for (byte col = 0; col < 4; col++) {
      if (cellBit(nextPiece, 0, row, col)) bevel(NEXT_X + col * CELL, NEXT_Y + 10 + row * CELL, CELL, colors[nextPiece]);
    }
  }
}

static void drawPanels() {
  tftPrint(ALEFT, "LEVEL", 8, 24, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(ALEFT, String(level), 8, 42, PrimaryColor, PrimaryColorSmooth, 28);
  tftPrint(ALEFT, "LINES", 8, 86, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(ALEFT, String(lines), 8, 104, PrimaryColor, PrimaryColorSmooth, 28);
  tftPrint(ALEFT, "Turn: move", 8, 160, SecondaryColor, SecondaryColorSmooth, 16);
  tftPrint(ALEFT, "Push: turn", 8, 178, SecondaryColor, SecondaryColorSmooth, 16);
  tftPrint(ALEFT, "BW: drop", 8, 196, SecondaryColor, SecondaryColorSmooth, 16);
  tftPrint(ALEFT, "BAND: pause", 8, 214, SecondaryColor, SecondaryColorSmooth, 16);
  tftPrint(ALEFT, "NEXT", 232, 24, ActiveColor, ActiveColorSmooth, 16);
  tft.drawRoundRect(NEXT_X - 4, NEXT_Y - 4, 48, 48, 4, FrameColor);
  tftPrint(ALEFT, "SCORE", 232, 100, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(ALEFT, String(score), 232, 118, PrimaryColor, PrimaryColorSmooth, 28);
  tftPrint(ALEFT, "BEST", 232, 160, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(ALEFT, String(tetrisFame.entry[0].score), 232, 178, PrimaryColor, PrimaryColorSmooth, 28);
  tftPrint(ALEFT, "MODE: back", 232, 214, SecondaryColor, SecondaryColorSmooth, 16);
  scoreShown = score;
  levelShown = level;
  linesShown = lines;
  bestShown = tetrisFame.entry[0].score;
}

static void updatePanels() {
  if (score != scoreShown) {
    tftReplace(ALEFT, String(scoreShown), String(score), 232, 118, PrimaryColor, PrimaryColorSmooth, BackgroundColor, 28);
    scoreShown = score;
  }
  if (lines != linesShown) {
    tftReplace(ALEFT, String(linesShown), String(lines), 8, 104, PrimaryColor, PrimaryColorSmooth, BackgroundColor, 28);
    linesShown = lines;
  }
  if (level != levelShown) {
    tftReplace(ALEFT, String(levelShown), String(level), 8, 42, PrimaryColor, PrimaryColorSmooth, BackgroundColor, 28);
    levelShown = level;
  }
  if (tetrisFame.entry[0].score != bestShown) {
    tftReplace(ALEFT, String(bestShown), String(tetrisFame.entry[0].score), 232, 178, PrimaryColor, PrimaryColorSmooth, BackgroundColor, 28);
    bestShown = tetrisFame.entry[0].score;
  }
}

static void redrawAll() {
  tft.fillScreen(BackgroundColor);
  drawFrame();
  drawField();
  drawPanels();
  drawNext();
  showPiece();
}

// ---------------------------------------------------------------- game
static void setInterval() {
  interval = level < 10 ? 800 - 70 * level : 90;
}

// A new piece at the top; false when there is no room: game over
static bool spawn() {
  cur = nextPiece;
  nextPiece = random(7);
  rot = 0;
  cx = 3;
  cy = 0;
  while (cy > -3) {  // the first filled row of the bitmap starts at the top of the field
    bool empty = true;
    for (byte col = 0; col < 4; col++) if (cellBit(cur, 0, -cy, col)) empty = false;
    if (!empty) break;
    cy--;
  }
  drawNext();
  if (!fits(cur, rot, cx, cy)) return false;
  showPiece();
  return true;
}

static void move(int dx) {
  if (!fits(cur, rot, cx + dx, cy)) return;
  hidePiece();
  cx += dx;
  showPiece();
  sfxMove();
}

static void rotate() {
  byte r = (rot + 1) % 4;
  static const int8_t kicks[] = {0, -1, 1, -2, 2};
  for (byte k = 0; k < sizeof(kicks); k++) {
    if (fits(cur, r, cx + kicks[k], cy)) {
      hidePiece();
      rot = r;
      cx += kicks[k];
      showPiece();
      sfxRotate();
      return;
    }
  }
}

// Full rows flash and disappear, the rows above come down
static void clearLines() {
  byte full[4], n = 0;
  for (int y = 0; y < ROWS; y++) {
    bool isFull = true;
    for (byte x = 0; x < COLS; x++) if (!field[x][y]) isFull = false;
    if (isFull) full[n++] = y;
  }
  if (!n) return;
  for (byte f = 0; f < 3; f++) {
    for (byte i = 0; i < n; i++) tft.fillRect(px(0), py(full[i]), COLS * CELL, CELL, f & 1 ? BackgroundColor : White);
    delay(60);
  }
  for (byte i = 0; i < n; i++) {
    for (int y = full[i]; y > 0; y--) {
      for (byte x = 0; x < COLS; x++) field[x][y] = field[x][y - 1];
    }
    for (byte x = 0; x < COLS; x++) field[x][0] = 0;
  }
  drawField();
  static const uint16_t points[] = {0, 40, 100, 300, 1200};
  score += points[n] * (level + 1);
  lines += n;
  sfxLines(n);
  if (lines / 10 != level) {
    level = lines / 10;
    setInterval();
    sfxLevel();
  }
  updatePanels();
}

// The piece becomes part of the field; false when the next one has no room
static bool lock() {
  for (byte row = 0; row < 4; row++) {
    for (byte col = 0; col < 4; col++) {
      if (!cellBit(cur, rot, row, col)) continue;
      int fy = cy + row;
      if (fy < 0) return false;  // locked above the field: game over
      field[cx + col][fy] = cur + 1;
    }
  }
  sfxLock();
  clearLines();
  return spawn();
}

static void hardDrop() {
  hidePiece();
  int from = cy;
  cy = landingY();
  score += 2 * (cy - from);
  showPiece();
  sfxDrop();
  updatePanels();
}

static void newGame() {
  memset(field, 0, sizeof(field));
  score = 0;
  lines = 0;
  level = 0;
  setInterval();
  nextPiece = random(7);
  tft.fillScreen(BackgroundColor);
  drawFrame();
  drawField();
  drawPanels();
  spawn();
  rotary = 0;
}

// Plays until the field is full (true) or MODE is pressed (false)
static bool play() {
  uint32_t next = millis() + interval;
  for (;;) {
    if (rotary) {
      move(rotary < 0 ? 1 : -1);
      rotary = 0;
    }
    if (pressed(knobPin)) rotate();
    if (pressed(bwPin)) {
      hardDrop();
      if (!lock()) return true;
      next = millis() + interval;
    }
    if (pressed(modePin)) return false;
    if (pressed(bandPin)) {
      sfxPause();
      box("PAUSED", "Push BAND or the knob", "to go on");
      while (!pressed(bandPin) && !pressed(knobPin)) {
        if (pressed(modePin)) return false;
        delay(10);
      }
      redrawAll();
      rotary = 0;
      next = millis() + interval;
    }
    if (millis() >= next) {
      next += interval;
      if (fits(cur, rot, cx, cy + 1)) {
        hidePiece();
        cy++;
        showPiece();
      } else if (!lock()) {
        return true;
      }
    }
    delay(2);
  }
}

// The field fills up with grey from the bottom, with falling tones
static void fillUp() {
  for (int y = ROWS - 1; y >= 0; y--) {
    for (byte x = 0; x < COLS; x++) bevel(px(x), py(y), CELL, GreyoutColor);
    if (y % 3 == 0) sfx(15, 200 + 40 * y);
    delay(30);
  }
  sfx(250, 120);
}

static bool startScreen() {
  tft.fillScreen(BackgroundColor);
  tft.drawRect(7, 7, 306, 226, FrameColor);
  tft.drawRect(9, 9, 302, 222, frameInner);
  tftPrint(ACENTER, "TETRIS", 160, 22, PrimaryColor, PrimaryColorSmooth, 28);
  tftPrint(ACENTER, "HALL OF FAME", 160, 56, SecondaryColor, SecondaryColorSmooth, 16);
  tetrisFame.draw(104, 76, 16);
  tftPrint(ACENTER, "Turn: move   Push: rotate   BW: drop", 160, 160, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(ACENTER, "BAND: pause   Knob: start   MODE: back", 160, 178, ActiveColor, ActiveColorSmooth, 16);
  for (byte p = 0; p < 7; p++) {  // the seven pieces in a row
    for (byte row = 0; row < 2; row++) {
      for (byte col = 0; col < 4; col++) {
        if (cellBit(p, 0, row, col)) bevel(24 + p * 40 + col * 8, 204 + row * 8, 8, colors[p]);
      }
    }
  }
  return waitForKnob();
}

static void gameOver() {
  fillUp();
  int rank = tetrisFame.enter(score);
  updatePanels();
  if (rank >= 0) box("GAME OVER", "Score " + String(score) + ", place " + String(rank + 1), "Push the knob to play again");
  else box("GAME OVER", "Score " + String(score), "Push the knob to play again");
}

static void run() {
  ghostColor = tft.alphaBlend(90, White, BackgroundColor);
  if (!startScreen()) return;
  for (;;) {
    sfxStart();
    newGame();
    if (!play()) break;  // MODE during the game
    gameOver();
    if (!waitForKnob()) break;
  }
}

}  // namespace tetris

// ============================================================================ tefman
namespace tefman {

// Maze of 31 x 21 cells of 10 px: walls, pellets, power pellets, the ghost house with its
// door and a tunnel on the middle row. The knob turns left or right relative to the way
// TEFman looks, the turn is taken at the first opening; a push turns him round.
static const byte COLS = 31, ROWS = 21, CELL = 10;
static const int FX = 5, FY = 26;
static const char *const maze[ROWS] = {
  "###############################",
  "#..............#..............#",
  "#.####.######..#..######.####.#",
  "#o####.######..#..######.####o#",
  "#.............................#",
  "#.####.##.####.#.####.##.####.#",
  "#......##.####.#.####.##......#",
  "######.##.............##.######",
  "######.####.........####.######",
  "######.####.###-###.####.######",
  "      .####.#     #.####.      ",
  "######.####.#######.####.######",
  "######.##.............##.######",
  "#......##.####.#.####.##......#",
  "#.####.##.####.#.####.##.####.#",
  "#o####...................####o#",
  "#.####.##.####.#.####.##.####.#",
  "#......##.............##......#",
  "#.####.######.###.######.####.#",
  "#.............................#",
  "###############################"
};
static char grid[ROWS][COLS];

enum { UP, RIGHT, DOWN, LEFT, NONE };
static const int8_t DX[] = {0, 1, 0, -1}, DY[] = {-1, 0, 1, 0};
enum { CHASE, SCATTER, FRIGHT, EYES, HOUSE };
enum { TURN_NONE, TURN_LEFT, TURN_RIGHT, TURN_BACK };

struct Mover {
  int x, y;    // pixels within the maze
  byte dir;
};
static Mover pac, ghost[4];
static byte ghostMode[4];
static uint32_t ghostLeave[4];   // when a ghost in the house may come out
static byte pacTurn, mouth, lives, level, fruitKind;
static bool pacStopped, fruitOn, powerVisible;
static uint16_t score, pelletsLeft, pelletsEaten;
static uint32_t frightUntil, fruitUntil, phaseStart, tick;
static bool scatter;
static byte ghostsEaten;
static uint16_t scoreShown;
static byte livesShown;

static const uint16_t WALL_COLOR = 0x2B7F, PELLET_COLOR = 0xFEB4, PAC_COLOR = 0xFFE0, DOOR_COLOR = 0xFC18;
static const uint16_t ghostColor[4] = {0xF800, 0xFC1F, 0x07FF, 0xFD20};
static const uint16_t FRIGHT_COLOR = 0x001F;

static void sfxWaka(bool a)  { sfx(10, a ? 420 : 300); }
static void sfxPower()       { sfx(25, 600); sfx(25, 800); sfx(25, 1000); }
static void sfxGhost()       { sfx(40, 1200); sfx(40, 1600); }
static void sfxFruit()       { sfx(30, 1500); sfx(30, 1800); }
static void sfxDeath()       { for (uint16_t hz = 600; hz >= 120; hz -= 60) sfx(40, hz); sfx(200, 100); }
static void sfxStart()       { sfx(60, 523); sfx(60, 659); sfx(60, 784); sfx(60, 1047); sfx(120, 784); }
static void sfxLevel()       { sfx(40, 1047); sfx(40, 1319); sfx(40, 1568); sfx(80, 2093); }

// ---------------------------------------------------------------- maze
static char cellAt(int cx, int cy) {
  if (cy < 0 || cy >= ROWS) return '#';
  cx = (cx + COLS) % COLS;
  return grid[cy][cx];
}

static bool passable(int cx, int cy, bool forGhost) {
  char c = cellAt(cx, cy);
  return c != '#' && (c != '-' || forGhost);
}

static int px(int x) { return FX + x; }
static int py(int y) { return FY + y; }

// Walls as lines between the centres of neighbouring wall cells
static void drawWalls(uint16_t color) {
  for (byte cy = 0; cy < ROWS; cy++) {
    for (byte cx = 0; cx < COLS; cx++) {
      if (grid[cy][cx] != '#') continue;
      int mx = px(cx * CELL + 4), my = py(cy * CELL + 4);
      bool any = false;
      if (cx + 1 < COLS && grid[cy][cx + 1] == '#') { tft.fillRect(mx, my, CELL, 2, color); any = true; }
      if (cy + 1 < ROWS && grid[cy + 1][cx] == '#') { tft.fillRect(mx, my, 2, CELL, color); any = true; }
      if (cx && grid[cy][cx - 1] == '#') any = true;
      if (cy && grid[cy - 1][cx] == '#') any = true;
      if (!any) tft.fillRect(mx, my, 2, 2, color);
    }
  }
}

static void drawCell(byte cx, byte cy) {
  if (grid[cy][cx] == '#') return;  // the wall lines stay, see restoreRect()
  int x0 = px(cx * CELL), y0 = py(cy * CELL);
  tft.fillRect(x0, y0, CELL, CELL, BackgroundColor);
  switch (grid[cy][cx]) {
    case '.': tft.fillRect(x0 + 4, y0 + 4, 2, 2, PELLET_COLOR); break;
    case 'o': if (powerVisible) tft.fillCircle(x0 + 4, y0 + 4, 3, PELLET_COLOR); break;
    case '-': tft.fillRect(x0, y0 + 4, CELL, 2, DOOR_COLOR); break;
  }
}

static void drawFruit() {
  int x0 = px(15 * CELL), y0 = py(12 * CELL);
  tft.fillCircle(x0 + 3, y0 + 6, 3, 0xF800);
  tft.fillCircle(x0 + 7, y0 + 5, 3, 0xF800);
  tft.drawLine(x0 + 3, y0 + 3, x0 + 6, y0, 0x07E0);
  tft.drawLine(x0 + 7, y0 + 2, x0 + 6, y0, 0x07E0);
}

static void drawWalls(uint16_t color);

// Puts the maze back under a rectangle in maze pixels: background, then the pellets and
// the door of the cells it touches. The wall lines sit 4 px inside their cells, so the
// sprites never touch them; a popup does, and gets the walls redrawn.
static void restoreRect(int x, int y, int w, int h, bool walls) {
  tft.fillRect(px(x), py(y), w, h, BackgroundColor);
  int c0 = x < 0 ? -1 : x / CELL, c1 = (x + w - 1) / CELL, r0 = max(0, y / CELL), r1 = min((int)ROWS - 1, (y + h - 1) / CELL);
  for (int cy = r0; cy <= r1; cy++) {
    for (int cx = c0; cx <= c1; cx++) {
      if (cx < 0 || cx >= COLS) continue;  // the tunnel ends
      drawCell(cx, cy);
      if (fruitOn && cx == 15 && cy == 12) drawFruit();
    }
  }
  if (walls) drawWalls(WALL_COLOR);
}

// Under a sprite at pixel x, y: one pixel of margin all round
static void restoreArea(int x, int y) {
  restoreRect(x - 1, y - 1, 12, 12, false);
}

static void drawPac() {
  int cx = px(pac.x + 4), cy = py(pac.y + 4);
  tft.fillCircle(cx, cy, 5, PAC_COLOR);
  if (mouth == 0 || pacStopped) return;
  int k = mouth == 1 ? 2 : 5;
  switch (pac.dir) {
    case RIGHT: tft.fillTriangle(cx, cy, cx + 7, cy - k, cx + 7, cy + k, BackgroundColor); break;
    case LEFT:  tft.fillTriangle(cx, cy, cx - 7, cy - k, cx - 7, cy + k, BackgroundColor); break;
    case UP:    tft.fillTriangle(cx, cy, cx - k, cy - 7, cx + k, cy - 7, BackgroundColor); break;
    case DOWN:  tft.fillTriangle(cx, cy, cx - k, cy + 7, cx + k, cy + 7, BackgroundColor); break;
  }
}

static void drawGhost(byte g) {
  int cx = px(ghost[g].x + 4), cy = py(ghost[g].y + 4);
  byte mode = ghostMode[g];
  if (mode != EYES) {
    uint16_t color = ghostColor[g];
    if (mode == FRIGHT) color = (frightUntil - millis() < 2000 && (millis() / 250) & 1) ? White : FRIGHT_COLOR;
    tft.fillCircle(cx, cy - 1, 5, color);
    tft.fillRect(cx - 5, cy - 1, 11, 6, color);
    tft.fillRect(cx - 3, cy + 4, 2, 1, BackgroundColor);  // the wavy skirt
    tft.fillRect(cx + 1, cy + 4, 2, 1, BackgroundColor);
    if (mode == FRIGHT) {
      tft.fillRect(cx - 3, cy - 2, 2, 2, PELLET_COLOR);
      tft.fillRect(cx + 1, cy - 2, 2, 2, PELLET_COLOR);
      return;
    }
  }
  tft.fillRect(cx - 4, cy - 3, 3, 3, White);  // the eyes look where the ghost goes
  tft.fillRect(cx + 1, cy - 3, 3, 3, White);
  int dx = DX[ghost[g].dir], dy = DY[ghost[g].dir];
  tft.drawPixel(cx - 3 + dx, cy - 2 + dy, 0x001F);
  tft.drawPixel(cx + 2 + dx, cy - 2 + dy, 0x001F);
}

static void drawStatus() {
  tft.fillRect(0, 0, 320, FY - 2, BackgroundColor);
  tftPrint(ALEFT, "SCORE " + String(score), 6, 4, PrimaryColor, PrimaryColorSmooth, 16);
  for (byte i = 0; i < lives; i++) tft.fillCircle(170 + i * 14, 12, 5, PAC_COLOR);
  tftPrint(ARIGHT, "LEVEL " + String(level), 314, 4, SecondaryColor, SecondaryColorSmooth, 16);
  scoreShown = score;
  livesShown = lives;
}

static void updateStatus() {
  if (score != scoreShown) {
    tftReplace(ALEFT, "SCORE " + String(scoreShown), "SCORE " + String(score), 6, 4, PrimaryColor, PrimaryColorSmooth, BackgroundColor, 16);
    scoreShown = score;
  }
  if (lives != livesShown) {
    tft.fillRect(160, 2, 80, 20, BackgroundColor);
    for (byte i = 0; i < lives; i++) tft.fillCircle(170 + i * 14, 12, 5, PAC_COLOR);
    livesShown = lives;
  }
}

static void redrawAll() {
  tft.fillScreen(BackgroundColor);
  drawWalls(WALL_COLOR);
  for (byte cy = 0; cy < ROWS; cy++) {
    for (byte cx = 0; cx < COLS; cx++) if (grid[cy][cx] == '.' || grid[cy][cx] == 'o' || grid[cy][cx] == '-') drawCell(cx, cy);
  }
  if (fruitOn) drawFruit();
  drawStatus();
  drawPac();
  for (byte g = 0; g < 4; g++) drawGhost(g);
}

// ---------------------------------------------------------------- movers
static bool aligned(const Mover &m) {
  return m.x % CELL == 0 && m.y % CELL == 0;
}

static void moveBy(Mover &m, byte dir, int step) {
  m.x += DX[dir] * step;
  m.y += DY[dir] * step;
  if (m.x < -CELL / 2) m.x += COLS * CELL;        // the tunnel
  if (m.x >= COLS * CELL - CELL / 2) m.x -= COLS * CELL;
}

static void placeMovers() {
  pac.x = 15 * CELL;
  pac.y = 15 * CELL;
  pac.dir = LEFT;
  pacTurn = TURN_NONE;
  pacStopped = false;
  mouth = 0;
  ghost[0].x = 15 * CELL; ghost[0].y = 8 * CELL; ghost[0].dir = LEFT; ghostMode[0] = CHASE;
  for (byte g = 1; g < 4; g++) {
    ghost[g].x = (11 + g * 2) * CELL;
    ghost[g].y = 10 * CELL;
    ghost[g].dir = UP;
    ghostMode[g] = HOUSE;
    ghostLeave[g] = millis() + 2000 + (g - 1) * 3500;
  }
  frightUntil = 0;
  phaseStart = millis();
  scatter = false;
}

// Target cell of a ghost, the character of each one
static void ghostTarget(byte g, int &tx, int &ty) {
  int pcx = (pac.x + 5) / CELL, pcy = (pac.y + 5) / CELL;
  byte mode = ghostMode[g];
  if (mode == EYES || mode == HOUSE) { tx = 15; ty = mode == EYES ? 10 : 8; return; }
  if (scatter) {
    static const int8_t cornerX[] = {29, 1, 29, 1}, cornerY[] = {1, 1, 19, 19};
    tx = cornerX[g]; ty = cornerY[g];
    return;
  }
  switch (g) {
    case 0: tx = pcx; ty = pcy; break;                                                   // straight at him
    case 1: tx = pcx + 4 * DX[pac.dir]; ty = pcy + 4 * DY[pac.dir]; break;             // ahead of him
    case 2: tx = pcx + random(-3, 4); ty = pcy + random(-3, 4); break;                 // roughly at him
    default:                                                                            // shy: keeps away when close
      if (abs(pcx - ghost[g].x / CELL) + abs(pcy - ghost[g].y / CELL) > 8) { tx = pcx; ty = pcy; } else { tx = 1; ty = 19; }
  }
}

static void steerGhost(byte g) {
  Mover &m = ghost[g];
  int cx = m.x / CELL, cy = m.y / CELL;
  byte mode = ghostMode[g];
  bool door = mode == EYES || mode == HOUSE;
  if (mode == EYES && cx == 15 && cy == 10) { ghostMode[g] = HOUSE; ghostLeave[g] = millis() + 1500; mode = HOUSE; }
  if (mode == HOUSE && cx == 15 && cy == 8) { ghostMode[g] = scatter ? SCATTER : CHASE; mode = ghostMode[g]; m.dir = random(2) ? LEFT : RIGHT; door = false; }
  int tx, ty;
  ghostTarget(g, tx, ty);
  byte back = (m.dir + 2) % 4;
  long bestDist = -1;
  byte bestDir = NONE;
  byte options = 0;
  for (byte d = 0; d < 4; d++) {
    if (d == back) continue;
    if (!passable(cx + DX[d], cy + DY[d], door)) continue;
    if (mode == HOUSE && cy == 10 && d == DOWN) continue;
    options++;
    long dx = cx + DX[d] - tx, dy = cy + DY[d] - ty;
    long dist = dx * dx + dy * dy;
    if (mode == FRIGHT) dist = random(1000);
    if (bestDir == NONE || dist < bestDist) { bestDist = dist; bestDir = d; }
  }
  if (!options) bestDir = back;
  m.dir = bestDir;
}

static void ghostStep(byte g) {
  Mover &m = ghost[g];
  byte mode = ghostMode[g];
  if (mode == HOUSE && millis() < ghostLeave[g]) {  // waiting: bobs up and down
    if (aligned(m)) m.dir = (tick / 10) & 1 ? UP : DOWN;
    return;
  }
  byte steps = mode == EYES ? 2 : 1;
  if (mode == FRIGHT && (tick & 1)) return;
  if (mode != FRIGHT && mode != EYES && level < 3 && tick % (level == 1 ? 8 : 12) == 0) return;
  for (byte s = 0; s < steps; s++) {
    if (aligned(m)) steerGhost(g);
    moveBy(m, m.dir, 2);
  }
}

static void pacStep() {
  if (aligned(pac)) {
    int cx = pac.x / CELL, cy = pac.y / CELL;
    if (pacTurn != TURN_NONE) {
      byte nd = pacTurn == TURN_LEFT ? (pac.dir + 3) % 4 : pacTurn == TURN_RIGHT ? (pac.dir + 1) % 4 : (pac.dir + 2) % 4;
      if (passable(cx + DX[nd], cy + DY[nd], false)) {
        pac.dir = nd;
        pacTurn = TURN_NONE;
      }
    }
    pacStopped = !passable(cx + DX[pac.dir], cy + DY[pac.dir], false);
    char c = grid[cy][cx];
    if (c == '.' || c == 'o') {
      grid[cy][cx] = ' ';
      pelletsLeft--;
      pelletsEaten++;
      score += c == 'o' ? 50 : 10;
      if (c == 'o') {
        frightUntil = millis() + max(2000, 7000 - 500 * level);
        ghostsEaten = 0;
        for (byte g = 0; g < 4; g++) {
          if (ghostMode[g] == CHASE || ghostMode[g] == SCATTER) {
            ghostMode[g] = FRIGHT;
            ghost[g].dir = (ghost[g].dir + 2) % 4;
          }
        }
        sfxPower();
      } else {
        sfxWaka(pelletsEaten & 1);
      }
      if (!fruitOn && (pelletsEaten == 70 || pelletsEaten == 170)) {
        fruitOn = true;
        fruitUntil = millis() + 9000;
        drawFruit();
      }
    }
  }
  if (!pacStopped) {
    moveBy(pac, pac.dir, 2);
    mouth = (mouth + 1) % 3;
  }
}

// ---------------------------------------------------------------- game
static void loadLevel() {
  pelletsLeft = 0;
  for (byte cy = 0; cy < ROWS; cy++) {
    for (byte cx = 0; cx < COLS; cx++) {
      grid[cy][cx] = maze[cy][cx];
      if (grid[cy][cx] == '.' || grid[cy][cx] == 'o') pelletsLeft++;
    }
  }
  grid[15][15] = ' ';  // where he starts
  pelletsLeft--;
  pelletsEaten = 0;
  fruitOn = false;
  powerVisible = true;
}

// The points for a ghost or the fruit, shown a moment where it was
static void showScoreAt(int x, int y, uint16_t points) {
  tftPrint(ACENTER, String(points), px(x + 5), py(y - 4), White, tft.alphaBlend(128, White, BackgroundColor), 16);
  delay(500);
  restoreRect(x - 18, y - 6, 46, 22, true);
}

static void die() {
  sfxDeath();
  int cx = px(pac.x + 4), cy = py(pac.y + 4);
  for (int r = 5; r >= 0; r--) {
    tft.fillCircle(cx, cy, 5, BackgroundColor);
    if (r) tft.fillCircle(cx, cy, r, PAC_COLOR);
    delay(90);
  }
  delay(300);
  lives--;
  updateStatus();
}

// One life; returns 0 when caught, 1 when the maze is empty, 2 for MODE
static byte play() {
  placeMovers();
  redrawAll();
  tick = 0;
  uint32_t next = millis();
  rotary = 0;
  for (;;) {
    if (rotary) {
      pacTurn = rotary < 0 ? TURN_RIGHT : TURN_LEFT;
      rotary = 0;
    }
    if (pressed(knobPin)) {  // turns round at once
      pac.dir = (pac.dir + 2) % 4;
      pacTurn = TURN_NONE;
      pacStopped = false;
    }
    if (pressed(modePin)) return 2;
    if (pressed(bandPin)) {
      sfx(30, 600);
      box("PAUSED", "Push BAND or the knob", "to go on");
      while (!pressed(bandPin) && !pressed(knobPin)) {
        if (pressed(modePin)) return 2;
        delay(10);
      }
      redrawAll();
      rotary = 0;
      next = millis();
    }
    if (millis() < next) {
      delay(1);
      continue;
    }
    next += 30;
    tick++;

    // Timed things: the fright, the fruit, the scatter and chase phases, blinking pellets
    if (frightUntil && millis() >= frightUntil) {
      frightUntil = 0;
      for (byte g = 0; g < 4; g++) if (ghostMode[g] == FRIGHT) ghostMode[g] = scatter ? SCATTER : CHASE;
    }
    if (fruitOn && millis() >= fruitUntil) {
      fruitOn = false;
      drawCell(15, 12);
    }
    if (millis() - phaseStart > (scatter ? 7000UL : 20000UL)) {
      scatter = !scatter;
      phaseStart = millis();
      for (byte g = 0; g < 4; g++) {
        if (ghostMode[g] == CHASE || ghostMode[g] == SCATTER) {
          ghostMode[g] = scatter ? SCATTER : CHASE;
          ghost[g].dir = (ghost[g].dir + 2) % 4;
        }
      }
    }
    if (tick % 10 == 0) {
      powerVisible = !powerVisible;
      for (byte cy = 0; cy < ROWS; cy++) for (byte cx = 0; cx < COLS; cx++) if (grid[cy][cx] == 'o') drawCell(cx, cy);
    }

    // Move everything: wipe, step, redraw
    int oldPx = pac.x, oldPy = pac.y;
    int oldGx[4], oldGy[4];
    for (byte g = 0; g < 4; g++) { oldGx[g] = ghost[g].x; oldGy[g] = ghost[g].y; }
    pacStep();
    for (byte g = 0; g < 4; g++) ghostStep(g);
    restoreArea(oldPx, oldPy);
    for (byte g = 0; g < 4; g++) restoreArea(oldGx[g], oldGy[g]);

    // Fruit and ghosts
    if (fruitOn && abs(pac.x - 15 * CELL) < 6 && abs(pac.y - 12 * CELL) < 6) {
      static const uint16_t fruitPoints[] = {100, 300, 500, 700};
      uint16_t points = fruitPoints[min(level - 1, 3)];
      score += points;
      fruitOn = false;
      sfxFruit();
      drawCell(15, 12);
      showScoreAt(15 * CELL, 12 * CELL, points);
    }
    for (byte g = 0; g < 4; g++) {
      if (abs(pac.x - ghost[g].x) >= 7 || abs(pac.y - ghost[g].y) >= 7) continue;
      if (ghostMode[g] == FRIGHT) {
        uint16_t points = 200 << ghostsEaten;
        if (ghostsEaten < 3) ghostsEaten++;
        score += points;
        ghostMode[g] = EYES;
        sfxGhost();
        showScoreAt(ghost[g].x, ghost[g].y, points);
        next = millis();
      } else if (ghostMode[g] != EYES && ghostMode[g] != HOUSE) {
        for (byte h = 0; h < 4; h++) if (h != g) restoreArea(ghost[h].x, ghost[h].y);
        drawPac();
        die();
        return 0;
      }
    }
    drawPac();
    for (byte g = 0; g < 4; g++) drawGhost(g);
    updateStatus();
    if (!pelletsLeft) return 1;
  }
}

static void levelClear() {
  sfxLevel();
  for (byte n = 0; n < 3; n++) {
    drawWalls(White);
    delay(150);
    drawWalls(WALL_COLOR);
    delay(150);
  }
}

static bool startScreen() {
  tft.fillScreen(BackgroundColor);
  tft.drawRect(7, 7, 306, 226, WALL_COLOR);
  tft.drawRect(9, 9, 302, 222, frameInner);
  tftPrint(ACENTER, "TEFMAN", 160, 22, PAC_COLOR, PAC_COLOR, 28);
  tftPrint(ACENTER, "HALL OF FAME", 160, 56, SecondaryColor, SecondaryColorSmooth, 16);
  tefmanFame.draw(104, 76, 16);
  tftPrint(ACENTER, "Turn: left or right   Push: turn round", 160, 160, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(ACENTER, "BAND: pause   Knob: start   MODE: back", 160, 178, ActiveColor, ActiveColorSmooth, 16);
  // A parade along the bottom
  pac.x = 60; pac.y = 180; pac.dir = RIGHT; mouth = 2; pacStopped = false;
  drawPac();
  for (byte g = 0; g < 4; g++) {
    ghost[g].x = 90 + g * 20; ghost[g].y = 180; ghost[g].dir = RIGHT; ghostMode[g] = CHASE;
    drawGhost(g);
  }
  for (byte i = 0; i < 6; i++) tft.fillRect(px(190 + i * 12), py(184), 2, 2, PELLET_COLOR);
  return waitForKnob();
}

static void run() {
  if (!startScreen()) return;
  for (;;) {
    score = 0;
    lives = 3;
    level = 1;
    loadLevel();
    sfxStart();
    bool leave = false;
    for (;;) {
      byte result = play();
      if (result == 2) { leave = true; break; }
      if (result == 1) {
        levelClear();
        level++;
        loadLevel();
        continue;
      }
      if (!lives) break;
    }
    if (leave) break;
    int rank = tefmanFame.enter(score);
    if (rank >= 0) box("GAME OVER", "Score " + String(score) + ", place " + String(rank + 1), "Push the knob to play again");
    else box("GAME OVER", "Score " + String(score), "Push the knob to play again");
    if (!waitForKnob()) break;
  }
}

}  // namespace tefman

// ============================================================================ invaders
namespace invaders {

// Eleven by five invaders march across the screen above four shields; the cannon at the
// bottom follows the knob, a push fires. Sprites are 12 x 8 bits, pushed through a small
// sprite buffer so a whole step of the formation stays quick.
static const byte INV_COLS = 11, INV_ROWS = 5, SW = 12, SH = 8;
static const int COL_PITCH = 16, ROW_PITCH = 14, FORM_W = INV_COLS * COL_PITCH - 4;
static const int CANNON_Y = 222, SHIELD_Y = 190, TOP = 22;
static const byte MAX_SHOTS = 3;

static const uint16_t sprites[3][2][SH] = {
  {{0x060, 0x0F0, 0x1F8, 0x36C, 0x3FC, 0x090, 0x168, 0x294}, {0x060, 0x0F0, 0x1F8, 0x36C, 0x3FC, 0x168, 0x204, 0x108}},  // squid
  {{0x204, 0x108, 0x3FC, 0x6F6, 0xFFF, 0xBFD, 0xA05, 0x090}, {0x204, 0x108, 0x3FC, 0x6F6, 0xFFF, 0x3FC, 0x402, 0x801}},  // crab
  {{0x0F0, 0x7FE, 0xFFF, 0xE67, 0xFFF, 0x39C, 0x666, 0x30C}, {0x0F0, 0x7FE, 0xFFF, 0xE67, 0xFFF, 0x198, 0x36C, 0xC03}}   // octopus
};
static const uint16_t cannonSprite[SH] = {0x060, 0x0F0, 0x0F0, 0x7FE, 0xFFF, 0xFFF, 0xFFF, 0xFFF};
static const uint16_t burstSprite[SH] = {0x488, 0x251, 0x102, 0x804, 0x102, 0x251, 0x488, 0x000};
static const uint16_t shieldShape[8] = {0x1FC, 0x3FE, 0x7FF, 0x7FF, 0x7FF, 0x7FF, 0x78F, 0x707};
static const uint16_t invColor[3] = {0x07FF, 0xFFE0, 0x07E0}, CANNON_COLOR = 0x07E0, SHIELD_COLOR = 0x07E0, UFO_COLOR = 0xF81F;

static TFT_eSprite spr = TFT_eSprite(&tft);
static bool alive[INV_ROWS][INV_COLS];
static int formX, formY, formDir;
static byte frame, aliveCount, level, lives;
static uint32_t stepAt, stepInterval, shotAt, ufoAt, burstUntil, explodeUntil;
static int cannonX, shotX, shotY, burstX, burstY;
static bool shotOn;
static struct { int x, y; bool on; } bombs[MAX_SHOTS];
static int ufoX, ufoDir;
static bool ufoOn;
static uint16_t shields[4][8];
static uint16_t score, scoreShown;
static byte livesShown, bass;

static void sfxShot()    { sfx(15, 1800); sfx(10, 1200); }
static void sfxKill()    { sfx(20, 700); sfx(20, 400); }
static void sfxUfo()     { sfx(6, 900); }
static void sfxUfoHit()  { sfx(30, 1500); sfx(30, 1900); sfx(30, 2300); }
static void sfxDeath()   { for (uint16_t hz = 500; hz >= 100; hz -= 50) sfx(35, hz); }
static void sfxLevel()   { sfx(40, 1047); sfx(40, 1319); sfx(40, 1568); sfx(80, 2093); }
static void sfxStart()   { sfx(40, 523); sfx(40, 659); sfx(60, 784); }

// ---------------------------------------------------------------- drawing
static void drawSprite(int x, int y, const uint16_t *rows, uint16_t color) {
  spr.fillSprite(BackgroundColor);
  for (byte r = 0; r < SH; r++) {
    for (byte c = 0; c < SW; c++) if ((rows[r] >> (SW - 1 - c)) & 1) spr.drawPixel(c, r, color);
  }
  spr.pushSprite(x, y);
}

static void eraseSprite(int x, int y) {
  tft.fillRect(x, y, SW, SH, BackgroundColor);
}

static int invX(byte c) { return formX + c * COL_PITCH; }
static int invY(byte r) { return formY + r * ROW_PITCH; }
static byte invType(byte r) { return r == 0 ? 0 : r < 3 ? 1 : 2; }

static void drawInvaders() {
  for (byte r = 0; r < INV_ROWS; r++) {
    for (byte c = 0; c < INV_COLS; c++) if (alive[r][c]) drawSprite(invX(c), invY(r), sprites[invType(r)][frame], invColor[invType(r)]);
  }
}

static void drawShieldBlock(byte s, byte r, byte c) {
  int x = 44 + s * 72 + c * 2, y = SHIELD_Y + r * 2;
  tft.fillRect(x, y, 2, 2, (shields[s][r] >> (10 - c)) & 1 ? SHIELD_COLOR : BackgroundColor);
}

static void drawShields() {
  for (byte s = 0; s < 4; s++) for (byte r = 0; r < 8; r++) for (byte c = 0; c < 11; c++) drawShieldBlock(s, r, c);
}

static void drawCannon() {
  drawSprite(cannonX, CANNON_Y, cannonSprite, CANNON_COLOR);
}

static void drawUfo(bool on) {
  if (!on) {
    tft.fillRect(ufoX, TOP, 16, 7, BackgroundColor);
    return;
  }
  tft.fillRoundRect(ufoX, TOP + 2, 16, 5, 2, UFO_COLOR);
  tft.fillRoundRect(ufoX + 4, TOP, 8, 4, 2, UFO_COLOR);
  tft.drawPixel(ufoX + 3, TOP + 4, BackgroundColor);
  tft.drawPixel(ufoX + 8, TOP + 4, BackgroundColor);
  tft.drawPixel(ufoX + 13, TOP + 4, BackgroundColor);
}

static void drawStatus() {
  tft.fillRect(0, 0, 320, 20, BackgroundColor);
  tftPrint(ALEFT, "SCORE " + String(score), 6, 2, PrimaryColor, PrimaryColorSmooth, 16);
  for (byte i = 0; i < lives; i++) drawSprite(160 + i * 16, 6, cannonSprite, CANNON_COLOR);
  tftPrint(ARIGHT, "LEVEL " + String(level), 314, 2, SecondaryColor, SecondaryColorSmooth, 16);
  tft.drawFastHLine(0, 20, 320, FrameColor);
  scoreShown = score;
  livesShown = lives;
}

static void updateStatus() {
  if (score != scoreShown) {
    tftReplace(ALEFT, "SCORE " + String(scoreShown), "SCORE " + String(score), 6, 2, PrimaryColor, PrimaryColorSmooth, BackgroundColor, 16);
    scoreShown = score;
  }
  if (lives != livesShown) {
    tft.fillRect(156, 2, 64, 16, BackgroundColor);
    for (byte i = 0; i < lives; i++) drawSprite(160 + i * 16, 6, cannonSprite, CANNON_COLOR);
    livesShown = lives;
  }
}

static void redrawAll() {
  tft.fillScreen(BackgroundColor);
  drawStatus();
  drawInvaders();
  drawShields();
  drawCannon();
  tft.drawFastHLine(0, 236, 320, FrameColor);
  if (ufoOn) drawUfo(true);
}

// ---------------------------------------------------------------- game
static void setStepInterval() {
  stepInterval = 40 + aliveCount * 12;
}

static void newFormation() {
  for (byte r = 0; r < INV_ROWS; r++) for (byte c = 0; c < INV_COLS; c++) alive[r][c] = true;
  aliveCount = INV_ROWS * INV_COLS;
  formX = 20;
  formY = 36 + min((int)level - 1, 5) * 8;
  formDir = 1;
  frame = 0;
  setStepInterval();
  shotOn = false;
  for (byte i = 0; i < MAX_SHOTS; i++) bombs[i].on = false;
  ufoOn = false;
  burstUntil = 0;
  stepAt = millis() + 500;
  shotAt = millis() + 1500;
  ufoAt = millis() + 15000 + random(10000);
}

static void newShields() {
  for (byte s = 0; s < 4; s++) for (byte r = 0; r < 8; r++) shields[s][r] = shieldShape[r];
}

// A shot or a bomb against the shields: true when it hit, the shield crumbles a little
static bool hitShield(int x, int y) {
  for (byte s = 0; s < 4; s++) {
    int sx = 44 + s * 72;
    if (x < sx || x >= sx + 22 || y < SHIELD_Y || y >= SHIELD_Y + 16) continue;
    byte c = (x - sx) / 2, r = (y - SHIELD_Y) / 2;
    if (!((shields[s][r] >> (10 - c)) & 1)) return false;
    for (int dr = -1; dr <= 1; dr++) {
      for (int dc = -1; dc <= 1; dc++) {
        int rr = r + dr, cc = c + dc;
        if (rr < 0 || rr > 7 || cc < 0 || cc > 10 || (dr && dc && random(2))) continue;
        shields[s][rr] &= ~(1 << (10 - cc));
        drawShieldBlock(s, rr, cc);
      }
    }
    return true;
  }
  return false;
}

static void burst(int x, int y) {
  if (burstUntil) eraseSprite(burstX, burstY);
  burstX = x;
  burstY = y;
  burstUntil = millis() + 120;
  drawSprite(x, y, burstSprite, White);
}

static void stepInvaders() {
  // The lowest and highest alive columns decide when the formation turns
  int lo = INV_COLS, hi = -1, bottom = -1;
  for (byte r = 0; r < INV_ROWS; r++) {
    for (byte c = 0; c < INV_COLS; c++) {
      if (!alive[r][c]) continue;
      if (c < lo) lo = c;
      if (c > hi) hi = c;
      if ((int)r > bottom) bottom = r;
    }
  }
  for (byte r = 0; r < INV_ROWS; r++) for (byte c = 0; c < INV_COLS; c++) if (alive[r][c]) eraseSprite(invX(c), invY(r));
  int nextX = formX + formDir * 4;
  if (nextX + lo * COL_PITCH < 4 || nextX + hi * COL_PITCH + SW > 316) {
    formDir = -formDir;
    formY += 8;
  } else {
    formX = nextX;
  }
  frame ^= 1;
  drawInvaders();
  static const uint16_t notes[] = {110, 98, 87, 78};
  sfx(aliveCount > 20 ? 25 : 15, notes[bass]);
  bass = (bass + 1) & 3;
}

static void fireBomb() {
  byte tries = 0;
  while (tries++ < 10) {
    byte c = random(INV_COLS);
    for (int r = INV_ROWS - 1; r >= 0; r--) {
      if (!alive[r][c]) continue;
      for (byte i = 0; i < MAX_SHOTS; i++) {
        if (bombs[i].on) continue;
        bombs[i].on = true;
        bombs[i].x = invX(c) + 5;
        bombs[i].y = invY(r) + SH;
        return;
      }
      return;
    }
  }
}

static void loseLife() {
  sfxDeath();
  for (byte n = 0; n < 4; n++) {
    drawSprite(cannonX, CANNON_Y, burstSprite, n & 1 ? 0xF800 : White);
    delay(120);
  }
  eraseSprite(cannonX, CANNON_Y);
  lives--;
  updateStatus();
  for (byte i = 0; i < MAX_SHOTS; i++) {
    if (bombs[i].on) tft.fillRect(bombs[i].x, bombs[i].y, 2, 6, BackgroundColor);
    bombs[i].on = false;
  }
  if (shotOn) tft.fillRect(shotX, shotY, 2, 6, BackgroundColor);
  shotOn = false;
  delay(600);
  cannonX = 154;
  drawCannon();
}

// One wave; 0 = cannon lost (lives left), 1 = wave cleared, 2 = MODE, 3 = invaded
static byte play() {
  cannonX = 154;
  redrawAll();
  rotary = 0;
  uint32_t next = millis();
  bool knobWasDown = true;
  for (;;) {
    if (pressed(modePin)) return 2;
    if (pressed(bandPin)) {
      sfx(30, 600);
      box("PAUSED", "Push BAND or the knob", "to go on");
      while (!pressed(bandPin) && !pressed(knobPin)) {
        if (pressed(modePin)) return 2;
        delay(10);
      }
      redrawAll();
      rotary = 0;
      next = millis();
      knobWasDown = true;
    }
    if (millis() < next) {
      delay(1);
      continue;
    }
    next += 20;

    // The cannon
    if (rotary) {
      int nx = constrain(cannonX + (rotary < 0 ? 6 : -6), 2, 306);
      rotary = 0;
      if (nx != cannonX) {
        eraseSprite(cannonX, CANNON_Y);
        cannonX = nx;
        drawCannon();
      }
    }
    bool knobDown = digitalRead(knobPin) == LOW;
    if (knobDown && !knobWasDown && !shotOn) {
      shotOn = true;
      shotX = cannonX + 5;
      shotY = CANNON_Y - 6;
      sfxShot();
    }
    knobWasDown = knobDown;

    // The shot
    if (shotOn) {
      tft.fillRect(shotX, shotY, 2, 6, BackgroundColor);
      shotY -= 6;
      bool gone = shotY < TOP;
      if (!gone && hitShield(shotX, shotY)) gone = true;
      if (!gone && ufoOn && shotY <= TOP + 7 && shotX >= ufoX - 1 && shotX < ufoX + 17) {
        uint16_t points = 50 * (1 + random(6));
        score += points;
        drawUfo(false);
        ufoOn = false;
        sfxUfoHit();
        tftPrint(ACENTER, String(points), ufoX + 8, TOP, White, White, 16);
        burstUntil = millis() + 400;  // the number goes with the next burst wipe
        burstX = ufoX - 6;
        burstY = TOP;
        gone = true;
      }
      if (!gone) {
        for (byte r = 0; r < INV_ROWS && !gone; r++) {
          for (byte c = 0; c < INV_COLS; c++) {
            if (!alive[r][c]) continue;
            int ix = invX(c), iy = invY(r);
            if (shotX + 1 < ix || shotX > ix + SW - 1 || shotY + 5 < iy || shotY > iy + SH - 1) continue;
            alive[r][c] = false;
            aliveCount--;
            setStepInterval();
            score += (3 - invType(r)) * 10;
            eraseSprite(ix, iy);
            burst(ix, iy);
            sfxKill();
            gone = true;
            break;
          }
        }
      }
      if (!gone) {
        for (byte i = 0; i < MAX_SHOTS; i++) {  // shot meets bomb: both go
          if (!bombs[i].on || abs(bombs[i].x - shotX) > 2 || abs(bombs[i].y - shotY) > 6) continue;
          tft.fillRect(bombs[i].x, bombs[i].y, 2, 6, BackgroundColor);
          bombs[i].on = false;
          gone = true;
        }
      }
      if (gone) shotOn = false; else tft.fillRect(shotX, shotY, 2, 6, White);
    }

    // The bombs
    for (byte i = 0; i < MAX_SHOTS; i++) {
      if (!bombs[i].on) continue;
      tft.fillRect(bombs[i].x, bombs[i].y, 2, 6, BackgroundColor);
      bombs[i].y += 3;
      bool gone = bombs[i].y > 230 || hitShield(bombs[i].x, bombs[i].y + 5);
      if (!gone && bombs[i].y + 5 >= CANNON_Y && bombs[i].x >= cannonX - 1 && bombs[i].x < cannonX + SW) {
        loseLife();
        return 0;
      }
      if (gone) bombs[i].on = false; else tft.fillRect(bombs[i].x, bombs[i].y, 2, 6, 0xFBE0);
    }
    if (millis() >= shotAt) {
      fireBomb();
      shotAt = millis() + 400 + random(900) - min(level * 60, 300);
    }

    // The formation
    if (millis() >= stepAt) {
      stepAt += stepInterval;
      stepInvaders();
      for (byte r = 0; r < INV_ROWS; r++) {
        for (byte c = 0; c < INV_COLS; c++) if (alive[r][c] && invY(r) + SH >= SHIELD_Y + 16) return 3;
      }
      if (!aliveCount) return 1;
    }

    // The ufo
    if (ufoOn) {
      if (frame == 0 && (millis() / 20) % 6 == 0) sfxUfo();
      drawUfo(false);
      ufoX += ufoDir * 2;
      if (ufoX < -16 || ufoX > 320) ufoOn = false; else drawUfo(true);
    } else if (millis() >= ufoAt && aliveCount > 8) {
      ufoOn = true;
      ufoDir = random(2) ? 1 : -1;
      ufoX = ufoDir > 0 ? -16 : 320;
      ufoAt = millis() + 20000 + random(15000);
    }

    if (burstUntil && millis() >= burstUntil) {
      tft.fillRect(burstX, burstY, 28, 16, BackgroundColor);
      burstUntil = 0;
    }
    updateStatus();
  }
}

static bool startScreen() {
  tft.fillScreen(BackgroundColor);
  tft.drawRect(7, 7, 306, 226, FrameColor);
  tft.drawRect(9, 9, 302, 222, frameInner);
  tftPrint(ACENTER, "SPACE INVADERS", 160, 22, PrimaryColor, PrimaryColorSmooth, 28);
  tftPrint(ACENTER, "HALL OF FAME", 160, 56, SecondaryColor, SecondaryColorSmooth, 16);
  invadersFame.draw(104, 76, 16);
  tftPrint(ACENTER, "Turn: move   Push: fire   BAND: pause", 160, 160, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(ACENTER, "Knob: start   MODE: back", 160, 178, ActiveColor, ActiveColorSmooth, 16);
  for (byte t = 0; t < 3; t++) {
    drawSprite(100 + t * 40, 204, sprites[t][0], invColor[t]);
    tftPrint(ALEFT, String((3 - t) * 10), 116 + t * 40, 202, ActiveColor, ActiveColorSmooth, 16);
  }
  ufoX = 40;
  drawUfo(true);
  tftPrint(ALEFT, "?", 60, 202, ActiveColor, ActiveColorSmooth, 16);
  drawSprite(240, 204, cannonSprite, CANNON_COLOR);
  return waitForKnob();
}

static void run() {
  spr.setColorDepth(16);
  spr.createSprite(SW, SH);
  if (startScreen()) {
    for (;;) {
      score = 0;
      lives = 3;
      level = 1;
      newShields();
      newFormation();
      sfxStart();
      bool leave = false;
      for (;;) {
        byte result = play();
        if (result == 2) { leave = true; break; }
        if (result == 1) {
          sfxLevel();
          delay(800);
          level++;
          newShields();
          newFormation();
        } else if (result == 3) {
          lives = 0;
          updateStatus();
        }
        if (!lives) break;  // after a lost life the wave simply goes on
      }
      if (leave) break;
      int rank = invadersFame.enter(score);
      if (rank >= 0) box("GAME OVER", "Score " + String(score) + ", place " + String(rank + 1), "Push the knob to play again");
      else box("GAME OVER", "Score " + String(score), "Push the knob to play again");
      if (!waitForKnob()) break;
    }
  }
  spr.deleteSprite();
}

}  // namespace invaders

// ============================================================================ menu
// Four cards to choose from; the knob moves, a push starts, MODE goes back to the radio
static void drawBits(int x, int y, const uint16_t *rows, byte width, byte height, byte scale, uint16_t color) {
  for (byte r = 0; r < height; r++) {
    for (byte c = 0; c < width; c++) if ((rows[r] >> (width - 1 - c)) & 1) tft.fillRect(x + c * scale, y + r * scale, scale, scale, color);
  }
}

static void drawCard(byte i, bool selected) {
  int x = 28 + (i & 1) * 140, y = 42 + (i >> 1) * 88;
  tft.fillRoundRect(x, y, 124, 80, 8, BackgroundColor);
  tft.drawRoundRect(x, y, 124, 80, 8, selected ? PrimaryColor : FrameColor);
  tft.drawRoundRect(x + 1, y + 1, 122, 78, 7, selected ? PrimaryColor : frameInner);
  const char *name;
  uint16_t best;
  switch (i) {
    case 0: {  // a little snake with an apple
      static const int8_t sx[] = {0, 1, 2, 2, 2, 3, 4}, sy[] = {2, 2, 2, 1, 0, 0, 0};
      for (byte k = 0; k < 7; k++) tft.fillRoundRect(x + 10 + sx[k] * 8, y + 44 + sy[k] * 8, 8, 8, 2, k == 6 ? PrimaryColor : (k & 1 ? SecondaryColor : tft.alphaBlend(170, SecondaryColor, BackgroundColor)));
      tft.fillCircle(x + 10 + 6 * 8 + 4, y + 44 + 4, 3, SignificantColor);
      name = "SNAKE";
      best = snakeFame.entry[0].score;
    } break;
    case 1: {  // a T and an L
      static const int8_t tx[] = {0, 1, 2, 1}, ty[] = {0, 0, 0, 1};
      for (byte k = 0; k < 4; k++) bevel(x + 10 + tx[k] * 9, y + 44 + ty[k] * 9, 9, tetris::colors[2]);
      static const int8_t lx[] = {4, 4, 4, 5}, ly[] = {0, 1, 2, 2};
      for (byte k = 0; k < 4; k++) bevel(x + 10 + lx[k] * 9, y + 42 + ly[k] * 9, 9, tetris::colors[6]);
      name = "TETRIS";
      best = tetrisFame.entry[0].score;
    } break;
    case 2: {  // TEFman chasing a pellet, a ghost behind him
      tft.fillCircle(x + 18, y + 56, 8, tefman::PAC_COLOR);
      tft.fillTriangle(x + 18, y + 56, x + 28, y + 50, x + 28, y + 62, BackgroundColor);
      tft.fillRect(x + 34, y + 55, 3, 3, tefman::PELLET_COLOR);
      tft.fillCircle(x + 48, y + 54, 7, tefman::ghostColor[0]);
      tft.fillRect(x + 41, y + 54, 15, 8, tefman::ghostColor[0]);
      tft.fillRect(x + 44, y + 51, 3, 3, White);
      tft.fillRect(x + 50, y + 51, 3, 3, White);
      name = "TEFMAN";
      best = tefmanFame.entry[0].score;
    } break;
    default: {  // a crab and the cannon
      drawBits(x + 8, y + 44, invaders::sprites[1][0], 12, 8, 2, invaders::invColor[1]);
      drawBits(x + 36, y + 56, invaders::cannonSprite, 12, 8, 1, invaders::CANNON_COLOR);
      name = "INVADERS";
      best = invadersFame.entry[0].score;
    }
  }
  tftPrint(ACENTER, name, x + 62, y + 6, PrimaryColor, PrimaryColorSmooth, 28);
  tftPrint(ALEFT, "BEST", x + 64, y + 42, ActiveColor, ActiveColorSmooth, 16);
  tftPrint(ALEFT, String(best), x + 64, y + 58, PrimaryColor, PrimaryColorSmooth, 16);
}

static void drawMenu(byte sel) {
  tft.fillScreen(BackgroundColor);
  tftPrint(ACENTER, "GAMES", 160, 6, PrimaryColor, PrimaryColorSmooth, 28);
  for (byte i = 0; i < 4; i++) drawCard(i, sel == i);
  tftPrint(ACENTER, "Turn: choose   Push: play   MODE: back", 160, 220, ActiveColor, ActiveColorSmooth, 16);
}

void GamesMenu(byte knob, byte mode, byte bw, byte band) {
  knobPin = knob;
  modePin = mode;
  bwPin = bw;
  bandPin = band;
  morseStop();
  randomSeed(micros());
  frameInner = tft.alphaBlend(90, FrameColor, BackgroundColor);
  snakeFame.load();
  tetrisFame.load();
  tefmanFame.load();
  invadersFame.load();
  byte sel = 0;
  drawMenu(sel);
  bool modeHeld = digitalRead(modePin) == LOW;  // still held from the long press that opened the menu
  rotary = 0;
  for (;;) {
    if (modeHeld) {
      if (digitalRead(modePin) == HIGH) modeHeld = false;
    } else if (pressed(modePin)) {
      break;
    }
    if (rotary) {
      byte old = sel;
      sel = (sel + (rotary < 0 ? 1 : 3)) % 4;
      rotary = 0;
      sfx(12, 1200);
      drawCard(old, false);
      drawCard(sel, true);
    }
    if (pressed(knobPin)) {
      switch (sel) {
        case 0: snake::run(); break;
        case 1: tetris::run(); break;
        case 2: tefman::run(); break;
        default: invaders::run(); break;
      }
      drawMenu(sel);
      rotary = 0;
    }
    delay(5);
  }
  rotary = 0;
}
