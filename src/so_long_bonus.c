/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/19 00:42:32 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	check_events(t_so_long *so_long)
{
	t_entity	*player;
	char		**map;
	char		event;

	player = so_long->player;
	map = so_long->map->data;
	event = map[player->pos.y][player->pos.x];
	if (event == 'C')
	{
		so_long->collectibles--;
		map[player->pos.y][player->pos.x] = '0';
		so_long->score++;
	}
	else if (event == 'E' && !so_long->collectibles)
	{
		ft_printf("You win !\n");
		secure_exit(so_long);
	}
}

void	movement_handler(t_so_long *so_long)
{
	t_entity	*player;
	char		**map;
	int			delta;
	int			direction;

	direction = so_long->player_direction;
	player = so_long->player;
	map = so_long->map->data;
	delta = player->pos.x + player->pos.y;
	if (direction == 0 && map[player->pos.y][player->pos.x - 1] != '1')
		player->pos.x--;
	else if (direction == 1 && map[player->pos.y][player->pos.x + 1] != '1')
		player->pos.x++;
	else if (direction == 2 && map[player->pos.y - 1][player->pos.x] != '1')
		player->pos.y--;
	else if (direction == 3 && map[player->pos.y + 1][player->pos.x] != '1')
		player->pos.y++;
	if (delta != player->pos.x + player->pos.y)
		ft_printf("%s:\t%d\n", NB_MOVES, ++so_long->moves);
	player->current_anim = player->anims[direction];
	player->current_frame++;
	player->current_frame %= player->current_anim.nb_frames;
	check_events(so_long);
}

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
	t_entity	*player;

	so_long = galloc(sizeof(t_so_long));
	if (!so_long)
		secure_exit(0);
	so_long->win = 0;
	so_long->mlx = mlx_init();
	so_long->map = get_map(so_long, filename);
	so_long->moves = 0;
	so_long->score = 0;
	so_long->win = mlx_new_window(so_long->mlx, so_long->map->width * GRID,
			so_long->map->height * GRID, "so_long");
	player = new_player(so_long->map->start, so_long);
	so_long->player = player;
	so_long->player_direction = 1;
	return (so_long);
}

void	*move_player(void *arg)
{
	t_so_long	*so_long;
	void		*mlx;

	so_long = (t_so_long *)arg;
	mlx = so_long->mlx;
	while (true)
	{
		usleep(200000);
		movement_handler(so_long);
		render_all(so_long);
		mlx_do_sync(mlx);
	}
	pthread_exit(NULL);
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
	render_all(so_long);
	if (pthread_create(&so_long->ticks, 0, move_player, (void *)so_long) != 0)
		crash_exit(so_long);
	mlx_hook(so_long->win, 2, 1L << 0, key_press, so_long);
	mlx_hook(so_long->win, 17, 0, secure_exit, so_long);
	mlx_expose_hook(so_long->win, render_all, so_long);
	mlx_loop(so_long->mlx);
	return (0);
}
