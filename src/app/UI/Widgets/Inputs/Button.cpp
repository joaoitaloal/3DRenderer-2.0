#include "Button.h"

void Button::render(Vector2 scrollOffset){
    ScrollableFrame::render(scrollOffset);

    Rectangle offsetBounds = get_offset_bounds();
    
    if(GuiButton(offsetBounds, label.c_str())){
        callback();
    }
}

Button::Button(Rectangle bounds_, string label_, function<void()> callback_)
    :ScrollableFrame(bounds_) 
{
    label = label_;
    callback = callback_;
}
