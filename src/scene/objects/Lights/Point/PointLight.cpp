#include "PointLight.h"

PointLight::PointLight(Vector3R position_, Color3 intensity_)
    : Light(MatrixR::identity_matrix(), MatrixR::identity_matrix())
{
    position = position_;
    intensity = intensity_;

    update_transformation_matrices();
}

Vector3R PointLight::get_light_vector(Vector3R origin){
    return (position - origin).normalize();
}

PointLight *PointLight::transform_return(const MatrixR &m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));

    return new PointLight(
        vector_transform(tr, position),
        intensity
    );
}

void PointLight::transform(const MatrixR &m){
    MatrixR tr = mul_mat(object_to_world, mul_mat(m, world_to_object));
    
    position = vector_transform(tr, position);
}

void PointLight::update_transformation_matrices(){
    world_to_object.m3 = -position.x;
    world_to_object.m7 = -position.y;
    world_to_object.m11 = -position.z;

    object_to_world = world_to_object.invert_matrix();
}
