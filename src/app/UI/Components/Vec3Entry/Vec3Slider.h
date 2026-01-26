#ifndef UI_VEC3SLIDER_H
#define UI_VEC3SLIDER_H

#include "../../Widgets/Inputs/Slider.h"
#include "../../Widgets/Inputs/Button.h"
#include "../../Widgets/Label.h"
#include "../../../../math/Vector3R.h"

// Width e Height hardcoded, não são influenciados pelo parâmetro de inicialização

// Componente genérico de entrada com 3 floats
// Chama on_submit sempre que o slider for atualizado, sem botão de submit separado
class Vec3Slider : public ScrollableFrame {
    public:
        Vec3Slider(Rectangle bounds_, string title_, float min, float max, function<void(Vector3R)> on_submit);

        void render(Vector2 scrollOffset) override;

    private:
        Label label;

        Slider x;
        Slider y;
        Slider z;

        Vector3R vector;
};

#endif // UI_VEC3SLIDER_H