#include "PointLight.h"

PointLight::PointLight(Vector3R position_, Color3 intensity_){
    position = position_;
    intensity = intensity_;
}

Vector3R PointLight::get_light_vector(Vector3R origin)
{
    return (position - origin).normalize();
}