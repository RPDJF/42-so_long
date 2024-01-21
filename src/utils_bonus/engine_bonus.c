/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:49:51 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/21 20:11:49 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

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
	{
		render_all(so_long);
		events_handler(so_long);
	}
	return (-1);
}

static int	check_ghost_collision(t_so_long *so_long)
{
	long	i;

	i = -1;
	while (i++, (size_t)i < so_long->nb_enemies)
		if (so_long->player.pos.x == so_long->enemies[i].pos.x
			&& so_long->player.pos.y == so_long->enemies[i].pos.y)
			return (1);
	return (0);
}

void	events_handler(t_so_long *so_long)
{
	t_entity	player;
	char		**map;
	char		event;

	player = so_long->player;
	map = so_long->map->data;
	event = map[player.pos.y][player.pos.x];
	if (check_ghost_collision(so_long))
		so_long->is_over = true;
	else if (event == 'C')
		collect_score(so_long);
	else if (event == 'E' && !so_long->collectibles)
		so_long->is_over = true;
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
