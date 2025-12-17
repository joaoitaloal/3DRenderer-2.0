#define RAYGUI_IMPLEMENTATION

/* ToDo:
    - Make rotation code(maybe try to make a Transform class)
        Clearly too dificult for now, spent a long time reading and still dont understand enough to implement it, gonna stick to a fixed camera and single object for now
    - Implement a better acceleration structure than the bounding box
    - Give more live control to the renderer using the UI
    - Implement threading so that the UI is not paused while rendering
        also thread the rendering probably, to make it faster
    - Make a Readme
    - Maybe make a "Scene" class with all the lights and meshes of the scene
    - Take a look at the ray-triangle intersection function from raylib to see how different is the implementation from mine
*/

#include "./app/app.h"

int main(){
    App app(1080, 720);
    
    app.start();

    return 0;
}