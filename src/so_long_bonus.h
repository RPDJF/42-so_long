/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:57 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/27 13:07:09 by rude-jes         ###   ########.fr       */
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
#  include "../libs/minilibx-linux/mlx_int.h"
# endif

// directions
# define LEFT 0
# define RIGHT 1
# define UP 2
# define DOWN 3

// config
# define WHITE 0xffffff
# define MAP_FORMAT "01CEPM"

// macros
# define GRID 19
# define SPRITES_DIR "sprites_bonus/"
# define TEXTURES_DIR "textures_bonus/"

// messages
# define NB_MOVES "number of movements:  "
# define NB_SCORE "current score :       "

// err messages
# define TOO_MUCH_ARG "Too much arguments"
# define NOT_ENOUGH_ARGS "Not enough arguments"
# define ERR_MAP "Error\n"
# define ERR_MAP_FORMAT "Error\nMap is not using the correct format \"01CEPM\""
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
	int		direction;
	t_pos	pos;
	t_anim	*anims;
	int		nb_anims;
	t_anim	current_anim;
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
	bool		is_over;
	int			score;
	int			collectibles;
	int			moves;
	void		*mlx;
	void		*win;
	t_map		*map;
	t_entity	player;
	t_entity	*enemies;
	size_t		nb_enemies;
}				t_so_long;

//	FROM FILE utils_bonus/enemies_ia_bonus.c

//		get_dir:	set and return next position for enemy
int			get_dir(t_so_long *so_long, t_entity *enemy);

//	FROM FILE utils_bonus/engine_bonus.c

//		movement_handler:	handles player movements
int			movement_handler(t_so_long *so_long, t_entity *entity);
//		teleport_handler:	handles entities teleportation
int			teleport_handler(t_so_long *so_long, t_entity *e);
//		events_handler:		handles events
void		events_handler(t_so_long *so_long);

//	FROM FILE utils_bonus/entities_bonus.c
//		models of pre-existent entities

//		new_player: creates a new player
t_entity	new_player(t_pos pos, t_so_long *so_long);
//		new_enemy: creates a new enemy
t_entity	new_enemy(t_pos pos, t_so_long *so_long);

//	FROM FILE utils_bonus/entities_utils_bonus.c

//		load_enemies:	creates an instance of each enemy in t_so_long
void		load_enemies(t_so_long *so_long, t_pos pos);
//		animate:	play next frame of entity animaion index
void		animate(t_entity *entity, int anim_idx);
//		foreach_entities:	iterate function f for each entity in entities
void		foreach_entities(int (*f)(t_so_long *, t_entity *),
				t_so_long *so_long, t_entity *entities, size_t size);

//	FROM FILE utils_bonus/entity_builder_bonus.c
//		entity building utilities

//		new_entity:	creates a new entity
t_entity	new_entity(char *name, t_pos pos, t_anim *anims);
//		new_anim:	creates new animation sets
t_anim		new_anim(char *entity, char *anim, int nb_frames, t_so_long *sl);

//	FROM FILE utils_bonus/exit_handler_bonus.c
//		handles secure exits

//		secure_exit:	simple exit with code 0, frees garbage collector and
//		closes window
int			secure_exit(void *param);
//		error_exit:	simple exit with code 1, frees garbage collector and
//		closes window
int			error_exit(void *param);
//		crash_exit:	exit on non-handling crashes like bad memory allocations
int			crash_exit(void *param);
//		map_error_handler:	exit with specific messages in case of map error
void		map_error_handler(t_so_long *so_long, int status);

//	FROM FILE utils_bonus/game_renderer_bonus.c

//		render_map: Draws the map to the mlx window
void		render_map(t_so_long *so_long);
//		render_entities:	Draws all of the entities, including player
void		render_entities(t_so_long *so_long);
//		render_entities:	Render map & entities, including player
int			render_all(void *param);

//	FROM FILE utils_bonus/map_checker_utils_bonus.c

//		check_map_name:	tests name of the map, exit on wrong filename
void		check_map_name(t_so_long *so_long, char *filename);

//	FROM FILE utils_bonus/map_checker_bonus.c

//		map_checker:	tests the map, return 0 if correct
//		returns 1 if invalid format
//		returns 2 if invalid shape
//		returns 3 if invalid nb elements (P==1, E==1, C>=1)
//		returns 4 if impossible map
int			map_checker(t_so_long *so_long, t_map *map);

//	FROM FILE utils_bonus/map_parser_bonus.c

//		load_map:	load mapfile as char 2D array, returns 0 on map error
t_map		*get_map(t_so_long *so_long, char *filename);
//		reset_map:	Reset start and end position
void		reset_map(t_map *map);
//		init_map:	Set properties of t_map struct (reset_map first !!)
int			init_map(t_so_long *so_long);

//	FROM FILE utils_bonus/mlx_wrapper_bonus.c

//		load_mpx:	Load mpx img and add it to the betterft garbage collector
void		*load_xpm(t_so_long *so_long, char *file, int *width, int *height);

//	FROM FILE utils_bonus/pathfinding_bonus.c

//		get_path:	Returns RIGHT LEFT UP or DOWN if possible, -1 if not
int			get_path(t_so_long *so_long, t_pos p1, t_pos p2);

#endif