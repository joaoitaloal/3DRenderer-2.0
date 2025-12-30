#include "Cylinder.h"

Cylinder::Cylinder(Vector3R base_center_, Vector3R axis_dir_, float radius_, float height_, Material3 material_)
    : Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix()),
    base(base_center_, -axis_dir_, radius_, false),
    roof(base_center_ + axis_dir_*height_, axis_dir_, radius_, false),
    Q(matrix_by_vector(vector_transpose(axis_dir_), axis_dir_)),
    M(subtract_matrix(MatrixR::identity_matrix(), Q))
{
    base_center = base_center_;
    axis_dir = axis_dir_;
    radius = radius_;
    height = height_;
    material = material_;

    // Isso deveria ser o centro da base ou o centro do cilindro?
    world_to_object.m3 = -base_center.x;
    world_to_object.m7 = -base_center.y;
    world_to_object.m11 = -base_center.z;

    object_to_world = world_to_object.invert_matrix();
}

Collision Cylinder::get_collision(RayR ray){
    return get_first_collision({base.get_collision(ray), roof.get_collision(ray), get_surface_collision(ray)});
}

Cylinder* Cylinder::transform_return(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));
    
    // Falta atualizar o raio e a altura
    return new Cylinder(
        vector_transform(tr, base_center),
        normal_transform(tr, axis_dir),
        radius,
        height,
        material
    );
}

void Cylinder::transform(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    base_center = vector_transform(tr, base_center);

    axis_dir = normal_transform(tr, axis_dir);

    // Provavelmente mais rápido criar dois circulos novos
    base.transform(tr);
    roof.transform(tr);

    Q = matrix_by_vector(vector_transpose(axis_dir), axis_dir);
    M = subtract_matrix(MatrixR::identity_matrix(), Q);

    // Falta atualizar o raio e a altura

    world_to_object.m3 = -base_center.x;
    world_to_object.m7 = -base_center.y;
    world_to_object.m11 = -base_center.z;

    object_to_world = world_to_object.invert_matrix();
}

// ToDo: caso a colisão ocorra na parte de dentro, inverter a normal, ou enfim fazer mudanças necessárias pra ver a parte de dentro
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