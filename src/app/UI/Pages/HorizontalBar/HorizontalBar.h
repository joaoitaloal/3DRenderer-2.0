#ifndef RENDERER_UI_HORIZONTALBAR_H
#define RENDERER_UI_HORIZONTALBAR_H

#include "../../Widgets/Frames/ScrollableFrame.h"
#include "../../Widgets/Inputs/NumberEntry.h"
#include "../../Widgets/Inputs/Button.h"
#include "../../Widgets/Label.h"
#include "../../UI_STATE.h"

class HorizontalBar : public Frame{
    public:
        HorizontalBar(Rectangle bounds_, UI_STATE* ui_state_);
        void render() override;

    private:
        UI_STATE* ui_state;

        float padding;

        // ----- Look at ----- //
        Label* lat_label;
        NumberEntry* lat_x;
        NumberEntry* lat_y;
        NumberEntry* lat_z;
        Button* lat_submit;

        Vector3R lat_vector;
};

#endif // RENDERER_UI_HORIZONTALBAR_H