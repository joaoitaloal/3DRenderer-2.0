#ifndef UI_VEC3ENTRY_H
#define UI_VEC3ENTRY_H

#include "../../Widgets/Inputs/NumberEntry.h"
#include "../../Widgets/Inputs/Button.h"
#include "../../../../math/Vector3R.h"

// Width e Height hardcoded, não são influenciados pelo parâmetro de inicialização

// Componente genérico de entrada com 3 floats
class Vec3Entry : public ScrollableFrame {
    public:
        Vec3Entry(Rectangle bounds_, string title_, string x_label, string y_label, string z_label, function<void(Vector3R)> on_submit);

        void render(Vector2 scrollOffset) override;

    private:
        Label label;

        NumberEntry x;
        NumberEntry y;
        NumberEntry z;

        Button submit;

        Vector3R vector;
};

#endif // UI_VEC3ENTRY_H