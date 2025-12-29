#ifndef RENDERER_SPOTLIGHT_H
#define RENDERER_SPOTLIGHT_H

#include "../Light.h"

// ToDo
class SpotLight : public Light {
    public:
        // SpotLight();
        //Vector3 get_light_vector(Vector3 origin) {};

        //void translate() override {};

        // Isso é ambiguo na verdade, rotaciona a posição em torno de um eixo ou a direção que a luz aponta?
        // Creio que rodar a posição em torno de um eixo faz mais sentido pra interface Rotatable,
        // mas ai da pra fazer um método separado que gira a direção, se quiser(não é requisito do trabalho)
        //void rotate() override {};


        // Situação parecida com a de cima
        //void mirror() override {};
};

#endif // RENDERER_SPOTLIGHT_H