#ifndef RENDERER_UI_HORIZONTALBAR_H
#define RENDERER_UI_HORIZONTALBAR_H

#include "../../Components/Vec3Entry.h"
#include "../../Components/Vec3Slider.h"
#include "../../UI_STATE.h"

class HorizontalBar : public Frame{
    public:
        HorizontalBar(Rectangle bounds_, UI_STATE* ui_state_);
        void render() override;

    private:
        float padding;

        Vec3Entry look_at_entry;
        Vec3Entry move_to_entry;

        // x: width; y: height; z: depth;
        Vec3Entry viewplane_entry;

        Vec3Slider proj_obliqua;

        Button proj_pers;
        Button proj_orto;

        Button zoom_in;
        Button zoom_out;

        Slider ambient_light;
};

#endif // RENDERER_UI_HORIZONTALBAR_H