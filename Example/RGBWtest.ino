#include "SK6812RGBW.h"

#define NUM_LEDS 60
/*
    Note. Library uses SPI1
    Connect the SK6812RGBW data input to MOSI on your board.

*/
SK6812RGBW strip = SK6812RGBW(NUM_LEDS);
// Note. Gamma is not really supported in the library, its only included as some functions used in this example require Gamma
uint8_t LEDGamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
    10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
    25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
    37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
    51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
    69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
    90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
    115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
    144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
    177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
    215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

void setup()
{
    strip.begin();// Sets up the SPI
    strip.show();// Clears the strip, as by default the strip data is set to all LED's off.
    strip.setBrightness(255);
}

void loop()
{
   colorWipe(strip.Color(255, 0, 0, 0), 15); // Red
    colorWipe(strip.Color(0, 0, 0, 0), 15); // off
    colorWipe(strip.Color(0, 255, 0, 0), 15); // Green
    colorWipe(strip.Color(0, 0, 0, 0), 15); // off
    colorWipe(strip.Color(0, 0, 255, 0), 15); // Blue
    colorWipe(strip.Color(0, 0, 0, 0), 15); // off
    colorWipe(strip.Color(0, 0, 0, 255), 15); // White
    colorWipe(strip.Color(0, 0, 0, 0), 15); // off
    colorWipe(strip.Color(200, 0, 0, 255), 15); // Warm White
    colorWipe(strip.Color(0, 0, 0, 0), 15); // off
    colorWipe(strip.Color(0, 0, 100, 255), 15); // Cold White

  rainbow(10,0);
   
        rainbowCycle(10,25);
      
      theaterChase(strip.Color(255, 0, 0,0), 60); // Red
           
        theaterChase(strip.Color(0, 255, 0,0), 60); // Green
      theaterChase(strip.Color(0, 0, 255,0), 60); // Blue
        theaterChase(strip.Color(0, 0, 0,255), 60); // White
       
        theaterChaseRainbow(60,0);
       
        whiteOverRainbow(20,75,5);
         
       pulseWhite(15);
       pulseWhite(15);
       pulseWhite(15);
       pulseWhite(15);
       delay(250);
       
       fullWhite();
       delay(250);
           
        rainbowFade2White(10,3,1);


    
}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait)
{
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}


void rainbow(uint8_t wait,uint8_t white) {
    uint16_t i, j;

    for (j = 0; j < 256; j++) {
        for (i = 0; i < strip.numPixels(); i++)
        {
            strip.setPixelColor(i, Wheel((i + j),white ));
        }
        strip.show();
        delay(wait);
    }
}



    // Slightly different, this makes the rainbow equally distributed throughout
    void rainbowCycle(uint8_t wait,uint8_t white)
    {
    uint16_t i, j;

    for(j=0; j<256*5; j++)
    { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++)
    {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j),white ));
    }
    strip.show();
    delay(wait);
    }
    }

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos,uint8_t white)
{
    if (WheelPos < 85)
    {
        return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,white);
    }
    else
    {
        if (WheelPos < 170)
        {
            WheelPos -= 85;
            return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,white);
        }
        else
        {
            WheelPos -= 170;
            return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,white);
        }
    }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
    for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
        for (int q = 0; q < 3; q++) {
            for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
                strip.setPixelColor(i + q, c);  //turn every third pixel on
            }
            strip.show();

            delay(wait);

            for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
                strip.setPixelColor(i + q, 0);      //turn every third pixel off
            }
        }
    }

}


//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait, uint8_t white) {
    for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
        for (int q = 0; q < 3; q++) {
            for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
                strip.setPixelColor(i + q, Wheel( (i + j) % 255 , white)); //turn every third pixel on
            }
            strip.show();

            delay(wait);

            for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
                strip.setPixelColor(i + q, 0);      //turn every third pixel off
            }
        }
    }
}

void pulseWhite(uint8_t wait) {
    for (int j = 0; j < 256 ; j++) {
        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0,0,0, LEDGamma[j] ) );
        }
        delay(wait);
        strip.show();
    }

    for (int j = 255; j >= 0 ; j--) {
        for (uint16_t i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0,0,0, LEDGamma[j] ) );
        }
        delay(wait);
        strip.show();
    }
}


void rainbowFade2White(uint8_t wait, int rainbowLoops, int whiteLoops) {
    float fadeMax = 100.0;
    int fadeVal = 0;
    uint32_t wheelVal;
    int redVal, greenVal, blueVal;

    for (int k = 0 ; k < rainbowLoops ; k ++) {

        for (int j = 0; j < 256; j++) { // 5 cycles of all colors on wheel

            for (int i = 0; i < strip.numPixels(); i++) {

                wheelVal = Wheel(((i * 256 / strip.numPixels()) + j) & 255,0);

                redVal = red(wheelVal) * float(fadeVal / fadeMax);
                greenVal = green(wheelVal) * float(fadeVal / fadeMax);
                blueVal = blue(wheelVal) * float(fadeVal / fadeMax);

                strip.setPixelColor( i, strip.Color( redVal, greenVal, blueVal,0 ) );

            }

            //First loop, fade in!
            if (k == 0 && fadeVal < fadeMax - 1) {
                fadeVal++;
            }

            //Last loop, fade out!
            else if (k == rainbowLoops - 1 && j > 255 - fadeMax ) {
                fadeVal--;
            }

            strip.show();
            delay(wait);
        }

    }



    delay(500);


    for (int k = 0 ; k < whiteLoops ; k ++) {

        for (int j = 0; j < 256 ; j++) {

            for (uint16_t i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(0,0,0, LEDGamma[j] ) );
            }
            strip.show();
            delay(wait);
        }

        delay(2000);
        for (int j = 255; j >= 0 ; j--) {

            for (uint16_t i = 0; i < strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(0,0,0, LEDGamma[j]) );
            }
            strip.show();
            delay(wait);
        }
    }

    delay(500);
}

void whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength ) {

    if (whiteLength >= strip.numPixels()) whiteLength = strip.numPixels() - 1;

    int head = whiteLength - 1;
    int tail = 0;

    int loops = 3;
    int loopNum = 0;

    static unsigned long lastTime = 0;


    while (true) {
        for (int j = 0; j < 256; j++) {
            for (uint16_t i = 0; i < strip.numPixels(); i++) {
                if ((i >= tail && i <= head) || (tail > head && i >= tail) || (tail > head && i <= head) ) {
                    strip.setPixelColor(i, strip.Color(0,0,0,255 ) );
                }
                else {
                    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255,0));
                }

            }

            if (millis() - lastTime > whiteSpeed) {
                head++;
                tail++;
                if (head == strip.numPixels()) {
                    loopNum++;
                }
                lastTime = millis();
            }

            if (loopNum == loops) return;

            head %= strip.numPixels();
            tail %= strip.numPixels();
            strip.show();
            delay(wait);
        }
    }

}

void fullWhite() {

    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0, 255 ) );
    }
    strip.show();
}

uint8_t red(uint32_t c) {
    return (c >> 16);
}
uint8_t green(uint32_t c) {
    return (c >> 8);
}
uint8_t blue(uint32_t c) {
    return (c);
}

