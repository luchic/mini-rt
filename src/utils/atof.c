/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:05:00 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:05:01 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

double	ft_atof_with_checker(const char *str, int *status)
{
	if (!ft_atof_checker(str))
	{
		set_status(status, 0);
		return (0.0);
	}
	set_status(status, 1);
	return (ft_atof(str));
}
