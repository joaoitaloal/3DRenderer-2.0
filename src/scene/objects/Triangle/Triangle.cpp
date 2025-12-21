#include "Triangle.h"

#include <limits>

Triangle::Triangle(Vector3R v1_, Vector3R v2_, Vector3R v3_){
    v1 = v1_;
    v2 = v2_;
    v3 = v3_;
}

/* 
    Most of the math for this code comes from chapter 4 and 5 of Fundamentals of Computer Graphics by Peter Shirley
    After a very simple and quick test this seems to be as fast as the raylib version??
    The book does not say what algorithm is this which is very weird but after some reading im pretty sure it is more-trumbore, which is the same technique used on raylib, so the similar speed makes sense
    After some more tests it actually is about 1.25x slower than the raylib version, should take a look at the source for raylib and see what is different there
*/
// Raylib already has this function but i wanted to try a custom implementation from zero to compare how badly it performs
Collision Triangle::get_collision(RayR ray){
    // Some terrible naming conventions here
    Collision col;
    const double inf = std::numeric_limits<float>::infinity();
    
    // M  = a(ei - hf) + b(gf - di) + d(dh- eg)
    float a = v1.x - v2.x; float d = v1.x - v3.x; float g = ray.direction.x; float j = v1.x - ray.position.x;
    float b = v1.y - v2.y; float e = v1.y - v3.y; float h = ray.direction.y; float k = v1.y - ray.position.y;
    float c = v1.z - v2.z; float f = v1.z - v3.z; float i = ray.direction.z; float l = v1.z - ray.position.z;

    float ei_minus_hf = e*i - h*f;
    float gf_minus_di = g*f - d*i;
    float dh_minus_eg = d*h - e*g;
    float M = a*ei_minus_hf + b*gf_minus_di + c*dh_minus_eg;

    float ak_minus_jb = a*k - j*b;
    float jc_minus_al = j*c - a*l;
    float bl_minus_kc = b*l - k*c;
    float t = -(f*ak_minus_jb + e*jc_minus_al + d*bl_minus_kc)/M;

    if(t < 0){
        col.distance = inf;
        col.hit = false;
        return col;
    }

    float gamma = (i*ak_minus_jb + h*jc_minus_al + g*bl_minus_kc)/M;

    if(gamma < 0 || gamma > 1){
        col.distance = inf;
        col.hit = false;
        return col;
    }

    float beta = (j*ei_minus_hf + k*gf_minus_di + l*dh_minus_eg)/M;

    if(beta < 0 || beta > 1 - gamma){
        col.distance = inf;
        col.hit = false;
        return col;
    }

    // hit
    col.hit = true;
    col.distance = t;
    Vector3R test = (v2 - v1)*beta + (v3 - v1)*gamma;
    col.point = v1 + test;

    Vector3R p1 = v2-v1; Vector3R p2 = v3-v1;
    col.normal = Vector3R{p1.y*p2.z - p1.z*p2.y, p1.z*p2.x - p1.x*p2.z, p1.x*p2.y - p1.y*p2.x}.normalize();

    return col;
}