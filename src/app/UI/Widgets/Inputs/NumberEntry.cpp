#include "NumberEntry.h"

void NumberEntry::render(Vector2 scrollOffset){
    ScrollableFrame::render(scrollOffset);

    Rectangle offsetBounds = get_offset_bounds();

    // Descobrir como isso funciona
    // GuiSetStyle(TEXTBOX, BACKGROUND_COLOR, ColorToInt(RAYWHITE));

    if(GuiTextBox(offsetBounds, text, 99, editMode)){
        editMode = !editMode;

        if(strcmp(text, "") && validate_input()){
            strcpy(lastValidated, text);
            cur_num = atof(lastValidated);
            callback(cur_num);
        }else{
            strcpy(text, lastValidated);
        }
    }
}

double NumberEntry::get_cur_num(){
    return cur_num;
}

void NumberEntry::set_callback(std::function<void(double num)> callback_){
    callback = callback_;
}

NumberEntry::NumberEntry(Rectangle bounds_, string title_, function<void(double num)> callback_)
    : ScrollableFrame(bounds_),
    label({bounds_.x - 16, bounds_.y, bounds_.width, bounds_.height}, title_)
{
    cur_num = 0;
    editMode = false;

    title = title_;
    callback = callback_;
}

bool NumberEntry::validate_input()
{
    int dot_num = 0;
    for(char c : text){
        if(c == 46 || c == 44) dot_num++;

        // Tem que desenhar a tabela verdade pra entender essa aqui
        if(dot_num > 1 || (c != 0 && c!=46 && c!=44 && (c < 48 || c > 57))) return false;
    }

    return true;
}
