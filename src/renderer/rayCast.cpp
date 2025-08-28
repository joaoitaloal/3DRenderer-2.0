#include <raylib.h>
#include <raymath.h>
#include "../scene/scene.h"

//Recebe Camera, plano, objetos, x e y do raio no plano, width e height e retorna a cor encontrada nesse pixel

Color* rayCast(Camera3* camera, Plane* plane, float origin_x, float origin_y, int WIDTH, int HEIGHT){
    float alpha = origin_x/WIDTH;
    float beta = origin_y/HEIGHT;

    Vector3 t = Vector3Add(
        Vector3Scale(*plane->p1, 1.0f-alpha),
        Vector3Scale(*plane->p2, alpha)
    );

    Vector3 b = Vector3Add(
        Vector3Scale(*plane->p3, 1.0f-alpha),
        Vector3Scale(*plane->p4, alpha)
    );

    Vector3 origin = Vector3Add(
        Vector3Scale(t, 1.0f-beta),
        Vector3Scale(b, beta)
    );

    Vector3 dir = Vector3Normalize(Vector3Subtract(origin, *camera->position));

    Ray ray = {origin, dir};


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