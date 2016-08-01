#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL2/SDL.h>

typedef struct {
  int width;
  int height;
  SDL_Event event;
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  uint32_t* pixels;
} Window;

void Window_init( Window*, const char*, int, int );
void Window_update( Window* );
void Window_pollevent( Window* w, int*, int*, int*, int*, int*, int*, int*, int*, int*, int*, int* );
void Window_clear( Window* );
void Window_destroy( Window* );

#endif
