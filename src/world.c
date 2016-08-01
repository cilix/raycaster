#include "main.h"
#include "window.h"
#include "camera.h"
#include "vmath.h"
#include "world.h"

#include <time.h>

#define SKY RGB(30, 144, 255)

#define OCEAN RGB(0, 119, 190)
#define BEACH RGB(139, 124, 101)
#define GRASSLAND RGB(118, 157, 68)
#define SUBTROPICAL_DESERT RGB(200, 172, 121)
#define TROPICAL_SEASONAL_FOREST RGB(71, 140, 53)
#define TROPICAL_RAIN_FOREST RGB(41, 102, 67)

#define OCEAN_SHADED RGBdark(0, 119, 190, 0.5)
#define BEACH_SHADED RGBdark(139, 124, 101, 0.5)
#define GRASSLAND_SHADED RGBdark(118, 157, 68, 0.5)
#define SUBTROPICAL_DESERT_SHADED RGBdark(200, 172, 121, 0.5)
#define TROPICAL_SEASONAL_FOREST_SHADED RGBdark(71, 140, 53, 0.5)
#define TROPICAL_RAIN_FOREST_SHADED RGBdark(41, 102, 67, 0.5)

#define MAX_ELEVATION 512.f
#define WATER_LEVEL 153

static unsigned int biome( int elevation, int moisture, int shadow ){
  float e = (float)elevation / (float)MAX_ELEVATION;
  float m = (float)moisture / (float)MAX_ELEVATION;
  float water = (float)WATER_LEVEL / MAX_ELEVATION;

  if( !shadow ){
    if( e <= water ) return OCEAN;
    if( e < water + 0.02 ) return BEACH;
    if (m < 0.36 ) return SUBTROPICAL_DESERT;
    if ( m < 0.53 ) return GRASSLAND;
    if (m < 0.66 ) return TROPICAL_SEASONAL_FOREST;
    return TROPICAL_RAIN_FOREST;
  } else {
    if( e <= water ) return OCEAN_SHADED;
    if( e < water + 0.02 ) return BEACH_SHADED;
    if (m < 0.36 ) return SUBTROPICAL_DESERT_SHADED;
    if ( m < 0.53 ) return GRASSLAND_SHADED;
    if (m < 0.66 ) return TROPICAL_SEASONAL_FOREST_SHADED;
    return TROPICAL_RAIN_FOREST_SHADED;
  }
}

/* temporary */
unsigned int terrain[MAP_WIDTH * MAP_HEIGHT];
unsigned int colormap[MAP_WIDTH * MAP_HEIGHT];
unsigned int moisture[MAP_WIDTH * MAP_HEIGHT];

static void loadmap( void ){
  int x, y;
  float ltan = tanf(M_PI / 8); /* light angle */

  for (x = 0; x < MAP_WIDTH; x++) {
    for (y = 0; y < MAP_HEIGHT; y++) {
      float hval, mval;

      float nx = ((float)x / MAP_WIDTH) ;
      float ny = ((float)y / MAP_HEIGHT) ;
      float dst = 2.f * (max2(fabs(nx - 0.5), fabs(ny - 0.5)));

      srand(10);

      hval = noise(8 * nx, 8 * ny)
        + (0.20 * noise(32 * nx, 32 * ny))
        + (0.10 * noise(64 * nx, 64 * ny));

      hval *= 0.7;
      hval = (hval + 0.05) * (1 - 1.00 * power(dst, 2.00));

      if( hval < 0 ){
        hval = 0;
      }

      srand(5);

      mval = noise(16 * nx, 16 * ny)
        + (0.3 * noise(512 * nx, 512 * ny));

      terrain[y * MAP_WIDTH + x] = (int)(hval * (float)MAX_ELEVATION);
      moisture[y * MAP_WIDTH + x] = (int)(mval * (float)MAX_ELEVATION);
    }
  }

  for (x = 0; x < MAP_WIDTH; x++) {
    for (y = 0; y < MAP_HEIGHT; y++) {
      int w = y * MAP_WIDTH;
      int z = x;
      int v = w + x;
      int h = terrain[v];
      int m = moisture[v];
      int shadow = 0;

      if( h < WATER_LEVEL ){
        h = WATER_LEVEL;
      }

      /* simple lightmap */
      for( ; z < MAP_WIDTH; z++ ){
        float ray;
        int height = terrain[w + z];
        if( height < WATER_LEVEL ){
          height = WATER_LEVEL;
        }
        if( height <= h ) continue;
        ray = ltan * (z - x) + h;
        if( (float)height > ray ){
          shadow = 1;
          break;
        }
      }

      colormap[v] = biome(h, m, shadow);
    }
  }
}
/* end */

void World_init( World* self, Camera* c, Window* w ){
  self->camera = c;
  self->window = w;

  loadmap();
}

void render_terrain( Window* w ){
  int i, j;

  for ( i = 0; i < MAP_WIDTH; i++ ){
    for( j = 0; j < MAP_HEIGHT; j++ ){
      int val = (int)terrain[j * MAP_WIDTH + i] / MAX_ELEVATION * 255; 
      int c = RGB(val, val, val);
      if( i > SCREEN_WIDTH || j > SCREEN_HEIGHT ) continue;
      setpixel(w->pixels, i, j, c);
    }
  }
}

void World_render( Camera* c, Window* w ){
  int i, j, max;
  int cx, cz;
  int halfWidth = SCREEN_WIDTH / 2;
  int depth = SCREEN_HEIGHT;
  int sx = -1;
  int ch;

  c->x = (float)((int)(c->x + MAP_WIDTH) % MAP_WIDTH);
  c->z = (float)((int)(c->z + MAP_HEIGHT) % MAP_HEIGHT);

  cz = (int)c->z;
  cx = (int)c->x;

  /* temporary - make sure camera doesn't go underground (for walking) */
  ch = (float)terrain[cz * MAP_WIDTH + cx];
  if( ch < WATER_LEVEL ){
    c->y = WATER_LEVEL + 4.f;
  } else {
    c->y = ch + 4.f;
  }

  i = cx - halfWidth;
  max = cx + halfWidth;

  for( ; i < max; i++, sx++ ){
    float dx = i;
    float dz = depth + cz;
    float x1 = cx, z1 = cz;
    int idx, prev = 0;

    rotate(&dx, &dz, c->x, c->z, c->a);

    dx -= cx;
    dz -= cz;

    dx = dx / depth;
    dz = dz / depth;

    for( j = 0; j < depth; j++ ){
      float y;
      int y0, depth = j ? j : 1;
      int z, x, h;

      x1 += dx;
      z1 += dz;

      x = ((int)(x1 + MAP_WIDTH) % MAP_WIDTH);
      z = ((int)(z1 + MAP_HEIGHT) % MAP_HEIGHT);

      idx = (z * MAP_WIDTH + x); /* switch to bit shifting */
      h = terrain[idx];
      if( h < WATER_LEVEL ) h = WATER_LEVEL;
      y = (float)h - c->y;
      y = ((y / depth) * SCREEN_HEIGHT) + (SCREEN_HEIGHT / 2);
      y0 = (int)(y - c->v); /* y-shearing for tilt */

      if( y0 < 0 ) y0 = 0;
      else if( y0 > SCREEN_HEIGHT ) y0 = SCREEN_HEIGHT;

      while( prev < y0 ){
        setpixel(w->pixels, sx, (SCREEN_HEIGHT - prev++), colormap[idx]);
      }
    }

    while( prev < SCREEN_HEIGHT ){
      setpixel(w->pixels, sx, (SCREEN_HEIGHT - prev++), SKY);
    }
  }
}
