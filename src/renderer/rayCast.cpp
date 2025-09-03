#include <raylib.h>
#include <raymath.h>
#include "../scene/view/view.h"
#include "../scene/objects/objects.h"
#include <cstdio>

//Recebe Camera, plano, objetos, x e y do raio no plano, width e height e retorna a cor encontrada nesse pixel

Color rayCast(View view, float origin_x, float origin_y, int WIDTH, int HEIGHT, Mesh3 mesh){
    Color color;
    if(mesh.faces.size() == 0){
        color = {0, 0, 0, 0};
        return color;
    }

    float alpha = origin_x/WIDTH;
    float beta = origin_y/HEIGHT;

    Ray ray = view.createRay(alpha, beta);

    RayCollision boxCol = GetRayCollisionBox(ray, mesh.bbox);
    
    if(!boxCol.hit){
        color = {0, 0, 0, 0};
        return color;
    }
    
    RayCollision col = GetRayCollisionTriangle(ray, mesh.faces[0].v1, mesh.faces[0].v2, mesh.faces[0].v3);
    color = mesh.faces[0].color;
    for(FaceTri tri : mesh.faces){
        RayCollision temp = GetRayCollisionTriangle(ray, tri.v1, tri.v2, tri.v3);

        if(!col.hit || (temp.hit && col.distance > temp.distance)){ 
            col = temp;
            color = tri.color;
        }
    }

    if(!col.hit){
        color = {0, 0, 0, 0};
    }

    return color;
}