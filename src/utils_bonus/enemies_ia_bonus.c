/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_ia_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:14:19 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/21 03:17:51 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

int	choose_dir(t_so_long *so_long, t_entity enemy)
{
	t_pos		*pos;
	char		**map;

	map = so_long->map->data;
	pos = &enemy.pos;
	if ((enemy.direction == UP && map[pos->y - 1][pos->x] == '1')
		|| (enemy.direction == DOWN && map[pos->y + 1][pos->x] == '1'))
	{
		enemy.direction = rand() % 2;
		if (enemy.direction == LEFT && map[pos->y][pos->x - 1] == '1')
			enemy.direction = RIGHT;
		if (enemy.direction == RIGHT && map[pos->y][pos->x + 1] == '1')
			enemy.direction = LEFT;
		return (choose_dir(so_long, enemy));
	}
	if ((enemy.direction == LEFT && map[pos->y][pos->x - 1] == '1')
		|| (enemy.direction == RIGHT && map[pos->y][pos->x + 1] == '1'))
	{
		enemy.direction = rand() % 2 + 2;
		if (enemy.direction == UP && map[pos->y - 1][pos->x] == '1')
			enemy.direction = DOWN;
		if (enemy.direction == DOWN && map[pos->y + 1][pos->x] == '1')
			enemy.direction = UP;
		return (choose_dir(so_long, enemy));
	}
	return (enemy.direction);
}

void	move_enemies(t_so_long *so_long)
{
	size_t		i;
	t_entity	*enemies;
	t_pos		*pos;

	enemies = so_long->enemies;
	i = 0;
	while (i < so_long->nb_enemies)
	{
		pos = &enemies->pos;
		enemies->direction = choose_dir(so_long, *enemies);
		if (enemies->direction == UP)
			pos->y--;
		else if (enemies->direction == DOWN)
			pos->y++;
		else if (enemies->direction == LEFT)
			pos->x--;
		else
			pos->x++;
		animate(enemies, enemies->direction % 2);
		enemies = &enemies[1];
		i++;
	}
}
