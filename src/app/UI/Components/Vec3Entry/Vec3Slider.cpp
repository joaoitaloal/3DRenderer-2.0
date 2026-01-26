#include "Vec3Slider.h"

Vec3Slider::Vec3Slider(Rectangle bounds_, string title_, float min, float max, function<void(Vector3R)> on_submit)
    : ScrollableFrame(bounds_),
    label({bounds.x, bounds.y, 50, 32}, title_),
    x({bounds.x, bounds.y + 32, 50, 16}, "x", "", min, max, 1, [this, on_submit](float num){ vector.x = num; on_submit(vector); }),
    y({bounds.x, bounds.y + 64, 50, 16}, "y", "", min, max, 1, [this, on_submit](float num){ vector.y = num; on_submit(vector); }),
    z({bounds.x, bounds.y + 96, 50, 16}, "z", "", min, max, 1, [this, on_submit](float num){ vector.z = num; on_submit(vector); })
{}

void Vec3Slider::render(Vector2 scrollOffset){
    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    GuiSetStyle(DEFAULT, TEXT_SIZE, 14);
    label.render({0, 0});
    GuiSetStyle(DEFAULT, TEXT_SIZE, 10);

    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);

    x.render({0, 0});
    y.render({0, 0});
    z.render({0, 0});
}

