#ifndef _MAIN_H
#define _MAIN_H

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

#define SCREEN_AR (SCREEN_HEIGHT / SCREEN_WIDTH)

#define darker(c, p) ((int)((float)(0 - c) * p + c))
#define lighter(c, p) ((int)((float)(255 - c) * p + c))

#define RGBA(r, g, b, a) ((a << 24) | (r << 16) | (g << 8) | b)
#define RGB(r, g, b) RGBA(r, g, b, 255)

#define RGBlight(r, g, b, p) RGB(lighter(r, p), lighter(g, p), lighter(b, p))
#define RGBdark(r, g, b, p) RGB(darker(r, p), darker(g, p), darker(b, p))

#define setpixel(p, x, y, v) p[y * SCREEN_WIDTH + x] = v

typedef struct { float x; float y; float z; } vertex_t;
typedef vertex_t tri_t[3];
typedef struct { int x; int y; int z; } vec3i_t;

#define min3(x, y, z) (x < y ? (x < z ? x : z) : (y < z ? y : z))
#define min2(x, y) (x < y ? x : y)
#define max3(x, y, z) (x > y ? (x > z ? x : z) : (y > z ? y : z))
#define max2(x, y) (x > y ? x : y)

#endif
