#ifndef Q2HX711_h
#define Q2HX711_h

#include "mbed.h"

class Q2HX711
{
  private:
    DigitalOut CLOCK_PIN;
    DigitalIn OUT_PIN;
    uint8_t GAIN;
    bool pinsConfigured;

  public:
    Q2HX711(PinName outputPin, PinName clockPin);
    virtual ~Q2HX711();
    bool readyToSend();
    void setGain(uint8_t gain = 128);
    long read();
};

#endif /* Q2HX711_h */
