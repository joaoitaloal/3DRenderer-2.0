#include "app.h"

// Temporario, tirar daqui depois
#include "../scene/objects/Lights/Point/PointLight.h"
// Esse não sei se é temporario, mas deve ir pra outro lugar em alguma refatoração
#include "../scene/objects/Mesh3/Mesh3.h"
#include "../scene/objects/Cylinder/Cylinder.h"
#include "../scene/objects/Sphere/Sphere.h"
#include "../scene/objects/Cone/Cone.h"

// Temporario
Material3 debug_temp_material(Color3 color){
    return {color, 0.5, 0.5, 0.3, 0.3, 10};
}

App::App(int win_width_, int win_height_)
    : view(new View({-10, 2, 0}, 2, 2, 1)),
    scene(view)
{
    win_width = win_width_;
    win_height = win_height_;

    live_rendering = false;

    ui_width = 360; ui_height = 500;
    ui_padding = 12;
    obj_file_entry_edit = false;
    obj_file_entry = "";

    // Rendered image dimensions
    render_witdh = 500; render_height = 500;

    // ========= Criando objetos =========
    // Malhas
    load_new_mesh("models/PlaneLow.obj", {0, 0.125, 0.25});
    //load_new_mesh("models/Cube.obj", {0.25, 0, 0});

    Vector3R axis(0.5, 0.7, 0.5);
    // Cilindro
    scene.push_shape(new Cylinder(
        {-10, 5, 10},
        axis.normalize(),
        3,
        10,
        debug_temp_material({0.25, 0, 0.25})
    ));
    // Esfera
    scene.push_shape(new Sphere(
        {0, 15, 0},
        3,
        debug_temp_material({1, 1, 0})
    ));
    // Cone
    scene.push_shape(new Cone(
        {5, 5, 0},
        axis.normalize(),
        3,
        4,
        debug_temp_material({0, 0, 0.25})
    ));
    // Plano
    scene.push_shape(new Plane(
        {0, 1, 0},
        {0, -10, 0},
        debug_temp_material({0, 0.25, 0}),
        false
    ));

    // Temporary manual light creation:
    scene.push_light(new PointLight({20, 20, 20}, {1, 1, 1}));

    // Window configuration
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(win_width, win_height, "Raytracer!!!!!!!!!!!");
    SetTargetFPS(60);

    // Setting UI styles, change this to another file just for organization
    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, ColorToInt((Color){ 100, 200, 255, 255 }));
    viewport = new Viewport(render_witdh, render_height, &scene);
}

// Falta ajeitar muita coisa aqui, principalmente coisas da UI que precisam sair desse método
void App::start()
{

    while(!WindowShouldClose()){
        process();
    }

    delete viewport;
    
    CloseWindow();
}

void App::load_new_mesh(string filename, Color3 color){
    try{
        // Material fixo temporário
        Mesh3* mesh = Mesh3::create_from_obj_file(filename, debug_temp_material(color));
        scene.push_shape(mesh);
    }catch(const int err){
        throw err; // Só pra ficar explicito o erro
    }
}

void App::process(){
    int fps = GetFPS();

    // Some screen controls, maybe temporary maybe not, definitely needs some work though
    if(!obj_file_entry_edit){
        if(IsKeyDown(KEY_W)){
            view->move(0, 0, USER_SPEED);
        }else if(IsKeyDown(KEY_S)){
            view->move(0, 0, -USER_SPEED);
        }
        if(IsKeyDown(KEY_A)){
            view->move(-USER_SPEED, 0, 0);
        }else if(IsKeyDown(KEY_D)){
            view->move(USER_SPEED, 0, 0);
        }
        if(IsKeyDown(KEY_SPACE)){
            view->move(0, USER_SPEED, 0);
        }else if(IsKeyDown(KEY_LEFT_SHIFT)){
            view->move(0, -USER_SPEED, 0);
        }
        if(IsKeyDown(KEY_LEFT)){
            view->rotate(0.1, 0, 0);
        }else if(IsKeyDown(KEY_RIGHT)){
            view->rotate(-0.1, 0, 0);
        }if(IsKeyDown(KEY_UP)){
            view->rotate(0, 0.1, 0);
        }else if(IsKeyDown(KEY_DOWN)){
            view->rotate(0, -0.1, 0);
        }
        if(IsKeyDown(KEY_Q)){
            view->rotate(0, 0, -0.1);
        }else if(IsKeyDown(KEY_E)){
            view->rotate(0, 0, 0.1);
        }
        if(IsKeyDown(KEY_ENTER) && !live_rendering){
            auto start = std::chrono::high_resolution_clock().now();
            viewport->update();
            auto end = std::chrono::high_resolution_clock().now();

           time_elapsed = end - start; 
        }
    }

    BeginDrawing();

    ClearBackground(BLACK);

    if(live_rendering){
        auto start = std::chrono::high_resolution_clock().now();
        viewport->update();
        auto end = std::chrono::high_resolution_clock().now();
        
        time_elapsed = end - start; 
    } 

    UpdateTexture(viewport->get_texture(), viewport->get_pixels());

    DrawTexture(viewport->get_texture(), 0 + ui_width, 0, WHITE);

    // UI

    Rectangle ui_bounds = {0, 0, ui_width, ui_height};
    DrawRectangleRec(ui_bounds, (Color){119, 80, 217, 255});
    DrawRectangleLinesEx(ui_bounds, 1, (Color){255, 255, 255, 255});

    // Não tá legal, ele carregar a mesh toda vez q clica, tá carregando meshs repetidas
    // Além disso esse obj_file_entry como um char* tá terrivel
    /*if(GuiTextBox((Rectangle){0 + ui_padding, 32, 260, 32}, obj_file_entry, 120, obj_file_entry_edit)){
        obj_file_entry_edit = !obj_file_entry_edit;

        load_new_mesh(obj_file_entry); 
    }*/

    if(GuiButton(Rectangle{ui_width/2 - 90, ui_height - 64 - ui_padding, 180, 64}, "Render Image")){
        auto start = std::chrono::high_resolution_clock().now();
        viewport->update();
        auto end = std::chrono::high_resolution_clock().now();

        time_elapsed = end - start;
    }

    GuiCheckBox({ui_padding,  2*ui_padding, 50, 50}, "Auto-Render", &live_rendering);

    GuiLabel((Rectangle){0 + ui_padding, 0, 32, 16}, std::to_string(fps).insert(0, "fps: ").c_str());

    // Render image displays

    DrawText(std::to_string(view->get_camera_position().x).insert(0, "cam X: ").c_str(), 0 + ui_width + ui_padding, 0 + ui_padding, 16, WHITE);
    DrawText(std::to_string(view->get_camera_position().y).insert(0, "cam Y: ").c_str(), 0 + ui_width + ui_padding, 16 + ui_padding, 16, WHITE);
    DrawText(std::to_string(view->get_camera_position().z).insert(0, "cam Z: ").c_str(), 0 + ui_width + ui_padding, 32 + ui_padding, 16, WHITE);

    DrawText(std::to_string(time_elapsed.count()/1000).insert(0, "Time to render: ").append("s").c_str(), 0 + ui_width, render_height - 24, 24, WHITE);

    EndDrawing();
}
