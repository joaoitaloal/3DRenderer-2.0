#include "Page.h"

void Page::render(){
    scrollPanel.render();
}

Page::Page(Rectangle bounds_, ControlFlow *flow_)
    : Frame(bounds_),
      scrollPanel(bounds_)
{
    flow = flow_;
}

VisibleFrame Page::get_cur_frame(){
    return flow->get_cur_frame();
}

void Page::set_cur_frame(VisibleFrame frame_){
    flow->set_cur_frame(frame_);
}

void Page::append_child(ScrollableFrame *child_){
    scrollPanel.append_child(child_);
}

void Page::remove_child(ScrollableFrame *child_){
    scrollPanel.remove_child(child_);
}

void Page::update_content_rec(){
    scrollPanel.update_content_rec();
}