#ifndef RENDERER_RING_H
#define RENDERER_RING_H

#include "../Circle.h"

class Ring : public Circle {
    public:
        Ring(Vector3R point_, Vector3R normal_, float radius1_, float radius2_, Material3 material_, Textura* tex, string name_, bool culled);
        Collision get_collision(RayR ray) override;
    
    private:
        float radius2;
};

#endif // RENDERER_CIRCLE_H