#include "Cylinder.h"

Cylinder::Cylinder(Vector3R base_center_, Vector3R axis_dir_, float radius_, float height_, Material3 material_, Textura* tex, string name_)
    : Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix(), name_),
    base(base_center_, -axis_dir_, radius_, material_, "Base", false),
    roof(base_center_ + axis_dir_*height_, axis_dir_, radius_, material_, "Roof", false),
    Q(matrix_by_vector(vector_transpose(axis_dir_), axis_dir_)),
    M(subtract_matrix(MatrixR::identity_matrix(), Q))
{
    base_center = base_center_;
    axis_dir = axis_dir_;
    radius = radius_;
    height = height_;
    material = material_;
    this->texture = tex;

    update_transformation_matrices();
}

Collision Cylinder::get_collision(RayR ray){
    return get_first_collision({base.get_collision(ray), roof.get_collision(ray), get_surface_collision(ray)});
}

Cylinder* Cylinder::transform_return(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    return new Cylinder(
        vector_transform(tr, base_center),
        normal_transform(tr, axis_dir),
        radius,
        height,
        material,
        texture,
        name
    );
}

void Cylinder::transform(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    base_center = vector_transform(tr, base_center);

    axis_dir = normal_transform(tr, axis_dir);

    base = {base_center, -axis_dir, radius, material, "Base", false};
    roof = {base_center + axis_dir*height, axis_dir, radius, material, "Roof", false};

    Q = matrix_by_vector(vector_transpose(axis_dir), axis_dir);
    M = subtract_matrix(MatrixR::identity_matrix(), Q);

    update_transformation_matrices();
}

void Cylinder::update_radius(float radius_){
    radius = radius_;
    base = {base_center, -axis_dir, radius, material, "Base", false};
    roof = {base_center + axis_dir*height, axis_dir, radius, material, "Roof", false};
}

void Cylinder::update_height(float height_){
    height = height_;
}

void Cylinder::scale(Vector3R dims){
    update_height(height*dims.y);
    dims.y = 0;
    update_radius(radius*dims.length());
}

// TODO: caso a colisão ocorra na parte de dentro, inverter a normal, ou enfim fazer mudanças necessárias pra ver a parte de dentro
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

    col.point = ray.calculate_point(col.distance);

    Vector3R center_to_point = col.point - base_center;
    float col_height = center_to_point * axis_dir;
    if(col_height < 0 || col_height > height) return col;

    col.normal = vector_transform(M, center_to_point).normalize();
    col.hit = true;
    Vector3R radial = center_to_point - axis_dir * col_height;

    Vector3R U;
    if (fabs(axis_dir.y) < 0.9f)
        U = cross_product(axis_dir,Vector3R(0,1,0)).normalize();
    else
        U = cross_product(axis_dir, Vector3R(1,0,0)).normalize();

    Vector3R V = cross_product(axis_dir ,U);

    float x = radial * U;
    float z = radial * V;

    col.u = 0.5f + atan2(z, x) / (2.0f * PI);
    col.v = col_height / height;

    return col;
}

void Cylinder::update_transformation_matrices(){
    world_to_object.m3 = -base_center.x;
    world_to_object.m7 = -base_center.y;
    world_to_object.m11 = -base_center.z;

    /* Esse código não devia ta aqui mas talvez ele seja util em algum lugar, é pra deixar o objeto reto em uma direção
    Vector3R up(0, 1, 0);
    float u_angle = angle_from_vectors(axis_dir, up);
    
    // Provavelmente tem como fazer isso de forma mais eficiente,
    // Talvez usando aquela matriz de rotação unica ao invés de uma pra cada eixo
    MatrixR rotation_y = get_y_rotation(u_angle);
    MatrixR rotation_z = get_z_rotation(u_angle);
    world_to_object = mul_mat(rotation_y, world_to_object);
    world_to_object = mul_mat(rotation_z, world_to_object);*/ 

    object_to_world = world_to_object.invert_matrix();
}
