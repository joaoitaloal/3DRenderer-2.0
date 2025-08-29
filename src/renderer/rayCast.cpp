#include <raylib.h>
#include <raymath.h>
#include "../scene/view/view.h"

//Recebe Camera, plano, objetos, x e y do raio no plano, width e height e retorna a cor encontrada nesse pixel

Color* rayCast(View view, float origin_x, float origin_y, int WIDTH, int HEIGHT){
    float alpha = origin_x/WIDTH;
    float beta = origin_y/HEIGHT;

    Ray ray = view.createRay(alpha, beta);

    RayCollision col = GetRayCollisionTriangle(ray, {50, 0, 20}, {9, 5, 15}, {0, 5, 20});

    Color* color = new Color();
    if(col.hit){
        color->r = 255;
        color->g = 0;
        color->b = 0;

        return color;
    }
    
    color->r = 0;
    color->g = 0;
    color->b = 0;

    return color;
}