#ifndef UNDER_WATER_H
# define UNDER_WATER_H

# include "ft_minirt.h"

typedef struct s_water {
	int		enabled;
	float	shimmer_strength;
	float	ripple_intensity;
	float	ripple_freq;
	float	ripple_speed;
	float	ripple_fade;
	double	ripple_start;
	int		ripple_active;
	float	center_x;
	float	center_y;
}	t_water;

void	water_init(t_app *app);
void	water_trigger_ripple(t_app *app, float cx, float cy);
void	water_update(t_app *app, double now);
void	water_apply_shimmer(t_vec3 *dir, double now, float strength);
void	water_apply_ripple(t_vec3 *dir, t_water *fx, double now,
			float uv_x, float uv_y);

#endif
