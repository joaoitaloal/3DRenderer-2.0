#include "Circle.h"

Circle::Circle(Vector3R point_, Vector3R normal_, float radius_, Material3 material_, bool culled = false)
    :Plane(normal_, point_, material_, nullptr, culled)
{
    radius = radius_;
    material = material_;

    update_transformation_matrices();
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

    return new Circle(
        plane,
        radius
    );
}

void Circle::transform(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    Plane::transform(tr);
    
    update_transformation_matrices();
}

void Circle::update_radius(float radius_){
    radius = radius_;
}

void Circle::update_transformation_matrices(){
    // Situação parecida com a do triangulo, não existe sem um objeto pai, talvez mudar a classe disso
}
