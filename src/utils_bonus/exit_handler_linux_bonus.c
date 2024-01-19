/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler_linux_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:52:28 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/19 01:50:46 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"
#include <stdio.h>
#include <signal.h>

int	secure_exit(void *param)
{
	t_so_long	*so_long;

	if (param)
	{
		so_long = (t_so_long *)param;
		if (so_long->win)
			mlx_destroy_window(so_long->mlx, so_long->win);
		mlx_destroy_display(so_long->mlx);
		free(so_long->mlx);
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
		mlx_destroy_display(so_long->mlx);
		free(so_long->mlx);
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
		mlx_destroy_display(so_long->mlx);
		free(so_long->mlx);
	}
	cleargarbage();
	exit(1);
	return (1);
}
