# Stopwatch Management Code for ATmega32

This is a simple C code for managing a stopwatch using an ATmega32 microcontroller. The code allows the user to set the hours, minutes, and seconds, and then start the stopwatch. It also includes an alarm feature.

## Drivers Used

1. **DIO (Data Input/Output) Driver**
   - Functionality: Used for setting the direction and value of digital I/O pins.

2. **GIE (General Interrupt Enable) Driver**
   - Functionality: Used to enable and disable global interrupts.

3. **EXTI (External Interrupt) Driver**
   - Functionality: Not explicitly mentioned in the code, so it might not be used in this specific project.

5. **TMR (Timer) Driver**
   - Functionality: Used for timer initialization and callbacks. Timer 0 is configured in CTC (Clear Timer on Compare Match) mode.

7. **LCD (Liquid Crystal Display) HAL (Hardware Abstraction Layer) Driver**
   - Functionality: Used for initializing and sending data to the LCD for display.

9. **Keypad HAL Driver**
   - Functionality: Used for initializing and reading keypad inputs from the user.

## Code Overview

The code allows the user to set the hours, minutes, and seconds for a stopwatch and then start the timer. It includes an alarm feature and displays the time on an LCD.

## Usage

1. Configure the necessary hardware connections.
2. Build and upload the code to the ATmega32 microcontroller.
3. Use a keypad to set the hours, minutes, and seconds for the stopwatch.
4. Press '=' to start the stopwatch.
5. The timer will count down, and when it reaches 0, an alarm message will be displayed on the LCD.
