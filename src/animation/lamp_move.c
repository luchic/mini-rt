#include "ft_minirt.h"
#include <math.h>

/*
** Utility: linear interpolation for smooth color transitions
*/
static t_rgb lerp_rgb(t_rgb a, t_rgb b, float t)
{
    t_rgb o;
    o.red   = a.red   + (b.red   - a.red)   * t;
    o.green = a.green + (b.green - a.green) * t;
    o.blue  = a.blue  + (b.blue  - a.blue)  * t;
    return (o);
}

/*
** Get sun color based on curve k (0 → sunrise, 1 → noon, 0 → sunset)
*/
static t_rgb get_sun_color(float k)
{
    t_rgb morning = {1.0f, 0.65f, 0.35f};
    t_rgb noon    = {1.0f, 1.0f, 1.0f};
    t_rgb evening = {1.0f, 0.45f, 0.25f};

    if (k < 0.5f)
        return lerp_rgb(morning, noon, k * 2.0f);
    return lerp_rgb(noon, evening, (k - 0.5f) * 2.0f);
}

/*
** Move sun across sky by updating its point-light position
** + update brightness & color smoothly
*/
void update_lamp_sun(t_app *app)
{
    t_light *sun;
    double time_now;
    float t, k, angle;

    sun = app->scene.lights;
    if (!sun)
        return;

    time_now = mlx_get_time();
    t = (float)(time_now * 0.2f);     // animation speed
    angle = t;

    /*
    ** Sun path: rotate on XZ plane, height controlled by sin()
    */
    float radius = 20.0f;
    float y = sinf(t) * 10.0f + 15.0f; // rising & falling height

    sun->pos.x = cosf(angle) * radius;
    sun->pos.z = sinf(angle) * radius;
    sun->pos.y = y;

    /*
    ** k = intensity curve (0 → sunrise, 1 → noon → 0 sunset)
    */
    k = sinf(t);
    if (k < 0.0f)
        k = 0.0f;

    sun->br = 0.2f + k * 1.5f;   // brightness

    sun->color = get_sun_color(k);
}
