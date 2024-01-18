/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/18 13:58:43 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	movement_handler(t_so_long *so_long, int direction)
{
	t_entity	*player;
	char		**map;
	int			delta;

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
	if (map[player->pos.y][player->pos.x] == 'C')
		map[player->pos.y][player->pos.x] = '0';
	if (map[player->pos.y][player->pos.x] == 'C')
		so_long->score++;
	if (delta != player->pos.x + player->pos.y)
		ft_printf("%s:\t%d\n", NB_MOVES, ++so_long->moves);
	player->current_anim = player->anims[direction];
	player->current_frame++;
	player->current_frame %= player->current_anim.nb_frames;
}

int	key_press(int keycode, void *param)
{
	t_so_long	*so_long;

	so_long = (t_so_long *)param;
	if (keycode == 53 || keycode == 65307)
		secure_exit(so_long);
	if (keycode == 65361 || keycode == 97
		|| keycode == 0 || keycode == 123)
		movement_handler(so_long, LEFT);
	if (keycode == 65363 || keycode == 100
		|| keycode == 2 || keycode == 124)
		movement_handler(so_long, RIGHT);
	if (keycode == 65362 || keycode == 119
		|| keycode == 13 || keycode == 126)
		movement_handler(so_long, UP);
	if (keycode == 65364 || keycode == 115
		|| keycode == 1 || keycode == 125)
		movement_handler(so_long, DOWN);
	render_map(so_long);
	render_entities(so_long);
	return (0);
}

int	main(int argc, char **argv)
{
	t_so_long	so_long;
	t_entity	*player;

	if (argc != 2)
		return (1);
	so_long.win = 0;
	so_long.mlx = mlx_init();
	so_long.map = get_map(&so_long, argv[1]);
	so_long.moves = 0;
	so_long.score = 0;
	so_long.win = mlx_new_window(so_long.mlx, so_long.map->width * GRID,
			so_long.map->height * GRID, "so_long");
	player = new_player(so_long.map->start, &so_long);
	so_long.player = player;
	render_map(&so_long);
	render_entities(&so_long);
	mlx_hook(so_long.win, 17, 0, secure_exit, &so_long);
	mlx_hook(so_long.win, 25, 0, secure_exit, &so_long);
	mlx_hook(so_long.win, 2, 1L << 0, key_press, &so_long);
	mlx_loop(so_long.mlx);
	return (0);
}
