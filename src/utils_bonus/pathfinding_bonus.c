/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:06:30 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 06:01:00 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static char	**map_dup(t_so_long *so_long)
{
	char	**map_cpy;
	int		i;

	map_cpy = (char **)galloc(sizeof(char *) * (so_long->map->height + 1));
	if (!map_cpy)
		crash_exit(so_long);
	i = -1;
	while (i++, i < so_long->map->height)
	{
		map_cpy[i] = ft_strdup(so_long->map->data[i]);
		if (!map_cpy[i])
			crash_exit(so_long);
	}
	map_cpy[i] = 0;
	return (map_cpy);
}

static int	pathfinder(t_so_long *so_long, char **map, t_pos p1, t_pos p2)
{
	if (p1.x < 0 || p1.y < 0 || p1.x >= so_long->map->width
		|| p1.y >= so_long->map->height || map[p1.y][p1.x] == '1')
		return (-1);
	if ((p1.x + 1 == p2.x && p1.y == p2.y)
		|| (p1.x - 1 == p2.x && p1.y == p2.y)
		|| (p1.x == p2.x && p1.y + 1 == p2.y)
		|| (p1.x == p2.x && p1.y - 1 == p2.y))
		return (3);
	map[p1.y][p1.x] = '1';
	p1.x++;
	if (pathfinder(so_long, map, p1, p2) >= 0)
		return (RIGHT);
	p1.x -= 2;
	if (pathfinder(so_long, map, p1, p2) >= 0)
		return (LEFT);
	p1.x++;
	p1.y++;
	if (pathfinder(so_long, map, p1, p2) >= 0)
		return (DOWN);
	p1.y -= 2;
	if (pathfinder(so_long, map, p1, p2) >= 0)
		return (UP);
	return (-1);
}

int	get_path(t_so_long *so_long, t_pos p1, t_pos p2)
{
	int		status;
	char	**map_cpy;

	map_cpy = map_dup(so_long);
	status = pathfinder(so_long, map_cpy, p1, p2);
	ft_memsuperclear((void **)map_cpy, so_long->map->height);
	return (status);
}
