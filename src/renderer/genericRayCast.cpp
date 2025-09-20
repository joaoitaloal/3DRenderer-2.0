#include "renderer.h"

inline float max(float a, float b){
    return a > b?a:b;
}

Color3 genericRecursiveRayCast(Ray ray, std::vector<Mesh3*>* meshes, std::vector<PointLight> lights, int depth){
    Color3 color = {0, 0, 0, 255};
    if(depth > 3){
        return color;
    }
    
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
    float ALI = 50; // temporary constant Ambient Light Intensity
    color = color + mesh->material.ka*ALI;

    for(PointLight light : lights){
        Vector3 shadowRayDir = light.pos - col.point;
        Ray shadowCheckRay = {col.point + shadowRayDir*EPSILON, shadowRayDir};

        RayCollision shadowCol;
        shadowCol.hit = false;
        for(Mesh3* shadowMesh : *meshes){
            if(meshShadowCheck(shadowCheckRay, shadowMesh)){
                shadowCol.hit = true;
                
                return color;
            }
        }

        Vector3 l = Vector3Normalize(shadowRayDir);

        color = color + light.intensity*mesh->material.kd*max(0, Vector3DotProduct(col.normal, l));

        Vector3 v = Vector3Normalize(ray.position - col.point);
        Vector3 h = Vector3Normalize(v+l);

        color = color + light.intensity*mesh->material.ks*powf(max(0, Vector3DotProduct(col.normal, h)), 10);

        // Specular Reflection
        Vector3 r = Vector3Normalize(ray.direction - col.normal*(Vector3DotProduct(ray.direction, col.normal))*2);
        Ray reflection = {col.normal + r*EPSILON, r};

        color = color + genericRecursiveRayCast(reflection, meshes, lights, depth + 1)*mesh->material.km;
    }

    return color.clampMax();
}