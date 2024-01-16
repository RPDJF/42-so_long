/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/16 03:12:19 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_pos		pos;
	t_entity	*player;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 640, 480, "so_long");
	pos.x = 20;
	pos.y = 40;
	player = new_player(pos, mlx);
	mlx_put_image_to_window(mlx, mlx_win, player->anims[0].frames[0].img, player->pos.x, player->pos.y);
	mlx_put_image_to_window(mlx, mlx_win, player->anims[0].frames[1].img, player->pos.x + 30, player->pos.y);
	mlx_put_image_to_window(mlx, mlx_win, player->anims[0].frames[2].img, player->pos.x + 60, player->pos.y);
	mlx_put_image_to_window(mlx, mlx_win, player->anims[1].frames[0].img, player->pos.x, player->pos.y + 30);
	mlx_put_image_to_window(mlx, mlx_win, player->anims[1].frames[1].img, player->pos.x + 30, player->pos.y + 30);
	mlx_put_image_to_window(mlx, mlx_win, player->anims[1].frames[2].img, player->pos.x + 60, player->pos.y + 30);
	mlx_loop(mlx);
	secure_exit(0);
}
