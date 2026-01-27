#include "Ring.h"

Ring::Ring(Vector3R point_, Vector3R normal_, float radius1_, float radius2_, Material3 material_, Textura *tex, string name_, bool culled)
    : Circle(point_, normal_, radius1_, material_, tex, name_, culled)
{
    radius2 = radius2_;
}

Collision Ring::get_collision(RayR ray)
{
    Collision col = Circle::get_collision(ray);
    
    if(col.hit && (col.point - point).length() < radius2 - EPSILON) col.hit = false;

    return col;
}
