#ifndef hx711_h
#define hx711_h

#include "mbed.h"

class hx711
{
  private:
    DigitalOut CLOCK_PIN;
    DigitalIn OUT_PIN;
    uint8_t GAIN;
    bool pinsConfigured;

  public:
    hx711(PinName outputPin, PinName clockPin);
    virtual ~hx711();
    bool readyToSend();
    void setGain(uint8_t gain = 128);
    long read();
};

#endif /* Q2HX711_h */
