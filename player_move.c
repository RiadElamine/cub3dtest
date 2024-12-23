/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:55:56 by relamine          #+#    #+#             */
/*   Updated: 2024/12/16 22:24:13 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define speed 3

void keyfunc(mlx_key_data_t keydata, void* param)
{
	t_map	*p_map;
	int		x;
	int		y;
	int y2;
	int x2;

	p_map = (t_map*)param;
	if (keydata.key == MLX_KEY_W)
	{
		y = ((p_map->player.player->instances[0].y - speed) / p_map->cell_height) ;
		x = p_map->player.player->instances[0].x / p_map->cell_width;
		x2 = (p_map->player.player->instances[0].x + (p_map->cell_width / 2)) / p_map->cell_width;
		if (p_map->map[y][x] != '1' && p_map->map[y][x2] != '1')
			p_map->player.player->instances[0].y -= speed;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		y = ((p_map->player.player->instances[0].y + speed + (p_map->cell_height / 2)) / p_map->cell_height) ;
		x = p_map->player.player->instances[0].x / p_map->cell_width;
		x2 = (p_map->player.player->instances[0].x + (p_map->cell_width / 2)) / p_map->cell_width;
		if (p_map->map[y][x] != '1' && p_map->map[y][x2] != '1')
			p_map->player.player->instances[0].y += speed;
	}
	else if (keydata.key == MLX_KEY_A)
	{
		y = ((p_map->player.player->instances[0].y + (p_map->cell_height / 2)) / p_map->cell_height) ;
		y2 = p_map->player.player->instances[0].y / p_map->cell_height;
		x = (p_map->player.player->instances[0].x - speed) / p_map->cell_width;
		if (p_map->map[y][x] != '1' && p_map->map[y2][x] != '1')
			p_map->player.player->instances[0].x -= speed;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		y = ((p_map->player.player->instances[0].y + (p_map->cell_height / 2)) / p_map->cell_height) ;
		y2 = p_map->player.player->instances[0].y / p_map->cell_height;
		x = (p_map->player.player->instances[0].x + speed + (p_map->cell_width / 2)) / p_map->cell_width;
		if (p_map->map[y][x] != '1' && p_map->map[y2][x] != '1')
			p_map->player.player->instances[0].x += speed;
	}
}

void move_player(t_map *p_map, mlx_t* mlx)
{
	mlx_key_hook(mlx, keyfunc, p_map);
}
