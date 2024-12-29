/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:10:37 by relamine          #+#    #+#             */
/*   Updated: 2024/12/26 05:21:21 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void load_textures(t_map *p_map)
{
	// printf("no = %s\n",p_map->textures);
    p_map->textures[0] = mlx_load_png(p_map->no);
    p_map->textures[1] = mlx_load_png(p_map->so);
    p_map->textures[2] = mlx_load_png(p_map->we);
    p_map->textures[3] = mlx_load_png(p_map->ea);
}


void map_render(t_map *p_map)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	p_map->mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!p_map->mlx)
		printf("Error\n"), exit(1);

	p_map->map_img = mlx_new_image(p_map->mlx, WIDTH, HEIGHT);
	if (!p_map->map_img || (mlx_image_to_window(p_map->mlx, p_map->map_img, 0, 0) < 0))
		printf("-Error\n"), exit(1);
	ft_memset(p_map->map_img->pixels, 100, p_map->map_img->width * p_map->map_img->height * sizeof(int32_t));
	// minimap(p_map, p_map->mlx);
	load_textures(p_map);

	raycasting(p_map, p_map->mlx, p_map->map_img);
	move_player(p_map, p_map->mlx);
	mlx_loop(p_map->mlx);
	mlx_delete_image(p_map->mlx, p_map->map_img);
	mlx_terminate(p_map->mlx);
}

