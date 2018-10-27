/*
 * sram.h
 *
 *  Created on: 27 paü 2018
 *      Author: ireneusz
 */

#ifndef SRAM_SRAM_H_
#define SRAM_SRAM_H_


#define SRAM_CONTROL_DDR DDRD
//SRAM control port
#define SRAM_CONTROL_PORT PORTD

//SRAM write enable
#define SRAM_WE (1<<PD2)
#define SRAM_WE_HIGH SRAM_CONTROL_PORT |= SRAM_WE
#define SRAM_WE_LOW SRAM_CONTROL_PORT &= ~SRAM_WE

//SRAM output enable
#define SRAM_OE (1<<PD3)
#define SRAM_OE_HIGH SRAM_CONTROL_PORT |= SRAM_OE
#define SRAM_OE_LOW SRAM_CONTROL_PORT &= ~SRAM_OE

//SRAM chip enable
#define SRAM_CE (1<<PD4)
#define SRAM_CE_HIGH SRAM_CONTROL_PORT |= SRAM_CE
#define SRAM_CE_LOW SRAM_CONTROL_PORT &= ~SRAM_CE

//data port
#define DATA_PORT_DDR DDRC
#define DATA_PORT PORTC
#define DATA_PIN PINC

void initSRAMControl(void);
void initLatch1(void);
void initLatch2(void);
void dataPortOutput(void);
void dataPortInput(void);
void setAddress(uint16_t byte);
void writeByte(uint8_t byte);
uint8_t readByte(void);


#endif /* SRAM_SRAM_H_ */
