#include "interfaces/ScreenInterface.h"

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include "config.h"
#include "tools/debug.h"


namespace ScreenInterface {
    TFT_eSPI* tft = nullptr;

    void initTFT_eSPI() {
        tft = new TFT_eSPI();

        PRINTDBG("Initializing tft...");
        tft->init();
        PRINTDBG("TFT initialized!");
        tft->setRotation(0);
        tft->fillScreen(TFT_BLACK);
    }

    void my_print(lv_log_level_t level, const char *buf) {
        LV_UNUSED(level);
        PRINTDBG(buf);
    }

    void initLVGL() {

    }
    
    void begin() {
        initTFT_eSPI();
        initLVGL();
    }
}