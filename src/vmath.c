#include "vmath.h"

float noise( float x, float y ){
  float vec[2];
  vec[0] = x;
  vec[1] = y;
  return (noise2(vec) + 1) / 2;
}

float power( float x, int y ){
  float t;
  if( y == 0 ) return 1;
  t = power(x, y >> 1);       
  if( y % 2 == 0 ) return t * t;
  if( y > 0 ) return x * t * t;
  return t * t / x;
} 

void rotate( 
  float* x, float* y, 
  float ox, float oy, 
  float theta 
){
  float cosr = cosf(theta);
  float sinr = sinf(theta);

  float x0 = *x, xn;
  float y0 = *y, yn;

  x0 -= ox;
  y0 -= oy;

  xn = (cosr * x0 - sinr * y0);
  yn = (cosr * y0 + sinr * x0);

  *x = xn + ox;
  *y = yn + oy;
}
