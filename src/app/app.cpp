#include "app.h"

// Temporario, tirar daqui depois
#include "../scene/objects/Lights/Point/PointLight.h"
// Esse não sei se é temporario, mas deve ir pra outro lugar em alguma refatoração
#include "../scene/objects/Mesh3/Mesh3.h"

App::App(int win_width_, int win_height_)
    : view(0, 2, -10, 1, 1)
{
    win_width = win_width_;
    win_height = win_height_;

    shapes = new vector<Shape*>;
    lights = new vector<Light*>;

    ui_width = 360; ui_height = 720;
    ui_padding = 12;
    obj_file_entry_edit = false;
    obj_file_entry = "";
    load_new_mesh("models/PlaneLow.obj", {0, 0.125, 0.25});
    load_new_mesh("models/Cube.obj", {0.25, 0, 0});

    // Rendered image dimensions
    render_witdh = 720; render_height = 720;
    render_offset = win_width-render_witdh; // Offset por causa da UI

    // Window configuration
    InitWindow(win_width, win_height, "Raytracer!!!!!!!!!!!");
    SetTargetFPS(60);

    // Setting UI styles, change this to another file just for organization
    GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, ColorToInt((Color){ 100, 200, 255, 255 }));

    // Inicializando textura que guarda os pixels do renderizador
    Image init = GenImageColor(render_witdh, render_height, BLACK);
    tex = new TextureCPU(init);
    UnloadImage(init);
}

App::~App(){
    delete tex;
}

// Falta ajeitar muita coisa aqui, principalmente coisas da UI que precisam sair desse método
void App::start()
{
    //std::chrono::duration<double, std::milli> time_elapsed(0);

    // Temporary manual light creation:
    Light* light = new PointLight({20, 20, 20}, {1, 1, 1});
    lights->push_back(light);

    while(!WindowShouldClose()){
        process();
    }
    
    CloseWindow();
}

void App::load_new_mesh(string filename, Color3 color){
    try{
        // Material fixo temporário
        Mesh3* mesh = Mesh3::create_from_obj_file(filename, {color, 0.5, 0.5, 0.3, 0.3, 10});
        shapes->push_back(mesh);

        cout << "Carregou!" << endl;
    }catch(const int err){
        throw err; // Só pra ficar explicito o erro
    }
}

void App::process(){
    int fps = GetFPS();

    // Some screen controls, maybe temporary maybe not, definitely needs some work though
    if(!obj_file_entry_edit){
        if(IsKeyDown(KEY_W)){
            view.move(0, 0, USER_SPEED);
        }else if(IsKeyDown(KEY_S)){
            view.move(0, 0, -USER_SPEED);
        }
        if(IsKeyDown(KEY_A)){
            view.move(USER_SPEED, 0, 0);
        }else if(IsKeyDown(KEY_D)){
            view.move(-USER_SPEED, 0, 0);
        }
        if(IsKeyDown(KEY_SPACE)){
            view.move(0, USER_SPEED, 0);
        }else if(IsKeyDown(KEY_LEFT_SHIFT)){
            view.move(0, -USER_SPEED, 0);
        }
        if(IsKeyDown(KEY_ENTER)){
            //auto start = std::chrono::high_resolution_clock().now();
            tex->update(view, render_witdh, render_height, shapes, lights);
            //auto end = std::chrono::high_resolution_clock().now();

            // The animation time is included, from my tests the animation takes 10/anim_speed seconds, this probably changes between different hardware since it is not on a fixed delay
           // time_elapsed = end - start; 
        }
    }

    BeginDrawing();

    ClearBackground(BLACK);

    UpdateTexture(tex->texture, tex->pixels);

    DrawTexture(tex->texture, 0 + render_offset, 0, WHITE);

    // UI

    Rectangle ui_bounds = {0, 0, ui_width, ui_height};
    DrawRectangleRec(ui_bounds, (Color){119, 80, 217, 255});
    DrawRectangleLinesEx(ui_bounds, 1, (Color){255, 255, 255, 255});

    GuiLabel((Rectangle){0 + ui_padding, 0, 32, 16}, std::to_string(fps).insert(0, "fps: ").c_str());

    if(GuiTextBox((Rectangle){0 + ui_padding, 32, 260, 32}, obj_file_entry, 120, obj_file_entry_edit)){
        obj_file_entry_edit = !obj_file_entry_edit;

        //load_new_mesh(obj_file_entry); // Não tá legal, ele carregar a mesh toda vez q clica, tá carregando meshs repetidas
    }

    if(GuiButton((Rectangle){ui_width/2 - 90, ui_height - 64 - ui_padding, 180, 64}, "Render Image")){
        //auto start = std::chrono::high_resolution_clock().now();
        tex->update(view, render_witdh, render_height, shapes, lights);
        //auto end = std::chrono::high_resolution_clock().now();

        // The animation time is included, from my tests the animation takes 10/anim_speed seconds, this probably changes between different hardware since it is not on a fixed delay
        //time_elapsed = end - start;
    }


    // Render image displays

    DrawText(std::to_string(view.position.x).insert(0, "cam X: ").c_str(), 0 + render_offset + ui_padding, 0 + ui_padding, 16, WHITE);
    DrawText(std::to_string(view.position.y).insert(0, "cam Y: ").c_str(), 0 + render_offset + ui_padding, 16 + ui_padding, 16, WHITE);
    DrawText(std::to_string(view.position.z).insert(0, "cam Z: ").c_str(), 0 + render_offset + ui_padding, 32 + ui_padding, 16, WHITE);

    //DrawText(std::to_string(time_elapsed.count()/1000).insert(0, "Time to render: ").append("s").c_str(), 0 + render_offset, render_height - 24, 24, WHITE);

    EndDrawing();
}
