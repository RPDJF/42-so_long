/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:52:28 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/18 02:53:10 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	secure_exit(void *param)
{
	t_so_long	*so_long;

	if (param)
		so_long = (t_so_long *)param;
	cleargarbage();
	if (param)
	{
		mlx_destroy_window(so_long->mlx, so_long->win);
		free(so_long->mlx);
	}
	exit(0);
	return (0);
}

int	error_exit(void *param)
{
	t_so_long	*so_long;

	if (param)
		so_long = (t_so_long *)param;
	cleargarbage();
	if (param)
	{
		mlx_destroy_window(so_long->mlx, so_long->win);
		free(so_long->mlx);
	}
	exit(1);
	return (1);
}
