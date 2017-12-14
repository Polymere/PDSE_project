
#ifndef my_prox_h
#define my_prox_h
#include "Arduino.h"

#define THR 25
#define MIN_DIST 0.0
#define MAX_DIST 350.0
#define N_STATE 3.0
#define MAX_PULSE_RANGE 23200 //us
#define PULSE_LENGHT 10//us
#define WIDTH (MAX_DIST-MIN_DIST/N_STATE)
#define DEBUG_PROX  1
class prox
{
    public :
        prox (char  trig_pin, char echo_pin, char id);
        char get_state(char prev_state); // only for the front sensor
        void set_level(); // only for the internal sensor
        bool is_smaller_than_level(); //only for the internal sensor
private :
    int get_dist();
    int _level;
    char _trig_pin;
    char _echo_pin;
    char _id;
};


#endif
