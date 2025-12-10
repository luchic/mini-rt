#include "under_water.h"
#include <math.h>

void	water_init(t_app *app)
{
	t_water	*fx;

	fx = &app->water;
	fx->enabled = 1;
	fx->shimmer_strength = 0.03f;
	fx->ripple_intensity = 0.08f;
	fx->ripple_freq = 14.0f;
	fx->ripple_speed = 3.0f;
	fx->ripple_fade = 2.2f;
	fx->ripple_active = 0;
	fx->ripple_start = 0.0;
	fx->center_x = 0.5f;
	fx->center_y = 0.5f;
}

void	water_trigger_ripple(t_app *app, float cx, float cy)
{
	t_water	*fx;

	fx = &app->water;
	fx->ripple_active = 1;
	fx->ripple_start = mlx_get_time();
	fx->center_x = cx;
	fx->center_y = cy;
}

void	water_update(t_app *app, double now)
{
	t_water	*fx;

	fx = &app->water;
	if (fx->ripple_active == 0)
		return ;
	if (now - fx->ripple_start > 3.0)
		fx->ripple_active = 0;
}

void	water_apply_shimmer(t_vec3 *dir, double now, float s)
{
	float	w;

	w = sinf(dir->x * 5.0f + now * 0.8f)
		* cosf(dir->y * 3.0f + now * 0.6f) * s;
	dir->x += w;
	dir->y += w * 0.5f;
}

void	water_apply_ripple(
		t_vec3 *dir, t_water *fx, double now,
		float uv_x, float uv_y)
{
	float	dx;
	float	dy;
	float	dist;
	float	t;
	float	phase;
	float	wave;
	float	off;

	if (fx->ripple_active == 0)
		return ;
	dx = uv_x - fx->center_x;
	dy = uv_y - fx->center_y;
	dist = sqrtf(dx * dx + dy * dy);
	t = now - fx->ripple_start;
	phase = dist * fx->ripple_freq - t * fx->ripple_speed;
	wave = sinf(phase);
	off = wave * expf(-dist * fx->ripple_fade) * fx->ripple_intensity;
	dir->x += dx * off;
	dir->y += dy * off;
}
