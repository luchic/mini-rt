#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include "ft_defines.h"
# include "ft_printf.h"
# include "libft.h"
# include <math.h>

// ====================== utils =======================
int		has_rt_extension(const char *file_name);
void	ft_exit(char *msg, int code);
void	*emalloc(size_t size);

int		ft_atoi_checker(const char *str);
int		ft_atof_checker(const char *str);
void	set_status(int *status, int value);
int		ft_atoi_with_checker(const char *str, int *status);
double	ft_atof_with_checker(const char *str, int *status);

void	free_split(char **split);

// ====================== init =======================
void	init_app(t_app *app, const char *scene);
void	camera_build(t_camera *camera);
void	setup_hooks(t_app *app);
void	init_camera_animation(t_app *app);

// ====================== math =======================
t_vec3	vec3(float x, float y, float z);
float	vlen(t_vec3 a);
t_vec3	vnorm(t_vec3 a);
t_ray	ray(t_vec3 origin, t_vec3 direction);
t_vec3	vclamp01(t_vec3 c);

t_vec3	vdivv(t_vec3 a, float k);
double	dot_product(t_vec3 origin, t_vec3 direction);
t_vec3	vcross_product(t_vec3 a, t_vec3 b);

t_vec3	vadd(t_vec3 a, t_vec3 b);
t_vec3	vsub(t_vec3 a, t_vec3 b);
t_vec3	vmul(t_vec3 a, float k);

/**
 * @brief Solve a quadratic equation.
 * @param a Coefficient of x^2.
 * @param b Coefficient of x.
 * @param c Constant term.
 * @param x Array of two elements to store the roots.
 * @return int Number of roots found (0, 1, or 2).
 */
int		solve_quadratic(double a, double b, double c, double x[2]);

/**
 * @brief Calculate the discriminant of a quadratic equation.
 * @param a Coefficient of x^2.
 * @param b Coefficient of x.
 * @param c Constant term.
 * @return double The discriminant value.
 */
double	discriminant(double a, double b, double c);

// ====================== parseer =======================
int		parse_file(const char *path, t_scene *sc);
int		parse_file_line(char *line, t_scene *scene);
int		parse_ambient_light(char **tokens, t_scene *scene);
int		parse_camera(char **tokens, t_scene *scene);
int		parse_light(char **tokens, t_scene *scene, int bonus_multi);
int		parse_sphere(char **tokens, t_scene *scene);
int		parse_plane(char **tokens, t_scene *scene);
int		parse_cylinder(char **tokens, t_scene *scene);
void	scene_add_obj(t_scene *scene, t_obj *node);
t_obj	*new_obj(int type, void *ptr);
int		parse_float(const char *str, float *out, float minv, float maxv);
int		parse_color(const char *s, t_rgb *color);
int		parse_v3(const char *s, t_vec3 *v);
int		parse_norm_v3(const char *s, t_vec3 *v);
int		parse_cone_bonus(char **tokens, t_scene *scene);
#endif