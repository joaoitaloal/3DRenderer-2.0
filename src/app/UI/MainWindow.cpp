#include "MainWindow.h"

MainWindow::MainWindow(int win_width, int win_height, int render_width, int render_height, UI_STATE* ui_state_)
    : Frame(Rectangle{0, 0, (float)win_width, (float)win_height}),
    vbar(Rectangle{0, (float)win_height-render_height, (float)win_width-render_width, (float)render_height}, ui_state_),
    hbar(Rectangle{(float)win_width-render_width, 0, (float)render_width, (float)win_height-render_height}, ui_state_)
{
    ui_state = ui_state_;
    padding = 12;

    InitWindow(win_width, win_height, "Raytracer!!!!!!!!!!!");

    // Setting UI styles, dar uma olhada no que mais da pra fz com essa função
    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, ColorToInt((Color){ 100, 200, 255, 255 }));
}

void MainWindow::render(){
    vbar.render();
    hbar.render();
}
