/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nluchini <nluchini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 13:04:51 by nluchini          #+#    #+#             */
/*   Updated: 2025/12/24 13:04:52 by nluchini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

int	has_rt_extension(const char *file_name)
{
	size_t	size;

	size = ft_strlen(file_name);
	if (size < 3)
		return (0);
	if (ft_strcmp(&file_name[size - 3], ".rt") != 0)
		return (0);
	return (1);
}

void	ft_exit(char *msg, int code)
{
	if (msg)
		ft_printf_fd(2, "Error: %s\n", msg);
	ft_clean();
	exit(code);
}
