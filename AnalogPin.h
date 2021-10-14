#ifndef ANALOGPIN_H
#define ANALOGPIN_H
#include "Pin.h"

#include "pico/stdlib.h"
#include "hardware/adc.h"

namespace Actinium {

    adc_init();

    class AnalogPin {
        BYTE m_pinNumber;
    public:
        Pin(BYTE pinNumber);
        float Read();
    }
}

#endif