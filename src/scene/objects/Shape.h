#ifndef RENDERER_SHAPE_H
#define RENDERER_SHAPE_H

#include "Material3.h"
#include "../../Textura/Textura.h"
#include "../../math/Vector3R.h"
#include "../../math/MatrixR.h"
#include "../../math/utils.h"

#include <string>

using namespace std;

// Classe de forma genérica
class Shape{
    public:
        virtual Collision get_collision(RayR ray) = 0;

        // Retorna um ponteiro para uma nova Shape, DELETAR DEPOIS DE USAR!!!!!!
        // Não confundir com o transform da interface Transformable(talvez seria melhor mudar de nome)
        virtual Shape* transform_return(const MatrixR& m) = 0;

        // Mesma coisa do de cima mas transforma a instância de fato
        virtual void transform(const MatrixR& m) = 0;

        virtual void scale(Vector3R dims) = 0;

        // Retornando uma referencia read-only, nem sei se precisa, talvez copiar seria suave
        const Material3& get_material() const { return material; }

        string get_name() { return name; }

        virtual bool has_texture() const {
            return texture != nullptr;
        }

        Textura* get_texture() const{
            return texture;
        }

        virtual ~Shape() = default;

    protected:
        Shape(MatrixR world_to_object_, MatrixR object_to_world_, string name_)
        : world_to_object(world_to_object_), 
        object_to_world(object_to_world_),
        name(name_) {}

        Material3 material;

        Textura* texture = nullptr;
        string name;

        // Leva o objeto pro centro do mundo
        MatrixR world_to_object;
        MatrixR object_to_world;

        virtual void update_transformation_matrices() = 0;
};

#endif // RENDERER_SHAPE_H