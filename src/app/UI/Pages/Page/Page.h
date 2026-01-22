#ifndef UI_PAGE_H
#define UI_PAGE_H

#include "../ControlFlow.h"
#include "../../Widgets/ScrollPanel/ScrollPanel.h"
#include "../../Widgets/Frames/Frame.h"

// Acho que num mundo ideal eu faria um vetor de páginas pro enum do flow acessar, mas é meio overkill pra um programa com *DUAS* páginas

// Page class, it is abstract because it doesnt implement the abstract render() from the frame class
class Page : public Frame{
    public:
        void render() override;
        Page(Rectangle bounds_, ControlFlow* flow_);

        VisibleFrame get_cur_frame();
        void set_cur_frame(VisibleFrame frame_);

        void append_child(ScrollableFrame* child_);
        void remove_child(ScrollableFrame* child_);
        void update_content_rec();
    private:
        ScrollPanel scrollPanel;

        ControlFlow* flow;
};

#endif // UI_PAGE_H