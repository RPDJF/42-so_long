/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 00:11:01 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/18 15:24:13 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	map_format_checker(t_map *map)
{
	const char	*valid_bytes = "01CEP";
	bool		trigger;
	int			h;
	int			i;
	int			j;

	h = -1;
	while (h++, map->data && map->data[h])
	{
		i = -1;
		while (i++, (map->data[h])[i])
		{
			trigger = false;
			j = -1;
			while (j++, valid_bytes[j])
				if ((map->data[h])[i] == valid_bytes[j])
					trigger = true;
			if (!trigger)
				return (-1);
		}
	}
	return (0);
}

static	int	map_shape_checker(t_map *map)
{
	int		i;

	while (map->data && map->data[map->height])
	{
		if (map->height == 0)
			map->width = ft_strlen(map->data[map->height]);
		if (map->width < 3
			|| (int)ft_strlen(map->data[map->height]) != map->width)
			return (-1);
		if (map->height == 0 || !map->data[map->height + 1])
		{
			i = -1;
			while (i++, map->data[map->height][i])
				if (map->data[map->height][i] != '1')
					return (-1);
		}
		if (map->data[map->height][0] != '1'
			|| map->data[map->height][map->width - 1] != '1')
			return (-1);
		map->height++;
	}
	if (map->height < 3)
		return (-1);
	return (0);
}

static int	map_tester(t_so_long *so_long, t_map *map)
{
	if (check_path(so_long, map, map->start, map->end) <= 0)
		return (-1);
	return (0);
}

static int	map_check_elements(t_map *map)
{
	int		score;
	int		spawn;
	int		exit;
	t_pos	pos;

	score = 0;
	spawn = 0;
	exit = 0;
	pos.y = -1;
	while (pos.y++, map->data[pos.y])
	{
		pos.x = -1;
		while (pos.x++, map->data[pos.y][pos.x])
		{
			if (map->data[pos.y][pos.x] == 'C')
				score++;
			else if (map->data[pos.y][pos.x] == 'P')
				spawn++;
			else if (map->data[pos.y][pos.x] == 'E')
				exit++;
		}
	}
	if (spawn != 1 || exit != 1 || score < 1)
		return (-1);
	return (score);
}

int	map_checker(t_so_long *so_long, t_map *map)
{
	if (map_format_checker(map) < 0)
		return (-1);
	else if (map_shape_checker(map) < 0)
		return (-2);
	so_long->collectibles = map_check_elements(map);
	if (so_long->collectibles < 0)
		return (-3);
	init_map(map);
	if (map_tester(so_long, map) < 0)
		return (-4);
	return (0);
}
