#include "hx711.h"

void hx711::hx711(PinName outputPin, PinName clockPin) : CLOCK_PIN(clockPin), OUT_PIN(outputPin)
{
    pinsConfigured = false;
    GAIN = 1;
}

void Q2HX711::~Q2HX711()
{
}

bool Q2HX711::readyToSend()
{
    if (!pinsConfigured)
    {
        // Configura los pines una vez, pero no en el constructor
        CLOCK_PIN.output();
        OUT_PIN.input();
        pinsConfigured = true;
    }
    return OUT_PIN == 0; // Considera LOW como condición de listo para enviar
}

void Q2HX711::setGain(byte gain)
{
    switch (gain)
    {
        case 128:
            GAIN = 1;
            break;
        case 64:
            GAIN = 3;
            break;
        case 32:
            GAIN = 2;
            break;
    }

    CLOCK_PIN = 0;
    read();
}

long Q2HX711::read()
{
    while (!readyToSend())
    {
        // Espera hasta que esté listo para enviar
    }

    byte data[3] = {0};

    for (int j = 2; j >= 0; j--)
    {
        for (int i = 7; i >= 0; i--)
        {
            CLOCK_PIN = 1;
            data[j] |= (OUT_PIN << i);
            CLOCK_PIN = 0;
        }
    }

    // Configura la ganancia
    for (int i = 0; i < GAIN; i++)
    {
        CLOCK_PIN = 1;
        CLOCK_PIN = 0;
    }

    data[2] ^= 0x80;
    return ((uint32_t)data[2] << 16) | ((uint32_t)data[1] << 8) | (uint32_t)data[0];
}
