#ifndef RENDERER_OBJECTS_H
#define RENDERER_OBJECTS_H

#include <raylib.h>
#include <vector>
#include "../scene.h"
#include "../../utils/utils.h"

// Maybe this should be a struct
class FaceTri {
    public:
        Vector3 v1, v2, v3; // vertices
        Vector3 vn1, vn2, vn3; // vertex normals
        Vector2 vt1, vt2, vt3; // texture vertices
};

class Mesh3 {
    public:
        std::vector<FaceTri> faces;
        BoundingBox bbox;
        Material3 material;
};

class Transform3{

};

struct FaceTriIndexes{
    int vertices[3];
    int v_normals[3];
    int v_tex[3];
};

struct PointLight {
    Vector3 pos;
    Color3 intensity;
};

#endif // RENDERER_OBJECTS_H