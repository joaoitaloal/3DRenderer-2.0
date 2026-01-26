#include "Vec3Entry.h"

Vec3Entry::Vec3Entry(Rectangle bounds_, string title_, string x_label, string y_label, string z_label, function<void(Vector3R)> on_submit)
    : ScrollableFrame(bounds_),
    label({bounds.x, bounds.y, 60, 32}, title_),
    x({bounds.x, bounds.y + 32, 60, 32}, x_label, [this](float num){ vector.x = num; }),
    y({bounds.x, bounds.y + 64, 60, 32}, y_label, [this](float num){ vector.y = num; }),
    z({bounds.x, bounds.y + 96, 60, 32}, z_label, [this](float num){ vector.z = num; }),
    submit({bounds.x + 5, bounds.y + 128, 50, 32}, "Submit", [this, on_submit]{
        on_submit(vector);
    })
{}

void Vec3Entry::render(Vector2 scrollOffset){
    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 14);
    label.render({0, 0});
    GuiSetStyle(DEFAULT, TEXT_SIZE, 10);

    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

    x.render({0, 0});
    y.render({0, 0});
    z.render({0, 0});
    submit.render({0, 0});
}

