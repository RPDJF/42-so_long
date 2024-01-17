/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:09:11 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/17 19:34:26 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include <fcntl.h>

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
		if (map->width < 3 || (int)ft_strlen(map->data[map->height]) != map->width)
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

static void	reset_map(t_map *map)
{
	map->start.x = -1;
	map->start.y = -1;
	map->end.x = -1;
	map->end.y = -1;
}

int	init_map(t_map *map)
{
	t_pos	pos;

	reset_map(map);
	pos.y = -1;
	while (pos.y++, map->data[pos.y])
	{
		pos.x = -1;
		while (pos.x++, map->data[pos.y][pos.x])
		{
			if (map->data[pos.y][pos.x] == 'P')
				if (map->start.x > -1)
					return (-1);
			if (map->data[pos.y][pos.x] == 'P')
				map->start = pos;
			if (map->data[pos.y][pos.x] == 'E')
				if (map->end.x > -1)
					return (-1);
			if (map->data[pos.y][pos.x] == 'E')
				map->end = pos;
		}
	}
	return (0);
}

static int	map_tester(t_so_long *so_long, t_map *map)
{
	if (check_path(so_long, map, map->start, map->end) <= 0)
		return (-1);
	return (0);
}

static int	map_checker(t_so_long *so_long, t_map *map)
{
	if (map_format_checker(map) < 0)
		return (-1);
	else if (map_shape_checker(map) < 0)
		return (-2);
	// need to check spawn, end and collectibles
	init_map(map);
	if (map_tester(so_long, map) < 0)
		return (-3);
	return (0);
}

static char	**load_map(char *filename)
{
	char	**map;
	char	*map_buffer;
	int		fd;
	size_t	i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	map = 0;
	map_buffer = ft_get_next_line(fd);
	i = 0;
	while (map_buffer)
	{
		map_buffer[ft_strlen(map_buffer) - 1] = 0;
		map = ft_reallocf(map, i * sizeof(char *), (i + 1) * sizeof(char *));
		map[i] = map_buffer;
		i += 1;
		map_buffer = ft_get_next_line(fd);
	}
	close(fd);
	map = ft_reallocf(map, i * sizeof(char *), (i + 1) * sizeof(char *));
	map[i] = 0;
	return (map);
}

t_map	*get_map(t_so_long *so_long, char *filename)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (0);
	map->data = load_map(filename);
	if (!map)
		return (0);
	if (map_checker(so_long, map) < 0)
		return (0);
	return (map);
}
