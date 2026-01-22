#ifndef RENDERER_UI_VERTICALBAR_H
#define RENDERER_UI_VERTICALBAR_H

#include "../../Widgets/Frames/ScrollableFrame.h"
#include "../../Widgets/Inputs/Button.h"
#include "../../Widgets/Inputs/CheckBox.h"
#include "../../UI_STATE.h"

class VerticalBar : public Frame{
    public:
        VerticalBar(Rectangle bounds_, UI_STATE* ui_state_);
        void render() override;

    private: 
        UI_STATE* ui_state;

        float padding;

        // Tenho que passar esses dois pra header, deixar só as coisas de transformação nessa classe aqui
        Button* render_bttn;
        CheckBox* live_render_box;
};

#endif // RENDERER_UI_VERTICALBAR_H