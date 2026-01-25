#include "Sphere.h"

Sphere::Sphere(Vector3R sphere_center_, float radius_, Material3 material_, Textura* tex, string name_)
    : Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix(), name_),
    sphere_center(sphere_center_), 
    radius(radius_)
{
    material = material_;
    this->texture = tex;

    update_transformation_matrices();
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

    col.point = ray.calculate_point(col.distance);
    Vector3R p = col.point - sphere_center;

    col.normal = p.normalize();
    col.hit = true;

    col.u = 0.5f + std::atan2(col.normal.z, col.normal.x)/(2.0f * PI);
    col.v = 0.5f - std::asin(col.normal.y)/PI;

    return col;
}

Sphere* Sphere::transform_return(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    return new Sphere(
        vector_transform(tr, sphere_center), 
        radius, 
        material,
        texture,
        name
    );
}

void Sphere::transform(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    sphere_center = vector_transform(tr, sphere_center);
    
    update_transformation_matrices();
}

void Sphere::set_radius(float radius_){
    radius = radius_;
}

void Sphere::scale(Vector3R dims){
    set_radius(radius*dims.length());
}

void Sphere::set_center(Vector3R pos){
    sphere_center = pos;
}

void Sphere::update_transformation_matrices(){
    world_to_object.m3 = -sphere_center.x;
    world_to_object.m7 = -sphere_center.y;
    world_to_object.m11 = -sphere_center.z;

    // Tecnicamente não precisa dessa função, mas a gente usa transformações tão raramente que tá ok
    object_to_world = world_to_object.invert_matrix();
}