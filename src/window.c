#include "window.h"

void Window_init( Window* w, const char* name, int width, int height ){
  SDL_Init(SDL_INIT_VIDEO);

  w->width = width;
  w->height = height;

  w->window = SDL_CreateWindow(
    name,
    SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, 
    width, 
    height, 
    0
  );

  w->renderer = SDL_CreateRenderer(w->window, -1, SDL_RENDERER_SOFTWARE);
  w->texture = SDL_CreateTexture(
    w->renderer,
    SDL_PIXELFORMAT_ARGB8888, 
    SDL_TEXTUREACCESS_STREAMING, 
    width, 
    height
  );

  w->pixels = malloc(sizeof(uint32_t) * (width * height));
  memset(w->pixels, 0, width * height * sizeof(uint32_t));
}

void Window_update( Window* w ){
  SDL_UpdateTexture(w->texture, NULL, w->pixels, w->width * sizeof(uint32_t));
}

void Window_pollevent( 
  Window* w, 
  int* quit, 
  int* left,       int* right, 
  int* forward,    int* back, 
  int* up,         int* down,
  int* rotateLeft, int* rotateRight,
  int* tiltUp,     int* tiltDown
){
  while( SDL_PollEvent(&(w->event)) ){
    if( w->event.type == SDL_QUIT ){
      *quit = 1;
    } else if( w->event.type == SDL_KEYDOWN ){
      switch( w->event.key.keysym.sym ){
        case SDLK_a: *left = 1; break;
        case SDLK_d: *right = 1; break;
        case SDLK_w: *forward = 1; break;
        case SDLK_s: *back = 1; break;
        case SDLK_1: *up = 1; break;
        case SDLK_2: *down = 1; break;
        case SDLK_LEFT: *rotateLeft = 1; break;
        case SDLK_RIGHT: *rotateRight = 1; break;
        case SDLK_UP: *tiltUp = 1; break;
        case SDLK_DOWN: *tiltDown = 1; break;
        default: break;
      }
    } else if( w->event.type == SDL_KEYUP ){
      switch( w->event.key.keysym.sym ){
        case SDLK_a: *left = 0; break;
        case SDLK_d: *right = 0; break;
        case SDLK_w: *forward = 0; break;
        case SDLK_s: *back = 0; break;
        case SDLK_0: *up = 0; break;
        case SDLK_2: *down = 0; break;
        case SDLK_LEFT: *rotateLeft = 0; break;
        case SDLK_RIGHT: *rotateRight = 0; break;
        case SDLK_UP: *tiltUp = 0; break;
        case SDLK_DOWN: *tiltDown = 0; break;
        default: break;
      }
    }
  }
}

void Window_clear( Window* w ){
  SDL_Delay(16);
  memset(w->pixels, 0, sizeof(uint32_t) * w->height * w->width);
  SDL_RenderClear(w->renderer);
  SDL_RenderCopy(w->renderer, w->texture, NULL, NULL);
  SDL_RenderPresent(w->renderer);
}

void Window_destroy( Window* w ){
  free(w->pixels);
  SDL_DestroyTexture(w->texture);
  SDL_DestroyRenderer(w->renderer);
  SDL_DestroyWindow(w->window);
  SDL_Quit();
}
