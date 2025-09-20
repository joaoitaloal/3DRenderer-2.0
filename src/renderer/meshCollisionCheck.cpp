#include "renderer.h"

RayCollision meshCollisionCheck(Ray ray, Mesh3* mesh){
    RayCollision col;
    col.hit = false;

    RayCollision boxCol = GetRayCollisionBox(ray, mesh->bbox);

    if(!boxCol.hit || mesh->faces.size() == 0){
        return col;
    }

    for(FaceTri tri : mesh->faces){
        //RayCollision temp = GetRayCollisionTriangle(ray, tri.v1, tri.v2, tri.v3);
        RayCollision temp = triangleCollisionCheck(ray, tri.v1, tri.v2, tri.v3);

        if(!col.hit || (temp.hit && col.distance > temp.distance)){ 
            col = temp;
        }
    }

    return col;
}