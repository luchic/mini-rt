#include "ft_minirt.h"
#include "tetris.h"

static void	image_create(t_app *app, int width, int height)
{
	app->img.img = mlx_new_image(app->mlx, width, height);
	if (!app->img.img)
	{
		mlx_terminate(app->mlx);
		ft_exit("mlx_new_image failed", 1);
	}
	app->img.width = width;
	app->img.height = height;
	if (mlx_image_to_window(app->mlx, app->img.img, 0, 0) < 0)
	{
		mlx_delete_image(app->mlx, app->img.img);
		mlx_terminate(app->mlx);
		ft_exit("mlx_image_to_window failed", 1);
	}
}

static void	init_window(t_app *app)
{
	app->width = WIN_W;
	app->height = WIN_H;
	app->mlx = mlx_init(app->width, app->height, "miniRT", false);
	if (!app->mlx)
		ft_exit("mlx_init failed", 1);
	image_create(app, app->width, app->height);
}

void	init_tetris(t_app *app, const char *scene)
{
	app->tetris_enabled = (ft_strstr(scene, "tetris") != NULL);
	app->tetris = NULL;
	if (app->tetris_enabled)
		tetris_simple_start(app);
	app->needs_redraw = 1;
	app->last_ts = mlx_get_time();
}

void	init_app(t_app *app, const char *scene)
{
	if (!has_rt_extension(scene))
		ft_exit("Usage: ./miniRT <scene.rt>", 1);
	ft_bzero(app, sizeof(t_app));
	if (!parse_file(scene, &app->scene))
		ft_exit("parse failed", 1);
	camera_build(&app->scene.camera);
	init_tetris(app, scene);
	init_camera_animation(app);
	init_window(app);
}
