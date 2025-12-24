/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shfx_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:45:00 by yyudi             #+#    #+#             */
/*   Updated: 2025/12/24 12:45:01 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

static void	shfx_phase0(t_app *a, t_shfx *st, double dt)
{
	t_sphere	*big;

	if (!a || !st)
		return ;
	big = (t_sphere *)st->big_obj->ptr;
	big->center.y = big->center.y - st->g * (float)dt;
	if (impact_happened(big, st->ground))
	{
		spawn_shards(a, st, big);
		big->radius = 0.0f;
		st->phase = 1;
	}
	a->needs_redraw = 1;
}

static void	shfx_process_shards(t_app *a, t_shfx *st, double dt)
{
	int			i;
	t_physics	*phy;
	t_obj		*obj;
	t_sphere	*shard;

	if (!a || !st)
		return ;
	i = 0;
	while (i < st->count)
	{
		phy = &st->shards[i];
		if (phy->active)
			phys_step(phy, (float)dt, st);
		obj = (t_obj *)phy->obj_ptr;
		if (obj)
		{
			shard = (t_sphere *)obj->ptr;
			if (shard)
				shard->center = phy->pos;
		}
		i++;
	}
}

void	shfx_update(t_app *a, double now)
{
	t_shfx	*st;
	double	dt;

	if (!a)
		return ;
	st = fx();
	if (!st->enabled || !st->big_obj || !st->big_obj->ptr)
		return ;
	dt = now - a->last_ts;
	if (dt < (1.0 / 60.0))
		return ;
	if (dt > 0.05)
		dt = 0.05;
	a->last_ts = now;
	if (st->phase == 0)
	{
		shfx_phase0(a, st, dt);
		return ;
	}
	shfx_process_shards(a, st, dt);
	a->needs_redraw = 1;
}
