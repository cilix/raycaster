#ifndef _WORLD_H
#define _WORLD_H

#include <stdio.h>
#include <math.h>

#define MAP_WIDTH 1024
#define MAP_HEIGHT 1024

typedef struct {
  Camera* camera;
  Window* window;
  uint32_t height_map[MAP_WIDTH * MAP_HEIGHT];
} World;

void World_init( World*, Camera*, Window* );
void World_render( Camera*, Window* );

#endif
