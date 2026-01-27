#ifndef RENDERER_DIRECTIONALLIGHT_H
#define RENDERER_DIRECTIONALLIGHT_H

#include "../Light.h"

// TODO
class DirectionalLight : public Light {
    public:
        DirectionalLight(Vector3R direction_, Color3 intensity_);

        Vector3R get_light_vector(Vector3R origin);
        
        DirectionalLight* transform_return(const MatrixR& m) override;
        void transform(const MatrixR& m) override;

        float get_distance(Vector3R pos) override;

    private:
        Vector3R direction;

        void update_transformation_matrices() override;
};

#endif // RENDERER_DIRECTIONALLIGHT_H