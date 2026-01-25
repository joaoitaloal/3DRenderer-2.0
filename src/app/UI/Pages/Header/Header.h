#ifndef UI_HEADER_H
#define UI_HEADER_H

#include "../../Widgets/Frames/ScrollableFrame.h"
#include "../../Widgets/Inputs/Button.h"
#include "../../Widgets/Inputs/CheckBox.h"
#include "../../UI_STATE.h"

class Header : public Frame{
    public:
        Header(Rectangle bounds_, UI_STATE* ui_state_);
        void render() override;

    private:
        UI_STATE* ui_state;
        float padding;

        Button render_bttn;
        CheckBox live_render_box;
};

#endif // UI_HEADER_H