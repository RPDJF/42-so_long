/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:49:48 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/21 18:48:59 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_entity	new_player(t_pos pos, t_so_long *so_long)
{
	t_entity	player;
	t_anim		*anims;
	char		*name;

	name = ft_strdup("player");
	if (!name)
		crash_exit(so_long);
	player = new_entity(name, pos, 0);
	player.nb_anims = 4;
	anims = galloc(sizeof(t_anim) * player.nb_anims);
	if (!anims)
		crash_exit(so_long);
	player.anims = anims;
	anims[LEFT] = new_anim(player.name, "left", 4, so_long);
	anims[RIGHT] = new_anim(player.name, "right", 4, so_long);
	anims[UP] = new_anim(player.name, "up", 4, so_long);
	anims[DOWN] = new_anim(player.name, "down", 4, so_long);
	player.current_anim = anims[1];
	player.current_frame = 0;
	return (player);
}
