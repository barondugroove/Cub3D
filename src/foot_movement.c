/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foot_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:06:29 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/27 16:37:58 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(int multi, t_player *player, char **map)
{
	if (!ft_strchr("123JAD" ,map[(int)player->posY]
		[(int)(player->posX + (player->dirX * MOVESPEED * multi))]))
		player->posX += (player->dirX * MOVESPEED) * multi;
	if (!ft_strchr("123JAD" ,map[(int)(player->posY + (player->dirY * MOVESPEED * multi))]
		[(int)player->posX]))
		player->posY += (player->dirY * MOVESPEED) * multi;
	//printf("\e[2AposX:%lf             \n", player->posX);
	//printf("posY:%lf              \n", player->posY);
}

void	strafe_player(int multi, t_player *player, char **map)
{
	if (!ft_strchr("123JAD" ,map[(int)player->posY]
		[(int)(player->posX + (player->planeX * MOVESPEED * multi))]))
		player->posX += (player->planeX * MOVESPEED) * multi;
	if (!ft_strchr("123JAD" ,map[(int)(player->posY + (player->planeY * MOVESPEED * multi))]
		[(int)player->posX]))
		player->posY += (player->planeY * MOVESPEED) * multi;
	//printf("\e[2AposX:%lf             \n", player->posX);
	//printf("posY:%lf              \n", player->posY);
}

void	rotate_player(int multi, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dirX;
	old_plane_x = player->planeX;
	player->dirX = player->dirX * cos(ROTSPEED * multi)
		- player->dirY * sin(ROTSPEED * multi);
	player->dirY = old_dir_x * sin(ROTSPEED * multi)
		+ player->dirY * cos(ROTSPEED * multi);
	player->planeX = player->planeX * cos(ROTSPEED * multi)
		- player->planeY * sin(ROTSPEED * multi);
	player->planeY = old_plane_x * sin(ROTSPEED * multi)
		+ player->planeY * cos(ROTSPEED * multi);
}

void	input_manager_foot(t_mlx *mlx)
{
	int	mult;

	mult = 1;
	if (mlx->player.inside != 0)
		mult = 2;
	if (mlx->player.up == 1)
		move_player(-500 * mult, &mlx->player, mlx->map);
	if (mlx->player.down == 1)
		move_player(750 * mult, &mlx->player, mlx->map);

	if (mlx->player.rot_l == 1)
		rotate_player(-5000, &mlx->player);
	if (mlx->player.rot_r == 1)
		rotate_player(5000, &mlx->player);

	if (mlx->player.left == 1)
		strafe_player(-300 * mult, &mlx->player, mlx->map);
	if (mlx->player.right == 1)
		strafe_player(300 * mult, &mlx->player, mlx->map);


	int mouse_x = 0;
	int mouse_y = 0;

	mlx_mouse_get_pos(mlx->mlx, mlx->win, &mouse_x, &mouse_y);
	rotate_player((WIN_W / 2 - mouse_x) * 100, &mlx->player);
	mlx_mouse_move(mlx->mlx, mlx->win, WIN_W / 2, WIN_H / 2);
}
