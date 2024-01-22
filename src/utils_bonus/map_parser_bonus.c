/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:09:11 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/22 01:49:28 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"
#include <fcntl.h>
#include <stdio.h>

void	reset_map(t_map *map)
{
	map->start.x = -1;
	map->start.y = -1;
	map->end.x = -1;
	map->end.y = -1;
}

int	init_map(t_so_long *so_long)
{
	t_pos	pos;

	so_long->enemies = 0;
	so_long->nb_enemies = 0;
	pos.y = -1;
	while (pos.y++, so_long->map->data[pos.y])
	{
		pos.x = -1;
		while (pos.x++, so_long->map->data[pos.y][pos.x])
		{
			if (so_long->map->data[pos.y][pos.x] == 'P')
				if (so_long->map->start.x > -1)
					return (-1);
			if (so_long->map->data[pos.y][pos.x] == 'P')
				so_long->map->start = pos;
			if (so_long->map->data[pos.y][pos.x] == 'E')
				if (so_long->map->end.x > -1)
					return (-1);
			if (so_long->map->data[pos.y][pos.x] == 'E')
				so_long->map->end = pos;
			if (so_long->map->data[pos.y][pos.x] == 'M')
				load_enemies(so_long, pos);
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

static void	load_map_textures(t_so_long *so_long, t_map *map)
{
	char	*tmp;

	tmp = ft_strjoin(TEXTURES_DIR, "wall.xpm");
	if (!tmp)
		crash_exit(so_long);
	map->wall.img = load_xpm(so_long, tmp, &map->wall.width, &map->wall.height);
	gfree(tmp);
	tmp = ft_strjoin(TEXTURES_DIR, "path.xpm");
	if (!tmp)
		crash_exit(so_long);
	map->path.img = load_xpm(so_long, tmp, &map->path.width, &map->path.height);
	gfree(tmp);
	tmp = ft_strjoin(TEXTURES_DIR, "score.xpm");
	if (!tmp)
		crash_exit(so_long);
	map->score.img = load_xpm(so_long, tmp, &map->score.width,
			&map->score.height);
	gfree(tmp);
	tmp = ft_strjoin(TEXTURES_DIR, "exit.xpm");
	if (!tmp)
		crash_exit(so_long);
	map->exit.img = load_xpm(so_long, tmp, &map->exit.width, &map->exit.height);
}

t_map	*get_map(t_so_long *so_long, char *filename)
{
	t_map	*map;
	int		status;

	check_map_name(filename);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (0);
	map->data = load_map(filename);
	if (!map->data)
		crash_exit(so_long);
	so_long->map = map;
	status = map_checker(so_long, map);
	if (status < 0)
		map_error_handler(so_long, status);
	load_map_textures(so_long, map);
	return (map);
}
