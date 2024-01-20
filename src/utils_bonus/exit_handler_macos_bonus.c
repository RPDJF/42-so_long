/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler_macos_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:52:28 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/20 19:33:35 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"
#include <stdio.h>

int	secure_exit(void *param)
{
	t_so_long	*so_long;

	if (param)
	{
		so_long = (t_so_long *)param;
		if (so_long->win)
			mlx_destroy_window(so_long->mlx, so_long->win);
	}
	cleargarbage();
	exit(0);
	return (0);
}

int	error_exit(void *param)
{
	t_so_long	*so_long;

	if (param)
	{
		so_long = (t_so_long *)param;
		if (so_long->win)
			mlx_destroy_window(so_long->mlx, so_long->win);
	}
	cleargarbage();
	exit(1);
	return (1);
}

int	crash_exit(void *param)
{
	t_so_long	*so_long;

	perror("ERROR");
	if (param)
	{
		so_long = (t_so_long *)param;
		if (so_long->win)
			mlx_destroy_window(so_long->mlx, so_long->win);
	}
	cleargarbage();
	exit(1);
	return (1);
}

void	map_error_handler(t_so_long *so_long, int status)
{
	if (!so_long->map->data)
		crash_exit(so_long);
	else if (status == -1)
		ft_putendl_fd(ERR_MAP_FORMAT, 2);
	else if (status == -2)
		ft_putendl_fd(ERR_MAP_SHAPE, 2);
	else if (status == -3)
		ft_putendl_fd(ERR_MAP_ELEMENTS, 2);
	else if (status == -4)
		ft_putendl_fd(ERR_MAP_IMPOSSIBLE, 2);
	error_exit(so_long);
}
