#include "VerticalBar.h"

VerticalBar::VerticalBar(Rectangle bounds_, UI_STATE* ui_state_)
    : Frame(bounds_)
{
    ui_state = ui_state_;
    padding = 12;

    render_bttn = new Button(Rectangle{bounds_.width/2 - 90, bounds.y + bounds_.height - 64 - padding, 180, 64}, "Render Image",
    [this] {
        //auto start = std::chrono::high_resolution_clock().now();
        ui_state->viewport->update();
        //auto end = std::chrono::high_resolution_clock().now();

        //time_elapsed = end - start;
    });

    live_render_box = new CheckBox({padding,  2*padding, 50, 50}, "Auto-Render",
    [this] (bool state) {
        ui_state->live_rendering = state;
    });
}

void VerticalBar::render(){
    Rectangle ui_bounds = get_bounds();
    DrawRectangleRec(ui_bounds, (Color){119, 80, 217, 255});
    DrawRectangleLinesEx(ui_bounds, 1, (Color){255, 255, 255, 255});

    // Não tá legal, ele carregar a mesh toda vez q clica, tá carregando meshs repetidas
    // Além disso esse obj_file_entry como um char* tá terrivel
    /*if(GuiTextBox((Rectangle){0 + ui_padding, 32, 260, 32}, obj_file_entry, 120, obj_file_entry_edit)){
        obj_file_entry_edit = !obj_file_entry_edit;

        load_new_mesh(obj_file_entry); 
    }*/

    render_bttn->render({0, 0});
    live_render_box->render({0, 0});
}
