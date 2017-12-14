#ifndef my_NeoMatrix_h
#define my_NeoMatrix_h
#include "Arduino.h"
#define DEBUG_MATRIX 0


class motion
{
    public :
        my_NeoMatrix(char pin);
        void set_trash_type(char type);
        void set_state(char state);
private :
    char _pin;
    char _trash_type;
    char _state;
};


#endif 
