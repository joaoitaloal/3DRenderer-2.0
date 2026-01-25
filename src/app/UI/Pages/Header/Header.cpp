#include "Header.h"

Header::Header(Rectangle bounds_, UI_STATE* ui_state_)
    : Frame(bounds_),
    ui_state(ui_state_),
    padding(12),
    render_bttn(Rectangle{bounds_.width/2 - 90, bounds.y + bounds_.height - 64 - padding, 180, 64}, "Render Image",
        [this] {
            //auto start = std::chrono::high_resolution_clock().now();
            ui_state->viewport->update();
            //auto end = std::chrono::high_resolution_clock().now();

            //time_elapsed = end - start;
        }
    ),
    live_render_box({padding,  2*padding, 50, 50}, "Auto-Render",
        [this] (bool state) {
            ui_state->live_rendering = state;
        }
    )
{}

void Header::render(){
    render_bttn.render({0, 0});
    live_render_box.render({0, 0});
}