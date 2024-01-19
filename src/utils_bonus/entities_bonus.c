/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:49:48 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/19 02:30:08 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

t_entity	*new_player(t_pos pos, t_so_long *so_long)
{
	t_entity	*player;
	t_anim		*anims;
	char		*name;

	name = ft_strdup("player");
	if (!name)
		crash_exit(so_long);
	player = new_entity(name, pos, 0, so_long);
	player->nb_anims = 4;
	anims = galloc(sizeof(t_anim) * player->nb_anims);
	if (!anims)
		crash_exit(so_long);
	player->anims = anims;
	anims[0] = new_anim("player", "left", 4, so_long);
	anims[1] = new_anim("player", "right", 4, so_long);
	anims[2] = new_anim("player", "up", 4, so_long);
	anims[3] = new_anim("player", "down", 4, so_long);
	player->current_anim = anims[1];
	player->current_frame = 0;
	return (player);
}

t_entity	*new_red(t_pos pos, t_so_long *so_long)
{
	t_entity	*red;
	t_anim		*anims;
	char		*name;

	name = ft_strdup("red");
	if (!name)
		crash_exit(so_long);
	red = new_entity(name, pos, 0, so_long);
	red->nb_anims = 1;
	anims = galloc(sizeof(t_anim) * red->nb_anims);
	if (!anims)
		crash_exit(so_long);
	red->anims = anims;
	anims[0] = new_anim("red", "right", 4, so_long);
	red->current_anim = anims[0];
	red->current_frame = 0;
	return (red);
}
