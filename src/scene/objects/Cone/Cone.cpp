#include "Cone.h"

Cone::Cone(Vector3R base_center_, Vector3R axis_dir_, float radius_, float height_, Material3 material_):
Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix()),
Q(matrix_by_vector(vector_transpose(axis_dir_), axis_dir_)),
M(subtract_matrix(MatrixR::identity_matrix(),Q)),
base(base_center_, -axis_dir_, radius_, false)
{
    axis_dir = axis_dir_;
    base_center = base_center_;
    radius = radius_;
    height = height_;
    material = material_;
    vertice = base_center_ + (axis_dir_ * height_);
}

Collision Cone::get_collision(RayR ray)  {
    return get_first_collision({base.get_collision(ray),get_surface_collision(ray)});
}

Collision Cone::get_surface_collision(RayR ray) {
    Collision col;
    col.hit = false;

    Vector3R w = ray.position - base_center;    
    Vector3R Mdr = vector_transform(M, ray.direction);
    Vector3R Qdr = vector_transform(Q, ray.direction);
    Vector3R Mw = vector_transform(M, w);
    Vector3R Qw = vector_transform(Q, w);
    Vector3R hdc = axis_dir * height;

    float a = ((Mdr * powf(height,2)) * Mdr) - ((Qdr * powf(radius,2)) * Qdr);
    float b = 2.0 * (((Mdr * powf(height,2)) * Mw) + (Qdr * powf(radius,2)) * (hdc - Qw));
    float c = ((Mw * powf(height,2)) *  Mw) - (((Qw - hdc) * powf(radius,2)) * (Qw - hdc));
    col.distance = modified_quadratic(a,b,c);
    if(col.distance < 0) return col;

    Vector3R p = ray.position + (ray.direction * col.distance);

    // testar a altura do cone
    float altura = (p - base_center) * axis_dir;
    if (altura < 0 || altura > height) return col;
    
    Vector3R u = (vertice - p).normalize();
    MatrixR ut = matrix_by_vector(vector_transpose(u), u);
    MatrixR Mu = subtract_matrix(MatrixR::identity_matrix(),ut);
    Vector3R normal = vector_transform(Mu, axis_dir);
    col.hit = true;
    col.normal = normal.normalize();
    col.point = p;

    return col;
}

Cone* Cone::transform_return(const MatrixR& m){
    return nullptr;
}

void Cone::transform(const MatrixR& m){
}