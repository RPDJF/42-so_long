/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_wrapper_linux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:20:47 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/21 18:48:10 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	*load_xpm(t_so_long *so_long, char *file, int *width, int *height)
{
	t_img	*img;

	img = mlx_xpm_file_to_image(so_long->mlx, file, width, height);
	if (!img)
		crash_exit(so_long);
	addgarbage(img->image);
	addgarbage(img);
	return (img);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
