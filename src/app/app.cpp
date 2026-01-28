#include "app.h"

// Temporario
Material3 debug_temp_material(Color3 color){
    return {color, 0.5, 0.5, 0.3, 0.3, 10};
}

App::App(int win_width_, int win_height_)
    : view(new View({-10, 2, 0}, 2, 2, 1)),
    scene(new Scene(view)),
    ui_state(new UI_STATE{viewport, false, nullptr, scene}),
    ui_win(win_width_, win_height_, RENDERER_WIN_WIDTH, RENDERER_WIN_HEIGHT, ui_state)
{
    win_width = win_width_;
    win_height = win_height_;
    
    // Rendered image dimensions
    render_witdh = RENDERER_WIN_WIDTH; render_height = RENDERER_WIN_HEIGHT;
    ui_padding = 12;
    
    textures.insert({"lua", new Textura("texturas/textura_lua.jpg")});
    textures.insert({"gargantua", new Textura("texturas/textura_gargantua.jpg")});
    textures.insert({"chao", new Textura("texturas/textura_chao.jpg")});
    textures.insert({"nave", new Textura("texturas/textura_nave.png")});
    textures.insert({"skybox", new Textura("texturas/space_skybox.jpg")});
    textures.insert({"chama", new Textura("texturas/textura_chama.png")});
    textures.insert({"ovni_cima", new Textura("texturas/textura_ovni_cima.png")});
    textures.insert({"ovni_base", new Textura("texturas/textura_ovni_base.png")});
    textures.insert({"sun", new Textura("texturas/sun.jpg")});
    textures.insert({"tex_placa_solar", new Textura("texturas/textura_placa_solar.png")});

    // Texturas a seguir são do site: https://planetpixelemporium.com
    textures.insert({"earth", new Textura("texturas/earth.jpg")});
    textures.insert({"jupiter", new Textura("texturas/jupiter.jpg")});
    textures.insert({"saturn", new Textura("texturas/saturn.jpg")});
    textures.insert({"saturn_ring", new Textura("texturas/saturn_ring.jpg")});

    //load_new_mesh("models/ovni_base.obj", {0.75, 0.75, 0.75}, "ovni", textures.at("ovni_base"), true);

    scene->set_background_tex(textures.at("skybox"));

    create_estacao({500, 500, 500});
    create_foguete({0, 0, 0}, 1);

    // Planetas
    scene->push_shape(new Sphere(
        {0, 250, 300},
        150,
        debug_temp_material({0, 0, 0}),
        textures.at("jupiter"),
        "jupiter"
    ));
    Vector3R earth_pos = {500, 300, 700};
    scene->push_shape(new Sphere(
        earth_pos,
        60,
        debug_temp_material({0, 0, 0}),
        textures.at("earth"),
        "Terra"
    ));
    scene->push_shape(new Sphere(
        earth_pos + Vector3R{60, 60, 60},
        10,
        debug_temp_material({0, 0, 0}),
        textures.at("lua"), // TODO
        "lua"
    ));
    Vector3R saturn_pos = {500, 550, 50};
    Vector3R saturn_ring_dir = {1, 1, 1};
    scene->push_shape(new Sphere(
        saturn_pos,
        100,
        debug_temp_material({0, 0, 0}),
        textures.at("saturn"), // TODO
        "Saturno"
    ));
    scene->push_shape(new Ring(
        saturn_pos,
        saturn_ring_dir.normalize(),
        200,
        150,
        debug_temp_material({0, 0, 0}),
        textures.at("saturn_ring"), // TODO
        "Anel",
        false
    )); 

    // Sol
    Vector3R sun_pos = {1000, 1000, 1000};
    scene->push_shape(new Sphere(
        sun_pos,
        250,
        {{0, 0, 0}, 0, 0, 0.5, 0, 0},
        textures.at("sun"),
        "sun"
    ));
    scene->push_light(new PointLight(sun_pos, {1, 1, 1}));

    // Gargantua
    Vector3R gargantua_pos = {250, 250, 1500};
    gargantua_ring = new Ring(
        gargantua_pos,
        {0, 0, -1},
        300,
        0,
        {{0, 0, 0}, 0, 0, 0, 0, 0},
        textures.at("gargantua"),
        "Gargantula_Ring",
        true
    );
    scene->push_shape(gargantua_ring);
    gargantua_ring2 = new Ring(
        gargantua_pos,
        {0, 1, -1},
        300,
        0,
        {{0, 0, 0}, 0, 0, 0, 0, 0},
        textures.at("gargantua"),
        "Gargantula_Ring",
        true
    );
    scene->push_shape(gargantua_ring2);
    scene->push_shape(new Sphere(
        gargantua_pos,
        200,
        {{0, 0, 0}, 0, 0, 0, 0, 0},
        nullptr,
        "Gargantula"
    ));
    

    // Luzes
    //scene->push_light(new DirectionalLight({0, -1, 0}, {1, 1, 1}));

    // Window configuration
    SetTargetFPS(60);

    // HACK: se por acaso algum código da ui rodar antes disso aqui o programa vai crashar
    // pq a gente começa passando uma referencia nula pra viewport
    viewport = new Viewport(RENDERER_WIN_WIDTH, RENDERER_WIN_HEIGHT, scene);
    ui_state->viewport = viewport;
}

void App::start()
{

    while(!WindowShouldClose()){
        process();
    }

    delete viewport;
    delete scene;
    delete ui_state;

    for(auto tex : textures){
        delete tex.second;
    }
    textures.clear();
    
    CloseWindow();
}

void App::load_new_mesh(string filename, Color3 color, string name, Textura* tex, bool culled = true){
    try{
        // Material fixo temporário
        Mesh3* mesh = Mesh3::create_from_obj_file(filename, debug_temp_material(color), name, tex, culled);
        scene->push_shape(mesh);
    }catch(const int err){
        throw err; // Só pra ficar explicito o erro
    }
}

void App::process(){
    int fps = GetFPS();
    bool moved = false;

    // Some screen controls, maybe temporary maybe not, definitely needs some work though
    if(IsKeyDown(KEY_W)){
        view->move(0, 0, USER_SPEED);
        moved = true;
    }else if(IsKeyDown(KEY_S)){
        view->move(0, 0, -USER_SPEED);
        moved = true;
    }
    if(IsKeyDown(KEY_A)){
        view->move(USER_SPEED, 0, 0);
        moved = true;
    }else if(IsKeyDown(KEY_D)){
        view->move(-USER_SPEED, 0, 0);
        moved = true;
    }
    if(IsKeyDown(KEY_SPACE)){
        view->move(0, USER_SPEED, 0);
        moved = true;
    }else if(IsKeyDown(KEY_LEFT_SHIFT)){
        view->move(0, -USER_SPEED, 0);
        moved = true;
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
    if(IsKeyDown(KEY_ENTER) || ui_state->live_rendering){
        auto start = chrono::high_resolution_clock().now();
        viewport->update();
        auto end = chrono::high_resolution_clock().now();
        UpdateTexture(viewport->get_texture(), viewport->get_pixels());

        time_elapsed = end - start;
    }
    if(IsKeyDown(KEY_J)){
        scene->move_to(Vector3R{0, 8+10+18+15 + 10, -20} + estacao_pos);
        scene->look_at(Vector3R{0, 1, 0}*(8+10+18+15 + 10) + estacao_pos);
        scene->move_to(Vector3R{0, 8+10+18+15 + 10, -40} + estacao_pos);
    }
    else if(IsKeyDown(KEY_K)){
        scene->move_to(Vector3R{20, 8+10+18+12, 20} + estacao_pos);
        scene->look_at(Vector3R{0, 1, 0}*(8+10+18+12) + estacao_pos);
    }
    else if(IsKeyDown(KEY_L)){
        scene->move_to(Vector3R{-15, 8+10+18+12 + 15, -15} + estacao_pos);
        scene->look_at(Vector3R{0, 1, 0}*(8+10+18+12) + estacao_pos);
    }

    if(moved){
        gargantua_ring->rotate_to(view->get_camera_position());
        MatrixR rot = get_rotation_around_axis(PI/2 - PI/15, {1, 0, 0});
        gargantua_ring2->set_normal(normal_transform(rot, gargantua_ring->get_normal()));
    }

    // Pick
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        Vector2 mouse_pos = GetMousePosition();
        mouse_pos.x -= win_width-render_witdh;
        mouse_pos.y -= win_height-render_height;
        if(mouse_pos.x >= 0 && mouse_pos.y >= 0){
            ui_state->picked = scene->get_collision(mouse_pos.x, mouse_pos.y, render_witdh, render_height);
        }
    }
    
    BeginDrawing();

    ClearBackground(BLACK);

    DrawTexture(viewport->get_texture(), win_width-render_witdh, win_height-render_height, WHITE);

    // UI
    ui_win.render();

    // Render image displays

    DrawText(to_string(view->get_camera_position().x).insert(0, "cam X: ").c_str(), 0 + win_width-render_witdh + ui_padding, 0 + win_height-render_height + ui_padding, 16, WHITE);
    DrawText(to_string(view->get_camera_position().y).insert(0, "cam Y: ").c_str(), 0 + win_width-render_witdh + ui_padding, 16 + win_height-render_height + ui_padding, 16, WHITE);
    DrawText(to_string(view->get_camera_position().z).insert(0, "cam Z: ").c_str(), 0 + win_width-render_witdh + ui_padding, 32 + win_height-render_height + ui_padding, 16, WHITE);

    DrawText(to_string(time_elapsed.count()/1000).insert(0, "Time to render: ").append("s").c_str(), 0 + win_width-render_witdh, win_height-render_height + render_height - 24, 24, WHITE);

    GuiLabel((Rectangle){0 + ui_padding, 0, 32, 16}, to_string(fps).insert(0, "fps: ").c_str());

    EndDrawing();
}

void App::create_estacao(Vector3R pos){
    estacao_pos = pos;
    Vector3R axis = {0, 1, 0};
    scene->push_shape(new Cylinder(
        pos,
        axis,
        14,
        8,
        debug_temp_material({0.25, 0.25, 0.25}), // TODO
        nullptr,
        "estacao_base1"
    ));
    scene->push_shape(new Cylinder(
        pos + axis*8,
        axis,
        8,
        10,
        debug_temp_material({0.25, 0.25, 0.25}), // TODO
        nullptr,
        "estacao_base2"
    ));
    scene->push_shape(new Cylinder(
        pos + axis*(8+10),
        axis,
        4,
        18,
        debug_temp_material({0.25, 0.25, 0.25}), // TODO
        nullptr,
        "estacao_base3"
    ));
    Mesh3* estacao_cabine = Mesh3::create_from_obj_file("models/Cube.obj", debug_temp_material({0.25, 0, 0}), "estacao_cabine", nullptr, true);
    estacao_cabine->transform(get_scale_matrix({15, 15, 15}));
    estacao_cabine->transform(get_translation_matrix(axis*(8+10+18) + pos));
    scene->push_shape(estacao_cabine);

    //scene->set_forward(cross_product(up, axis).normalize());
    
    // Placas solares
    Mesh3* placa_solar1 = Mesh3::create_from_obj_file("models/Cube.obj", debug_temp_material({0.25, 0, 0}), "placa_solar1", textures.at("tex_placa_solar"), true);
    placa_solar1->transform(get_translation_matrix(Vector3R{0, 8+5, -10} + pos));
    placa_solar1->transform(get_scale_matrix({10, 0.1, 45}));
    scene->push_shape(placa_solar1);
    
    Mesh3* placa_solar2 = Mesh3::create_from_obj_file("models/Cube.obj", debug_temp_material({0.25, 0, 0}), "placa_solar1", textures.at("tex_placa_solar"), true);
    placa_solar2->transform(get_translation_matrix(Vector3R{0, 8+5, 10} + pos));
    placa_solar2->transform(get_scale_matrix({10, 0.1, 45}));
    scene->push_shape(placa_solar2);
    
    Mesh3* placa_solar3 = Mesh3::create_from_obj_file("models/Cube.obj", debug_temp_material({0, 0, 0}), "placa_solar1", textures.at("tex_placa_solar"), true);
    placa_solar3->transform(get_translation_matrix(Vector3R{-10, 8+5, 0} + pos));
    placa_solar3->transform(get_scale_matrix({30, 0.1, 5}));
    scene->push_shape(placa_solar3);
    
    Mesh3* placa_solar4 = Mesh3::create_from_obj_file("models/Cube.obj", debug_temp_material({0, 0, 0}), "placa_solar1", textures.at("tex_placa_solar"), true);
    placa_solar4->transform(get_translation_matrix(Vector3R{10, 8+5, 0} + pos));
    placa_solar4->transform(get_scale_matrix({30, 0.1, 5}));
    scene->push_shape(placa_solar4);
}

void App::create_foguete(Vector3R pos, float scale){
    Vector3R axis_foguete = {0, 0, 1};
    Vector3R pos_foguete = pos;

    scene->push_shape(new Cylinder(
        pos_foguete,
        axis_foguete,
        3*scale,
        10*scale,
        debug_temp_material({0.25, 0, 0}), // TODO
        textures.at("nave"),
        "Fuselagem"
    ));
    scene->push_shape(new Cone(
        (pos_foguete + axis_foguete*10*scale),
        axis_foguete,
        3*scale,
        6*scale,
        debug_temp_material({0.25, 0, 0}), // TODO
        nullptr,
        "Ponta"
    ));
    scene->push_shape(new Cone(
        (pos_foguete - axis_foguete*2*scale),
        axis_foguete,
        2.5*scale,
        4*scale,
        debug_temp_material({0.25, 0, 0}), // TODO
        nullptr,
        "Motor"
    ));
    
    Mesh3* chama = Mesh3::create_from_obj_file("models/Chama.obj", debug_temp_material({0, 0, 0}), "chama nave", textures.at("chama"), true);
    chama->transform(get_scale_matrix({2.0f*scale, 2.0f*scale, 2.0f*scale}));
    chama->transform(get_x_rotation(-PI/2));
    chama->transform(get_translation_matrix(axis_foguete*((-2-4 + 3)*scale) + pos_foguete));
    scene->push_shape(chama);

    Mesh3* asa1 = Mesh3::create_from_obj_file("models/Triangle.obj", debug_temp_material({0.25, 0, 0}), "chama nave", nullptr, false);
    asa1->transform(get_scale_matrix({2.0f*scale, 2.0f*scale, 2.0f*scale}));
    //asa1->transform(get_y_rotation(PI/2));
    //asa1->transform(get_x_rotation(PI/2));
    asa1->transform(get_translation_matrix(Vector3R{0, 3*scale, 0} + pos_foguete));
    scene->push_shape(asa1);

    Mesh3* asa2 = Mesh3::create_from_obj_file("models/Triangle.obj", debug_temp_material({0.25, 0, 0}), "chama nave", nullptr, false);
    asa2->transform(get_scale_matrix({2.0f*scale, 2.0f*scale, 2.0f*scale}));
    asa2->transform(get_x_rotation(PI));
    asa2->transform(get_translation_matrix(axis_foguete*((-2-4 + 3)*scale) + pos_foguete));
    scene->push_shape(asa2);

    Mesh3* asa3 = Mesh3::create_from_obj_file("models/Triangle.obj", debug_temp_material({0.25, 0, 0}), "chama nave", nullptr, false);
    asa3->transform(get_scale_matrix({2.0f*scale, 2.0f*scale, 2.0f*scale}));
    asa3->transform(get_x_rotation(PI));
    asa3->transform(get_translation_matrix(axis_foguete*((-2-4 + 3)*scale) + pos_foguete));
    scene->push_shape(asa3);

    //load_new_mesh("models/Triangle.obj", {0.25, 0.25, 0.25}, "Asa1", nullptr, false);
}

void App::create_ovni(Vector3R pos, Vector3R dir, float scale){
}
