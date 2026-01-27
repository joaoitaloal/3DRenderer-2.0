#include "Cone.h"

Cone::Cone(Vector3R base_center_, Vector3R axis_dir_, float radius_, float height_, Material3 material_, Textura* tex, string name_)
    :Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix(), name_),
Q(matrix_by_vector(vector_transpose(axis_dir_), axis_dir_)),
M(subtract_matrix(MatrixR::identity_matrix(),Q)),
base(base_center_, -axis_dir_, radius_, material_, nullptr, "Base", true),
texture(tex),
base_center(base_center_),
axis_dir(axis_dir_),
radius(radius_),
height(height_),
vertice(base_center + (axis_dir * height))
{
    material = material_;

    update_transformation_matrices();
}

Collision Cone::get_collision(RayR ray)  {
    return get_first_collision({base.get_collision(ray), get_surface_collision(ray)});
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

    float h2 = powf(height, 2);
    float r2 = powf(radius, 2);

    float a = h2*(Mdr * Mdr) - r2*(Qdr * Qdr);
    float b = 2.0 * (h2*(Mdr * Mw) + r2*(Qdr * (hdc - Qw)));
    
    Vector3R qw_minus_hdc = (Qw - hdc);
    float c = h2* (Mw * Mw) - r2*( qw_minus_hdc * qw_minus_hdc);

    float delta = powf(b, 2) - (4*a*c);

    if(delta < 0) return col;
    delta = sqrtf(delta);

    float x1 = (-b + delta)/(2*a);
    float x2 = (-b - delta)/(2*a);

    Vector3R point1 = ray.calculate_point(x1);
    Vector3R point2 = ray.calculate_point(x2);

    Vector3R vecH1 = vector_transform(Q, point1 - base_center);
    Vector3R vecH2 = vector_transform(Q, point2 - base_center);

    bool hit1 = false;
    bool hit2 = false;

    if(vecH1*axis_dir > 0 && vecH1.length() <= height){
        col.point = point1;
        col.distance = x1;
        hit1 = true;
    }
    if(vecH2*axis_dir > 0 && vecH2.length() <= height){
        if((!hit1 && x2 > 0) || (x1 > x2 && x2 > 0)){
            col.point = point2;
            col.distance = x2;
        }
        hit2 = true;
    }
    if((!hit1 && !hit2) || col.distance < 0) return col;
    
    Vector3R u = (vertice - col.point).normalize();
    MatrixR ut = matrix_by_vector(vector_transpose(u), u);
    MatrixR Mu = subtract_matrix(MatrixR::identity_matrix(), ut);

    col.normal = vector_transform(Mu, axis_dir).normalize();
    col.hit = true;

    return col;
}

void Cone::update_transformation_matrices(){
    world_to_object.m3 = -base_center.x;
    world_to_object.m7 = -base_center.y;
    world_to_object.m11 = -base_center.z;

    object_to_world = world_to_object.invert_matrix();
}

Cone* Cone::transform_return(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));
    
    return new Cone(
        vector_transform(tr, base_center),
        normal_transform(tr, axis_dir),
        radius,
        height,
        material,
        texture,
        name
    );
}

void Cone::transform(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    base_center = vector_transform(tr, base_center);
    axis_dir = normal_transform(tr, axis_dir);

    base = {base_center, -axis_dir, radius, material, nullptr, "Base", true};
    vertice = base_center + (axis_dir * height);

    Q = matrix_by_vector(vector_transpose(axis_dir), axis_dir);
    M = subtract_matrix(MatrixR::identity_matrix(), Q);

    update_transformation_matrices();
}

void Cone::update_radius(float radius_){
    radius = radius_;
    base.update_radius(radius);
}

void Cone::update_height(float height_){
    height = height_;
    vertice = base_center + (axis_dir * height);
}

void Cone::scale(Vector3R dims){
    update_height(height*dims.y);
    update_radius(radius*(dims.x+dims.z)/2);
}
