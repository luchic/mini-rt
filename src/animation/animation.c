#include "ft_minirt.h"

static t_vec3 rot_y(t_vec3 v, float ang)
{
	float c;
	float s;
	t_vec3  r;

	c = cosf(ang);
	s = sinf(ang);
	r.x =  c * v.x + s * v.z;
	r.y =  v.y;
	r.z = -s * v.x + c * v.z;
	return (r);
}

void	anim_init(t_app *a)
{
	a->animation.enabled = 1;
	a->animation.speed = 0.6f;
	a->animation.radius = 4.0f;
	a->last_ts = mlx_get_time();
}

static void orbit_camera(t_app *a, double t)
{
	float	ang;
	t_vec3	look;
	t_vec3	pos;

	ang = (float)(t * a->animation.speed);
	look = vec3(0.0f, 0.0f, 0.0f);
	pos = vec3(a->animation.radius, 1.5f, 0.0f);
	pos = rot_y(pos, ang);
	a->scene.camera.pos = pos;
	a->scene.camera.direction = vnorm(vsub(look, pos));
	camera_build(&a->scene.camera);
}

static void spin_objects(t_scene *sc, double t)
{
	t_obj	*o;
	float	ang;

	o = sc->objs;
	ang = (float)(0.4f * t);
	while (o)
	{
		if (o->type == OBJ_PLANE)
			((t_plane*)o->ptr)->normal = rot_y(((t_plane*)o->ptr)->normal, ang);
		if (o->type == OBJ_CYLINDER)
			((t_cylinder*)o->ptr)->axis = rot_y(((t_cylinder*)o->ptr)->axis, ang);
		o = o->next;
	}
}

void	anim_update(t_app *a, double now)
{
	double dt;
	double t;

	if (!a->animation.enabled)
		return ;
	dt = now - a->last_ts;
	if (dt < (1.0 / 60.0))
		return ;
	a->last_ts = now;
	t = now;
	orbit_camera(a, t);
	spin_objects(&a->scene, t);
	a->needs_redraw = 1;
}