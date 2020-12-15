#include "TemperatureIcon.h"

// stuff for the screen
TFT_eSPI tft = TFT_eSPI(135, 240);
TFT_eSprite spr = TFT_eSprite(&tft);
TFTDisplay tftDisplay = TFTDisplay(&tft);
TemperatureIcon temperatureIcon(&tft, &spr, 200, 10);

////////////////////////////////////////
void setup()
{
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(1);
    Serial.begin(115200);
    temperatureIcon.init();
}

void loop()
{
      temperatureIcon.draw(random(2,40));
      delay(2000);
}