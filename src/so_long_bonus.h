/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <ruipaulo.unify@outlook.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/18 23:56:22 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libs/betterft/betterft.h"
# include <stdbool.h>
# include <pthread.h>

// compatibility checker
# ifdef __APPLE__
#  include "../libs/minilibx_opengl/mlx.h"
# endif

# ifndef __APPLE__
#  include "../libs/minilibx-linux/mlx.h"
# endif

// directions
# define LEFT 0
# define RIGHT 1
# define UP 2
# define DOWN 3

// macros
# define GRID 19
# define SPRITES_DIR "sprites/"
# define TEXTURES_DIR "textures/"

// messages
# define NB_MOVES "number of movements"

// err messages
# define TOO_MUCH_ARG "Too much arguments"
# define NOT_ENOUGH_ARGS "Not enough arguments"
# define ERR_MAP "Error\n"
# define ERR_MAP_FORMAT "Error\nMap is not using the correct format \"01PCE\""
# define ERR_MAP_SHAPE "Error\nMap has an invalid shape"
# define ERR_MAP_ELEMENTS "Error\nMap elements must to contain 1 Player, \
1 Exit and at least 1 Collectible"
# define ERR_MAP_IMPOSSIBLE "Error\nMap is impossible"
# define ERR_MAP_EXTENSION "Error\nthe map have not .ber extension"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_xpm
{
	void	*img;
	int		width;
	int		height;
}			t_xpm;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_anim
{
	char	*name;
	int		nb_frames;
	t_xpm	*frames;
}			t_anim;

typedef struct s_entity
{
	char	*name;
	t_pos	pos;
	t_anim	*anims;
	int		nb_anims;
	t_anim	current_anim;
	bool	anim_active;
	int		current_frame;
}			t_entity;

typedef struct s_map
{
	char	**data;
	int		score_remain;
	t_pos	start;
	t_pos	end;
	int		height;
	int		width;
	t_xpm	wall;
	t_xpm	path;
	t_xpm	score;
	t_xpm	exit;
}			t_map;

typedef struct s_so_long
{
	int			score;
	int			collectibles;
	int			moves;
	void		*mlx;
	void		*win;
	t_map		*map;
	t_entity	*player;
	int			player_direction;
	pthread_t	ticks;
}				t_so_long;

//	FROM FILE utils/entities.c
//		models of pre-existent entities

//		new_player: creates a new player
t_entity	*new_player(t_pos pos, t_so_long *so_long);

//	FROM FILE utils/entity_builder.c
//		entity building utilities

//		new_entity:	creates a new entity
t_entity	*new_entity(char *name, t_pos pos, t_anim *anims, t_so_long *sl);
//		new_anim:	creates new animation sets
t_anim		new_anim(char *entity, char *anim, int nb_frames, t_so_long *sl);

//	FROM FILE utils/exit_handler.c
//		handles secure exits

//		secure_exit:	simple exit with code 0, frees garbage collector and
//		closes window
int			secure_exit(void *param);
//		error_exit:	simple exit with code 1, frees garbage collector and
//		closes window
int			error_exit(void *param);
int			crash_exit(void *param);

//	FROM FILE utils/game_renderer.c

//		render_map: Draws the map to the mlx window
void		render_map(t_so_long *so_long);
//		render_entities:	Draws all of the entities, including player
void		render_entities(t_so_long *so_long);
//		render_entities:	Render map & entities, including player
int			render_all(void *param);

//	FROM FILE utils/map_checker_utils.c

//		check_map_name:	tests name of the map, exit on wrong filename
void		check_map_name(char *filename);

//	FROM FILE utils/map_checker.c

//		map_checker:	tests the map, return 0 if correct
//		returns 1 if invalid format
//		returns 2 if invalid shape
//		returns 3 if invalid nb elements (P==1, E==1, C>=1)
//		returns 4 if impossible map
int			map_checker(t_so_long *so_long, t_map *map);

//	FROM FILE utils/map_parser.c

//		load_map:	load mapfile as char 2D array, returns 0 on map error
t_map		*get_map(t_so_long *so_long, char *filename);
//		init_map:	Set properties of t_map struct
int			init_map(t_map *map);

//	FROM FILE utils/path_checker.c

//		check_path:	Check if path is possible between 2 t_pos positions
int			check_path(t_so_long *so_long, t_map *map, t_pos pos1, t_pos pos2);

#endif