/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:47:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/21 23:35:25 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

void	load_enemies(t_so_long *so_long, t_pos pos)
{
	so_long->enemies = ft_reallocf(so_long->enemies,
			so_long->nb_enemies * sizeof(t_entity),
			(so_long->nb_enemies + 1) * sizeof(t_entity));
	so_long->enemies[so_long->nb_enemies] = new_enemy(pos, so_long);
	so_long->nb_enemies++;
}

void	animate(t_entity *entity, int anim_idx)
{
	entity->current_anim = entity->anims[anim_idx];
	entity->current_frame++;
	entity->current_frame %= entity->current_anim.nb_frames;
}

void	foreach_entities(int (*f)(t_so_long *, t_entity *),
			t_so_long *so_long, t_entity *entities, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		f(so_long, &entities[i++]);
}
