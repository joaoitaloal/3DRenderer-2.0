#include <raymath.h>

class Camera3 {
    public:
        Vector3* position;

        Camera3(float set_x, float set_y, float set_z){
            position = new Vector3();

            position->x = set_x;
            position->y = set_y;
            position->z = set_z;
        }

        ~Camera3(){
            delete position;
        }
};