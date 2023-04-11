/** Definitions for pad I/O **/

#include <stdint.h>

// Constants

#define MAX_LED		1
#define MAX_PHASES	4
#define MAX_BUTTON	2

#define OUTPUT_PORTB	0x20
#define OUTPUT_PORTC	0x00
#define OUTPUT_PORTD	0xF0

#define INPUT_PORTB	0x00
#define INPUT_PORTC	0x00
#define INPUT_PORTD	0x0C

#define PULLUP_PORTB	0x00
#define PULLUP_PORTC	0x00
#define PULLUP_PORTD	0x0C

// Macros

#define OUT_set(mask)		\
  { outstate |= mask; outputs_set((outstate&0x00ff0000)>>16,(outstate&0x0000ff00)>>8,(outstate&0x000000ff)); }
#define OUT_unset(mask)		\
  { outstate &= ~mask; outputs_set((outstate&0x00ff0000)>>16,(outstate&0x0000ff00)>>8,(outstate&0x000000ff)); }
#define OUT_toggle(mask)	\
  { outstate ^= mask; outputs_set((outstate&0x00ff0000)>>16,(outstate&0x0000ff00)>>8,(outstate&0x000000ff)); }
#define IN_glue(portb,portc,portd)\
   (((((uint32_t)portb<<8)|(uint32_t)portc)<<8)|(uint32_t)portd)

// Global variables

extern uint32_t leds[MAX_LED];
extern uint32_t phases[MAX_PHASES];
extern uint32_t outstate;
extern uint32_t buttons[MAX_BUTTON];
