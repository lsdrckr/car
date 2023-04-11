/** Definitions for I/O **/

// Prototypes

void inputs_init(int portb,int portc,int portd,int pullupb,int pullupc,int pullupd);
void outputs_init(int portb,int portc,int portd);
void inputs_get(int *portb,int *portc,int *portd);
void outputs_set(int portb,int portc,int portd);
