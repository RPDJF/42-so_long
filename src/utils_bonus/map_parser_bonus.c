/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:09:11 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/18 22:51:40 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"
#include <fcntl.h>
#include <stdio.h>

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

static void	load_map_textures(t_so_long *so_long, t_map *map)
{
	char	*tmp;

	tmp = ft_strjoin(TEXTURES_DIR, "wall.xpm");
	if (!tmp)
		crash_exit(so_long);
	map->wall.img = mlx_xpm_file_to_image(so_long->mlx, tmp,
			&map->wall.width, &map->wall.height);
	gfree(tmp);
	tmp = ft_strjoin(TEXTURES_DIR, "path.xpm");
	if (!tmp)
		crash_exit(so_long);
	map->path.img = mlx_xpm_file_to_image(so_long->mlx, tmp,
			&map->path.width, &map->path.height);
	gfree(tmp);
	tmp = ft_strjoin(TEXTURES_DIR, "score.xpm");
	if (!tmp)
		crash_exit(so_long);
	map->score.img = mlx_xpm_file_to_image(so_long->mlx, tmp,
			&map->score.width, &map->score.height);
	gfree(tmp);
	tmp = ft_strjoin(TEXTURES_DIR, "exit.xpm");
	if (!tmp)
		crash_exit(so_long);
	map->exit.img = mlx_xpm_file_to_image(so_long->mlx, tmp,
			&map->exit.width, &map->exit.height);
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
	status = map_checker(so_long, map);
	if (status < 0)
	{
		if (!map->data)
			crash_exit(so_long);
		else if (status == -1)
			ft_putendl_fd(ERR_MAP_FORMAT, 2);
		else if (status == -2)
			ft_putendl_fd(ERR_MAP_SHAPE, 2);
		else if (status == -3)
			ft_putendl_fd(ERR_MAP_ELEMENTS, 2);
		else if (status == -4)
			ft_putendl_fd(ERR_MAP_IMPOSSIBLE, 2);
		error_exit(so_long);
	}
	load_map_textures(so_long, map);
	return (map);
}
