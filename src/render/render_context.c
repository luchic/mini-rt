
#include "ft_minirt.h"
#include <math.h>

void	set_render_context(t_app *app)
{
	app->render_ctx.aspect = (float)app->width / (float)app->height;
	app->render_ctx.fov_rad = app->scene.camera.fov_deg * PI_F / 180.0f;
	app->render_ctx.scale = tanf(app->render_ctx.fov_rad * 0.5f);
}