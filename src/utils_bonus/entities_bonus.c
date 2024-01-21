/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:49:48 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/21 04:54:34 by rude-jes         ###   ########.fr       */
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
	anims[LEFT] = new_anim(player.name, "left", 4, so_long);
	anims[RIGHT] = new_anim(player.name, "right", 4, so_long);
	anims[UP] = new_anim(player.name, "up", 4, so_long);
	anims[DOWN] = new_anim(player.name, "down", 4, so_long);
	player.current_anim = anims[1];
	player.current_frame = 0;
	return (player);
}

static char	*get_entity_color(t_so_long *so_long, char *name)
{
	char			*color;
	static int		id;

	id = id % 4;
	color = 0;
	if (id == 0)
		color = ft_strjoin("red_", name);
	else if (id == 1)
		color = ft_strjoin("blue_", name);
	else if (id == 2)
		color = ft_strjoin("pink_", name);
	else if (id == 3)
		color = ft_strjoin("orange_", name);
	if (!color)
		crash_exit(so_long);
	id++;
	return (color);
}

t_entity	new_enemy(t_pos pos, t_so_long *so_long)
{
	t_entity		enemy;
	t_anim			*anims;
	char			*name;
	char			*color;

	name = ft_strdup("enemy");
	if (!name)
		crash_exit(so_long);
	enemy = new_entity(name, pos, 0);
	enemy.nb_anims = 2;
	anims = galloc(sizeof(t_anim) * enemy.nb_anims);
	if (!anims)
		crash_exit(so_long);
	enemy.anims = anims;
	color = get_entity_color(so_long, enemy.name);
	anims[LEFT] = new_anim(color, "left", 4, so_long);
	anims[RIGHT] = new_anim(color, "right", 4, so_long);
	gfree(color);
	enemy.current_anim = anims[0];
	enemy.current_frame = 0;
	enemy.direction = UP;
	return (enemy);
}
