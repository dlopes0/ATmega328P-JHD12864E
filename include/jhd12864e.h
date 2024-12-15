#pragma once

#ifndef JHD12864E_H
#define JHD12864E_H

#define T_WIDTH 200 // Time width (200us)

// ===========================================================================================================================================================================
// Instruction Set Table
//
// INSTRUCTION         RS  R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0  FUNCTION
// Display On/Off      L   L   L   L   H   H   H   H   H   L/H  L:OFF, H:ON
// Set address Y       L   L   L   H   [   Y ADDRESS (0-63)  ]  Set Y address in the Y address counter
// Set page X          L   L   H   L   H   H   H   [PAGE(0-7)]  Set X address at the X address register
// Display start line  L   L   H   H   [  DISPLAY SL (0-63)  ]  Indicates the display data RAM displayed at the top of the screen
// Status read         L   H   B   On  Rst L   L   L   L   L    Read status:
//                             u   Off                          BUSY   L: Ready
//                             s                                       H: In operation
//                             y                                ON/OFF L: Display ON
//                                                                     H: Display OFF
//                                                              RESET  L: Normal
//                                                                     H: Reset
// Write display data  H   L   [ Write data                 ]  Writes data DB(0:7) into display data RAM. After writing instruction, Y address is increased by 1 automatically
// Read display data   H   H   [ Read data                  ]  Read data DB(0:7) from display data RAM to the data bus
// ===========================================================================================================================================================================

// =======================
// Wiring Configuration
//
// JHD12864E -> ATmega328p
//         E -> PD2
//       R/W -> PB5
//      CS1B -> PC0
//      CS2B -> PC1
//       CS3 -> PC2
//        RS -> PC3
//       DB0 -> PD5
//       DB1 -> PD6
//       DB2 -> PD7
//       DB3 -> PB0
//       DB4 -> PB1
//       DB5 -> PB2
//       DB6 -> PB3
//       DB7 -> PB4
// =======================

void write_operation(uint16_t op);
uint16_t read_operation();

#endif