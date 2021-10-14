#include "Pin.h"

using namespace Actinium;

Pin::Pin(unsigned char pinNumber, PinMode mode) {
    this->m_pinNumber = pinNumber;
    this->m_pinMode = mode;
    gpio_init(pinNumber);
    switch(mode){
        case PinMode::OUT:
            gpio_set_dir(pinNumber, GPIO_OUT);
            break;
        case PinMode::IN:
            gpio_set_dir(pinNumber, GPIO_IN);
            break;
    }
}

bool Pin::Read() {
    return gpio_get(this->m_pinNumber);
}

void Pin::Write(PinStatus status) {
    this->Write(status == PinStatus::HIGH);
}

void Pin::Write(bool status) {
    gpio_put(this->m_pinNumber, status);
}

void Pin::On() {
    this->Write(PinStatus::HIGH);
}

void Pin::Off() {
    this->Write(PinStatus::LOW);
}