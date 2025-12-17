#include "PointLight.h"

PointLight::PointLight(Vector3 position_, Color3 intensity_){
    position = position_;
    intensity = intensity_;
}

Vector3 PointLight::get_light_vector(Vector3 origin)
{
    return Vector3Normalize(position - origin);
}