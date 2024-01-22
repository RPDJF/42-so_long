/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_ia_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:14:19 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/21 23:33:22 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static int	get_dir_h(t_so_long *so_long, t_entity *enemy, t_pos *pos)
{
	char		**map;

	map = so_long->map->data;
	enemy->direction = rand() % 2;
	if (enemy->direction == LEFT && map[pos->y][pos->x - 1] == '1')
		enemy->direction = RIGHT;
	if (enemy->direction == RIGHT && map[pos->y][pos->x + 1] == '1')
		enemy->direction = LEFT;
	return (get_dir(so_long, enemy));
}

static int	get_dir_v(t_so_long *so_long, t_entity *enemy, t_pos *pos)
{
	char		**map;

	map = so_long->map->data;
	enemy->direction = rand() % 2 + 2;
	if (enemy->direction == UP && map[pos->y - 1][pos->x] == '1')
		enemy->direction = DOWN;
	if (enemy->direction == DOWN && map[pos->y + 1][pos->x] == '1')
		enemy->direction = UP;
	return (get_dir(so_long, enemy));
}

int	get_dir(t_so_long *so_long, t_entity *enemy)
{
	t_pos		*pos;
	char		**map;

	map = so_long->map->data;
	pos = &enemy->pos;
	if ((enemy->direction == UP && map[pos->y - 1][pos->x] == '1')
		|| (enemy->direction == DOWN && map[pos->y + 1][pos->x] == '1'))
		enemy->direction = get_dir_h(so_long, enemy, pos);
	if ((enemy->direction == LEFT && map[pos->y][pos->x - 1] == '1')
		|| (enemy->direction == RIGHT && map[pos->y][pos->x + 1] == '1'))
		enemy->direction = get_dir_v(so_long, enemy, pos);
	return (enemy->direction);
}