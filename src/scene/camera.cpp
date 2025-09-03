#include <raymath.h>

class Camera3 {
    public:
        Vector3 position;
        Vector3 direction;

        Camera3(float set_pos_x, float set_pos_y, float set_pos_z, float set_dir_x, float set_dir_y, float set_dir_z){
            position = {set_pos_x, set_pos_y, set_pos_z};
            direction = {set_dir_x, set_dir_y, set_dir_z};
        }

        Camera3(Vector3 &set_position, Vector3 &set_direction)
            : position(set_position), direction(set_direction) {};

        Camera3() = default;
};