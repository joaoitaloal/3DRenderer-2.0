#include "view.h"
#include "../../renderer/renderer.h"
#include <vector>

inline float max(float a, float b){
    return a > b?a:b;
}

View::View(float set_x, float set_y, float set_z, float set_plane_width, float set_plane_height){
    position = {set_x, set_y, set_z};

    cam = {set_x, set_y, set_z, 0, 0, 1};
    plane = {set_plane_width, set_plane_height, &cam};
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
Color3 View::rayCast(float origin_x, float origin_y, int WIDTH, int HEIGHT, std::vector<Mesh3*>* meshes, std::vector<PointLight> lights){
    Color3 color = {0, 0, 0, 255};

    float alpha = origin_x/WIDTH;
    float beta = origin_y/HEIGHT;

    Ray ray = createRay(alpha, beta);

    Mesh3* mesh;
    RayCollision col;
    col.hit = false;
    for(Mesh3* curMesh : *meshes){
        
        RayCollision temp = meshCollisionCheck(ray, curMesh);
        if(!col.hit || (temp.hit && col.distance > temp.distance)){
            col = temp;
            mesh = curMesh;
        }
    }

    if(!col.hit){
        return color;
    }

    // Shading
    float ALI = 20; // temporary constant Ambient Light Intensity
    color = color + mesh->material.ka*ALI;

    for(PointLight light : lights){
        Vector3 lightDir = light.pos - col.point;
        Ray shadowCheckRay = {col.point + lightDir*EPSILON, lightDir};

        RayCollision shadowCol;
        shadowCol.hit = false;
        for(Mesh3* shadowMesh : *meshes){
            if(meshShadowCheck(shadowCheckRay, shadowMesh)){
                shadowCol.hit = true;
                
                return color;
            }
        }

        Vector3 l = Vector3Normalize(lightDir);

        color = color + light.intensity*mesh->material.kd*max(0, Vector3DotProduct(col.normal, l));

        Vector3 v = Vector3Normalize(cam.position - col.point);
        Vector3 h = Vector3Normalize(v+l);

        color = color + light.intensity*mesh->material.ks*powf(max(0, Vector3DotProduct(col.normal, h)), 10);

        // Specular Reflection
        Vector3 r = Vector3Normalize(ray.direction - col.normal*(Vector3DotProduct(ray.direction, col.normal))*2);
        Ray reflection = {col.point + r*EPSILON, r};

        color = color + genericRecursiveRayCast(reflection, meshes, lights, 0)*mesh->material.km;
    }

    return color.clampMax();
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