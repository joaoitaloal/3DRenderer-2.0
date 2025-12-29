#include "Circle.h"

Circle::Circle(Vector3R point_, Vector3R normal_, float radius_, bool culled = false)
    :Plane(normal_, point_, culled)
{
    radius = radius_;
}

Collision Circle::get_collision(RayR ray){
    Collision col = Plane::get_collision(ray);

    if(col.hit && (col.point - point).length() > radius) col.hit = false;

    return col;
}

Circle *Circle::transform(MatrixR m)
{

}
