/* Mentor's Wall Jewel
 * Created By: Ayan Pahwa
 * Design Details : Created with Adobe Illustrator 
 * Front Panel : Laser cut and Laser engraved
 * Total Number of LEDs : 420
 * Tricolor mode :
           Green  : 0-131
           White  : 132-298
           Saffron : 299-420           
*/


#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   4    // Pusbutton Pin

#define PIXEL_PIN    6    // Strip Pin

#define PIXEL_COUNT 420  // Total LEDs

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_RGB     Pixels are wired for RGB bitstream
// NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
// NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
// NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH; // Pushbutton activates on LOW
int showType = 0;

void setup() 
{
  
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Enabling pullup resistors
  strip.begin();
  strip.show(); // Initialize all pixels to 'off' 
  
}

void loop() 
{
  
  bool newState = digitalRead(BUTTON_PIN); // Get current button state

  if (newState == LOW && oldState == HIGH)  // Check if state changed from high to low (button press)
  {
    
    delay(20); // Short delay to debounce button
    newState = digitalRead(BUTTON_PIN); // Check if button is still low after debounce
    
    if (newState == LOW) 
    {
      
      showType++;
      if (showType > 10)
        showType=0;
      startShow(showType);
      
    }
  }

  oldState = newState; // Set the last button state to the old state
  
}


void startShow(int i) 
{
  
  switch(i)
  {
    case 0: colorWipe(strip.Color(0, 0, 0), 1);            // off
            break;
    case 1: colorWipe(strip.Color(255, 0, 0), 1);          // Red
            break;
    case 2: colorWipe(strip.Color(0, 255, 0), 1);          // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 255), 1);          // Blue
            break;
    case 4: triColor();                                    // Indin Flag
            break;      
    case 5: colorWipe(strip.Color(100, 100, 100), 1);      // White
            break;
    case 6: colorWipe(strip.Color(255, 105, 255), 1);      // Pink
            break;
    case 7: colorWipe(strip.Color(240, 200, 0), 1);        // Gold
            break;
    case 8: rainbow(20);                                   // Rainbow
            break;
    case 9: rainbowCycle(10);                              // Rainbow cycle
            break;
    case 10: stars();                                      // Twinkling Effect
            break;            
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) 
{
  
  for(uint16_t i=0; i<strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) 
{

  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    for(i=0; i<strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) 
{
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) 
{
  for (int j=0; j<10; j++) 
  {  
    for (int q=0; q < 3; q++) 
    {
      for (int i=0; i < strip.numPixels(); i=i+3) 
      {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) 
      {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) 
{
  for (int j=0; j < 256; j++) 
  {     
    for (int q=0; q < 3; q++) 
    {
      for (int i=0; i < strip.numPixels(); i=i+3) 
      {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) 
      {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) 
  {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) 
  {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void triColor() 
{

  for(int i=0;i<=131;i++) 
  {
  strip.setPixelColor(i, strip.Color(0,255,0));
  delay(1);
  strip.show();
  }

  for(int j=132;j<=298;j++) 
  {
  strip.setPixelColor(j, strip.Color(255,255,255));
  delay(1);
  strip.show();
  }  

  for(int k=299;k<=420;k++) 
  {
  strip.setPixelColor(k, strip.Color(130,100,50));
  delay(1);
  strip.show();
  }  
    
}

void stars() 
{

  strip.show();
  while(1) // Last animation in continous loop
  Sparkle(random(255), random(255), random(255), 50);
}


void Sparkle(byte red, byte green, byte blue, int SpeedDelay) 
{
  int Pixel = random(PIXEL_COUNT);
  strip.setPixelColor(Pixel, strip.Color(0,0, 255));
  strip.show();
  delay(SpeedDelay);
  strip.setPixelColor(Pixel, strip.Color(0, 0, 0));
  strip.show();

}



