#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);
const byte eye_1[8][8]={{0, 0,0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 1, 1, 0, 0},
                        {0, 0, 0, 1, 1, 1, 1, 0},
                        {0, 0, 0, 0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0}};

const byte eye_2[8][8]={{0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 1, 1, 0, 0},
                        {0, 0, 0, 1, 1, 1, 1, 0},
                        {0, 0, 0, 1, 1, 1, 1, 0},
                        {0, 0, 0, 1, 1, 1, 1, 0},
                        {0, 0, 0, 0, 1, 1, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0}};

const byte eye_3[8][8]={{0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 1, 1, 0, 0},
                        {0, 0, 0, 1, 1, 1, 1, 0},
                        {0, 0, 1, 1, 1, 1, 1, 1},
                        {0, 0, 1, 1, 1, 1, 1, 1},
                        {0, 0, 1, 1, 1, 1, 1, 1},
                        {0, 0, 0, 1, 1, 1, 1, 0},
                        {0, 0, 0, 0, 1, 1, 0, 0}};

const byte eye_s[8][8]={{0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 1, 0, 0, 0},
                        {0, 0, 1, 1, 1, 1, 0, 0},
                        {0, 0, 1, 1, 1, 1, 0, 0},
                        {0, 1, 1, 1, 1, 1, 1, 0},
                        {0, 1, 1, 1, 1, 1, 1, 0},
                        {1, 1, 0, 0, 0, 0, 1, 1}};
                        
const uint16_t colorAlu=matrix.Color(128,128,128);
const uint16_t colorGlass=matrix.Color(34,191,13);
const uint16_t colorPet=matrix.Color(16,55,209);
const uint16_t colorWaste=matrix.Color(216,21,21);
const uint16_t colorPaper=matrix.Color(255,255,0);

void display_state(byte state)
{
  if state==old_state
    brightness+=10;
  else
     brightness=10;
  if brightness >100
     brightness=100; 
  switch (state)
  {
     case 0: //No user nearby : display text
       for (i=0;i<MATRIX_SIZE;i++)
       {
         for (j=0;j<MATRIX_SIZE;j++)
           if(eye_
       }
       break;
     case 1: // User far
     
       break;
     case 2: //closer
     
       break;
     case 3: //closest
     
       break;
     case 4: //bonus
     
       break;
     default ://cp case 0
     
  }
}
                     
  
 
