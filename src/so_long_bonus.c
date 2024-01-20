/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/20 19:14:21 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	key_press(int keycode, void *param)
{
	t_so_long	*so_long;

	so_long = (t_so_long *)param;
	if (keycode == 53 || keycode == 65307)
		secure_exit(so_long);
	if (keycode == 65361 || keycode == 97
		|| keycode == 0 || keycode == 123)
		so_long->player_direction = LEFT;
	if (keycode == 65363 || keycode == 100
		|| keycode == 2 || keycode == 124)
		so_long->player_direction = RIGHT;
	if (keycode == 65362 || keycode == 119
		|| keycode == 13 || keycode == 126)
		so_long->player_direction = UP;
	if (keycode == 65364 || keycode == 115
		|| keycode == 1 || keycode == 125)
		so_long->player_direction = DOWN;
	return (0);
}

static t_so_long	*new_so_long(char *filename)
{
	t_so_long	*so_long;
	t_entity	player;
	int			width;
	int			height;

	so_long = galloc(sizeof(t_so_long));
	if (!so_long)
		secure_exit(0);
	so_long->win = 0;
	so_long->mlx = mlx_init();
	if (!so_long->mlx)
		crash_exit(so_long);
	so_long->map = get_map(so_long, filename);
	so_long->moves = 0;
	so_long->score = 0;
	width = (so_long->map->width + 4) * GRID;
	height = (so_long->map->height + 7) * GRID;
	so_long->win = mlx_new_window(so_long->mlx, width, height, "so_long");
	if (!so_long->win)
		crash_exit(so_long);
	player = new_player(so_long->map->start, so_long);
	so_long->player = player;
	so_long->player_direction = 1;
	return (so_long);
}

int	ticks(void *arg)
{
	t_so_long	*so_long;

	so_long = (t_so_long *)arg;
	usleep(120000);
	movement_handler(so_long);
	move_enemies(so_long);
	events_handler(so_long);
	render_all(so_long);
	teleport_handler(so_long, &so_long->player);
	events_handler(so_long);
	return (0);
}

int	main(int argc, char **argv)
{
	t_so_long	*so_long;

	if (argc > 2)
		ft_putendl_fd(TOO_MUCH_ARG, 2);
	else if (argc < 2)
		ft_putendl_fd(NOT_ENOUGH_ARGS, 2);
	if (argc != 2)
		return (error_exit(0));
	so_long = new_so_long(argv[1]);
	mlx_hook(so_long->win, 2, 1L << 0, key_press, so_long);
	mlx_hook(so_long->win, 17, 0, secure_exit, so_long);
	mlx_expose_hook(so_long->win, render_all, so_long);
	mlx_loop_hook(so_long->mlx, ticks, so_long);
	mlx_loop(so_long->mlx);
	return (0);
}
