/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/16 04:00:56 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/betterft/betterft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <stdbool.h>

# define SPRITES_DIR "sprites/"

typedef struct	s_so_long
{
	void	*mlx;
	void	*win;
}					t_so_long;

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

typedef struct	s_entity
{
	char	*name;
	t_pos	pos;
	t_anim	*anims;
	int		nb_anims;
	t_anim	current_anim;
	bool	anim_active;
	t_xpm	current_frame;
}					t_entity;

//	FROM FILE utils/entities.c
//		models of pre-existent entities

//		new_player: creates a new player
t_entity	*new_player(t_pos pos, t_so_long so_long);

//	FROM FILE utils/entity_builder.c
//		entity building utilities

//		new_entity:	creates a new entity
t_entity	*new_entity(char *name, t_pos pos, t_anim *anims, t_so_long so_long);
//		new_anim:	creates new animation sets
t_anim		new_anim(char *entity, char *anim_name, int nb_frames, t_so_long so_long);

//	FROM FILE utils/exit_handler.c
//		handles secure exits

//		secure_exit:	simple exit with code 0, frees garbage collector and closes window
int			secure_exit(t_so_long so_long);
//		error_exit:	simple exit with code 1, frees garbage collector and closes window
int			error_exit(t_so_long so_long);


#endif