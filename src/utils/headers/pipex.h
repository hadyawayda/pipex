/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:35:39 by hawayda           #+#    #+#             */
/*   Updated: 2024/08/31 05:09:13 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 48

# include "ft_printf.h"
# include "libft.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

typedef struct s_image
{
	void	*img_ptr;
	int		width;
	int		height;
}			t_image;

typedef struct s_enemy
{
	int		x;
	int		y;
	int		direction;
}			t_enemy;

typedef struct s_game
{
	char	**map;
	void	*mlx_ptr;
	void	*window;
	void	*img_wall;
	t_image	img_player[6];
	t_image	img_enemy[6];
	t_enemy	enemy;
	void	*img_collectible;
	void	*img_exit;
	void	*img_empty;
	int		player_y;
	int		player_x;
	int		map_width;
	int		map_height;
	int		collectibles;
	int		collected;
	int		moves;
	int		keys[65565];
}			t_game;

int			update(t_game *game);
int			close_game(t_game *game);
int			move_enemy(t_game *game);
int			validate_map(t_game *game);
int			check_path_to_exit(t_game *game);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
int			parse_map_lines(char *file, t_game *game);
int			handle_keypress(int keycode, t_game *game);

void		load_game(t_game *game);
void		render_map(t_game *game);
void		cleanup_game(t_game *game);
void		load_textures(t_game *game);
void		display_move_count(t_game *game);
void		initialize_player_position(t_game *game);
void		move_player(t_game *game, int new_x, int new_y);

#endif