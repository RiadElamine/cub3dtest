/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:04:36 by relamine          #+#    #+#             */
/*   Updated: 2024/12/30 10:43:38 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_map(t_map **p_map)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (printf("Error\n"), exit(1), (void)0);
	map->f.r = -1;
	map->f.g = -1;
	map->f.b = -1;
	map->c.r = -1;
	map->c.g = -1;
	map->c.b = -1;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->map = NULL;
	map->fd = -1;
	*p_map = map;
}

void free_map(t_map *map)
{
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->map)
		ft_free(map->map);
	if (map->fd != -1)
		close(map->fd);
	if (map->map_img)
		mlx_delete_image(map->mlx, map->map_img);
	if (map->player.player)
		mlx_delete_image(map->mlx, map->player.player);
	if (map->mlx)
		mlx_terminate(map->mlx);
	if (map->textures[0])
		mlx_delete_texture(map->textures[0]);
	if (map->textures[1])
		mlx_delete_texture(map->textures[1]);
	if (map->textures[2])
		mlx_delete_texture(map->textures[2]);
	if (map->textures[3])
		mlx_delete_texture(map->textures[3]);
	free(map);
}

void get_posplayer(t_map *p_map, int i, int j)
{
	if (p_map->map[i][j] == 'N')
		p_map->player.rot_angle = 3 * M_PI / 2;
	if (p_map->map[i][j] == 'S')
		p_map->player.rot_angle = M_PI / 2;
	if (p_map->map[i][j] == 'W')
		p_map->player.rot_angle = M_PI;
	if (p_map->map[i][j] == 'E')
		p_map->player.rot_angle = 0;
	p_map->player.x = j;
	p_map->player.y = i;
	p_map->player.y_double = p_map->player.y * TILE_SIZE + TILE_SIZE / 2.0;
    p_map->player.x_double = p_map->player.x * TILE_SIZE + TILE_SIZE / 2.0;
	p_map->player.walk_dir = 0;
	p_map->player.walk_side = 0;
	p_map->player.turn_dir = 0;
	p_map->player.walk_speed = 2.0;
	p_map->player.turn_speed = 1 * (M_PI / 180);
	p_map->x_inter = -1;
	p_map->y_inter = -1;
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int get_cell_color(t_map *p_map, int x, int y)
{
    int color;

    if (p_map->map[y][x] == '1')
        color = get_rgba(255, 255, 255, 255);
    else if (p_map->map[y][x] == ' ')
        color = get_rgba(100, 100, 100, 0);
    else
        color = get_rgba(0, 0, 0, 100);

    return color;
}
