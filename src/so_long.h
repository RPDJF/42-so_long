/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/16 01:21:25 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/betterft/betterft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <stdbool.h>

# define SPRITES_DIR "../sprites/"

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}					t_data;

typedef struct	s_xpm
{
	void	*img;
	int		width;
	int		height;
}					t_xpm;

typedef struct	s_pos
{
	int	x;
	int	y;
}					t_pos;

typedef struct	s_anim
{
	char	*name;
	int		nb_frames;
	t_xpm	*frames;
}					t_anim;

//	For characters entities, we assume that anim 0 = right, 1 = left, 2 = up, 3 = down
typedef struct	s_entity
{
	char	*name;
	t_pos	pos;
	t_anim	*anims;
	int		nb_anims;
	t_anim	current_anim;
	bool	anim_active;
	int		current_frame;
}					t_entity;

//	FROM FILE utils/entities.c
//		models of pre-existent entities

//		new_player: creates a new player
t_entity 	*new_player(t_pos pos, void *mlx);


//	FROM FILE utils/entity_builder.c
//		entity building utilities

//		new_entity:	creates a new entity
t_entity	*new_entity(char *name, t_pos pos, t_anim *anims);
//		new_animation:	creates new animation sets
t_anim		new_animation(char *sprite_name, char *anim_name, int nb_frames, void *mlx);


//	FROM FILE utils/exit_handler.c
//		handles secure exits
void		secure_exit(int code);

#endif