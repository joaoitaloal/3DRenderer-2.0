#ifndef RENDERER_SCENE_H
#define RENDERER_SCENE_H

#include <raylib.h>

class Camera3 {
    public:
        Vector3 position;
        Vector3 direction;

        Camera3(float set_pos_x, float set_pos_y, float set_pos_z, float set_dir_x, float set_dir_y, float set_dir_z);

        Camera3(Vector3 &set_position, Vector3 &set_direction);

        Camera3();
};

class Plane {
    private:
        Camera3* parent;
    public:
        Vector3 p1; Vector3 p2; Vector3 p3; Vector3 p4;
        float width; float height;

        // Centered in the origin(0, 0, 0)
        Plane(float set_width, float set_height, Camera3* set_parent);
        
        Plane();

        void updatePosition();
};

class Material3{
    public:
        float kd; float ks; float ka; float km; // Light intensity coefficients
};

#endif // RENDERER_SCENE_H
