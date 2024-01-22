/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:49:51 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/22 04:46:11 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	game_win(t_so_long *so_long)
{
	ft_printf("You win !\n");
	secure_exit(so_long);
}

static void	collect_score(t_so_long *so_long)
{
	t_entity	player;
	char		**map;

	player = so_long->player;
	map = so_long->map->data;
	so_long->collectibles--;
	map[player.pos.y][player.pos.x] = '0';
	so_long->score += 10;
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

void	events_handler(t_so_long *so_long)
{
	t_entity	player;
	char		**map;
	char		event;
	static int	delta;
	char		*text;

	player = so_long->player;
	map = so_long->map->data;
	event = map[player.pos.y][player.pos.x];
	if (delta != so_long->moves)
	{
		delta = so_long->moves;
		ft_putstr_fd(NB_MOVES, STDOUT_FILENO);
		text = ft_itoa(so_long->moves);
		if (!text)
			crash_exit(so_long);
		ft_putendl_fd(text, STDOUT_FILENO);
		gfree(text);
	}
	if (event == 'C')
		collect_score(so_long);
	else if (event == 'E' && !so_long->collectibles)
		game_win(so_long);
}
