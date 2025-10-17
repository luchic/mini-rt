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
double dot_product(t_vec3 origin, t_vec3 direction);
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
#endif