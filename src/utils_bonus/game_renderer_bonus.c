/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderer_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:36:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/21 18:53:43 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	put_image(t_so_long *so_long, void *img, t_pos pos)
{
	void	*mlx;
	void	*win;

	mlx = so_long->mlx;
	win = so_long->win;
	mlx_put_image_to_window(mlx, win, img,
		(pos.x + 2) * GRID, (pos.y + 4) * GRID);
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
				|| data[pos.y][pos.x] == 'R'
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
	t_entity	player;
	t_entity	*enemies;
	size_t		i;

	enemies = so_long->enemies;
	i = 0;
	while (i < so_long->nb_enemies)
	{
		put_image(so_long,
			enemies[i].current_anim.frames[enemies[i].current_frame].img,
			enemies[i].pos);
		i++;
	}
	player = so_long->player;
	put_image(so_long,
		player.current_anim.frames[player.current_frame].img, player.pos);
}

int	render_all(void *param)
{
	t_so_long	*so_long;
	t_pos		pos;
	char		*text;

	so_long = (t_so_long *)param;
	mlx_clear_window(so_long->mlx, so_long->win);
	render_map(so_long);
	render_entities(so_long);
	pos.x = (so_long->map->width / 2 - 2) * GRID;
	pos.y = 2 * GRID;
	text = ft_strjoin(NB_MOVES, ft_itoa(so_long->moves));
	if (!text)
		crash_exit(so_long);
	mlx_string_put(so_long->mlx, so_long->win,
		pos.x, pos.y, WHITE, text);
	gfree(text);
	pos.x = pos.x;
	pos.y = pos.y + GRID;
	text = ft_strjoin(NB_SCORE, ft_itoa(so_long->score));
	if (!text)
		crash_exit(so_long);
	mlx_string_put(so_long->mlx, so_long->win,
		pos.x, pos.y, WHITE, text);
	gfree(text);
	return (0);
}
