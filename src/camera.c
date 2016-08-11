#include <math.h>

#include "main.h"
#include "camera.h"

#define SPEED 1.5f

void Camera_init( Camera* c ){
  c->x = 0.f;
  c->y = 0.f;
  c->a = 0.f;
  c->z = 0.f;
  c->v = 0.f;
}

/* move the following to 1 function */
void Camera_moveleft( Camera* c ){
  float a = c->a + M_PI;
  float x = SPEED * cosf(a);
  float z = SPEED * sinf(a);

  c->z += z;
  c->x += x;
}

void Camera_moveright( Camera* c ){
  float a = c->a;
  float x = SPEED * cosf(a);
  float z = SPEED * sinf(a);

  c->z += z;
  c->x += x;
} 

void Camera_moveforward( Camera* c ){
  float a = c->a + M_PI / 2;
  float x = SPEED * cosf(a);
  float z = SPEED * sinf(a);

  c->z += z;
  c->x += x;
} 

void Camera_moveback( Camera* c ){
  float a = c->a + (M_PI / 2 * 3);
  float x = SPEED * cosf(a);
  float z = SPEED * sinf(a);

  c->z += z;
  c->x += x;
} 

void Camera_rotateleft( Camera* c ){
  c->a += 0.1;
  if( c->a >= 2 * M_PI )
    c->a = 0.f;
} 

void Camera_rotateright( Camera* c ){
  c->a -= 0.1;
  if( c->a <= 0 )
    c->a = 2 * M_PI;
} 

void Camera_moveup( Camera* c ){
  c->y += SPEED;
} 

void Camera_movedown( Camera* c ){
  c->y -= SPEED;
}

void Camera_tiltup( Camera* c ){
  if( c->v >= SCREEN_HEIGHT ) return;
  c->v += 25;
}

void Camera_tiltdown( Camera* c ){
  if( c->v <= -SCREEN_HEIGHT ) return;
  c->v -= 25;
}
