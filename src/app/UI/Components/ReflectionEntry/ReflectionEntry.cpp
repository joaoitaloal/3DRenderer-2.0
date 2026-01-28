#include "ReflectionEntry.h"

ReflectionEntry::ReflectionEntry(Rectangle bounds_, string title_, function<void(Vector3R)> on_submit)
    : ScrollableFrame(bounds_),
    label({bounds.x, bounds.y, 120, 32}, title_),
    x({bounds.x, bounds.y + 32, 40, 32}, "x", [this](float num){ vector.x = num; }),
    y({bounds.x + 40, bounds.y + 32, 40, 32}, "y", [this](float num){ vector.y = num; }),
    z({bounds.x + 80, bounds.y + 32, 40, 32}, "z", [this](float num){ vector.z = num; }),
    submit({bounds.x + 40 - 5, bounds.y + 64, 50, 32}, "Submit", [this, on_submit]{
        on_submit(vector);
    })
{
}

void ReflectionEntry::render(Vector2 scrollOffset){
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
