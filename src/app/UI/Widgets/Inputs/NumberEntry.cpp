#include "NumberEntry.h"

void NumberEntry::render(Vector2 scrollOffset){
    ScrollableFrame::render(scrollOffset);

    Rectangle offsetBounds = get_offset_bounds();

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

    // Caixinha pra label:
    //DrawRectangleRec({bounds.x, bounds.y - bounds.height/2 + 12, 16, 12}, (Color){119, 80, 217, 255});
    //DrawRectangleLinesEx({bounds.x, bounds.y - bounds.height/2 + 12, 16, 12}, 1, (Color){255, 255, 255, 255});
    label.render({scrollOffset});
}

float NumberEntry::get_cur_num(){
    return cur_num;
}

void NumberEntry::set_callback(std::function<void(float num)> callback_){
    callback = callback_;
}

NumberEntry::NumberEntry(Rectangle bounds_, string title_, function<void(float num)> callback_)
    : ScrollableFrame(bounds_),
    label({bounds_.x, bounds_.y - bounds.height/2, bounds_.width, bounds_.height}, title_)
{
    cur_num = 0;
    editMode = false;

    title = title_;
    callback = callback_;
}

bool NumberEntry::validate_input()
{
    int dot_num = 0;
    int minus_num = 0;
    for(char c : text){
        if(c == 45){
            minus_num++;
            if(minus_num > 1) return false;
        }
        if(c == 46 || c == 44){
            dot_num++;
            if(dot_num > 1) return false;
        }

        // Tem que desenhar a tabela verdade pra entender essa aqui
        if(c != 0 && c!=46 && c!=45 && c!=44 && (c < 48 || c > 57)) return false;
    }

    return true;
}
