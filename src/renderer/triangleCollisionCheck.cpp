#include "renderer.h"

// Most of the math for this code comes from chapter 4 and 5 of Fundamentals of Computer Graphics by Peter Shirley
// After a very simple and quick test this seems to be as fast as the raylib version??
// The book does not say what algorithm is this which is very weird but after some reading im pretty sure it is more-trumbore, which is the same technique used on raylib, so the similar speed makes sense

// Raylib already has this function but i want to try a custom implementation from zero to compare how badly it performs
RayCollision triangleCollisionCheck(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3){
    // Some terrible naming conventions here
    RayCollision col;
    
    // M  = a(ei - hf) + b(gf - di) + d(dh- eg)
    float a = p1.x - p2.x; float d = p1.x - p3.x; float g = ray.direction.x; float j = p1.x - ray.position.x;
    float b = p1.y - p2.y; float e = p1.y - p3.y; float h = ray.direction.y; float k = p1.y - ray.position.y;
    float c = p1.z - p2.z; float f = p1.z - p3.z; float i = ray.direction.z; float l = p1.z - ray.position.z;

    float ei_minus_hf = e*i - h*f;
    float gf_minus_di = g*f - d*i;
    float dh_minus_eg = d*h - e*g;
    float M = a*ei_minus_hf + b*gf_minus_di + c*dh_minus_eg;

    float ak_minus_jb = a*k - j*b;
    float jc_minus_al = j*c - a*l;
    float bl_minus_kc = b*l - k*c;
    float t = (f*ak_minus_jb + e*jc_minus_al + d*bl_minus_kc)/M;

    if(t < 0){
        col.hit = false;
        return col;
    }

    float gamma = (i*ak_minus_jb + h*jc_minus_al + g*bl_minus_kc)/M;

    if(gamma < 0 || gamma > 1){
        col.hit = false;
        return col;
    }

    float beta = (j*ei_minus_hf + k*gf_minus_di + l*dh_minus_eg)/M;

    if(beta < 0 || beta > 1 - gamma){
        col.hit = false;
        return col;
    }

    // hit
    col.hit = true;
    col.distance = t;
    col.point = p1 + (p2 - p1)*beta + (p3 - p1)*gamma;

    Vector3 v1 = p2-p1; Vector3 v2 = p3-p1;
    Vector3 normal = {v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x};
    col.normal = Vector3Normalize(normal);

    return col;
}