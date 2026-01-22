#include "CheckGroup.h"

void CheckGroup::render(Vector2 scrollOffset){
    ScrollableFrame::render(scrollOffset);

    //Rectangle offsetBounds = get_offset_bounds();
}

CheckGroup::CheckGroup(Rectangle bounds_, std::vector<bool*> options_)
    :ScrollableFrame(bounds_)
{
    options = options_;
}
