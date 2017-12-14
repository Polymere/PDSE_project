
#ifndef my_aperture_h
#define my_aperture_h
#include "Arduino.h"
#include "Servo.h"

#define OP_SPEED 180
#define CL_SPEED 0
#define DEBUG_APERTURE 1
class aperture
{
    public :
    aperture(char pin_motor,char pin_but_open,char pin_but_close);
       void open();
       void close();
private :
    void stop();
    char _pin_motor;
    char _pin_open;
    char _pin_close;
    Servo _servo;
};


#endif 
