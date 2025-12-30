#include "Circle.h"

Circle::Circle(Vector3R point_, Vector3R normal_, float radius_, bool culled = false)
    :Plane(normal_, point_, culled)
{
    radius = radius_;
}

Circle::Circle(Plane plane, float radius_)
    :Plane(plane)
{
    radius = radius_;
}

Collision Circle::get_collision(RayR ray){
    Collision col = Plane::get_collision(ray);

    if(col.hit && (col.point - point).length() > radius) col.hit = false;

    return col;
}

Circle *Circle::transform_return(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    Plane plane = *Plane::transform_return(tr);

    // Falta atualizar o raio do circulo
    return new Circle(
        plane,
        radius
    );
}

void Circle::transform(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    Plane::transform(tr);
    
    // Falta atualizar o raio do circulo
}
