#ifndef RENDERER_SHAPEGROUO_H
#define RENDERER_SHAPEGROUO_H

#include "../../../math/BoundingBox/BoundingBoxR.h"
#include "../Shape.h"

#include <vector>

// Tá meio TODO, não terminei ela inteira e nem sei se ajudaria muito.

class ShapeGroup : public Shape {
    public:
        ShapeGroup(Vector3R position, string name_);
        ~ShapeGroup();

        Collision get_collision(RayR ray) override;

        ShapeGroup* transform_return(const MatrixR& m) override;
        void transform(const MatrixR& m) override;

        // Escalar todos? ou não fazer nada?
        void scale(Vector3R dims) override {};

        void push_shape(Shape* shape);

    private:
        std::vector<Shape*> shapes;
        //BoundingBoxR bbox; // TODO

        Vector3R anchor;
        
        void update_transformation_matrices();
};

#endif // RENDERER_GRRENDERER_SHAPEGROUO_HOUP_H