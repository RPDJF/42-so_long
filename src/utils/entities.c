/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:49:48 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/16 03:28:55 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_entity	*new_player(t_pos pos, void *mlx)
{
	t_entity	*player;
	t_anim		*anims;
	char		*name;

	name = ft_strdup("player");
	if (!name)
		secure_exit(1);
	player = new_entity(name, pos, 0);
	player->nb_anims = 2;
	anims = galloc(sizeof(t_anim) * player->nb_anims);
	if (!anims)
		secure_exit(1);
	player->anims = anims;
	anims[0] = new_anim("player", "right", 3, mlx);
	anims[1] = new_anim("player", "left", 3, mlx);
	player->current_anim = anims[0];
	return (player);
}
