
#include "ft_minirt.h"
#include <string.h>

// void	print_vec3(t_vec3 v, const char *name)
// {
//     ft_printf("%s: (%.2f, %.2f, %.2f)\n", name, v.x, v.y, v.z);
// }

// void	print_rgb(t_rgb color, const char *name)
// {
//     ft_printf("%s: (%.2f, %.2f, %.2f)\n", name, color.red, color.green, color.blue);
// }

// void	print_material(t_material *mat)
// {
//     ft_printf("    Material:\n");
//     print_rgb(mat->color, "      Color");
//     ft_printf("      Specular: %.2f\n", mat->specular);
//     ft_printf("      Specular exp: %.2f\n", mat->sp_exp);
//     ft_printf("      Checker: %s\n", mat->checker ? "Yes" : "No");
//     ft_printf("      Bump: %s\n", mat->bump ? "Yes" : "No");
// }

// void	print_objects(t_obj *obj)
// {
//     int	count = 0;
    
//     ft_printf("\n=== OBJECTS ===\n");
//     while (obj)
//     {
//         count++;
//         ft_printf("Object %d:\n", count);
        
//         if (obj->type == OBJ_SPHERE)
//         {
//             t_sphere *sphere = (t_sphere *)obj->ptr;
//             ft_printf("  Type: SPHERE\n");
//             print_vec3(sphere->center, "  Center");
//             ft_printf("  Radius: %.2f\n", sphere->radius);
//             print_material(&sphere->material);
//         }
//         else if (obj->type == OBJ_PLANE)
//         {
//             t_plane *plane = (t_plane *)obj->ptr;
//             ft_printf("  Type: PLANE\n");
//             print_vec3(plane->position, "  Position");
//             print_vec3(plane->normal, "  Normal");
//             print_material(&plane->material);
//         }
//         else if (obj->type == OBJ_CYLINDER)
//         {
//             t_cylinder *cyl = (t_cylinder *)obj->ptr;
//             ft_printf("  Type: CYLINDER\n");
//             print_vec3(cyl->center, "  Center");
//             print_vec3(cyl->axis, "  Axis");
//             ft_printf("  Radius: %.2f\n", cyl->radius);
//             ft_printf("  Height: %.2f\n", cyl->height);
//             print_material(&cyl->material);
//         }
//         else if (obj->type == OBJ_CONE)
//         {
//             t_cone *cone = (t_cone *)obj->ptr;
//             ft_printf("  Type: CONE\n");
//             print_vec3(cone->center, "  Center");
//             print_vec3(cone->axis, "  Axis");
//             ft_printf("  Angle: %.2f\n", cone->angle);
//             ft_printf("  Height: %.2f\n", cone->height);
//             print_material(&cone->material);
//         }
//         else
//         {
//             ft_printf("  Type: UNKNOWN (%d)\n", obj->type);
//         }
        
//         ft_printf("\n");
//         obj = obj->next;
//     }
//     ft_printf("Total objects: %d\n", count);
// }

// void	print_lights(t_light *light)
// {
//     int count = 0;
    
//     ft_printf("\n=== LIGHTS ===\n");
//     while (light)
//     {
//         count++;
//         ft_printf("Light %d:\n", count);
//         print_vec3(light->pos, "  Position");
//         ft_printf("  Brightness: %.2f\n", light->br);
//         print_rgb(light->color, "  Color");
//         ft_printf("\n");
//         light = light->next;
//     }
//     ft_printf("Total lights: %d\n", count);
// }

// void	print_app(t_app *app)
// {
//     ft_printf("===============================\n");
//     ft_printf("       MINI-RT APP INFO        \n");
//     ft_printf("===============================\n");
    
//     // App basic info
//     ft_printf("Window dimensions: %dx%d\n", app->width, app->height);
//     ft_printf("MLX pointer: %p\n", app->mlx);
//     ft_printf("Image pointer: %p\n", app->img.img);
//     ft_printf("Image dimensions: %dx%d\n", app->img.width, app->img.height);
    
//     // Scene validation flags
//     ft_printf("\n=== SCENE VALIDATION ===\n");
//     ft_printf("Has Ambient: %s\n", app->scene.has_a ? "Yes" : "No");
//     ft_printf("Has Camera: %s\n", app->scene.has_c ? "Yes" : "No");
//     ft_printf("Has Light: %s\n", app->scene.has_l ? "Yes" : "No");
    
//     // Scene info
//     ft_printf("\n=== AMBIENT LIGHT ===\n");
//     ft_printf("Ambient ratio: %.2f\n", app->scene.amb);
//     print_rgb(app->scene.amb_color, "Ambient color");
    
//     // Camera info
//     ft_printf("\n=== CAMERA ===\n");
//     print_vec3(app->scene.camera.pos, "Position");
//     print_vec3(app->scene.camera.direction, "Direction");
//     ft_printf("FOV: %.2f degrees\n", app->scene.camera.fov_deg);
//     print_vec3(app->scene.camera.right, "Right vector");
//     print_vec3(app->scene.camera.up, "Up vector");
    
//     // Animation info
//     ft_printf("\n=== ANIMATION ===\n");
//     ft_printf("Enabled: %s\n", app->animation.enabled ? "Yes" : "No");
//     ft_printf("Speed: %.2f\n", app->animation.speed);
//     ft_printf("Radius: %.2f\n", app->animation.radius);
    
//     // Other app flags
//     ft_printf("\n=== APP FLAGS ===\n");
//     ft_printf("Needs redraw: %s\n", app->needs_redraw ? "Yes" : "No");
//     ft_printf("Tetris enabled: %s\n", app->tetris_enabled ? "Yes" : "No");
//     ft_printf("Last timestamp: %.2f\n", app->last_ts);
    
//     // Lights info (multiple lights possible)
//     print_lights(app->scene.lights);
    
//     // Objects info
//     print_objects(app->scene.objs);
    
//     ft_printf("===============================\n");
// }


// void			shfx_trigger(t_app *app);
// void			shfx_update(t_app *app, double now);

// static t_obj	*find_first(t_scene *sc, t_objtype ty)
// {
// 	t_obj	*o;

// 	o = sc ? sc->objs : 0;
// 	while (o)
// 	{
// 		if (o->type == ty)
// 			return (o);
// 		o = o->next;
// 	}
// 	return (0);
// }

#include <stdio.h>

void set_render_context(t_app *app)
{
	app->render_ctx.aspect = (float)app->width / (float)app->height;
	app->render_ctx.fov_rad = app->scene.camera.fov_deg * PI_F / 180.0f;
	app->render_ctx.scale = tanf(app->render_ctx.fov_rad * 0.5f);
}

int	main(int argc, char **argv)
{
	t_app app;

	ft_bzero(&app, sizeof(t_app));
	if (argc != 2)
		ft_exit("Usage: ./miniRT <scene.rt>", 1);
	init_app(&app, argv[1]);
	set_render_context(&app);
	render(&app);
	if (!app.tetris_enabled && find_first(&app.scene, OBJ_SPHERE))
		shfx_trigger(&app);

	printf("Camera: position (%.2f, %.2f, %.2f), direction (%.2f, %.2f, %.2f), FOV %.2f\n",
		app.scene.camera.pos.x, app.scene.camera.pos.y, app.scene.camera.pos.z,
		app.scene.camera.direction.x, app.scene.camera.direction.y, app.scene.camera.direction.z,
		app.scene.camera.fov_deg);
	setup_hooks(&app);
	mlx_loop(app.mlx);
	image_destroy(&app);
	if (app.mlx)
		mlx_terminate(app.mlx);
	return (0);
}