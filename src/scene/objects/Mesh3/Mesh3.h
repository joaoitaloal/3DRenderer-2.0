#ifndef RENDERER_MESH3_H
#define RENDERER_MESH3_H

#include <vector>
#include <string>

#include "../Triangle/Triangle.h"

using namespace std;

// Classe de malha, use o método estático pra criar instancias, não o construtor
class Mesh3 : public Shape {
    public:
        Mesh3(vector<Triangle>* faces_, BoundingBoxR bbox_);
        ~Mesh3();

        static Mesh3* create_from_obj_file(string filename, Material3 material_);

        Collision get_collision(RayR ray) override;
    private:
        // O gerenciamento de memória do vetor faces é feito pela classe
        vector<Triangle>* faces;

        // Criar uma classe BoundingBox nossa
        BoundingBoxR bbox;
};

Mesh3* ParseOBJFile(string filename);

#endif // RENDERER_MESH3_H