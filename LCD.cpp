#include "LCD.h"
#include "pico/stdlib.h"
#include "bitset"

using namespace Actinium;

std::string CharToLCDBin(char character) {
    BYTE index = 0;
    BYTE newLocation;
    if(isalpha(character)) {
        if(isupper(character)) {
            index = character - (char)'A';
            newLocation = LCD_UPPERCASE_START_INDEX + index;
        } else {
            index = character - (char)'a';
            newLocation = LCD_LOWERCASE_START_INDEX + index;
        }
    }
    else if(isdigit(character)) {
        index = character - (char)'0';
        newLocation = LCD_NUMERIC_START_INDEX + index;
    }
    else {
        switch(character) {
            case ' ':
                newLocation = 0b10000000;
                break;
            case '#':
                newLocation = 0b00100011;
                break;
            case '!':
                newLocation = 0b00100001;
                break;
        }
    }
    return std::bitset<8>(newLocation).to_string();
}

void LCD::Apply() {
    sleep_ms(2);
    this->m_E_PIN.On();
    sleep_ms(2);
    this->m_E_PIN.Off();
}

void LCD::SetPins(BIT RS,
                  BIT RW,
                  BIT DB7,
                  BIT DB6,
                  BIT DB5,
                  BIT DB4,
                  BIT DB3,
                  BIT DB2,
                  BIT DB1,
                  BIT DB0) {
    this->m_RS_PIN.Write(RS);
    this->m_RW_PIN.Write(RW);
    this->m_DB7_PIN.Write(DB7);
    this->m_DB6_PIN.Write(DB6);
    this->m_DB5_PIN.Write(DB5);
    this->m_DB4_PIN.Write(DB4);
    this->m_DB3_PIN.Write(DB3);
    this->m_DB2_PIN.Write(DB2);
    this->m_DB1_PIN.Write(DB1);
    this->m_DB0_PIN.Write(DB0);
    this->Apply();
}

void LCD::SetPins(std::string bits) {
    if(bits.length() != 10)
        return; // Data is wonky. No good!

    this->m_RS_PIN.Write(bits[0] == '1');
    this->m_RW_PIN.Write(bits[1] == '1');
    this->m_DB7_PIN.Write(bits[2] == '1');
    this->m_DB6_PIN.Write(bits[3] == '1');
    this->m_DB5_PIN.Write(bits[4] == '1');
    this->m_DB4_PIN.Write(bits[5] == '1');
    this->m_DB3_PIN.Write(bits[6] == '1');
    this->m_DB2_PIN.Write(bits[7] == '1');
    this->m_DB1_PIN.Write(bits[8] == '1');
    this->m_DB0_PIN.Write(bits[9] == '1');
    this->Apply();
}

void LCD::ResetPins(bool ResetEnable) {
    if(ResetEnable)
        this->m_E_PIN.Off();
    this->SetPins(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

void LCD::ResetCursor() {
    this->SetPins(0, 0, 0, 0, 0, 0, 0, 0, 1, 0);
}

void LCD::CursorPos(BYTE position) {
    this->ResetCursor();
    for(int i = 0; i < position; ++i)
        this->CursorRight();
}

void LCD::CursorEnd() {
    this->CursorPos(16);
}

void LCD::CursorRight() {
    this->SetPins(0, 0, 0, 0, 0, 1, 0, 1, 0, 0);
}

void LCD::CursorLeft() {
    this->SetPins(0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
}

void LCD::ClearDisplay() {
    this->SetPins(0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
}

void LCD::WriteChar(char input) {
    this->SetPins("10" + CharToLCDBin(input));
}

void LCD::WriteString(std::string input, unsigned int sleep) {
    for(int i = 0; i < input.length(); ++i) {
        this->WriteChar(input[i]);
        sleep_ms(sleep);
    }
}

void LCD::EntryMode(ShiftDirection Shift, bool ShiftDisplay) {
    BIT ShiftRight = Shift == ShiftDirection::RIGHT;
    this->SetPins(0, 0, 0, 0, 0, 0, 0, 1, ShiftRight, ShiftDisplay);
}

void LCD::FunctionSet(LineCount NumLines, CharSize dispSize) {
    BIT TwoLines = NumLines == LineCount::TWO;
    BIT Size = dispSize == CharSize::FiveByEleven;
    this->SetPins(0, 0, 0, 0, 1, 1, TwoLines, Size, 0, 0);
}

void LCD::On(bool cursor, bool cursorBlink) {
    this->SetPins(0, 0, 0, 0, 0, 0, 1, 1, cursor, cursorBlink);
}

void LCD::Off() {
    this->SetPins(0, 0, 0, 0, 0, 0, 1, 1, 0, 0);
}

LCD::LCD(BYTE RS,
         BYTE RW,
         BYTE E,
         BYTE DB7,
         BYTE DB6,
         BYTE DB5,
         BYTE DB4,
         BYTE DB3,
         BYTE DB2,
         BYTE DB1,
         BYTE DB0)
{
    this->m_RS_PIN = Pin(RS, PinMode::OUT);
    this->m_RW_PIN = Pin(RW, PinMode::OUT);
    this->m_E_PIN = Pin(E, PinMode::OUT);
    this->m_DB7_PIN = Pin(DB7, PinMode::OUT);
    this->m_DB6_PIN = Pin(DB6, PinMode::OUT);
    this->m_DB5_PIN = Pin(DB5, PinMode::OUT);
    this->m_DB4_PIN = Pin(DB4, PinMode::OUT);
    this->m_DB3_PIN = Pin(DB3, PinMode::OUT);
    this->m_DB2_PIN = Pin(DB2, PinMode::OUT);
    this->m_DB1_PIN = Pin(DB1, PinMode::OUT);
    this->m_DB0_PIN = Pin(DB0, PinMode::OUT);
    this->ClearDisplay();
    this->FunctionSet(LineCount::TWO, CharSize::FiveByEight);
    this->EntryMode(ShiftDirection::RIGHT, false);
}