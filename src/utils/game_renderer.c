/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 21:36:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/18 00:55:01 by rude-jes         ###   ########.fr       */
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
	char	**map;

	map = so_long->map->data;
	static t_texture	wall;
	static t_texture	path;
	static t_texture	score;
	if (!wall.img)
		wall.img = mlx_xpm_file_to_image(so_long->mlx, ft_strjoin(TEXTURES_DIR, "wall.xpm"), &wall.width, &wall.height);
	if (!path.img)
		path.img = mlx_xpm_file_to_image(so_long->mlx, ft_strjoin(TEXTURES_DIR, "path.xpm"), &path.width, &score.height);
	if (!score.img)
		score.img = mlx_xpm_file_to_image(so_long->mlx, ft_strjoin(TEXTURES_DIR, "score.xpm"), &score.width, &score.height);
	pos.y = -1;
	while (pos.y++, map[pos.y])
	{
		pos.x = -1;
		while (pos.x++, map[pos.y][pos.x])
		{
			if (map[pos.y][pos.x] == '1')
				put_image(so_long, wall.img, pos);
			else if (map[pos.y][pos.x] == '0'
				|| map[pos.y][pos.x] == 'P' || map[pos.y][pos.x] == 'E')
				put_image(so_long, path.img, pos);
			else if (map[pos.y][pos.x] == 'C')
				put_image(so_long, score.img, pos);
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
