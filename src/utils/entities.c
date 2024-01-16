/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:49:48 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/16 04:01:25 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_entity	*new_player(t_pos pos, t_so_long so_long)
{
	t_entity	*player;
	t_anim		*anims;
	char		*name;

	name = ft_strdup("player");
	if (!name)
		error_exit(so_long);
	player = new_entity(name, pos, 0, so_long);
	player->nb_anims = 2;
	anims = galloc(sizeof(t_anim) * player->nb_anims);
	if (!anims)
		error_exit(so_long);
	player->anims = anims;
	anims[0] = new_anim("player", "right", 3, so_long);
	anims[1] = new_anim("player", "left", 3, so_long);
	player->current_anim = anims[0];
	return (player);
}
