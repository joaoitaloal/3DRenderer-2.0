#ifndef RENDERER_SCENE_H
#define RENDERER_SCENE_H

#include "../math/Vector3R.h"

class Camera3 {
    public:
        Vector3R position;
        Vector3R direction;

        Camera3(float set_pos_x, float set_pos_y, float set_pos_z, float set_dir_x, float set_dir_y, float set_dir_z);

        Camera3(Vector3R &set_position, Vector3R &set_direction);

        Camera3();
};

// Plano de visão especificamente, tem que mudar de nome
class PlaneV {
    private:
        Camera3* parent;
    public:
        Vector3R p1; Vector3R p2; Vector3R p3; Vector3R p4;
        float width; float height;

        // Centered in the origin(0, 0, 0)
        PlaneV(float set_width, float set_height, Camera3* set_parent);
        
        PlaneV();

        void updatePosition();
};

#endif // RENDERER_SCENE_H
