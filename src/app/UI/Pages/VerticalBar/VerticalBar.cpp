#include "VerticalBar.h"

VerticalBar::VerticalBar(Rectangle bounds_, UI_STATE* ui_state_)
    : Frame(bounds_),
      ui_state(ui_state_),
      padding(12),
      shape_name({bounds.x + bounds.width/2 - 50, bounds.y + padding, 100, 32}, "None"),
      transl_entry(
        {bounds.x + bounds.width/3 - 50, bounds.y + padding + 32, 0, 0}, "Mov", "x", "y", "z",
        [this](Vector3R vec){ 
            if(ui_state->picked != nullptr)
                ui_state->picked->transform(get_translation_matrix(vec));
        }
      ),
      scale_entry(
        {bounds.x + bounds.width/3 + 50, bounds.y + padding + 32, 0, 0}, "Scale", "x", "y", "z",
        [this](Vector3R vec){
            if(ui_state->picked != nullptr)
                ui_state->picked->scale(vec);
        }
      ),
      rot_entry(
        {bounds.x + bounds.width/3 - 50, bounds.y + padding + 200, 0, 0}, "Rotation",
        [this](Vector3R vec, float angle){
            if(ui_state->picked != nullptr)
                ui_state->picked->transform(get_rotation_around_axis(angle, vec.normalize()));
        }
      )
{}

void VerticalBar::render(){
    Rectangle ui_bounds = get_bounds();
    DrawRectangleRec(ui_bounds, (Color){119, 80, 217, 255});
    DrawRectangleLinesEx(ui_bounds, 1, (Color){255, 255, 255, 255});

    
    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 14);
    if(ui_state->picked != nullptr)
        shape_name.set_text(ui_state->picked->get_name());
    shape_name.render({0, 0});
    GuiSetStyle(DEFAULT, TEXT_SIZE, 10);

    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

    transl_entry.render({0, 0});
    scale_entry.render({0, 0});
    rot_entry.render({0, 0});
}
