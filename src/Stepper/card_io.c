/** Handle pad I/O **/

#include "io.h"
#include "card_io.h"

// Global variables

uint32_t leds[MAX_LED]={0x00200000};
uint32_t phases[MAX_PHASES]={0x00000080,0x00000040,0x00000020,0x00000010};
uint32_t outstate=0x00000000;
uint32_t buttons[MAX_BUTTON]={0x00000008,0x00000004};
