#include "Frame.h"

Frame::Frame(Rectangle bounds_){
    bounds = bounds_; 
}

Rectangle Frame::get_bounds(){
    return bounds;
}
