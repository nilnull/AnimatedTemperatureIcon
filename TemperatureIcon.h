#ifndef ARDUINO_TEMPRATUREICON_H
#define ARDUINO_TEMPRATUREICON_H
#include <Arduino.h>
#include <TFT_eSPI.h>

class TemperatureIcon
{

private:
	bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap);
	bool drawNumber(float value);
	uint16_t getColour(float num);
	void drawEmptySymbol();
	int getValidNumber(float number);
	float calculateDelay(float t);
	TFT_eSPI *_tft;
	TFT_eSprite *_spr;
	int16_t x;
	int16_t y;
	float currentValue;
	int targetValue = 23;

public:
	TemperatureIcon(TFT_eSPI *tft, TFT_eSprite *spr, int16_t x, int16_t y);
	TemperatureIcon(TFT_eSPI *tft, TFT_eSprite *spr, int targetValue, int16_t x, int16_t y);
	bool checkBound(float newValue, float prevValue);
	bool draw(float value);
	void drawExactDegree(float value);
	void init();
	void setTargetValue(int val);
	int getTargetValue();
	void drawTargetValue();
	~TemperatureIcon();

};
#endif
