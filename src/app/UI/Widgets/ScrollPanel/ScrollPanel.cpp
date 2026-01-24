#include "ScrollPanel.h"

ScrollPanel::ScrollPanel(Rectangle bounds_)
    : Frame(bounds_)
{
    scroll = { 0, 0 };
    view = { 0, 0, 0, 0 };

    panelRec = { 0, 0, bounds_.width, bounds.height };
    panelContentRec = { 0, 0, 0, 0 };
}

void ScrollPanel::append_child(ScrollableFrame *child_){
    children.push_back(child_);
    panelContentRec = get_max_children_bounds(); // Não é super eficiente mas não deve ser um problema
}

void ScrollPanel::remove_child(ScrollableFrame *child_){
    size_t i = 0;
    for(; i < children.size(); i++){
        if(child_ == children.at(i)) break;
    }
    if(i < children.size()) children.erase(children.begin() + i);
}

void ScrollPanel::update_content_rec(){
    panelContentRec = get_max_children_bounds();
}

ScrollPanel::~ScrollPanel()
{
    for (ScrollableFrame* child : children){
        delete child;
    }
}

void ScrollPanel::render(){
    GuiScrollPanel(panelRec, 0, panelContentRec, &scroll, &view);

    BeginScissorMode(view.x, view.y, view.width, view.height);
        for (ScrollableFrame* child : children){
            child->render(Vector2{panelRec.x + scroll.x, panelRec.y + scroll.y});
        }
    EndScissorMode();

    //DrawStyleEditControls();
}

Rectangle ScrollPanel::get_max_children_bounds(){
    float maxWidth = 0, maxHeight = 0;
    for(ScrollableFrame* child : children){
        Rectangle childBounds = child->get_bounds();

        float childWidth = childBounds.width + childBounds.x;
        if(childWidth > maxWidth) maxWidth = childWidth;
        
        float childHeight = childBounds.height + childBounds.y;
        if(childHeight > maxHeight) maxHeight = childHeight;
    }

    return Rectangle{0, 0, maxWidth, maxHeight};
}

/* Draw and process scroll bar style edition controls
void ScrollPanel::DrawStyleEditControls(void)
{
    // ScrollPanel style controls
    //----------------------------------------------------------
    GuiGroupBox({ 550, 170, 220, 205 }, "SCROLLBAR STYLE");

    int style = GuiGetStyle(SCROLLBAR, BORDER_WIDTH);
    GuiLabel({ 555, 195, 110, 10 }, "BORDER_WIDTH");
    GuiSpinner({ 670, 190, 90, 20 }, 0, &style, 0, 6, false);
    GuiSetStyle(SCROLLBAR, BORDER_WIDTH, style);

    style = GuiGetStyle(SCROLLBAR, ARROWS_SIZE);
    GuiLabel({ 555, 220, 110, 10 }, "ARROWS_SIZE");
    GuiSpinner({ 670, 215, 90, 20 }, 0, &style, 4, 14, false);
    GuiSetStyle(SCROLLBAR, ARROWS_SIZE, style);

    style = GuiGetStyle(SCROLLBAR, SLIDER_PADDING);
    GuiLabel({ 555, 245, 110, 10 }, "SLIDER_PADDING");
    GuiSpinner({ 670, 240, 90, 20 }, 0, &style, 0, 14, false);
    GuiSetStyle(SCROLLBAR, SLIDER_PADDING, style);

    bool scrollBarArrows = GuiGetStyle(SCROLLBAR, ARROWS_VISIBLE);
    GuiCheckBox({ 565, 280, 20, 20 }, "ARROWS_VISIBLE", &scrollBarArrows);
    GuiSetStyle(SCROLLBAR, ARROWS_VISIBLE, scrollBarArrows);

    style = GuiGetStyle(SCROLLBAR, SLIDER_PADDING);
    GuiLabel({ 555, 325, 110, 10 }, "SLIDER_PADDING");
    GuiSpinner({ 670, 320, 90, 20 }, 0, &style, 0, 14, false);
    GuiSetStyle(SCROLLBAR, SLIDER_PADDING, style);

    style = GuiGetStyle(SCROLLBAR, SLIDER_WIDTH);
    GuiLabel({ 555, 350, 110, 10 }, "SLIDER_WIDTH");
    GuiSpinner({ 670, 345, 90, 20 }, 0, &style, 2, 100, false);
    GuiSetStyle(SCROLLBAR, SLIDER_WIDTH, style);

    const char *text = GuiGetStyle(LISTVIEW, SCROLLBAR_SIDE) == SCROLLBAR_LEFT_SIDE? "SCROLLBAR: LEFT" : "SCROLLBAR: RIGHT";
    bool toggleScrollBarSide = GuiGetStyle(LISTVIEW, SCROLLBAR_SIDE);
    GuiToggle({ 560, 110, 200, 35 }, text, &toggleScrollBarSide);
    GuiSetStyle(LISTVIEW, SCROLLBAR_SIDE, toggleScrollBarSide);
    //----------------------------------------------------------

    // ScrollBar style controls
    //----------------------------------------------------------
    GuiGroupBox({ 550, 20, 220, 135 }, "SCROLLPANEL STYLE");

    style = GuiGetStyle(LISTVIEW, SCROLLBAR_WIDTH);
    GuiLabel({ 555, 35, 110, 10 }, "SCROLLBAR_WIDTH");
    GuiSpinner({ 670, 30, 90, 20 }, 0, &style, 6, 30, false);
    GuiSetStyle(LISTVIEW, SCROLLBAR_WIDTH, style);

    style = GuiGetStyle(DEFAULT, BORDER_WIDTH);
    GuiLabel({ 555, 60, 110, 10 }, "BORDER_WIDTH");
    GuiSpinner({ 670, 55, 90, 20 }, 0, &style, 0, 20, false);
    GuiSetStyle(DEFAULT, BORDER_WIDTH, style);
    //----------------------------------------------------------
}*/