# Actinium
A small library for interacting with various electronics with a Raspberry Pi Pico Microcontroller.

---

### Printing Hello World
```cpp
#include "pico/stdlib.h
#include "LCH.h"

int main() {
	// Constructor accepts the number of the 11 pins which are connected to the LCD
    // In order: RS, RW, E, D0, D1, D2, D3, D4, D5, D6, D7
	Actinium::LCD display(5, 6, 7, 15, 14, 13, 12, 11, 10, 9, 8);
	
	// By default, the LCD starts in multiline mode, with a font size of 5x8 pixels,
	// shifting the cursor to the right, without shifting the display, with a blinking cursor.
	// These defaults can be changed after creating the LCD object
	
	// Set the line count, and font size:
	display.FunctionSet(Actinium::LineCount::ONE, Actinium::FontSize::FiveByEight);
	
	// Shift the cursor to the right after each character.
	// We pass false as the second parameter, indicating to not shift the entire display.
	display.EntryMode(Actinium::ShiftDirection::RIGHT,  false);
	
	// Turn on the display. First parameter indicates if we should have a cursor, and the 
	// second parameter indicates if the cursor should blink.
	// Both of these parameters are optional.
	display.On(true, true);
	
	// All that is left now is to write to the display!
	display.WriteString("Hello World");
}
```
