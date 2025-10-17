#ifndef FT_DEFINES_H
# define FT_DEFINES_H

# include "MLX42.h"

# define WIN_W 800
# define WIN_H 600
# define EPS 1e-4
# define TMAX 1e9
# define PI_F 3.14159265358979323846f

typedef struct s_tetris	t_tetris;

typedef enum e_objtype
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYL,
	OBJ_CONE
}						t_objtype;

typedef struct s_v3
{
	float				x;
	float				y;
	float				z;
}						t_vec3;

typedef struct s_ray
{
	t_vec3				o;
	t_vec3				d;
}						t_ray;

typedef struct s_rgb
{
	float				red;
	float				g;
	float				b;
}						t_rgb;

typedef struct s_img
{
	mlx_image_t			*img;
	int					width;
	int					height;
}						t_img;

typedef struct s_camera
{
	t_vec3				pos;
	t_vec3				direction;
	float				fov_deg;
	t_vec3				right;
	t_vec3				up;
}						t_camera;

typedef struct s_light
{
	t_vec3				pos;
	t_rgb				color;
	float				br;
	struct s_light		*next;
}						t_light;

typedef struct s_material
{
	t_rgb				color;
	int					checker;
	float				specular;
	float				sp_exp;
	int					bump;
}						t_material;

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
	int					needs_redraw;
	double				last_ts;
	int					tetris_enabled;
	t_tetris			*tetris;
}						t_app;

typedef struct s_physics
{
	t_vec3				pos;
	t_vec3				vel;
	float				radius;
	int					active;
	void				*obj_ptr;
}						t_phys;

typedef struct s_shfx
{
	int					enabled;
	int phase;       /* 0=falling, 1=shattered */
	int count;       /* shard aktif */
	float g;         /* gravitasi */
	float bounce;    /* koef. restitusi */
	float fric;      /* friksi lantai */
	t_obj *big_obj;  /* node objek besar */
	t_plane *ground; /* lantai (optional) */
	s_physics			shards[128];
}						t_shfx;

#endif