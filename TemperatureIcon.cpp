#include "TemperatureIcon.h"
// Font attached to this sketch
#include "NotoSansBold36.h"
#define AA_FONT_LARGE NotoSansBold36
// Jpeg image array attached to this sketch
#include "temperature.h"

///////////////////////////////////////////////////////////////////////SPRITE
#define TEXT_COLOR TFT_WHITE
#define BAR_COLOUR 0x4228
#define BAR_WIDTH 5
#define BAR_HEIGHT 83
#define BAR_GAP 7
#define BAR_CIRCLE_R 9.5
#define ACCEPTABLE_DIFF 1
#define SPEED 10
#define MAX_TEMP 40
#define MIN_TEMP 2

#define IMAGE_WIDTH 37
#define IMAGE_HEIGHT 118

uint16_t number_warper_width;
float lastNumber = 0;
float barCenterX = 0;
float barTop = 0;
float tempdegree = MAX_TEMP - MIN_TEMP;
float pixelperdegree = 2;
/////////////////////////////////////////////////////////////////////////////

TemperatureIcon::~TemperatureIcon()
{
}

TemperatureIcon::TemperatureIcon(TFT_eSPI *tft, TFT_eSprite *spr, int16_t x, int16_t y)
{
  _tft = tft;
  _spr = spr;
  this->x = x;
  this->y = y;
  barCenterX = this->x + IMAGE_WIDTH / 2 - BAR_WIDTH / 2;
  barTop = this->y + BAR_GAP;
  tempdegree = MAX_TEMP - MIN_TEMP;
  pixelperdegree = BAR_HEIGHT / tempdegree;
}
TemperatureIcon::TemperatureIcon(TFT_eSPI *tft, TFT_eSprite *spr, int target, int16_t x, int16_t y)
{
  _tft = tft;
  _spr = spr;
  this->x = x;
  this->y = y;
  this->targetValue = target;
  barCenterX = this->x + IMAGE_WIDTH / 2 - BAR_WIDTH / 2;
  barTop = this->y + BAR_GAP;
  tempdegree = MAX_TEMP - MIN_TEMP;
  pixelperdegree = BAR_HEIGHT / tempdegree;
}

void TemperatureIcon::init()
{
  /////////////////////////////////////////////////////////SPRITE
  // Load the font and create the Sprite for reporting the value
  _spr->loadFont(AA_FONT_LARGE);
  _spr->setTextSize(.8);
  number_warper_width = _spr->textWidth("77.7");
  _spr->createSprite(number_warper_width, _spr->fontHeight());
  _spr->fillSprite(TFT_BLACK);
  _spr->setTextColor(TEXT_COLOR, TFT_BLACK);
  _spr->setTextDatum(MC_DATUM);
  _spr->setTextPadding(number_warper_width);
  _tft->setPivot(this->x / 2, IMAGE_HEIGHT / 2);
  // Push signature symbol image

  _tft->setTextColor(TEXT_COLOR, TFT_BLACK);
  _tft->setTextDatum(MC_DATUM);
  this->drawEmptySymbol();
  this->drawTargetValue();
}

void TemperatureIcon::setTargetValue(int val)
{
  this->targetValue = val;
  this->drawEmptySymbol();
  this->drawTargetValue();
  this->drawNumber(val);
}

int TemperatureIcon::getTargetValue()
{
  return this->targetValue;
}

void TemperatureIcon::drawTargetValue()
{
  //Draw Center Line
  _tft->fillRoundRect(this->x, (barTop + 1) + (MAX_TEMP - this->targetValue) * pixelperdegree, 20, 1, 1, TFT_WHITE);
  // Plot the label text
}

uint16_t TemperatureIcon::getColour(float num)
{
  uint8_t r, g, b;
  if (num < targetValue)
  {
    r = map(num, targetValue, MAX_TEMP, 255, 0);
    g = 180;
    b = map(num, targetValue, MAX_TEMP, 0, 30);
    return _tft->color565(r, g, b);
  }
  else
  {
    r = map(num, targetValue, MAX_TEMP, 0, 255);
    g = 100;
    b = map(num, targetValue, MAX_TEMP, 255, 0);
    return _tft->color565(r, g, b);
  }
}

void TemperatureIcon::drawEmptySymbol()
{
  _tft->pushImage(this->x, this->y, IMAGE_WIDTH, IMAGE_HEIGHT, image_data_temperature);
  _tft->fillCircle(this->x, this->y + IMAGE_HEIGHT + IMAGE_WIDTH / 2, BAR_CIRCLE_R, 0x04bc);
 
}

/*
void colorgradient(int x, int y, int w, int h, int percent)
{
    tft.drawRect(x, y, w, h, TFT_BLACK);
    for (int row = 1; row < h - 1; row++) {
        tft.drawFastHLine(x + 1, y + row, w - 2, temp2color(row, 0, h));
    }
}
*/
bool TemperatureIcon::tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
  // Stop further decoding as image is running off bottom of screen
  if (y >= _tft->height())
    return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  _tft->pushImage(x, y, w, h, bitmap);

  // Return 1 to decode next block
  return 1;
}

bool TemperatureIcon::draw(float value)
{
  if (this->checkBound(value, lastNumber))
  {

    int newNumber = this->getValidNumber(value);
    int prevNumber = lastNumber;
    bool showNext = true;
    int animationCount = 0;

    int target = MAX_TEMP;
    if (newNumber <= prevNumber)
    {
      target = MIN_TEMP;
    }
    // animationCount to avoid infinitive loop
    while (showNext && animationCount < 30)
    {
      animationCount++;
      showNext = this->drawNumber(target);
      target = (target + newNumber) / 2;
      Serial.printf("NUMBER %f  --- DIFF : %i ",this->calculateDelay(abs(target-newNumber)), target-newNumber);
      delay(this->calculateDelay(abs(target-newNumber)) * SPEED );
    }
    this->drawNumber(value);
  }
  this->drawExactDegree(value);
  return true;
}
float TemperatureIcon::calculateDelay(float t)
{
    float sqt = t * t;
    return sqt / (2.0f * (sqt - t) + 1.0f);
}

bool TemperatureIcon::checkBound(float newValue, float prevValue)
{
  return !isnan(newValue) && (newValue < prevValue - ACCEPTABLE_DIFF || newValue > prevValue + ACCEPTABLE_DIFF);
}

int TemperatureIcon::getValidNumber(float number)
{
  int val = number;
  if (val < MIN_TEMP)
    return MIN_TEMP;
  else if (val > MAX_TEMP)
    return MAX_TEMP;
  return val;
}

void TemperatureIcon::drawExactDegree(float value)
{
  _tft->drawString(String(value, 2) + "(oC)", this->x - number_warper_width / 2, this->y + (IMAGE_HEIGHT / 2) + 20, 2);
}
bool TemperatureIcon::drawNumber(float value)
{
  int newNumber = value;
  int prevNumber = lastNumber;
  uint16_t colo = getColour(value);

  if (!this->checkBound(value, lastNumber) || newNumber == prevNumber)
  {
    Serial.println("EQUAL");
    return false;
  }
  if (newNumber > MAX_TEMP)
  {
    Serial.println("BIGGGGG...............");
    newNumber = MAX_TEMP;
  }
  else if (newNumber < MIN_TEMP)
  {
    Serial.println("SMALLLL.................");
    newNumber = MIN_TEMP;
  }

  Serial.printf("[Last NUMB %f : NEW: %f \n", prevNumber, newNumber);

  while (newNumber != prevNumber)
  {
    Serial.printf("  ---  [Last NUMB %u : NEW: %u  ---- %f \n", prevNumber, newNumber, number_warper_width);
    if (prevNumber < newNumber)
    {
      prevNumber++;
    }
    else
    {
      prevNumber--;
    }
    float degHeight = ((MAX_TEMP - newNumber) * pixelperdegree);
    _spr->drawNumber(newNumber, number_warper_width / 2, this->y + (IMAGE_HEIGHT / 2));
    _spr->pushSprite(this->x - (number_warper_width), IMAGE_HEIGHT / 2 - this->y);
    _tft->fillRoundRect(barCenterX, barTop + 1 + degHeight, BAR_WIDTH, BAR_HEIGHT - degHeight, 1, colo);
    _tft->fillRoundRect(barCenterX, barTop, BAR_WIDTH, degHeight, 1, TFT_LIGHTGREY);
    Serial.printf(" Temp Deg:%f , pixeldeg %f , barheight : %f ", tempdegree, pixelperdegree, degHeight);
  }
  _tft->fillCircle(this->x + (IMAGE_WIDTH / 2), this->y + IMAGE_HEIGHT - (IMAGE_WIDTH / 2), BAR_CIRCLE_R, colo);
  lastNumber = value;
  return true;
}
