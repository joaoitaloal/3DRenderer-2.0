#include <raylib.h>

#include "../scene.h"

// Camera and plane combined
class View{
    private:
        Camera3 cam;
        Plane plane;
    public:
        Vector3 position;

        View(Camera3 &set_cam, Plane &set_plane)
            : cam(set_cam), plane(set_plane) {
                position = cam.position;
            };

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

        //temp
        void move(float x, float z, float y){
            cam.position.x += x;
            cam.position.y += y;
            cam.position.z += z;

            position.x += x;
            position.y += y;
            position.z += z;

            plane.p1.x += x;
            plane.p2.x += x;
            plane.p3.x += x;
            plane.p4.x += x;

            plane.p1.y += y;
            plane.p2.y += y;
            plane.p3.y += y;
            plane.p4.y += y;

            plane.p1.z += z;
            plane.p2.z += z;
            plane.p3.z += z;
            plane.p4.z += z;
        }

};