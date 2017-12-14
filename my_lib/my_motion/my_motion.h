
#ifndef my_motion_h
#define my_motion_h
#include "Arduino.h"
#define DEBUG_MOTION 0
class motion
{
    public :
        motion(char pin, char id);
        bool get_motion();
private :
    char _pin;
    char _id;
};


#endif
