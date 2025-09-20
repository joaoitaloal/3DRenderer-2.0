#ifndef RENDERER_RENDERER_H
#define RENDERER_RENDERER_H

#include <raylib.h>
#include <raymath.h>
#include "../scene/view/view.h"
#include "../scene/objects/objects.h"
#include <cstdio>

#include "../texture/texture.h"

/*
    Should renderToScreen not be a method of TextureCPU?
    and rayCast a method of view?
*/

//Recebe Camera, plano, objetos, x e y do raio no plano, width e height e retorna a cor encontrada nesse pixel
//Color rayCast(View view, float origin_x, float origin_y, int WIDTH, int HEIGHT, Mesh3* mesh);

//void renderToScreen(TextureCPU* tex, View view, Mesh3* mesh, int WIDTH, int HEIGHT, int anim_speed);

// ToDo
RayCollision triangleCollisionCheck(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3);

RayCollision meshCollisionCheck(Ray ray, Mesh3* mesh);

bool meshShadowCheck(Ray ray, Mesh3* mesh);

#endif // RENDERER_RENDERER_H
