#include <raylib.h>

#include "../scene.h"

// Camera and plane combined
class View{
    private:
        Camera3 cam;
        Plane plane;
    public:
        View(Camera3 &set_cam, Plane &set_plane)
            : cam(set_cam), plane(set_plane) {};

        void setFov(float fov){
    
        }

        Ray createRay(float alpha, float beta){
            Vector3 t = Vector3Add(
                Vector3Scale(plane.p1, 1.0f-alpha),
                Vector3Scale(plane.p2, alpha)
            );

            Vector3 b = Vector3Add(
                Vector3Scale(plane.p3, 1.0f-alpha),
                Vector3Scale(plane.p4, alpha)
            );

            Vector3 origin = Vector3Add(
                Vector3Scale(t, 1.0f-beta),
                Vector3Scale(b, beta)
            );

            Vector3 dir = Vector3Normalize(Vector3Subtract(origin, cam.position));

            Ray ray = {origin, dir};

            return ray;
        }

};