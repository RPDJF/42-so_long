/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:49:51 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/20 19:28:29 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static void	game_win(t_so_long *so_long)
{
	ft_printf("You win !\n");
	secure_exit(so_long);
}

void	movement_handler(t_so_long *so_long)
{
	t_entity	*player;
	char		**map;
	int			delta;
	int			direction;
	t_pos		*pos;

	player = &so_long->player;
	direction = player->direction;
	pos = &player->pos;
	map = so_long->map->data;
	delta = pos->x + pos->y;
	if (pos->x > 0 && direction == LEFT && map[pos->y][pos->x - 1] != '1')
		pos->x--;
	else if (pos->x < so_long->map->width - 1
		&& direction == RIGHT && map[pos->y][pos->x + 1] != '1')
		pos->x++;
	else if (pos->y > 0 && direction == UP && map[pos->y - 1][pos->x] != '1')
		pos->y--;
	else if (pos->y < so_long->map->height - 1
		&& direction == DOWN && map[pos->y + 1][pos->x] != '1')
		pos->y++;
	if (delta != pos->x + pos->y)
		++so_long->moves;
	animate(player, direction);
}

int	teleport_handler(t_so_long *so_long, t_entity *e)
{
	if ((e->pos.x == 0)
		|| (e->pos.x == so_long->map->width - 1)
		|| (e->pos.y == 0)
		|| (e->pos.y == so_long->map->height - 1))
	{
		mlx_do_sync(so_long->mlx);
		usleep(120000);
	}
	if (e->pos.x == 0)
		e->pos.x = so_long->map->width - 1;
	else if (e->pos.x == so_long->map->width - 1)
		e->pos.x = 0;
	else if (e->pos.y == 0)
		e->pos.y = so_long->map->height - 1;
	else if (e->pos.y == so_long->map->height - 1)
		e->pos.y = 0;
	if ((e->pos.x == so_long->map->width - 1)
		|| (e->pos.x == 0)
		|| (e->pos.y == so_long->map->height - 1)
		|| (e->pos.y == 0))
		return (render_all(so_long));
	return (-1);
}

void	events_handler(t_so_long *so_long)
{
	t_entity	player;
	char		**map;
	char		event;

	player = so_long->player;
	map = so_long->map->data;
	event = map[player.pos.y][player.pos.x];
	if (event == 'C')
		collect_score(so_long);
	else if (event == 'E' && !so_long->collectibles)
		game_win(so_long);
}

void	collect_score(t_so_long *so_long)
{
	t_entity	player;
	char		**map;

	player = so_long->player;
	map = so_long->map->data;
	so_long->collectibles--;
	map[player.pos.y][player.pos.x] = '0';
	so_long->score += 10;
}
