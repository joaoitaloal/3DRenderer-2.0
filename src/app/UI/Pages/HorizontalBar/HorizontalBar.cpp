#include "HorizontalBar.h"

HorizontalBar::HorizontalBar(Rectangle bounds_, UI_STATE* ui_state_)
    : Frame(bounds_)
{
    ui_state = ui_state_;
    padding = 12;
    
    // ----- Look at ----- //
    // TODO: transformar essa estrutura debaixo em um componente, vai ser mt usada
    // Acho que se eu usar o setStyle dá pra centralizar essa label fácil sem calcular pixel
    lat_label = new Label({bounds.x + padding, bounds.y + padding, 100, 32}, "look_at");
    lat_x = new NumberEntry({bounds.x + padding, bounds.y + padding + 32, 100, 32}, "x", [this](double num){
        lat_vector.x = num;
    });

    lat_y = new NumberEntry({bounds.x + padding, bounds.y + padding + 64, 100, 32}, "y", [this](double num){
        lat_vector.y = num;
    });

    lat_z = new NumberEntry({bounds.x + padding, bounds.y + padding + 96, 100, 32}, "z", [this](double num){
        lat_vector.z = num;
    });
    lat_submit = new Button({bounds.x + padding + 25, bounds.y + padding + 128, 50, 32}, "Submit", [this]{
        ui_state->scene->look_at(lat_vector);
    });
}

void HorizontalBar::render(){
    Rectangle ui_bounds = get_bounds();
    DrawRectangleRec(ui_bounds, (Color){119, 80, 217, 255});
    DrawRectangleLinesEx(ui_bounds, 1, (Color){255, 255, 255, 255});

    lat_label->render({0, 0});
    lat_x->render({0, 0});
    lat_y->render({0, 0});
    lat_z->render({0, 0});
    lat_submit->render({0, 0});
}
