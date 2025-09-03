#ifndef COLOR_RAYCAST
#define COLOR_RAYCAST

#include "rayCast.cpp"
Color rayCast(View view, float origin_x, float origin_y, int WIDTH, int HEIGHT, Mesh3* mesh);

#endif

#ifndef RENDER_SCREEN
#define RENDER_SCREEN

#include "renderScreen.cpp"
void renderToScreen(TextureCPU* tex, View view, Mesh3* mesh, int WIDTH, int HEIGHT, int anim_speed);

#endif
