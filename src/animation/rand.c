#include "ft_minirt.h"

void	rng_seed(t_app *app, unsigned int seed_value)
{
	if (seed_value == 0)
		seed_value = 1;
	app->rng_seed = seed_value;
}

static unsigned int	rng_xorshift32(t_app *app)
{
	unsigned int	x;

	x = app->rng_seed;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	app->rng_seed = x;
	return (x);
}

float	rng_random01(t_app *app)
{
	unsigned int	random_bits;

	random_bits = rng_xorshift32(app);
	return ((float)(random_bits & 0x00FFFFFFu) / 16777216.0f);
}
