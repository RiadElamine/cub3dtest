/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:10:37 by relamine          #+#    #+#             */
/*   Updated: 2024/12/17 20:07:37 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void map_render(t_map *p_map)
{
	mlx_image_t*	map;
	mlx_t*			mlx;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		printf("Error\n"), exit(1);

	map = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!map || (mlx_image_to_window(mlx, map, 0, 0) < 0))
		printf("-Error\n"), exit(1);

	ft_memset(map->pixels, 100, map->width * map->height * sizeof(int32_t));

		minimap(p_map, mlx);
		move_player(p_map, mlx);
		raycasting(p_map, mlx, map);
		mlx_loop(mlx);
		mlx_terminate(mlx);
	
}
