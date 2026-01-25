#ifndef UI_VEC3SLIDER_H
#define UI_VEC3SLIDER_H

#include "../Widgets/Inputs/NumberEntry.h"
#include "../Widgets/Inputs/Slider.h"
#include "../Widgets/Inputs/Button.h"
#include "../../../math/Vector3R.h"

// Width e Height hardcoded, não são influenciados pelo parâmetro de inicialização
class Vec3Slider : public ScrollableFrame {
    public:
        Vec3Slider(Rectangle bounds_, string title_, function<void(Vector3R)> on_submit);

        void render(Vector2 scrollOffset) override;

    private:
        Label label;

        Slider x;
        Slider y;
        Slider z;

        Button submit;

        Vector3R vector;
};

#endif // UI_VEC3SLIDER_H