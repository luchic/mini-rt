#include "rt.h"

static int	hit_any(t_scene *sc, t_ray ray_in, float tmax)
{
	t_obj *node = sc->objs;
	float t_candidate; t_v3 n_tmp; t_mat m_tmp;

	while (node)
	{
		if (node->type == OBJ_SPHERE && hit_sphere((t_sphere*)node->ptr, ray_in, tmax, &t_candidate, &n_tmp, &m_tmp)) return (1);
		if (node->type == OBJ_PLANE  && hit_plane((t_plane*)node->ptr,  ray_in, tmax, &t_candidate, &n_tmp, &m_tmp)) return (1);
		if (node->type == OBJ_CYL    && hit_cylinder((t_cyl*)node->ptr, ray_in, tmax, &t_candidate, &n_tmp, &m_tmp)) return (1);
		if (node->type == OBJ_CONE   && hit_cone((t_cone*)node->ptr,   ray_in, tmax, &t_candidate, &n_tmp, &m_tmp)) return (1);
		node = node->next;
	}
	return (0);
}

int	in_shadow(t_scene *sc, t_v3 point, t_v3 light_dir, float light_dist)
{
	t_ray shadow_ray = ray(vadd(point, vmul(light_dir, EPS * 8.0f)), light_dir);
	return (hit_any(sc, shadow_ray, light_dist - EPS));
}
