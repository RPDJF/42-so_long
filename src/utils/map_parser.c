/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:09:11 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/18 00:11:26 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include <fcntl.h>

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
