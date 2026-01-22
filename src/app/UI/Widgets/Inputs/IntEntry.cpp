#include "IntEntry.h"

#include <iostream>

void IntEntry::render(Vector2 scrollOffset){
    ScrollableFrame::render(scrollOffset);

    Rectangle offsetBounds = get_offset_bounds();

    if(GuiValueBox(offsetBounds, title.c_str(), &cur_num, 0, 100, editMode)){
        editMode = !editMode;

        if(cur_num > max_num) cur_num = max_num;
        else if (cur_num < min_num) cur_num = min_num;

        callback(cur_num);
    }
}

int IntEntry::get_cur_num()
{
    return cur_num;
}

void IntEntry::set_callback(function<void(int num)> callback_){
    callback = callback_;
}

IntEntry::IntEntry(Vector2 pos_, string title_, int min_num_, int max_num_, function<void(int num)> callback_)
    :ScrollableFrame({pos_.x, pos_.y, 200, 32})
{
    cur_num = 0;
    editMode = false;

    max_num = max_num_;
    min_num = min_num_;

    title = title_;

    callback = callback_;
}
