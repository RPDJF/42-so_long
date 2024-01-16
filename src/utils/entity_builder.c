/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:46:01 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/16 03:30:20 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

t_entity	*new_entity(char *name, t_pos pos, t_anim *anims)
{
	t_entity	*entity;

	entity = galloc(sizeof(t_entity));
	if (!entity)
		secure_exit(1);
	entity->name = name;
	entity->pos.x = pos.x;
	entity->pos.y = pos.y;
	entity->anims = anims;
	return (entity);
}

static t_xpm	*fetch_frames(char *base_filename, int nb_frames, void *mlx)
{
	t_xpm	*frames;
	char	*filename;
	char	*tmp;
	int		i;

	frames = galloc(sizeof(t_xpm) * nb_frames);
	if (!frames)
		secure_exit(1);
	i = -1;
	while (i++, i < nb_frames)
	{
		tmp = ft_itoa(i);
		if (!tmp)
			secure_exit(1);
		filename = ft_strreplace(base_filename, "{id}", tmp);
		if (!filename)
			secure_exit(1);
		frames[i].img = mlx_xpm_file_to_image(mlx, filename,
				&(frames->width), &(frames->height));
	}
	return (frames);
}

t_anim	new_anim(char *entity, char *anim_name, int nb_frames, void *mlx)
{
	t_anim	anim;
	char	*xpm_filename;

	anim.nb_frames = nb_frames;
	anim.name = ft_strdup(sprite_name);
	if (!anim.name)
		secure_exit(1);
	xpm_filename = ft_strjoin(SPRITES_DIR, sprite_name);
	if (!xpm_filename)
		secure_exit(1);
	xpm_filename = ft_strjoin(xpm_filename, "/");
	if (!xpm_filename)
		secure_exit(1);
	xpm_filename = ft_strjoin(xpm_filename, anim_name);
	if (!xpm_filename)
		secure_exit(1);
	xpm_filename = ft_strjoin(xpm_filename, "-{id}.xpm");
	if (!xpm_filename)
		secure_exit(1);
	anim.frames = fetch_frames(xpm_filename, nb_frames, mlx);
	return (anim);
}
