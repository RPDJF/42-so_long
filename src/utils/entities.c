/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:49:48 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/16 01:27:30 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_entity *new_player(t_pos pos, void *mlx)
{
	t_entity	*player;
	t_anim		*anims;
	char		*name;

	name = ft_strdup("player");
	if (!name)
		secure_exit(1);
	player = new_entity(name, pos, 0);
	player->nb_anims = 1;
	anims = galloc(sizeof(t_anim) * player->nb_anims);
	if (!anims)
		secure_exit(1);
	player->anims[0] = new_animation("player", "right", 3, mlx);
	player->current_anim = player->anims[0];
	return (player);
}
