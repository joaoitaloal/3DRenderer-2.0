#include "Plane.h"

Plane::Plane(Vector3R normal_, Vector3R point_, bool culled = false){
    normal = normal_;
    point = point_;

    backface_culled = culled;
}

Plane::Plane(Vector3R v1, Vector3R v2, Vector3R v3, bool culled = false){
    Vector3R p1 = v2-v1; Vector3R p2 = v3-v1;
    normal = cross_product(p1, p2).normalize();

    point = v1;
    backface_culled = culled;
}

Collision Plane::get_collision(RayR ray)
{
    Collision col;
    col.hit = false;

    float dir_dot = ray.direction * normal;
    if((backface_culled && dir_dot >= 0) || dir_dot == 0) return col;

    // Se tiver muito ilegivel dá pra separar em várias linhas
    col.distance = -(((ray.position - point) * normal)/dir_dot);
    if(col.distance < 0) return col;

    col.hit = true;
    col.normal = normal;
    col.point = ray.position + (ray.direction*col.distance);

    return col;
}
