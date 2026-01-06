#ifndef RENDERER_LIGHT_H
#define RENDERER_LIGHT_H

#include "../../../math/Color3.h"
#include "../../../math/Vector3R.h"
#include "../../../math/MatrixR.h"

// Luz genérica, talvez poderia herdar de shape, mas seria estranho ter colisão
class Light{
    public:
        // Retorna o vetor l
        virtual Vector3R get_light_vector(Vector3R origin) = 0;

        // Retorna um ponteiro para uma nova Luz, DELETAR DEPOIS DE USAR!!!!!!
        virtual Light* transform_return(const MatrixR& m) = 0;

        // Mesma coisa do transform_return mas transforma a instância atual de fato
        virtual void transform(const MatrixR& m) = 0;

        Color3 get_intensity() { return intensity; }

        virtual ~Light() = default;
    protected:
        Light(MatrixR world_to_object_, MatrixR object_to_world_) : world_to_object(world_to_object_), object_to_world(object_to_world_){}
        Color3 intensity;

        // Leva o objeto pro centro do mundo
        MatrixR world_to_object;
        MatrixR object_to_world;

        virtual void update_transformation_matrices() = 0;
};

#endif // RENDERER_LIGHT_H