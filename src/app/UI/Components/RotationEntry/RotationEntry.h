#ifndef UI_ROTATIONENTRY_H
#define UI_ROTATIONENTRY_H

#include "../../Widgets/Inputs/NumberEntry.h"
#include "../../Widgets/Inputs/Button.h"
#include "../../Widgets/Inputs/Slider.h"
#include "../../../../math/Vector3R.h"

// Componente especificamente pra fazer rotações
class RotationEntry : public ScrollableFrame {
    public:
        RotationEntry(Rectangle bounds_, string title_, function<void(Vector3R, float)> on_submit);

        void render(Vector2 scrollOffset) override;

    private:
        Label label;

        NumberEntry x;
        NumberEntry y;
        NumberEntry z;

        Slider angle_entry;

        Button submit;

        Vector3R vector;
        float angle;
};

#endif // UI_ROTATIONENTRY_H