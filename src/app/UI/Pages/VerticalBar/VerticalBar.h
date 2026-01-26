#ifndef RENDERER_UI_VERTICALBAR_H
#define RENDERER_UI_VERTICALBAR_H

#include "../../Components/Vec3Entry/Vec3Entry.h"
#include "../../Components/RotationEntry/RotationEntry.h"
#include "../../UI_STATE.h"

class VerticalBar : public Frame{
    public:
        VerticalBar(Rectangle bounds_, UI_STATE* ui_state_);
        void render() override;

    private: 
        UI_STATE* ui_state;

        float padding;

        Label shape_name;

        Vec3Entry transl_entry;
        Vec3Entry scale_entry;

        RotationEntry rot_entry;

        // Tenho que fazer um input diferente pra rotação,
        // já que ela vai receber um eixo e um angulo
        
        // Vai faltar cisalhamento(Shear),
        // reflexão em volta de um plano
        
};

#endif // RENDERER_UI_VERTICALBAR_H