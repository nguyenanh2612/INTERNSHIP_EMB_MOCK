# README: Mock Embedded discription

## Overview

This document provides details descriptions about the MOCK EMB that our group creates and sets in the program. 

## Running the Program

1. **Start the Program:**
   - Once the program is flashed onto the board, it will begin execution immediately. The main loop will handle time and date updates, manage display settings, and check alarms.

2. **Interact with the Program:**
   - **Buttons:**
     - **BUTTON_PIN1 (PTC12):** Switches between time and date display modes.
     - **BUTTON_PIN2 (PTC13):** Toggles the display on and off.
   - **Display:**
     - When enabled, the 7-segment display will show either the current time or date based on the selected mode.
     - When disabled, the program allow you to set the new date and time for calculation and display. Furthermore alarm mode set also is enabled here. You can set alarm time for board (Display by GREEN LED in 1 second). Furthermore, you can also set the program display the real time. 

   - **UART and SPI Outputs:**
     - The program sends the current time and date via UART and SPI.

## Note

   - You have to set up all data you have before push apply button on GUI 
   - With the unit test, you want to run unit test, you have to convert function emb_mock() in main.c file to comment and calls fucntions that i've revealed in test report excel.If no or call functions in UNIT_TEST.h, they can break the program. 
