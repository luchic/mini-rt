#include "ft_minirt.h"

/* ===========================================================
** Basic vector scale
** ===========================================================*/
static t_vec3 vscale(t_vec3 v, float k)
{
    return vec3(v.x * k, v.y * k, v.z * k);
}

/* ===========================================================
** Smooth step lerp (optional smoothing)
** ===========================================================*/
static float smooth(float a, float b, float t)
{
    return a + (b - a) * (t * t * (3 - 2 * t));
}

/* ===========================================================
** Free camera movement (WASD + vertical)
** ===========================================================*/
static void camera_move(t_app *app, double dt)
{
    t_camera *c = &app->scene.camera;

    float speed = c->move_speed * dt;

    t_vec3 forward = vnorm(c->direction);
    t_vec3 right   = vnorm(vcross_product(forward, vec3(0,1,0)));

    t_vec3 target_pos = c->pos;

    if (mlx_is_key_down(app->mlx, MLX_KEY_W))
        target_pos = vadd(target_pos, vscale(forward, speed));
    if (mlx_is_key_down(app->mlx, MLX_KEY_S))
        target_pos = vsub(target_pos, vscale(forward, speed));
    if (mlx_is_key_down(app->mlx, MLX_KEY_A))
        target_pos = vsub(target_pos, vscale(right,   speed));
    if (mlx_is_key_down(app->mlx, MLX_KEY_D))
        target_pos = vadd(target_pos, vscale(right,   speed));

    if (mlx_is_key_down(app->mlx, MLX_KEY_SPACE))
        target_pos.y += speed;
    if (mlx_is_key_down(app->mlx, MLX_KEY_LEFT_CONTROL))
        target_pos.y -= speed;

    float alpha = 0.25f;
    c->pos.x = smooth(c->pos.x, target_pos.x, alpha);
    c->pos.y = smooth(c->pos.y, target_pos.y, alpha);
    c->pos.z = smooth(c->pos.z, target_pos.z, alpha);
}

/* ===========================================================
** Init animation timestamp
** ===========================================================*/
void anim_init(t_app *app)
{
    app->last_ts = mlx_get_time();
    app->scene.camera.move_speed = 4.0f;
    app->scene.camera.mouse_sens = 0.0025f;
}

/* ===========================================================
** Main animation update loop
** ===========================================================*/
void cam_anim_update(t_app *app, double now)
{
    if (!app || !app->animation.enabled)
        return;

    double dt = now - app->last_ts;
    if (dt < (1.0 / 60.0))
        return;

    app->last_ts = now;

    camera_move(app, dt);
    camera_build(&app->scene.camera);

    app->needs_redraw = 1;
}
