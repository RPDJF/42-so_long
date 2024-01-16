/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/16 04:35:35 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
int	key_press(int keycode, void *so_long)
{
	if (keycode == 53)
		secure_exit(so_long);
	return (0);
}


int	main(void)
{
	t_so_long	so_long;
	t_pos		pos;
	t_entity	*player;

	so_long.mlx = mlx_init();
	so_long.win = mlx_new_window(so_long.mlx, 640, 480, "so_long");
	mlx_hook(so_long.win, 17, 0, secure_exit, &so_long);
	mlx_hook(so_long.win, 2, 0, key_press, &so_long);
	pos.x = 20;
	pos.y = 40;
	player = new_player(pos, &so_long);
	mlx_put_image_to_window(so_long.mlx, so_long.win, player->anims[0].frames[0].img, player->pos.x, player->pos.y);
	mlx_put_image_to_window(so_long.mlx, so_long.win, player->anims[0].frames[1].img, player->pos.x + 30, player->pos.y);
	mlx_put_image_to_window(so_long.mlx, so_long.win, player->anims[0].frames[2].img, player->pos.x + 60, player->pos.y);
	mlx_put_image_to_window(so_long.mlx, so_long.win, player->anims[1].frames[0].img, player->pos.x, player->pos.y + 30);
	mlx_put_image_to_window(so_long.mlx, so_long.win, player->anims[1].frames[1].img, player->pos.x + 30, player->pos.y + 30);
	mlx_put_image_to_window(so_long.mlx, so_long.win, player->anims[1].frames[2].img, player->pos.x + 60, player->pos.y + 30);
	mlx_loop(so_long.mlx);
	return (0);
}
