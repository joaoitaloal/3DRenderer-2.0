#include "ScrollableFrame.h"

void ScrollableFrame::render(Vector2 scrollOffset){
    offsetBounds = {
                bounds.x + scrollOffset.x,
                bounds.y + scrollOffset.y,
                bounds.width,
                bounds.height
            };
}

ScrollableFrame::ScrollableFrame(Rectangle bounds_)
    : Frame(bounds_)
{
    offsetBounds = { bounds_.x, bounds.y, bounds.width, bounds.height };
}

Rectangle ScrollableFrame::get_offset_bounds(){
    return offsetBounds; 
}
