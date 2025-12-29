#include "Sphere.h"

Sphere::Sphere(Vector3R sphere_center_, float radius_, Material3 material_)
: sphere_center(sphere_center_), radius(radius_) 
{
    material = material_;
}

Collision Sphere::get_collision(RayR ray){
    Collision col;
    col.hit = false;

    Vector3R w = ray.position - sphere_center;
    float a = ray.direction * ray.direction; 
    float b = 2 * (ray.direction * w);
    float c = (w * w) - radius * radius;
    col.distance = modified_quadratic(a,b,c);
    if(col.distance < 0) return col;

    Vector3R rt = ray.position + ray.direction * col.distance;
    Vector3R p = rt - sphere_center;
    Vector3R normal = p.normalize();

    // Se tiver muito ilegivel dá pra separar em várias linhas
    col.hit = true;
    col.normal = normal;
    col.point = ray.position + (ray.direction*col.distance);

    return col;
}

Sphere* Sphere::transform(MatrixR m){

}
