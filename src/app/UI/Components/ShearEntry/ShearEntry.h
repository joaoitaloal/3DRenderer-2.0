#ifndef UI_SHEARENTRY_H
#define UI_SHEARENTRY_H

#include "../../Widgets/Inputs/NumberEntry.h"
#include "../../Widgets/Inputs/Button.h"
#include "../../Widgets/Inputs/Slider.h"
#include "../../../../math/Vector3R.h"

// Componente especificamente pra fazer rotações
class ShearEntry : public ScrollableFrame {
    public:
        ShearEntry(Rectangle bounds_, string title_, function<void(Vector2, Vector2, Vector2)> on_submit);

        void render(Vector2 scrollOffset) override;

    private:
        Label label;

        Label label_xy;
        Slider xy_x;
        Slider xy_y;

        Label label_xz;
        Slider xz_x;
        Slider xz_z;
        
        Label label_yz;
        Slider yz_y;
        Slider yz_z;

        Button reset;
        Button submit;

        Vector2 xy = {0, 0}, xz = {0, 0}, yz = {0, 0};
};

#endif // UI_SHEARENTRY_H