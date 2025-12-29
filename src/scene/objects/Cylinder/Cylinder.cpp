#include "Cylinder.h"

Cylinder::Cylinder(Vector3R base_center_, Vector3R axis_dir_, float radius_, float height_)
    :base(base_center, -axis_dir_, radius_, false),
    roof(base_center + axis_dir_*height_, axis_dir_, radius_, false),
    Q(matrix_by_vector(vector_transpose(axis_dir), axis_dir)),
    M(subtract_matrix(identity_matrix(), Q))
{
    base_center = base_center_;
    axis_dir = axis_dir_;
    radius = radius_;
    height = height_;
}

Collision Cylinder::get_collision(RayR ray){
    return Collision();
    return get_first_collision({base.get_collision(ray), roof.get_collision(ray), get_surface_collision(ray)});
}

Collision Cylinder::get_surface_collision(RayR ray){
    Collision col;
    col.hit = false;

    Vector3R w = base_center - ray.position;

    Vector3R MRay = vector_transform(ray.direction, M);
    Vector3R MW = vector_transform(w, M);

    float a = MRay * MRay;
    float b = MRay * MW;
    float c = (MW * MW) - powf(radius, 2);

    col.distance = modified_quadratic(a, b, c);
    if(col.distance < 0) return col;

    col.point = ray.position + (ray.direction*col.distance);

    Vector3R center_to_point = col.point - base_center;
    float col_height = center_to_point * axis_dir;
    if(col_height < 0 || col_height > height) return col;

    col.normal = vector_transform(center_to_point, M).normalize();
    col.hit = true;

    return col;
}