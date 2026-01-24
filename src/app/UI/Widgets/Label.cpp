#include "Label.h"

void Label::render(Vector2 scrollOffset){
    ScrollableFrame::render(scrollOffset);

    Rectangle offsetBounds = get_offset_bounds();

    GuiLabel(offsetBounds, text.c_str());
}

void Label::set_text(string text_){
    text = text_;
}

Label::Label(Rectangle bounds_, string text_)
    :ScrollableFrame(bounds_)
{
    text = text_;
}
