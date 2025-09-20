#include "renderer.h"

bool meshShadowCheck(Ray ray, Mesh3* mesh){
    RayCollision boxCol = GetRayCollisionBox(ray, mesh->bbox);

    if(!boxCol.hit || mesh->faces.size() == 0){
        return false;
    }

    for(FaceTri tri : mesh->faces){
        //RayCollision temp = GetRayCollisionTriangle(ray, tri.v1, tri.v2, tri.v3);
        RayCollision temp = triangleCollisionCheck(ray, tri.v1, tri.v2, tri.v3);

        if(temp.hit) return true;
    }

    return false;
}