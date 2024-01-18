/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:46:01 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/18 00:09:27 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_entity	*new_entity(char *name, t_pos pos, t_anim *anims, t_so_long *sl)
{
	t_entity	*entity;

	entity = galloc(sizeof(t_entity));
	if (!entity)
		error_exit(sl);
	entity->name = name;
	entity->pos.x = pos.x;
	entity->pos.y = pos.y;
	entity->anims = anims;
	return (entity);
}

static t_xpm	*fetch_frames(char *base_filename, int nb_frames, t_so_long *sl)
{
	t_xpm	*frames;
	char	*filename;
	char	*tmp;
	int		i;

	frames = galloc(sizeof(t_xpm) * nb_frames);
	if (!frames)
		error_exit(sl);
	i = -1;
	while (i++, i < nb_frames)
	{
		tmp = ft_itoa(i);
		if (!tmp)
			error_exit(sl);
		filename = ft_strreplace(base_filename, "{id}", tmp);
		if (!filename)
			error_exit(sl);
		frames[i].img = mlx_xpm_file_to_image(sl->mlx, filename,
				&(frames->width), &(frames->height));
	}
	return (frames);
}

t_anim	new_anim(char *entity, char *anim_name, int nb_frames, t_so_long *sl)
{
	t_anim	anim;
	char	*xpm_filename;

	anim.nb_frames = nb_frames;
	anim.name = ft_strdup(entity);
	if (!anim.name)
		error_exit(sl);
	xpm_filename = ft_strjoin(SPRITES_DIR, entity);
	if (!xpm_filename)
		error_exit(sl);
	xpm_filename = ft_strjoin(xpm_filename, "/");
	if (!xpm_filename)
		error_exit(sl);
	xpm_filename = ft_strjoin(xpm_filename, anim_name);
	if (!xpm_filename)
		error_exit(sl);
	xpm_filename = ft_strjoin(xpm_filename, "-{id}.xpm");
	if (!xpm_filename)
		error_exit(sl);
	anim.frames = fetch_frames(xpm_filename, nb_frames, sl);
	return (anim);
}
