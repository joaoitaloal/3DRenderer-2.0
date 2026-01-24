#define RAYGUI_IMPLEMENTATION

// ToDo list antiga, vou manter por enquanto mas ignore!!!
/* ToDo:
    - Implement a better acceleration structure than the bounding box
    - Give more live control to the renderer using the UI
    - Implement threading so that the UI is not paused while rendering
        also thread the rendering probably, to make it faster
    - Make a Readme
    - Maybe make a "Scene" class with all the lights and meshes of the scene
    - Take a look at the ray-triangle intersection function from raylib to see how different is the implementation from mine
    - There are some very small holes between triangles that share edges, probably some precision problem
*/

#include "./app/app.h"

int main(){
    SetTraceLogLevel(LOG_WARNING);
    
    App app(700, 700);
    
    app.start();

    return 0;
}