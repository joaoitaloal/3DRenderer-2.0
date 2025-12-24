#include "scene.h"

PlaneV::PlaneV(float set_width, float set_height, Camera3* set_parent){
    parent = set_parent;
    width = set_width; height = set_height;

    //Is this correct? the way they are ordered seems wrong.
    p1 = {width + parent->position.x, height + parent->position.y, 1 + parent->position.z};
    p2 = {-width + parent->position.x, height + parent->position.y, 1 + parent->position.z};
    p3 = {width + parent->position.x, -height + parent->position.y, 1 + parent->position.z};
    p4 = {-width + parent->position.x, -height + parent->position.y, 1 + parent->position.z};
}

PlaneV::PlaneV() = default;

void PlaneV::updatePosition(){
    p1 = {width + parent->position.x, height + parent->position.y, 1 + parent->position.z};
    p2 = {-width + parent->position.x, height + parent->position.y, 1 + parent->position.z};
    p3 = {width + parent->position.x, -height + parent->position.y, 1 + parent->position.z};
    p4 = {-width + parent->position.x, -height + parent->position.y, 1 + parent->position.z};
}