#include "ft_minirt.h"
#include <math.h>

/* ============================================================
** Linear interpolation untuk warna (0–1)
** ============================================================ */
static t_vec3	vec3_lerp(t_vec3 a, t_vec3 b, float t)
{
	t_vec3	out;

	out.x = a.x + (b.x - a.x) * t;
	out.y = a.y + (b.y - a.y) * t;
	out.z = a.z + (b.z - a.z) * t;
	return (out);
}

/* ============================================================
** Rotasi vektor terhadap sumbu Y — penting untuk gerak matahari.
** ============================================================ */
static t_vec3	rot_y(t_vec3 v, float ang)
{
	t_vec3	r;
	float	c;
	float	s;

	c = cosf(ang);
	s = sinf(ang);
	r.x = c * v.x + s * v.z;
	r.y = v.y;
	r.z = -s * v.x + c * v.z;
	return (r);
}

/* ============================================================
** Warna dinamis matahari (sunrise → noon → sunset)
** ============================================================ */
static t_vec3	get_sun_color(float k)
{
	t_vec3 morning = vec3(1.0f, 0.65f, 0.35f);  // warm orange
	t_vec3 noon    = vec3(1.0f, 1.0f, 1.0f);    // white
	t_vec3 evening = vec3(1.0f, 0.45f, 0.25f);  // reddish sunset

	if (k < 0.5f)
		return vec3_lerp(morning, noon, k * 2.0f);
	return vec3_lerp(noon, evening, (k - 0.5f) * 2.0f);
}

/* ============================================================
** SUN MOVEMENT — ANIMASI UTAMA
** ============================================================ */
void	update_lamp_sun(t_app *app)
{
	double	time_now;
	float	t;
	float	angle;
	float	k;
	t_light	*sun;

	/* Ambil light#0 sebagai matahari */
	sun = &app->scene.light[0];

	/* waktu global dari MLX */
	time_now = mlx_get_time();

	/* kecepatan animasi; tweak kalau perlu */
	t = (float)(time_now * 0.3f);

	/* angle rotasi matahari pada langit */
	angle = t;

	/* base direction matahari saat sunrise → timur (+X) */
	t_vec3 base_dir = vec3(1.0f, 0.35f, 0.0f);

	/* rotasi untuk pergerakan timur → barat */
	sun->dir = rot_y(base_dir, angle);
	sun->dir = vec3_norm(sun->dir);

	/* kurva intensitas → sunrise → noon → sunset */
	k = sinf(t);
	if (k < 0.0f)
		k = 0.0f;

	/* intensitas minimal + dynamic intensity */
	sun->intensity = 0.2f + k * 0.8f;

	/* warna matahari berubah */
	sun->color = get_sun_color(k);
}
