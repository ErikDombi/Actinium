#include "AnalogPin.h"

using namespace Actinium;

AnalogPin::AnalogPin(unsigned char pinNumber) {
    this->m_pinNumber = pinNumber;
    adc_gpio_init()
}

float AnalogPin::Read() {
    
}