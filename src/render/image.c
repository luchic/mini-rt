#include "rt.h"

static unsigned char u8_clamp(float x)
{
	if (x < 0.0f) x = 0.0f;
	if (x > 1.0f) x = 1.0f;
	return (unsigned char)(x * 255.0f + 0.5f);
}

static uint32_t pack_rgba(t_rgb color)
{
	unsigned char r = u8_clamp(color.r);
	unsigned char g = u8_clamp(color.g);
	unsigned char b = u8_clamp(color.b);
	unsigned char a = 255;
	return ((uint32_t)r << 24) | ((uint32_t)g << 16)
	     | ((uint32_t)b << 8)  | (uint32_t)a;
}

void    image_create(t_app *app, int w, int h)
{
	app->img.img = mlx_new_image(app->mlx, w, h);
	if (!app->img.img)
		die("mlx_new_image failed");
	app->img.w = w;
	app->img.h = h;
	if (mlx_image_to_window(app->mlx, app->img.img, 0, 0) < 0)
		die("mlx_image_to_window failed");
}

void    image_destroy(t_app *app)
{
	if (app->img.img)
	{
		mlx_delete_image(app->mlx, app->img.img);
		app->img.img = NULL;
	}
}

void    image_put_px(t_img *img, int x, int y, t_rgb color)
{
	uint32_t    *pixels;
	size_t       pixel_index;

	if (x < 0 || y < 0) return ;
	if (x >= img->w || y >= img->h) return ;
	pixels = (uint32_t *)img->img->pixels;
	pixel_index = (size_t)y * (size_t)img->img->width + (size_t)x;
	pixels[pixel_index] = pack_rgba(color);
}
