/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/15 19:37:32 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

// Colors
# define SKYCOLOR 0x2faee0
# define FLOORCOLOR 0xFFECD1//0x000000//0xFFECD1

# define CEILINGCOLOR 0xc4c4c4
# define IN_FLOORCOLOR 0xc4c4c4


# define FOV 0.8
# define FPS 60

// Screen size
# define WIN_W 1024
# define WIN_H 768

// Movement
# define MOVESPEED 0.00001//0.05
# define ROTSPEED 0.000005


# define CRASH_SPEED 750

enum e_keycode
{
	KEY_W = 115,
	KEY_S = 119,
	KEY_A = 97,
	KEY_D = 100,
	KEY_Q = 113,
	KEY_E = 101,
	KEY_F = 102,
	KEY_M = 109,
	KEY_ARROW_L = 65361,
	KEY_ARROW_R = 65363,
	ESC = 0xFF1B
};


//
//		STRUCTS
typedef struct s_raycast {
	//what cardinal point the raycast hit is perpendicular to
	int		side;


	//what type of wall the ray has hit
	int		wall_type;

	//what direction to step in x or y-direction (either +1 or -1)
	int		stepX;
	int		stepY;

	double	raydirX;
	double	raydirY;

	//which box of the map we're in
	int		mapX;
	int		mapY;


	int		tex_x;

	//length of ray from current position to next x or y-side
	double	sideDistX;
	double	sideDistY;
	double	DeltaDistX;
	double	DeltaDistY;
}				t_raycast;

typedef struct s_player {
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;

	//SAVES
	double	planeX_save;
	double	planeY_save;
	double	dirX_save;
	double	dirY_save;
	double	posX_save;
	double	posY_save;

	double speed;
	int	inside;
	int	biking;
	int	using;
	int	rot_l;
	int rot_r;
	int left;
	int right;
	int up;
	int down;

}				t_player;

typedef struct s_display {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		tex_width;
	int		tex_height;
}				t_display;

typedef struct s_mlx {
	void		*mlx;
	void		*win;
	char		**map;
	char		*mapname;
	int			map_y;
	int			map_x;
	int			started;
	int			crashed;
	t_display	display;
	t_player	player;

	t_display	in_wall;
	t_display	texture;
	t_display	texture2;
	t_display	crash;
	t_display	bike;
	t_display	bike_wheel;

}				t_mlx;

//
//		PARSING
void	check_map_ext(t_mlx *v);
char	**create_map(t_mlx *mlx);
void	place_player_on_map(t_mlx *mlx, char **map);


//
//		MOVEMENT
void	input_manager_foot(t_mlx *mlx);
void	input_manager_bike(t_mlx *mlx);
void	rotate_player(int multi, t_player *player);

//
//		INPUTS
int		key_press(int key, t_mlx *mlx);
int		key_release(int key, t_mlx *mlx);
int		input_manager(t_mlx *mlx);

//
//		RENDER
int		frames(t_mlx *mlx);
void	ft_display(t_mlx *mlx);

//
//		SCREENS
void	start_screen(t_mlx *mlx);
void	crash_screen(t_mlx *mlx);
void	draw_backdrop(t_mlx *mlx);



void	free_map(t_mlx *mlx, char **map);

//
//		MLX
void	my_mlx_pixel_put(t_display *data, int x, int y, int color);
int		my_mlx_get_color(t_display *texture, int x, int y);
void	put_img_transp(t_mlx *mlx, t_display img, int pad_x, int pad_y);
void	exit_game(t_mlx *mlx);


#endif
