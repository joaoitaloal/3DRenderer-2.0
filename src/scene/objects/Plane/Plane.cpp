#include "Plane.h"

Plane::Plane(Vector3R normal_, Vector3R point_, Material3 material_, Textura* tex, string name_, bool culled = false)
    : Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix(), name_)
{
    normal = normal_.normalize();
    point = point_;
    material = material_;

    backface_culled = culled;
    this->texture = tex;

    update_transformation_matrices();
}

Plane::Plane(Vector3R v1, Vector3R v2, Vector3R v3, Textura* tex, string name_, bool culled = false)
    :Shape(MatrixR::identity_matrix(), MatrixR::identity_matrix(), name_)
{
    Vector3R p1 = v2-v1; Vector3R p2 = v3-v1;
    normal = cross_product(p1, p2).normalize();

    point = v1;
    backface_culled = culled;
    texture = tex;
    
    update_transformation_matrices();
}

Collision Plane::get_collision(RayR ray)
{
    Collision col;
    col.hit = false;

    float dir_dot = ray.direction * normal;
    if((backface_culled && dir_dot >= 0) || dir_dot == 0) return col;

    // Se tiver muito ilegivel dá pra separar em várias linhas
    col.distance = -(((ray.position - point) * normal)/dir_dot);
    if(col.distance < 0) return col;

    col.hit = true;
    col.normal = normal;
    col.point = ray.calculate_point(col.distance);

    if(texture != nullptr){
        float escala = 0.01;

        Vector3R texPoint = col.point - point;
        
        Vector3R up = {0, 1, 0};
        float dot = normal*up;
        if(dot != 1){
            MatrixR texRot = get_rotation_around_axis(acos(dot), cross_product(normal, up).normalize());
            texPoint = vector_transform(texRot, texPoint);
        }
        
        col.u = texPoint.x * escala;
        col.v = texPoint.z * escala;
        col.u = col.u - std::floor(col.u);
        col.v = col.v - std::floor(col.v);
    }

    return col;
}

Plane* Plane::transform_return(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    return new Plane(
        normal_transform(tr, normal), 
        vector_transform(tr, point), 
        material,
        texture,
        name,
        backface_culled
    );
}

void Plane::transform(const MatrixR& m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    normal = normal_transform(tr, normal);
    point = vector_transform(tr, point);

    update_transformation_matrices();
}

Vector3R Plane::get_normal(){
    return normal;
}

void Plane::update_transformation_matrices(){
    world_to_object.m3 = -point.x;
    world_to_object.m7 = -point.y;
    world_to_object.m11 = -point.z;

    // Tecnicamente não precisa dessa função, mas a gente usa transformações tão raramente que tá ok
    object_to_world = world_to_object.invert_matrix();
}
