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
void	anim_init(t_app *app);
void	cam_anim_update(t_app *app, double now);

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

t_vec3	vec3_project_on_axis(t_vec3 v, t_vec3 axis);
t_vec3	vec3_reject_from_axis(t_vec3 v, t_vec3 axis);
t_vec3	vec_scale(t_vec3 v, float k);

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
int		parse_spotlight(char **tokens, t_scene *scene);

// ======================= anim ===========================
void	shfx_trigger(t_app *a);
void	shfx_update(t_app *a, double now);
void	rng_seed(t_app *app, unsigned int seed_value);
float	rng_random01(t_app *app);
void	update_lamp_sun(t_app *app);
void	lamp_toggle(t_app *app);
t_obj	*find_first(t_scene *sc, t_objtype type);
void	cam_anim_update(t_app *app, double now);
t_plane	*find_ground(t_scene *sc);
void	phys_step(t_physics *b, float dt, t_shfx *st);
void	spawn_shards(t_app *app, t_scene *sc, t_shfx *st, t_sphere *big);
t_shfx	*fx(void);
int		impact_happened(t_sphere *big, t_plane *pl);



// ====================== render =======================
int		hit_sphere(t_sphere *sp, t_ray ray_in, t_ray *hit_out);
int		hit_plane(t_plane *pl, t_ray ray_in, float tmax, t_ray *ray_hit);
int		hit_cylinder(t_cylinder *cy, t_ray ray, float tmax, t_ray *rec);
int		hit_cone(t_cone *co, t_ray ray, float tmax, t_ray *rec);
void	render(t_app *a);
int		trace_ray(t_scene *sc, t_ray r, t_rgb *out_color);
int		in_shadow(t_scene *sc, t_vec3 p, t_vec3 ldir, float ldist);
t_rgb	shade(t_scene *sc, t_ray hit_view, t_vec3 normal, t_material *mat);
void	image_put_px(t_img *img, int x, int y, t_rgb color);

void	set_render_context(t_app *app);
void	image_destroy(t_app *app);


// ====================== rgb utils =========================
t_rgb	rgb_add(t_rgb a, t_rgb b);
t_rgb	rgb_mul(t_rgb a, float k);
t_rgb	rgb_mod(t_rgb a, t_rgb b);
t_rgb	rgb_clamp01(t_rgb c);

t_rgb	accum_lights(t_scene *sc, t_ray hv, t_vec3 n);

t_rgb	checker_bonus(t_vec3 p, t_rgb base);
t_vec3	bump_bonus(t_vec3 n, t_vec3 p, t_material *m);
t_rgb	specular_bonus(t_vec3 n, t_vec3 l, t_vec3 v, t_material *m);
int		in_shadow(t_scene *sc, t_vec3 p, t_vec3 to_l, float max_d);
t_vec3	apply_normal_map(t_objtype type, t_vec3 local_p, t_vec3 n, t_material *m);

t_vec3	vproj_on_n(t_vec3 v, t_vec3 n);
float	plane_signed_dist(t_vec3 p, t_plane *pl);

void mouse_look_callback(double xpos, double ypos, void *param);

#endif