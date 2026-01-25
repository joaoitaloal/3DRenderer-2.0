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
    scene(new Scene(view)),
    ui_state(new UI_STATE{viewport, false, scene}),
    ui_win(win_width_, win_height_, RENDERER_WIN_WIDTH, RENDERER_WIN_HEIGHT, ui_state)
{
    win_width = win_width_;
    win_height = win_height_;
    
    // Rendered image dimensions
    render_witdh = RENDERER_WIN_WIDTH; render_height = RENDERER_WIN_HEIGHT;
    ui_padding = 12;

    // ========= Criando objetos =========
    // Malhas
    //load_new_mesh("models/PlaneLow.obj", {0, 0.125, 0.25});
    load_new_mesh("models/ovni_cima.obj", {0.75, 0.75, 0.75});
    load_new_mesh("models/ovni_base.obj", {0.25, 0.25, 0.25});
    
    // Texturas
    Textura* lua =  new Textura("texturas/textura_lua.jpg");
    Textura* chao = new Textura("texturas/textura_chao.jpg");
    Textura* nave = new Textura("texturas/textura_nave3.jpg");
    Vector3R axis(0.5, 0.7, 0.5);
    // Cilindro
    scene->push_shape(new Cylinder(
        {-10, 5, 10},
        axis.normalize(),
        3,
        10,
        debug_temp_material({0.25, 0, 0.25}),
        nave
    ));
    // Esfera
    scene->push_shape(new Sphere(
        {0, 15, 0},
        3,
        debug_temp_material({1, 1, 0}),
        lua
    ));
    // Cone
    scene->push_shape(new Cone(
        {5, 5, 0},
        axis.normalize(),
        3,
        4,
        debug_temp_material({0, 0, 0.25}),
        nullptr
    ));
    // Plano
    scene->push_shape(new Plane(
        {0, 1, 0},
        {0, -10, 0},
        debug_temp_material({0, 0.25, 0}),
        chao,
        true
    ));

    // Temporary manual light creation:
    scene->push_light(new PointLight({20, 20, 20}, {1, 1, 1}));

    // Window configuration
    SetTargetFPS(60);

    // HACK: se por acaso algum código da ui rodar antes disso aqui o programa vai crashar
    // pq a gente começa passando uma referencia nula pra viewport
    viewport = new Viewport(RENDERER_WIN_WIDTH, RENDERER_WIN_HEIGHT, scene);
    ui_state->viewport = viewport;
}

// Falta ajeitar muita coisa aqui, principalmente coisas da UI que precisam sair desse método
void App::start()
{

    while(!WindowShouldClose()){
        process();
    }

    delete viewport;
    delete scene;
    delete ui_state;
    
    CloseWindow();
}

void App::load_new_mesh(string filename, Color3 color){
    try{
        // Material fixo temporário
        Mesh3* mesh = Mesh3::create_from_obj_file(filename, debug_temp_material(color));
        scene->push_shape(mesh);
    }catch(const int err){
        throw err; // Só pra ficar explicito o erro
    }
}

void App::process(){
    int fps = GetFPS();

    // Some screen controls, maybe temporary maybe not, definitely needs some work though
    if(IsKeyDown(KEY_W)){
        view->move(0, 0, USER_SPEED);
    }else if(IsKeyDown(KEY_S)){
        view->move(0, 0, -USER_SPEED);
    }
    if(IsKeyDown(KEY_A)){
        view->move(USER_SPEED, 0, 0);
    }else if(IsKeyDown(KEY_D)){
        view->move(-USER_SPEED, 0, 0);
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
        view->rotate(0, -0.1, 0);
    }else if(IsKeyDown(KEY_DOWN)){
        view->rotate(0, 0.1, 0);
    }
    if(IsKeyDown(KEY_Q)){
        view->rotate(0, 0, -0.1);
    }else if(IsKeyDown(KEY_E)){
        view->rotate(0, 0, 0.1);
    }
    if(IsKeyDown(KEY_ENTER) && !ui_state->live_rendering){
        auto start = std::chrono::high_resolution_clock().now();
        viewport->update();
        auto end = std::chrono::high_resolution_clock().now();

        time_elapsed = end - start; 
    }
    
    BeginDrawing();

    ClearBackground(BLACK);

    if(ui_state->live_rendering){
        auto start = std::chrono::high_resolution_clock().now();
        viewport->update();
        auto end = std::chrono::high_resolution_clock().now();
        
        time_elapsed = end - start; 
    } 

    UpdateTexture(viewport->get_texture(), viewport->get_pixels());

    DrawTexture(viewport->get_texture(), win_width-render_witdh, win_height-render_height, WHITE);

    // UI
    ui_win.render();

    // Render image displays

    DrawText(std::to_string(view->get_camera_position().x).insert(0, "cam X: ").c_str(), 0 + win_width-render_witdh + ui_padding, 0 + win_height-render_height + ui_padding, 16, WHITE);
    DrawText(std::to_string(view->get_camera_position().y).insert(0, "cam Y: ").c_str(), 0 + win_width-render_witdh + ui_padding, 16 + win_height-render_height + ui_padding, 16, WHITE);
    DrawText(std::to_string(view->get_camera_position().z).insert(0, "cam Z: ").c_str(), 0 + win_width-render_witdh + ui_padding, 32 + win_height-render_height + ui_padding, 16, WHITE);

    DrawText(std::to_string(time_elapsed.count()/1000).insert(0, "Time to render: ").append("s").c_str(), 0 + win_width-render_witdh, win_height-render_height + render_height - 24, 24, WHITE);

    GuiLabel((Rectangle){0 + ui_padding, 0, 32, 16}, std::to_string(fps).insert(0, "fps: ").c_str());

    EndDrawing();
}
