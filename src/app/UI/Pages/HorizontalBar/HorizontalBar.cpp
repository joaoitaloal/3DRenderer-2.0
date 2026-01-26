#include "HorizontalBar.h"

HorizontalBar::HorizontalBar(Rectangle bounds_, UI_STATE* ui_state_)
    : Frame(bounds_),
      padding(12),
      look_at_entry(
        {bounds.x + padding, bounds.y + padding, 0, 0}, "Look at", "x", "y", "z",
        [ui_state_](Vector3R vec){ ui_state_->scene->look_at(vec); }
      ),
      move_to_entry(
        {bounds.x + padding + 60, bounds.y + padding, 0, 0}, "Move to", "x", "y", "z",
        [ui_state_](Vector3R vec){ ui_state_->scene->move_to(vec); }
      ),
      viewplane_entry(
        {bounds.x + padding + 120, bounds.y + padding, 0, 0}, "Plane", "width", "height", "depth",
        [ui_state_](Vector3R vec){ ui_state_->scene->set_dimensions(vec); }
      ),
      proj_obliqua(
        {bounds.x + padding + 300, bounds.y + padding, 0, 0}, "Obliqua", -1, 1,
        [ui_state_](Vector3R vec){ ui_state_->scene->set_projection_obliq(vec); }
      ),
      proj_pers(
        {bounds.x + 2*padding + 180, bounds.y + padding, 60, 32}, "Proj pers",
        [ui_state_]() { ui_state_->scene->set_projection_pers(); }
      ),
      proj_orto(
        {bounds.x + 2*padding + 180, bounds.y + padding + 32, 60, 32}, "Proj orto",
        [ui_state_]() { ui_state_->scene->set_projection_obliq({0, 0, 1}); }
      ),
      zoom_in(
        {bounds.x + 2*padding + 180, bounds.y + padding + 96, 60, 32}, "Zoom in",
        [ui_state_]() { ui_state_->scene->zoom(0.9); }
      ),
      zoom_out(
        {bounds.x + 2*padding + 180, bounds.y + padding + 128, 60, 32}, "Zoom out",
        [ui_state_]() { ui_state_->scene->zoom(1.1); }
      ),
      ambient_light({bounds.x + 2*padding + 240, bounds.y + padding + 128, 60, 32}, "0", "1", 0, 1, 0.2, [ui_state_](float num){
        ui_state_->scene->set_ambient_light(num);
      })
{}

void HorizontalBar::render(){
    Rectangle ui_bounds = get_bounds();
    DrawRectangleRec(ui_bounds, (Color){119, 80, 217, 255});
    DrawRectangleLinesEx(ui_bounds, 1, (Color){255, 255, 255, 255});

    look_at_entry.render({0, 0});    
    move_to_entry.render({0, 0});
    viewplane_entry.render({0, 0});

    proj_obliqua.render({0, 0});
    
    proj_pers.render({0, 0});
    proj_orto.render({0, 0});

    zoom_in.render({0, 0});
    zoom_out.render({0, 0});

    ambient_light.render({0, 0});
}
