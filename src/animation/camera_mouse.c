#include "ft_minirt.h"

void mouse_look_callback(double xpos, double ypos, void *param)
{
    t_app    *app = param;
    t_camera *cam = &app->scene.camera;

    static double last_x = 0;
    static double last_y = 0;
    static int first = 1;

    if (first)
    {
        last_x = xpos;
        last_y = ypos;
        first = 0;
    }

    double dx = xpos - last_x;
    double dy = ypos - last_y;
    last_x = xpos;
    last_y = ypos;

    cam->yaw   += dx * cam->mouse_sens;
    cam->pitch -= dy * cam->mouse_sens;

    if (cam->pitch > 1.5f)  cam->pitch = 1.5f;
    if (cam->pitch < -1.5f) cam->pitch = -1.5f;

    t_vec3 dir;
    dir.x = cosf(cam->yaw) * cosf(cam->pitch);
    dir.y = sinf(cam->pitch);
    dir.z = sinf(cam->yaw) * cosf(cam->pitch);
    cam->direction = vnorm(dir);

    camera_build(cam);
}
