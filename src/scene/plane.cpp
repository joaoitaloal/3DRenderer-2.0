#include <raymath.h>
#include "../utils/utils.h"

class Plane {
    private:
        Camera3* parent;
    public:
        Vector3* p1; Vector3* p2; Vector3* p3; Vector3* p4;
        float width; float height;

        // Centered in the origin(0, 0, 0)
        Plane(float set_width, float set_height, Camera3* set_parent){
            parent = set_parent;
            width = set_width; height = set_height;

            //Is this correct? the way they are ordered seems wrong.
            p1 = createVector3(width + parent->position->x, height + parent->position->y, 1 + parent->position->z);
            p2 = createVector3(-width + parent->position->x, height + parent->position->y, 1 + parent->position->z);
            p3 = createVector3(width + parent->position->x, -height + parent->position->y, 1 + parent->position->z);
            p4 = createVector3(-width + parent->position->x, -height + parent->position->y, 1 + parent->position->z);
        }

        void updatePosition(){
            // Not the best way to do it for sure, i need to stop using pointers where i dont need them
            delete p1;
            delete p2;
            delete p3;
            delete p4;

            p1 = createVector3(width + parent->position->x, height + parent->position->y, 1 + parent->position->z);
            p2 = createVector3(-width + parent->position->x, height + parent->position->y, 1 + parent->position->z);
            p3 = createVector3(width + parent->position->x, -height + parent->position->y, 1 + parent->position->z);
            p4 = createVector3(-width + parent->position->x, -height + parent->position->y, 1 + parent->position->z);
        }

        ~Plane(){
            delete p1;
            delete p2;
            delete p3;
            delete p4;
        }
};