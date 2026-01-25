#ifndef RENDERER_POINTLIGHT_H
#define RENDERER_POINTLIGHT_H

#include "../Light.h"

class PointLight : public Light{
    public:
        PointLight(Vector3R position_, Color3 intensity_);

        Vector3R get_light_vector(Vector3R origin);
        
        PointLight* transform_return(const MatrixR& m) override;
        void transform(const MatrixR& m) override;

        float get_distance(Vector3R pos) override;

    private:
        Vector3R position;

        void update_transformation_matrices() override;
};

#endif // RENDERER_POINTLIGHT_H