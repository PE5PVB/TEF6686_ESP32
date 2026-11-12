#ifndef TFT_PANEL_H
#define TFT_PANEL_H
#include <TFT_eSPI.h>

// The panel size is a runtime setting (Main settings -> Device -> ARS display), so this
// subclass exposes what TFT_eSPI only accepts in its constructor. Standard panels are
// 240 x 320 (landscape at rotation 3 / 1, BGR); the ARS panel is 320 x 240 (landscape
// at rotation 0 / 2, RGB).
class TFTPanel : public TFT_eSPI {
  public:
    using TFT_eSPI::TFT_eSPI;
    void setPanelSize(int16_t w, int16_t h) {
      _init_width = _width = w;
      _init_height = _height = h;
      resetViewport();
    }
};
#endif
