#include "Cylinder.h"

Cylinder::Cylinder(Vector3R base_center_, Vector3R axis_dir_, float radius_, float height_, Material3 material_)
    :base(base_center_, -axis_dir_, radius_, false),
    roof(base_center_ + axis_dir_*height_, axis_dir_, radius_, false),
    Q(matrix_by_vector(vector_transpose(axis_dir_), axis_dir_)),
    M(subtract_matrix(identity_matrix(), Q))
{
    base_center = base_center_;
    axis_dir = axis_dir_;
    radius = radius_;
    height = height_;
    material = material_;
}

Collision Cylinder::get_collision(RayR ray){
    return get_first_collision({base.get_collision(ray), roof.get_collision(ray), get_surface_collision(ray)});
}

Cylinder* Cylinder::transform(MatrixR m){
    //return Shape();
}

Collision Cylinder::get_surface_collision(RayR ray){
    Collision col;
    col.hit = false;

    Vector3R w = ray.position - base_center;

    Vector3R MRay = vector_transform(M, ray.direction);
    Vector3R MW = vector_transform(M, w);

    float a = MRay * MRay;
    float b = 2*(MRay * MW);
    float c = (MW * MW) - powf(radius, 2);

    col.distance = modified_quadratic(a, b, c);
    if(col.distance < 0) return col;

    col.point = ray.position + (ray.direction*col.distance);

    Vector3R center_to_point = col.point - base_center;
    float col_height = center_to_point * axis_dir;
    if(col_height < 0 || col_height > height) return col;

    col.normal = vector_transform(M, center_to_point).normalize();
    col.hit = true;

    return col;
}