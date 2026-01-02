#include "Sphere.h"

Sphere::Sphere(Vector3R sphere_center_, float radius_, Material3 material_)
    : Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix()),
    sphere_center(sphere_center_), 
    radius(radius_) 
{
    material = material_;

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

    Vector3R rt = ray.position + ray.direction * col.distance;
    Vector3R p = rt - sphere_center;
    Vector3R normal = p.normalize();

    // Se tiver muito ilegivel dá pra separar em várias linhas
    col.hit = true;
    col.normal = normal;
    col.point = ray.position + (ray.direction*col.distance);

    return col;
}

Sphere* Sphere::transform_return(const MatrixR& m){
    //MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));
    MatrixR tr = m;

    return new Sphere(
        vector_transform(tr, sphere_center), 
        radius * (tr.trace()-m.m15)/3, 
        material
    );
}

void Sphere::transform(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    sphere_center = vector_transform(tr, sphere_center);

    // Gambiarrinha, a escala é aplicada pegando a média da diagonal da matriz
    // Tá erradissimo inclusive, rotação e cisalhamento tá modificando o raio 
    radius = radius * (tr.trace()-m.m15)/3;
    
    update_transformation_matrices();
}

void Sphere::update_transformation_matrices(){
    world_to_object.m3 = -sphere_center.x;
    world_to_object.m7 = -sphere_center.y;
    world_to_object.m11 = -sphere_center.z;

    object_to_world = world_to_object.invert_matrix();
}
