#include <raymath.h>
#include "../utils/utils.h"

#include "scene.h"

class Plane {
    private:
        Camera3* parent;
    public:
        Vector3 p1; Vector3 p2; Vector3 p3; Vector3 p4;
        float width; float height;

        // Centered in the origin(0, 0, 0)
        Plane(float set_width, float set_height, Camera3* set_parent){
            parent = set_parent;
            width = set_width; height = set_height;

            //Is this correct? the way they are ordered seems wrong.
            p1 = {width + parent->position.x, height + parent->position.y, 1 + parent->position.z};
            p2 = {-width + parent->position.x, height + parent->position.y, 1 + parent->position.z};
            p3 = {width + parent->position.x, -height + parent->position.y, 1 + parent->position.z};
            p4 = {-width + parent->position.x, -height + parent->position.y, 1 + parent->position.z};
        }

        void updatePosition(){
            p1 = {width + parent->position.x, height + parent->position.y, 1 + parent->position.z};
            p2 = {-width + parent->position.x, height + parent->position.y, 1 + parent->position.z};
            p3 = {width + parent->position.x, -height + parent->position.y, 1 + parent->position.z};
            p4 = {-width + parent->position.x, -height + parent->position.y, 1 + parent->position.z};
        }

        Plane() = default;
};