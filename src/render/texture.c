#include "ft_minirt.h"
#include <math.h>
#include <stdlib.h>

static void	uv_sphere(const t_vec3 p, float *u, float *v)
{
	float	theta;
	float	phi;

	theta = atan2f(p.z, p.x);
	phi = acosf(fmaxf(-1.0f, fminf(1.0f, p.y)));
	*u = (theta + PI_F) / (2.0f * PI_F);
	*v = phi / PI_F;
}

static t_vec3	pack_norm_vector(size_t idx, mlx_texture_t *tex)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	t_vec3			n;

	r = tex->pixels[idx + 0];
	g = tex->pixels[idx + 1];
	b = tex->pixels[idx + 2];
	n.x = (r / 255.0f) * 2.0f - 1.0f;
	n.y = (g / 255.0f) * 2.0f - 1.0f;
	n.z = (b / 255.0f) * 2.0f - 1.0f;
	return (vnorm(n));
}

static t_vec3	sample_normal_tex(mlx_texture_t *tex, float u, float v)
{
	uint32_t	x;
	uint32_t	y;
	size_t		idx;

	if (!tex || tex->width == 0 || tex->height == 0)
		return (vec3(0.0f, 0.0f, 1.0f));
	x = (uint32_t)fmodf(fmaxf(0.0f, u) * tex->width, tex->width);
	y = (uint32_t)fmodf(fmaxf(0.0f, v) * tex->height, tex->height);
	idx = (y * tex->width + x) * 4;
	return (pack_norm_vector(idx, tex));
}

static t_vec3	apply_tbn(t_vec3 tn, t_vec3 n)
{
	t_vec3	b;
	t_vec3	t;

	t = vnorm(vcross_product(vec3(0.0f, 1.0f, 0.0f), n));
	if (dot_product(t, t) < EPS)
		t = vnorm(vcross_product(vec3(1.0f, 0.0f, 0.0f), n));
	b = vcross_product(n, t);
	return (vnorm(vadd(vadd(vmul(t, tn.x), vmul(b, tn.y)), vmul(n, tn.z))));
}

t_vec3	apply_normal_map(
	t_objtype type,
	t_vec3 local_p,
	t_vec3 n,
	t_material *m)
{
	float	u;
	float	v;
	t_vec3	tn;

	if (!m || !m->has_normal_map || !m->normal_tex)
		return (n);
	if (type == OBJ_SPHERE)
		uv_sphere(local_p, &u, &v);
	else if (type == OBJ_PLANE)
	{
		u = local_p.x - floorf(local_p.x);
		v = local_p.z - floorf(local_p.z);
	}
	else
		return (n);
	tn = sample_normal_tex(m->normal_tex, u, v);
	return (apply_tbn(tn, n));
}
