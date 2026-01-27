#include "ShearEntry.h"

ShearEntry::ShearEntry(Rectangle bounds_, string title_, function<void(Vector2, Vector2, Vector2)> on_submit)
    : ScrollableFrame(bounds_),
    label({bounds.x, bounds.y, 60, 32}, "Shear"),
    label_xy({bounds.x - 15, bounds.y + 32, 15, 32}, "xy"),
    xy_x({bounds.x, bounds.y + 32, 30, 32}, "", "", -0.5f, 0.5f, 0, 
        [this](float num){
            xy.x = num;
        }
    ),
    xy_y({bounds.x + 30, bounds.y + 32, 30, 32}, "", "", -0.5f, 0.5f, 0, 
        [this](float num){
            xy.y = num;
        }
    ),
    label_xz({bounds.x - 15, bounds.y + 64, 15, 32}, "xz"),
    xz_x({bounds.x, bounds.y + 64, 30, 32}, "", "", -0.5f, 0.5f, 0, 
        [this](float num){
            xz.x = num;
        }
    ),
    xz_z({bounds.x + 30, bounds.y + 64, 30, 32}, "", "", -0.5f, 0.5f, 0, 
        [this](float num){
            xz.y = num;
        }
    ),
    label_yz({bounds.x - 15, bounds.y + 96, 15, 32}, "yz"),
    yz_y({bounds.x, bounds.y + 96, 30, 32}, "", "", -0.5f, 0.5f, 0, 
        [this](float num){
            yz.x = num;
        }
    ),
    yz_z({bounds.x + 30, bounds.y + 96, 30, 32}, "", "", -0.5f, 0.5f, 0, 
        [this](float num){
            yz.y = num;
        }
    ),
    reset({bounds.x, bounds.y + 128, 60, 32}, "Reset", [this](){
        xy_x.reset();
        xy_y.reset();
        xz_x.reset();
        xz_z.reset();
        yz_y.reset();
        yz_z.reset();
    }),
    submit({bounds.x, bounds.y + 160, 60, 32}, "Submit", [on_submit, this](){
        on_submit(xy, xz, yz);
    })
{}

void ShearEntry::render(Vector2 scrollOffset){
    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 14);
    label.render({0, 0});
    GuiSetStyle(DEFAULT, TEXT_SIZE, 10);
    label_xy.render({0, 0});
    label_xz.render({0, 0});
    label_yz.render({0, 0});
    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

    xy_y.render({0, 0});
    xz_x.render({0, 0});

    xz_z.render({0, 0});
    xy_x.render({0, 0});

    yz_y.render({0, 0});
    yz_z.render({0, 0});

    reset.render({0, 0});
    submit.render({0, 0});
}
