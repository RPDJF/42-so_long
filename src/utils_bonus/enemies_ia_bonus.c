/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_ia_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:14:19 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/22 04:30:44 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static int	get_dir_h(t_so_long *so_long, t_entity *enemy, t_pos *pos)
{
	char		**map;

	map = so_long->map->data;
	enemy->direction = rand() % 2;
	if (pos->x > 0
		&& enemy->direction == LEFT && map[pos->y][pos->x - 1] == '1')
		enemy->direction = RIGHT;
	if (pos->x < so_long->map->width
		&& enemy->direction == RIGHT && map[pos->y][pos->x + 1] == '1')
		enemy->direction = LEFT;
	return (get_dir(so_long, enemy));
}

static int	get_dir_v(t_so_long *so_long, t_entity *enemy, t_pos *pos)
{
	char		**map;

	map = so_long->map->data;
	enemy->direction = rand() % 2 + 2;
	if (pos->y > 0
		&& enemy->direction == UP && map[pos->y - 1][pos->x] == '1')
		enemy->direction = DOWN;
	if (pos->y < so_long->map->height
		&& enemy->direction == DOWN && map[pos->y + 1][pos->x] == '1')
		enemy->direction = UP;
	return (get_dir(so_long, enemy));
}

static int	get_nb_paths(t_so_long *so_long, t_entity *enemy)
{
	int		nb;
	t_pos	pos;
	char	**map;

	map = so_long->map->data;
	pos = enemy->pos;
	nb = 0;
	if (map[pos.y][pos.x + 1] != '1')
		nb++;
	if (map[pos.y][pos.x - 1] != '1')
		nb++;
	if (map[pos.y + 1][pos.x] != '1')
		nb++;
	if (map[pos.y - 1][pos.x] != '1')
		nb++;
	return (nb);
}

static int	get_dir_rng(t_so_long *so_long, t_entity *enemy,
	char **map, t_pos *pos)
{
	if (map[pos->y - 1][pos->x - 1] == '1'
		&& map[pos->y - 1][pos->x + 1] == '1'
		&& map[pos->y + 1][pos->x - 1] == '1'
		&& map[pos->y + 1][pos->x + 1] == '1'
		&& get_nb_paths(so_long, enemy) >= 3)
	{
		if (!(rand() % 3))
			return (rand() % 4);
		else
		{
			if (pos->y > so_long->player.pos.y)
				return (UP);
			else if (pos->y < so_long->player.pos.y)
				return (DOWN);
			else if (pos->x < so_long->player.pos.x)
				return (RIGHT);
			else if (pos->x > so_long->player.pos.x)
				return (LEFT);
		}
	}
	return (enemy->direction);
}

int	get_dir(t_so_long *so_long, t_entity *enemy)
{
	t_pos		*pos;
	char		**map;

	map = so_long->map->data;
	pos = &enemy->pos;
	if (rand() % 2 && ((pos->y > 0 && pos->y < so_long->map->height)
			&& (pos->x > 0 && pos->x < so_long->map->width)))
			enemy->direction = get_dir_rng(so_long, enemy, map, pos);
	if ((pos->y > 0 && (enemy->direction == UP
				&& map[pos->y - 1][pos->x] == '1'))
		|| (pos->y < so_long->map->height && (enemy->direction == DOWN
				&& map[pos->y + 1][pos->x] == '1')))
		enemy->direction = get_dir_h(so_long, enemy, pos);
	if ((pos->x > 0 && (enemy->direction == LEFT
				&& map[pos->y][pos->x - 1] == '1'))
		|| (pos->x < so_long->map->width && (enemy->direction == RIGHT
				&& map[pos->y][pos->x + 1] == '1')))
		enemy->direction = get_dir_v(so_long, enemy, pos);
	return (enemy->direction);
}
