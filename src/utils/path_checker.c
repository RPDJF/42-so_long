/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:08:24 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/17 22:45:29 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	path_finder(t_map *map, t_pos pos1, t_pos pos2, t_list *history);

static int	path_finder_h(t_map *map, t_pos pos1, t_pos pos2, t_list *history)
{
	t_pos	tmp;

	if (pos1.x < map->width && map->data[pos1.y][pos1.x + 1] != '1')
	{
		tmp = pos1;
		tmp.x++;
		if (path_finder(map, tmp, pos2, history) == 1)
			return (1);
	}
	if (pos1.x > 0 && map->data[pos1.y][pos1.x - 1] != '1')
	{
		tmp = pos1;
		tmp.x--;
		if (path_finder(map, tmp, pos2, history) == 1)
			return (1);
	}
	return (0);
}

static int	path_finder_v(t_map *map, t_pos pos1, t_pos pos2, t_list *history)
{
	t_pos	tmp;

	if (pos1.x > 0 && map->data[pos1.y - 1][pos1.x] != '1')
	{
		tmp = pos1;
		tmp.y--;
		if (path_finder(map, tmp, pos2, history) == 1)
			return (1);
	}
	if (pos1.x > 0 && map->data[pos1.y + 1][pos1.x] != '1')
	{
		tmp = pos1;
		tmp.y++;
		if (path_finder(map, tmp, pos2, history) == 1)
			return (1);
	}
	return (0);
}

static int	path_finder(t_map *map, t_pos pos1, t_pos pos2, t_list *history)
{
	t_list	*head;

	if (pos1.x == pos2.x && pos1.y == pos2.y)
		return (1);
	history = ft_lstaddr(history, &pos1);
	if (!history)
		return (-1);
	head = history->next;
	while (head)
	{
		if (((t_pos *)head->content)->x == pos1.x
			&& ((t_pos *)head->content)->y == pos1.y)
			return (0);
		head = head->next;
	}
	if (path_finder_h(map, pos1, pos2, history)
		|| path_finder_v(map, pos1, pos2, history))
		return (1);
	return (0);
}

int	check_path(t_so_long *so_long, t_map *map, t_pos pos1, t_pos pos2)
{
	int	rslt;

	rslt = path_finder(map, pos1, pos2, 0);
	if (rslt < 0)
		secure_exit(so_long);
	return (rslt);
}
