/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2023/02/02 23:56:43 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map_dimension(t_mlx *mlx)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(mlx->mapname, 0);
	if (fd == -1)
	{
		ft_printf("Error\nProblem with mapname", "%s");
		exit (0);
	}
	line = get_next_line(fd);
	mlx->map_x = ft_strlen(line) - 1;
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}

void	print_map(char **map)
{
	int	y;

	y = -1;
	ft_printf("map:\n");
	while (map[++y])
		ft_printf("%s\n", map[y]);
	ft_printf("\n\n\n");
}

char	**create_map(t_mlx *mlx)
{
	char	**map;
	char	*buf;
	int		fd;
	int		y;
	int		x;

	y = -1;
	mlx->map_y = get_map_dimension(mlx);
	fd = open(mlx->mapname, 0);
	map = malloc(sizeof(int *) * (mlx->map_y + 1));
	while (++y < mlx->map_y)
	{
		buf = get_next_line(fd);
		map[y] = malloc(sizeof(int) * (ft_strlen(buf) + 1));
		if (!buf)
			break;
		x = -1;
		while (++x < mlx->map_x - 1)
			map[y][x] = buf[x];


		map[y][x] = '\0';
				
		free(buf);
	}
	map[y] = NULL;
	close(fd);

	print_map(map);

	return (map);
}
