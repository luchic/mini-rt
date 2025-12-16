#include "ft_minirt.h"
#include <math.h>
#include <stdlib.h>

static void uv_sphere(const t_vec3 p, float *u, float *v)
{
    float theta = atan2f(p.z, p.x);
    float phi = acosf(fmaxf(-1.0f, fminf(1.0f, p.y)));
    *u = (theta + PI_F) / (2.0f * PI_F);
    *v = phi / PI_F;
}

static void uv_plane(const t_vec3 p, float *u, float *v)
{
    *u = p.x - floorf(p.x);
    *v = p.z - floorf(p.z);
}

static t_vec3 sample_normal_tex(mlx_texture_t *tex, float u, float v)
{
    if (!tex || tex->width == 0 || tex->height == 0)
        return (vec3(0.0f, 0.0f, 1.0f));
    uint32_t x = (uint32_t)fmodf(fmaxf(0.0f, u) * tex->width, tex->width);
    uint32_t y = (uint32_t)fmodf(fmaxf(0.0f, v) * tex->height, tex->height);
    size_t idx = (y * tex->width + x) * 4;
    unsigned char r = tex->pixels[idx + 0];
    unsigned char g = tex->pixels[idx + 1];
    unsigned char b = tex->pixels[idx + 2];
    t_vec3 n;
    n.x = (r / 255.0f) * 2.0f - 1.0f;
    n.y = (g / 255.0f) * 2.0f - 1.0f;
    n.z = (b / 255.0f) * 2.0f - 1.0f;
    return vnorm(n);
}

/* Apply normal map to sphere and plane via object-local UV */
t_vec3 apply_normal_map(t_objtype type, t_vec3 local_p, t_vec3 n, t_material *m)
{
    float u, v;
    t_vec3 t, b, tn;

    if (!m || !m->has_normal_map || !m->normal_tex)
        return n;
    if (type == OBJ_SPHERE)
        uv_sphere(local_p, &u, &v);
    else if (type == OBJ_PLANE)
        uv_plane(local_p, &u, &v);
    else
        return n;
    tn = sample_normal_tex(m->normal_tex, u, v);
    /* Build tangent basis: choose any tangent orthogonal to n */
    t = vnorm(vcross_product(vec3(0.0f, 1.0f, 0.0f), n));
    if (dot_product(t, t) < EPS)
        t = vnorm(vcross_product(vec3(1.0f, 0.0f, 0.0f), n));
    b = vcross_product(n, t);
    /* Transform tangent-space normal to world */
    return vnorm(vadd(vadd(vmul(t, tn.x), vmul(b, tn.y)), vmul(n, tn.z)));
}
