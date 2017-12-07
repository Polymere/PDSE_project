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
const byte eye0[8][8]={{0,   0,   0,   0,   0,   0,   0,   0},
{0,   0,   0,   0,   1,   1,   0,   0},
{0,   0,   0,   1,   1,   1,   1,   0},
{0,   0,   1,   1,   1,   1,   1,   1},
{0,   0,   1,   1,   1,   1,   1,   1},
{0,   0,   1,   1,   1,   1,   1,   1},
{0,   0,   0,   1,   1,   1,   1,   0},
{0,   0,   0,   0,   1,   1,   0,   0}};
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
  
}
int k1=0;
int k2=0;
int k3=0;
byte i,j=0;
void loop()
{
  if (k1>=256)
    k1=0;
   if(k2>=256)
     k2=0;
   if(k3>=256)
       k3=0;
  for (i=0;i<8;i++)
  {
    for(j=0;j<8;j++)
    {
      if(eye0[i][j]==1)
        matrix.drawPixel(i,j,matrix.Color(k1,k2,k3));
    }
  }
  k1++;
  k2+=2;
  k3+=3;
  matrix.show();
  
}
