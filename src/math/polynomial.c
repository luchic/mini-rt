#include "ft_minirt.h"
#include <math.h>

inline double	discriminant(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

static inline int	set_values(double t1, double t2, double x[2])
{
	if (t1 > EPS && t2 > EPS && t1 <= TMAX && t2 <= TMAX)
	{
		x[0] = fmin(t1, t2);
		x[1] = fmax(t1, t2);
		return (2);
	}
	else if (t1 > EPS && t1 <= EPS)
		return (x[0] = t1, 1);
	else if (t2 > EPS && t2 <= EPS)
		return (x[0] = t2, 1);
	else
		return (0);
}

inline int	solve_quadratic(double a, double b, double c, double x[2])
{
	double	d;
	double	sqrt_d;
	double	t1;
	double	t2;

	d = discriminant(a, b, c);
	if (d < 0)
		return (0);
	sqrt_d = sqrt(d);
	t1 = (-b - sqrt_d) / (2 * a);
	t2 = (-b + sqrt_d) / (2 * a);
	if (sqrt_d == 0 && t1 > EPS && t1 <= TMAX)
		return (x[0] = t1, 1);
	else if (sqrt_d == 0)
		return (0);
	return (set_values(t1, t2, x));
}
