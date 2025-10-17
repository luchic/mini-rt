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
	float				r;
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

typedef struct s_mat
{
	t_rgb				color;
	int					checker;
	float				specular;
	float				sp_exp;
	int					bump;
}						t_mat;

typedef struct s_sphere
{
	t_vec3				c;
	float				r;
	t_mat				m;
}						t_sphere;
typedef struct s_plane
{
	t_vec3				p;
	t_vec3				n;
	t_mat				m;
}						t_plane;
typedef struct s_cyl
{
	t_vec3				c;
	t_vec3				a;
	float				r;
	float				h;
	t_mat				m;
}						t_cyl;
typedef struct s_cone
{
	t_vec3				c;
	t_vec3				a;
	float				ang;
	float				h;
	t_mat				m;
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

typedef struct s_phys
{
	t_vec3				pos;
	t_vec3				vel;
	float				r;
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
	t_phys				shards[128];
}						t_shfx;

#endif