/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:04:57 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:04:58 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"
#include <limits.h>

void	set_status(int *status, int value)
{
	if (status)
		*status = value;
}

int	ft_atoi_with_checker(const char *str, int *status)
{
	if (!ft_atoi_checker(str))
	{
		set_status(status, 0);
		return (0);
	}
	set_status(status, 1);
	return (ft_atoi(str));
}
