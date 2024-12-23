/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:54:27 by relamine          #+#    #+#             */
/*   Updated: 2024/12/17 19:13:46 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_player(t_map *p_map, mlx_t* mlx)
{
	mlx_image_t*	player;
	int				player_width;
	int				player_height;
	int				x;
	int				y;

	player_width = (p_map->cell_width / 2);
	player_height = (p_map->cell_height / 2);
	player = mlx_new_image(mlx, player_width, player_height);
	if (!player || (mlx_image_to_window(mlx, player, (p_map->player.x *  p_map->cell_width),
		(p_map->player.y * p_map->cell_height)) < 0))
		printf("wError\n"), exit(1);
	y = 0;
	while (y < player_height)
	{
		x = 0;
		while (x < player_width)
		{
			mlx_put_pixel(player, x, y, get_rgba(241, 196, 15, 255));
			x++;
		}
		y++;
	}
	p_map->player.player = player;
}

int get_max_width(t_map *p_map)
{
	int	max;
	int	y;
	int	x_map;

	max = 0;
	y = 0;
	while (y < ft_count(p_map->map))
	{
		x_map = ft_strlen(p_map->map[y]);
		if (x_map > max)
			max = x_map;
		y++;
	}
	return (max);
}

void draw_minimap_cell(t_map *p_map, mlx_image_t*img, int x, int y)
{
    int color;
    int y_map;
    int x_map;
	int x_pixel;
	int y_pixel;

	color = get_cell_color(p_map, x, y);
	y_map =0;
	while (y_map < p_map->cell_height)
	{
		x_map = 0;
		while (x_map < p_map->cell_width)
		{
			x_pixel = x * p_map->cell_width + x_map;
			y_pixel = y * p_map->cell_height + y_map;
			if ((x_map == 0 || y_map == 0 || y_map == p_map->cell_height
				|| x_map == p_map->cell_width) && p_map->map[y][x] != ' ')
				mlx_put_pixel(img, x_pixel, y_pixel, get_rgba(0, 0, 0, 100));
			else
				mlx_put_pixel(img, x_pixel, y_pixel, color);
			x_map++;
		}
		y_map++;
	}
}

void draw_minimap(t_map *p_map, mlx_image_t* img)
{
	int y;
	int x;
	int map_height;
	int map_width;

	map_height = ft_count(p_map->map);
	p_map->cell_width = M_WIDTH / get_max_width(p_map);
	p_map->cell_height = M_HEIGHT / map_height;
	y = 0;
	while (y < map_height)
	{
		map_width = ft_strlen(p_map->map[y]);
		x = 0;
		while (x < map_width)
		{
			draw_minimap_cell(p_map, img, x, y);
			x++;
		}
		y++;
	}
	return ;
}

void minimap(t_map *p_map, mlx_t* mlx)
{
	mlx_image_t* minimap = mlx_new_image(mlx, M_WIDTH, M_HEIGHT);
	if (!minimap || (mlx_image_to_window(mlx, minimap, 0, 0) < 0))
		printf("*Error\n"), exit(1);

	draw_minimap(p_map, minimap);
	
	render_player(p_map, mlx);
}
