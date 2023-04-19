/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:32:57 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/19 17:57:52 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D_bonus.h"

void	init_tex(t_mlx *mlx, t_display *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx->mlx, path,
			&tex->tex_width, &tex->tex_height);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
}

void	error_message(char *msg, char *line)
{
	ft_putstr_fd("Error.\n", 2);
	ft_putstr_fd(msg, 2);
	if (line)
		ft_putstr_fd(line, 2);
}

void	exit_game_light(t_mlx *mlx, char **data)
{
	(void)mlx;
	if (data)
		free_map(data);
	exit(1);
}

//Ft_parsing but doesn't init structs and all
void	ft_change_map(t_mlx *mlx)
{
	char	**data;

	check_map_ext(mlx);
	data = get_data_from_file(mlx);
	check_assets(mlx, data);
	fetch_assets(mlx, data);
	free_map(data);
}