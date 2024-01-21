/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 18:47:27 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/21 18:48:26 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	animate(t_entity *entity, int anim_idx)
{
	entity->current_anim = entity->anims[anim_idx];
	entity->current_frame++;
	entity->current_frame %= entity->current_anim.nb_frames;
}
