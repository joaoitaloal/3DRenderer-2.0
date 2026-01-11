#ifndef RENDERER_MESH3_H
#define RENDERER_MESH3_H

#include <vector>
#include <string>

#include "../Triangle/Triangle.h"
#include "../../../math/BoundingBox/BoundingBoxR.h"

using namespace std;

// TODO: inserir um vetor pivô para as transformações, ao invés de usar a bbox

// Classe de malha, use o método estático pra criar instancias, não o construtor
class Mesh3 : public Shape {
    public:
        Mesh3(vector<Triangle*> faces_, BoundingBoxR bbox_, Material3 material_, Vector3R anchor_);
        ~Mesh3();

        static Mesh3* create_from_obj_file(string filename, Material3 material_);

        Collision get_collision(RayR ray) override;

        Mesh3* transform_return(const MatrixR& m) override;
        void transform(const MatrixR& m) override;

    private:
        // O gerenciamento de memória do vetor faces é feito pela classe
        vector<Triangle*> faces;
        Vector3R anchor;

        // TODO: Criar uma classe BoundingBox nossa
        BoundingBoxR bbox;

        void update_transformation_matrices() override;
};

Mesh3* ParseOBJFile(string filename, Material3 material_);

#endif // RENDERER_MESH3_H