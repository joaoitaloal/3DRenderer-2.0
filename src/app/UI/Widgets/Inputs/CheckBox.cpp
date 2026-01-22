#include "CheckBox.h"

void CheckBox::render(Vector2 scrollOffset){
    ScrollableFrame::render(scrollOffset);

    Rectangle offsetBounds = get_offset_bounds();

    GuiCheckBox(offsetBounds, label.c_str(), &state);
    if(state != last_state){
        callback(state);
        last_state = state;
    }
}

CheckBox::CheckBox(Rectangle bounds_, string label_, function<void(bool)> callback_)
    :ScrollableFrame(bounds_)
{
    label = label_;
    last_state = false;
    state = false;
    callback = callback_;
}

void CheckBox::set_callback(function<void(bool)> callback_){
    callback = callback_;
}

bool CheckBox::get_state()
{
    return state;
}
