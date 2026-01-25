#ifndef RENDERER_CAMERA3_H
#define RENDERER_CAMERA3_H

#include "../../math/MatrixR.h"
#include "../../math/Vector3R.h"

// Plano de visão
class WorldWindow {
    public:
        WorldWindow(float set_width, float set_height, float depth_, Vector3R parent_pos);

        void move(float x, float y, float z, Vector3R left, Vector3R forwards, Vector3R up);
        void rotate(float x_angle, float y_angle, float z_angle, Vector3R parent_pos, Vector3R left, Vector3R forwards, Vector3R up);

        Vector3R bi_interpolate(float alpha, float beta);

        Vector3R calculate_forward();
        Vector3R calculate_up();
        Vector3R calculate_left();

        float get_width();
        float get_height();
        float get_depth();

        void set_zoom(float zoom_, Vector3R parent_pos, Vector3R left, Vector3R forwards, Vector3R up);

        // HACK: temp i guess
        void set_dimensions(Vector3R dims, Vector3R parent_pos, Vector3R left, Vector3R forwards, Vector3R up);
        void update_dimensions(Vector3R parent_pos, Vector3R left, Vector3R forwards, Vector3R up);

        protected:
            Vector3R p1, p2, p3, p4;
            float width, height, depth;
            float zoom;

};

class Camera3 {
    public:
        Camera3(Vector3R position_, float view_width_, float view_height_, float plane_distance_);

        void move(float x, float y, float z);
        void move_to(float x, float y, float z);

        void rotate(float x_angle, float y_angle, float z_angle);

        void look_at(float x, float y, float z);

        Vector3R get_position();
        Vector3R get_forwards();

        Vector3R bi_interpolate(float alpha, float beta);

        void set_dimensions(Vector3R dims);

        // HACK: temp
        void set_up(Vector3R up_);
        void set_zoom(float amount);

    protected:
        Vector3R position;
        WorldWindow win;

        Vector3R left, forwards, up;
};

#endif // RENDERER_CAMERA3_H