[![Build Status](https://travis-ci.com/nilnull/AnimatedTemperatureIcon.svg?branch=master)](https://travis-ci.com/nilnull/AnimatedTemperatureIcon)

# Animated Temperature Icon
  ``Show temperature like a boss on tft screens``

AnimatedTemperatureIcon is a lightweight library for arduino to show temperature with animation on TFT Screens

This is what I made for my self for fun and shared in case if anyone wants to use.


## Compatible Hardware

I just tried TTGO T-Display, you need to change defined sizes for other screen sizes  

## Dependencies

Arduino TFT graphics library 

## Settings

| property            | default value  | description                                                          |
|---------------------|----------------|----------------------------------------------------------------------|
| TEXT_COLOR          | TFT_WHITE      | Color of texts                                                       |
| BAR_COLOUR          | 0x4228         | Color of vertical bar                                                |   
| BAR_WIDTH           | 5              | Width of vertical bar                                                |
| BAR_HEIGHT          | 83             | Height of vertical bar                                               |
| BAR_GAP             | 7              | Gap between vertical bar and top of image                            |
| BAR_CIRCLE_R        | 9.5            | Radius of circle                                                     |
| ACCEPTABLE_DIFF     | 1              | if the difference be less than this number it would not change       |
| SPEED               | 10             | Speed of bar animation                                               |
| MAX_TEMP            | 40             | Maximum temperature                                                  |
| MIN_TEMP            | 2              | Minimum temperature                                                  |
| IMAGE_WIDTH         | 37             | Width of image                                                       |
| IMAGE_HEIGHT        | 118            | height of image                                                      |


## License

This code is released under the MIT License.
