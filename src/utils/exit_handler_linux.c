/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler_linux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:52:28 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/18 13:34:43 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include <stdio.h>

int	secure_exit(void *param)
{
	t_so_long	*so_long;

	cleargarbage();
	if (param)
	{
		so_long = (t_so_long *)param;
		mlx_destroy_window(so_long->mlx, so_long->win);
		mlx_destroy_display(so_long->mlx);
		free(so_long->mlx);
	}
	exit(0);
	return (0);
}

int	error_exit(void *param)
{
	t_so_long	*so_long;

	cleargarbage();
	if (param)
	{
		so_long = (t_so_long *)param;
		mlx_destroy_window(so_long->mlx, so_long->win);
		mlx_destroy_display(so_long->mlx);
		free(so_long->mlx);
	}
	exit(1);
	return (1);
}

int	crash_exit(void *param)
{
	t_so_long	*so_long;

	perror("ERROR");
	cleargarbage();
	if (param)
	{
		so_long = (t_so_long *)param;
		mlx_destroy_window(so_long->mlx, so_long->win);
		mlx_destroy_display(so_long->mlx);
		free(so_long->mlx);
	}
	exit(1);
	return (1);
}
