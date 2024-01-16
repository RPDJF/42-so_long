/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:52:28 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/16 04:30:49 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	secure_exit(void *param)
{
	t_so_long	*so_long;

	so_long = (t_so_long *)param;
	cleargarbage();
	mlx_destroy_window(so_long->mlx, so_long->win);
	exit(0);
	return (0);
}

int	error_exit(void *param)
{
	t_so_long	*so_long;

	so_long = (t_so_long *)param;
	cleargarbage();
	mlx_destroy_window(so_long->mlx, so_long->win);
	exit(1);
	return (0);
}