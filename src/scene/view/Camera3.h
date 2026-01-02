#ifndef RENDERER_CAMERA3_H
#define RENDERER_CAMERA3_H

#include "../../math/MatrixR.h"
#include "../../math/Vector3R.h"

// Plano de visão
class WorldWindow {
    public:
        WorldWindow(float set_width, float set_height, Vector3R parent_pos);

        void move(float x, float y, float z, Vector3R left, Vector3R forwards, Vector3R up);
        void rotate(float x_angle, float y_angle, float z_angle, Vector3R parent_pos, Vector3R left, Vector3R forwards, Vector3R up);

        Vector3R bi_interpolate(float alpha, float beta);

        Vector3R calculate_forward();
        Vector3R calculate_up();
        Vector3R calculate_left();

    protected:
        Vector3R p1; Vector3R p2; Vector3R p3; Vector3R p4;
        float width; float height;
};

class Camera3 {
    public:
        Camera3(float x_, float y_, float z_, float view_width_, float view_height_, float plane_distance_);
        void move(float x, float y, float z);
        void rotate(float x_angle, float y_angle, float z_angle);

        Vector3R get_position();

        Vector3R bi_interpolate(float alpha, float beta);

    protected:
        Vector3R position;
        WorldWindow win;

        Vector3R left;
        Vector3R forwards;
        Vector3R up;
};

#endif // RENDERER_CAMERA3_H