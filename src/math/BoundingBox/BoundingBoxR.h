#ifndef RENDERER_BOUNDINGBOX_H
#define RENDERER_BOUNDINGBOX_H

// Não sei se isso devia ta na pasta math mas sigamos
#include "../utils.h"
#include "../MatrixR.h"

class BoundingBoxR{
    public:
        BoundingBoxR(Vector3R min_, Vector3R max_);

        bool get_collision(RayR ray);

        void transform(const MatrixR& m);
        BoundingBoxR transform_return(const MatrixR& m);

    private:
        Vector3R min, max;
};

#endif // RENDERER_BOUNDINGBOX_H