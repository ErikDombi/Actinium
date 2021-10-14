#ifndef LCD_H
#define LCD_H

#include <string>
#include "Pin.h"

namespace Actinium {

    typedef unsigned char BYTE;
    typedef bool BIT;

    const BYTE LCD_UPPERCASE_START_INDEX = 0b01000001;
    const BYTE LCD_LOWERCASE_START_INDEX = 0b01100001;
    const BYTE LCD_NUMERIC_START_INDEX = 0b00110000;

    std::string CharToLCDBin(char character);

    enum ShiftDirection {
        RIGHT,
        LEFT
    };

    enum LineCount {
        ONE,
        TWO
    };

    enum FontSize {
        FiveByEight,
        FiveByEleven
    };

    class LCD {
        Pin m_RS_PIN = Pin(0, PinMode::OUT);
        Pin m_RW_PIN = Pin(0, PinMode::OUT);
        Pin m_E_PIN = Pin(0, PinMode::OUT);
        Pin m_DB7_PIN = Pin(0, PinMode::OUT);
        Pin m_DB6_PIN = Pin(0, PinMode::OUT);
        Pin m_DB5_PIN = Pin(0, PinMode::OUT);
        Pin m_DB4_PIN = Pin(0, PinMode::OUT);
        Pin m_DB3_PIN = Pin(0, PinMode::OUT);
        Pin m_DB2_PIN = Pin(0, PinMode::OUT);
        Pin m_DB1_PIN = Pin(0, PinMode::OUT);
        Pin m_DB0_PIN = Pin(0, PinMode::OUT);
    public:
        // 10 BYTE constructor takes pin numbers of required outputs
        LCD(BYTE RS,
            BYTE RW,
            BYTE E,
            BYTE DB7,
            BYTE DB6,
            BYTE DB5,
            BYTE DB4,
            BYTE DB3,
            BYTE DB2,
            BYTE DB1,
            BYTE DB0);
        void SetPins(BIT RS,
                    BIT RW,
                    BIT DB7,
                    BIT DB6,
                    BIT DB5,
                    BIT DB4,
                    BIT DB3,
                    BIT DB2,
                    BIT DB1,
                    BIT DB0);
        void SetPins(std::string bits);
        void ResetPins(bool ResetEnable = true);
        void ResetCursor();
        void CursorEnd();
        void CursorPos(BYTE position);
        void CursorRight();
        void CursorLeft();
        void ClearDisplay();
        void WriteChar(char input);
        void WriteString(std::string input, unsigned int sleep = 2);
        void Apply();
        void EntryMode(ShiftDirection Shift, bool ShiftDisplay);
        void FunctionSet(LineCount NumLines, FontSize dispSize);
        void On(bool cursor = true, bool cursorBlink = true);
        void Off();
    };

}
#endif