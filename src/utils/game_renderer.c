/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:36:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/18 16:00:49 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	put_image(t_so_long *so_long, void *img, t_pos pos)
{
	void	*mlx;
	void	*win;

	mlx = so_long->mlx;
	win = so_long->win;
	mlx_put_image_to_window(mlx, win, img, pos.x * GRID, pos.y * GRID);
}

void	render_map(t_so_long *so_long)
{
	t_pos	pos;
	t_map	*map;
	char	**data;

	map = so_long->map;
	data = map->data;
	pos.y = -1;
	while (pos.y++, data[pos.y])
	{
		pos.x = -1;
		while (pos.x++, data[pos.y][pos.x])
		{
			if (data[pos.y][pos.x] == '1')
				put_image(so_long, map->wall.img, pos);
			else if (data[pos.y][pos.x] == '0'
				|| data[pos.y][pos.x] == 'P'
				|| (data[pos.y][pos.x] == 'E' && so_long->collectibles))
				put_image(so_long, map->path.img, pos);
			else if (data[pos.y][pos.x] == 'C')
				put_image(so_long, map->score.img, pos);
			else if (data[pos.y][pos.x] == 'E' && !so_long->collectibles)
				put_image(so_long, map->exit.img, pos);
		}
	}
}

void	render_entities(t_so_long *so_long)
{
	t_entity	*player;

	player = so_long->player;
	put_image(so_long,
		player->current_anim.frames[player->current_frame].img, player->pos);
}

int	render_all(void *param)
{
	t_so_long	*so_long;

	so_long = (t_so_long *)param;
	render_map(so_long);
	render_entities(so_long);
	return (0);
}
