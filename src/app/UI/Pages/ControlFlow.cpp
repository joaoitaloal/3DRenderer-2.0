#include "ControlFlow.h"

ControlFlow::ControlFlow(){
    cur_frame = INPUTFRAME;
}

void ControlFlow::set_cur_frame(VisibleFrame frame){
    cur_frame = frame;
}

VisibleFrame ControlFlow::get_cur_frame()
{
    return cur_frame;
}
