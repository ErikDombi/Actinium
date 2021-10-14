#ifndef PIN_H
#define PIN_H

#include "pico/stdlib.h"

namespace Actinium {

    enum PinMode {
        OUT,
        IN
    };

    enum PinStatus {
        LOW,
        HIGH
    };

    class Pin {
        PinMode m_pinMode;
        PinMode m_activeMinMode;
        unsigned char m_pinNumber;
    public:
        Pin(unsigned char pinNumber, PinMode mode);
        bool Read();
        void Write(PinStatus status);
        void Write(bool status);
        void On();
        void Off();

        operator bool() { return Read(); }
    };
}

#endif