#include <raymath.h>

class Camera3 {
    public:
        Vector3 position;

        Camera3(float set_x, float set_y, float set_z){
            position = {set_x, set_y, set_z};
        }

        Camera3(Vector3 &set_position)
            : position(set_position) {};
};