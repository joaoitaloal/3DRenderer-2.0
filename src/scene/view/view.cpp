#include "view.h"

View::View(float set_x, float set_y, float set_z){
    position = {set_x, set_y, set_z};

    cam = {set_x, set_y, set_z, 0, 0, 1};
    plane = {1, 0.75, &cam};
}

View::View(Camera3 &set_cam, Plane &set_plane)
    : cam(set_cam), plane(set_plane) {
                    position = cam.position;
                };

// Not implemented yet
void View::setFov(float fov){};

Ray View::createRay(float alpha, float beta){
    Vector3 t = Vector3Add(
        Vector3Scale(plane.p1, 1.0f-alpha),
        Vector3Scale(plane.p2, alpha)
    );

    Vector3 b = Vector3Add(
        Vector3Scale(plane.p3, 1.0f-alpha),
        Vector3Scale(plane.p4, alpha)
    );

    Vector3 origin = Vector3Add(
        Vector3Scale(t, 1.0f-beta),
        Vector3Scale(b, beta)
    );

    Vector3 dir = Vector3Normalize(Vector3Subtract(origin, cam.position));

    Ray ray = {origin, dir};

    return ray;
}

// Objetos, x e y do raio no plano, width e height e retorna a cor encontrada nesse pixel
Color View::rayCast(float origin_x, float origin_y, int WIDTH, int HEIGHT, Mesh3* mesh){
    Color color;
    if(mesh->faces.size() == 0){
        color = {0, 0, 0, 0};
        return color;
    }

    float alpha = origin_x/WIDTH;
    float beta = origin_y/HEIGHT;

    Ray ray = createRay(alpha, beta);

    RayCollision boxCol = GetRayCollisionBox(ray, mesh->bbox);
    
    if(!boxCol.hit){
        color = {0, 0, 0, 0};
        return color;
    }
    
    RayCollision col = GetRayCollisionTriangle(ray, mesh->faces[0].v1, mesh->faces[0].v2, mesh->faces[0].v3);
    color = mesh->faces[0].color;
    for(FaceTri tri : mesh->faces){
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

//temp
void View::move(float x, float y, float z){
    cam.position.x += x;
    cam.position.y += y;
    cam.position.z += z;

    position.x += x;
    position.y += y;
    position.z += z;

    plane.updatePosition();
}