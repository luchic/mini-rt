#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include "ft_defines.h"


// ====================== utils =======================
int		has_rt_extension(const char *file_name);
void	ft_exit(char *msg, int code);

// ====================== init =======================
void	init_app(t_app *app, const char *scene);


// ====================== math =======================
t_vec3	vec3(float x, float y, float z);
float	vlen(t_vec3 a);
t_vec3	vnorm(t_vec3 a);
t_ray	ray(t_vec3 o, t_vec3 d);
t_vec3	vclamp01(t_vec3 c);

t_vec3	vdivv(t_vec3 a, float k);
float	vdot(t_vec3 a, t_vec3 b);
t_vec3	vcross(t_vec3 a, t_vec3 b);

t_vec3	vadd(t_vec3 a, t_vec3 b);
t_vec3	vsub(t_vec3 a, t_vec3 b);
t_vec3	vmul(t_vec3 a, float k);
#endif