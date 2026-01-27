#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3R direction_, Color3 intensity_)
    : Light(MatrixR::identity_matrix(), MatrixR::identity_matrix())
{
    direction = direction_.normalize();
    intensity = intensity_;

    update_transformation_matrices();
}

Vector3R DirectionalLight::get_light_vector(Vector3R origin){
    return -direction;
}

DirectionalLight *DirectionalLight::transform_return(const MatrixR &m){
    return new DirectionalLight(direction, intensity);
}

void DirectionalLight::transform(const MatrixR &m){}

float DirectionalLight::get_distance(Vector3R pos){
    return 0;
}

void DirectionalLight::update_transformation_matrices(){}
