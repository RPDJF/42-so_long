/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_ia_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 16:14:19 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/20 19:16:41 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	move_enemies(t_so_long *so_long)
{
	size_t		i;
	t_entity	*enemies;
	char		**map;
	t_pos		*pos;

	enemies = so_long->enemies;
	map = so_long->map->data;
	i = 0;
	while (i < so_long->nb_enemies)
	{
		pos = &enemies->pos;
		if ((enemies->direction == UP && map[pos->y - 1][pos->x] == '1')
			|| (enemies->direction == DOWN && map[pos->y + 1][pos->x] == '1')
			|| (enemies->direction == LEFT && map[pos->y][pos->x - 1] == '1')
			|| (enemies->direction == RIGHT && map[pos->y][pos->x + 1] == '1'))
		{
			enemies->direction = rand() % 4;
			move_enemies(so_long);
			return ;
		}
		if (enemies->direction == UP)
			pos->y--;
		else if (enemies->direction == DOWN)
			pos->y++;
		else if (enemies->direction == LEFT)
			pos->x--;
		else
			pos->x++;
		enemies->current_frame++;
		enemies->current_frame %= enemies->anims->nb_frames;
		enemies = &enemies[1];
		i++;
	}
}
