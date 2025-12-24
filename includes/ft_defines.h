/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_defines.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 14:03:27 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 14:28:52 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFINES_H
# define FT_DEFINES_H

# include "MLX42.h"

# define WIN_W 800
# define WIN_H 600
# define EPS 1e-4
# define TMAX 1e9
# define PI_F 3.14159265358979323846f


typedef enum e_objtype
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE
}						t_objtype;

typedef struct s_render_context
{
	float	aspect;
	float	fov_rad;
	float	scale;
}			t_render_context;

typedef struct s_vec3
{
	float				x;
	float				y;
	float				z;
}						t_vec3;

typedef struct s_rgb
{
	float				red;
	float				green;
	float				blue;
}						t_rgb;

typedef struct s_material
{
	t_rgb				color;
	int					checker;
	float				specular;
	float				sp_exp;
	int					bump;
	int					has_normal_map;
	mlx_texture_t		*normal_tex;
}						t_material;

typedef struct s_ray
{
	t_vec3				origin;
	t_vec3				direction;
	float				t;
	t_vec3				normal;
	t_material			material;
	t_objtype			type;
	t_vec3				local_p;
}						t_ray;

typedef struct s_img
{
	mlx_image_t			*img;
	int					width;
	int					height;
}						t_img;

typedef enum e_lighttype
{
	LIGHT_POINT,
	LIGHT_SPOT
}						t_lighttype;

typedef struct s_camera
{
	t_vec3				pos;
	t_vec3				direction;
	float				fov_deg;
	t_vec3				right;
	t_vec3				up;
	float				yaw;
	float				pitch;
	float				move_speed;
	float				mouse_sens;

}						t_camera;

typedef struct s_light
{
	t_lighttype			type;
	t_vec3				pos;
	t_vec3				dir;
	t_rgb				color;
	float				br;
	float				cutoff_cos;
	struct s_light		*next;
}						t_light;

typedef struct s_sphere
{
	t_vec3				center;
	float				radius;
	t_material			material;
}						t_sphere;

typedef struct s_plane
{
	t_vec3				position;
	t_vec3				normal;
	t_material			material;
}						t_plane;

typedef struct s_cylinder
{
	t_vec3				center;
	t_vec3				axis;
	float				radius;
	float				height;
	t_material			material;
}						t_cylinder;

typedef struct s_cone
{
	t_vec3				center;
	t_vec3				axis;
	float				angle;
	float				height;
	t_material			material;
}						t_cone;

typedef struct s_obj
{
	t_objtype			type;
	void				*ptr;
	struct s_obj		*next;
}						t_obj;

typedef struct s_scene
{
	int					has_a;
	int					has_c;
	int					has_l;
	float				amb;
	t_rgb				amb_color;
	t_camera			camera;
	t_light				*lights;
	t_obj				*objs;
}						t_scene;

typedef struct s_animation
{
	int					enabled;
	float				speed;
	float				radius;
}						t_animation;

typedef struct s_app
{
	mlx_t				*mlx;
	int32_t				width;
	int32_t				height;
	t_img				img;
	t_scene				scene;
	t_animation			animation;
	t_render_context	render_ctx;
	int					needs_redraw;
	int					lamp_enabled;
	double				last_ts;
	unsigned int		rng_seed;
	double				mouse_last_x;
	double				mouse_last_y;
	int					mouse_first;
	int					mouse_look_enabled;
}						t_app;

typedef struct s_physics
{
	t_vec3				pos;
	t_vec3				vel;
	float				radius;
	int					active;
	void				*obj_ptr;
}						t_physics;

typedef struct s_shfx
{
	int					enabled;
	int					phase;
	int					count;
	float				g;
	float				bounce;
	float				fric;
	t_obj				*big_obj;
	t_plane				*ground;
	t_physics			shards[128];
}						t_shfx;

typedef struct s_hit_context
{
	t_vec3		axis;
	t_vec3		oc;
	t_vec3		rdp;
	t_vec3		ocp;
	t_vec3		cap_center;
	float		dv;
	float		ov;
	float		k;
	float		tmax;
	t_cylinder	*cylinder;
}	t_hit_context;

typedef struct s_light_once_ctx
{
	float	dist;
	float	spot;
	double	nd;
	t_rgb	lc;
	t_rgb	sum;
	t_vec3	dir;
}	t_light_once_ctx;

typedef struct s_cap_ctx
{
	t_vec3	axis;
	t_vec3	center;
	float	radius;
	float	*tmax;
}t_cap_ctx;


#endif