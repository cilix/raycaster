#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"
#include "window.h"
#include "camera.h"
#include "vmath.h"
#include "world.h"

int main( int argc, char** argv ){
  int quit        = 0;
  int left        = 0; 
  int right       = 0; 
  int up          = 0; 
  int down        = 0;
  int forward     = 0;
  int back        = 0;
  int rotateRight = 0;
  int rotateLeft  = 0;
  int tiltUp      = 0;
  int tiltDown    = 0;

  Window window;
  Camera camera;
  World world;
  
  Window_init(&window, "Game", SCREEN_WIDTH, SCREEN_HEIGHT);
  Camera_init(&camera);
  World_init(&world, &camera, &window);

  while( !quit ){
    Window_update(&window);
    Window_clear(&window);

    Window_pollevent(
      &window, 
      &quit, 
      &left,       &right, 
      &forward,    &back, 
      &up,         &down, 
      &rotateLeft, &rotateRight, 
      &tiltUp,     &tiltDown
    );

    if( left )        Camera_moveleft(&camera);
    if( right )       Camera_moveright(&camera);
    if( up )          Camera_moveup(&camera);
    if( down )        Camera_movedown(&camera);
    if( forward )     Camera_moveforward(&camera);
    if( back )        Camera_moveback(&camera);
    if( rotateLeft )  Camera_rotateleft(&camera);
    if( rotateRight ) Camera_rotateright(&camera);
    if( tiltUp )      Camera_tiltup(&camera);
    if( tiltDown )    Camera_tiltdown(&camera);
    
    World_render(&camera, &window);
  }

  Window_destroy(&window);

  return 0;
}
