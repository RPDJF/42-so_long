/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:49:48 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/20 16:55:07 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

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
	anims[0] = new_anim("player", "left", 4, so_long);
	anims[1] = new_anim("player", "right", 4, so_long);
	anims[2] = new_anim("player", "up", 4, so_long);
	anims[3] = new_anim("player", "down", 4, so_long);
	player.current_anim = anims[1];
	player.current_frame = 0;
	return (player);
}

t_entity	new_enemy(t_pos pos, t_so_long *so_long)
{
	t_entity	enemy;
	t_anim		*anims;
	char		*name;

	name = ft_strdup("enemy");
	if (!name)
		crash_exit(so_long);
	enemy = new_entity(name, pos, 0);
	enemy.nb_anims = 1;
	anims = galloc(sizeof(t_anim) * enemy.nb_anims);
	if (!anims)
		crash_exit(so_long);
	enemy.anims = anims;
	anims[0] = new_anim("enemy", "right", 4, so_long);
	enemy.current_anim = anims[0];
	enemy.current_frame = 0;
	enemy.direction = UP;
	return (enemy);
}
