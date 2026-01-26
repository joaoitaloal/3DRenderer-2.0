#include "Circle.h"

Circle::Circle(Vector3R point_, Vector3R normal_, float radius_, Material3 material_, string name_, bool culled = false)
    :Plane(normal_, point_, material_, nullptr, name_, culled)
{
    radius = radius_;
    material = material_;

    update_transformation_matrices();
}

Circle::Circle(Vector3R point_, Vector3R normal_, float radius_, Material3 material_, Textura *tex, string name_, bool culled)
    :Plane(normal_, point_, material_, tex, name_, culled)
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

    if(col.hit && (col.point - point).length() > radius + EPSILON) col.hit = false;

    return col;
}

Circle *Circle::transform_return(const MatrixR& m){
    //MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    Plane plane = *Plane::transform_return(m);

    return new Circle(
        plane,
        radius
    );
}

void Circle::transform(const MatrixR& m){
    //MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    Plane::transform(m);
    
    update_transformation_matrices();
}

void Circle::update_radius(float radius_){
    radius = radius_;
}

void Circle::scale(Vector3R dims){
    update_radius(radius*dims.length());
}

// Criando um raio na direção do plano pra ver a distância
float Circle::get_distance(Vector3R point_){
    RayR testRay = {point_, -normal};
    return Plane::get_collision(testRay).distance;
}

void Circle::rotate_to(Vector3R point_){
    normal = (point_ - point).normalize();
}

void Circle::update_transformation_matrices(){
    // Situação parecida com a do triangulo, não existe sem um objeto pai, talvez mudar a classe disso
}
