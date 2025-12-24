/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:04:55 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:04:56 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	*emalloc(size_t size)
{
	void	*ptr;

	ptr = ft_malloc(size);
	if (!ptr)
		ft_exit("malloc failed", 1);
	return (ptr);
}
