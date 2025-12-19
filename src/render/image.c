#include "ft_minirt.h"

static unsigned char	u8_clamp(float x)
{
	if (x < 0.0f)
		x = 0.0f;
	if (x > 1.0f)
		x = 1.0f;
	return ((unsigned char)(x * 255.0f + 0.5f));
}

static uint32_t	pack_rgba(t_rgb color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = u8_clamp(color.red);
	g = u8_clamp(color.green);
	b = u8_clamp(color.blue);
	return ((0xFFu << 24) | (uint32_t)b << 16
		| ((uint32_t)g << 8) | ((uint32_t)r));
}

void	image_create(t_app *app, int w, int h)
{
	app->img.img = mlx_new_image(app->mlx, w, h);
	if (!app->img.img)
		ft_exit("mlx_new_image failed", 1);
	app->img.width = w;
	app->img.height = h;
	if (mlx_image_to_window(app->mlx, app->img.img, 0, 0) < 0)
		ft_exit("mlx_image_to_window failed", 1);
}

void	image_destroy(t_app *app)
{
	if (app->img.img)
	{
		mlx_delete_image(app->mlx, app->img.img);
		app->img.img = NULL;
	}
}

void	image_put_px(t_img *img, int x, int y, t_rgb color)
{
	uint32_t	*pixels;
	size_t		pixel_index;

	if (x < 0 || y < 0)
		return ;
	if (x >= img->width || y >= img->height)
		return ;
	pixels = (uint32_t *)img->img->pixels;
	pixel_index = (size_t)y * (size_t)img->img->width + (size_t)x;
	pixels[pixel_index] = pack_rgba(color);
}
