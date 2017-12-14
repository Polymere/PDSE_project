#include <Arduino.h>
#include "my_aperture.h"
#include <Servo.h>

aperture::aperture(char pin_motor,char pin_but_open,char pin_but_close)
{
    _pin_close=pin_but_close;
    _pin_motor=pin_motor;
    _pin_open=pin_but_open;
    #if DEBUG_APERTURE ==1
        if (!Serial)
            Serial.begin(9600);
        Serial.println("Aperture initialized");
    #endif

}
void aperture::open()
{
    #if DEBUG_APERTURE ==1
        Serial.println("Opening");
    #endif
    //attachInterrupt(digitalPinToInterrupt(_pin_open),stop,RISING);
        attachInterrupt(_pin_open,stop,RISING);
    _servo.attach(_pin_motor);
    _servo.write(OP_SPEED);
}
void aperture::close()
{
#if DEBUG_APERTURE ==1
    Serial.println("Closing");
#endif
    //attachInterrupt(digitalPinToInterrupt(_pin_close),stop,RISING);
    attachInterrupt(_pin_close,stop,RISING);
    _servo.attach(_pin_motor);
    _servo.write(CL_SPEED);
}
void aperture::stop()
{
    #if DEBUG_APERTURE ==1
        Serial.println("Stop");
    #endif
    _servo.detach();
}
