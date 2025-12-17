#ifndef RENDERER_MATERIAL3_H
#define RENDERER_MATERIAL3_H

// Talvez deveria ser uma struct
class Material3{
    public:
        float kd; float ks; float ka; float kr; float km; // Light intensity coefficients
};

#endif // RENDERER_MATERIAL3_H