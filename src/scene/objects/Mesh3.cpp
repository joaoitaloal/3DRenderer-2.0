#include <raylib.h>
#include <vector>

#include "./objects.h"

class Mesh3 {
    public:
        std::vector<FaceTri> faces;
        BoundingBox bbox;
};