/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:35:21 by saharchi          #+#    #+#             */
/*   Updated: 2024/12/23 02:26:21 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double get_horizontal(t_map *p_map, double ray_angle)
{
    double x_inter, y_inter;
    double x_step, y_step;

    // Player position in pixels
    double x_player_pixel = p_map->player.x * TILE_SIZE + TILE_SIZE / 2;
    double y_player_pixel = p_map->player.y * TILE_SIZE + TILE_SIZE / 2;

    // Determine ray direction
    if (ray_angle > 0 && ray_angle < M_PI)
        y_step = TILE_SIZE; // Facing down
    else
        y_step = -TILE_SIZE; // Facing up

    y_inter = y_player_pixel / TILE_SIZE * TILE_SIZE;
    if (y_step > 0)
        y_inter += TILE_SIZE; // Adjust for rays facing down

    x_inter = x_player_pixel + (y_inter - y_player_pixel) / tan(ray_angle);
	
	if (x_inter < 0)
		x_inter = 0;
	
    x_step = y_step / tan(ray_angle);

    // Iterate through the grid
    while (1)
    {
        int map_x = (int)(x_inter / TILE_SIZE);
        int map_y = (int)(y_inter / TILE_SIZE);

        // Boundary and wall collision checks
        if (map_y < 0 || map_y >= ft_count(p_map->map) ||
            map_x < 0 || (size_t)map_x >= ft_strlen(p_map->map[map_y]) ||
            p_map->map[map_y][map_x] == '1')
        {
            break;
        }

        // Move to the next horizontal intersection
        y_inter += y_step;
        x_inter += x_step;
    }

    // Return the distance
    return sqrt(pow(x_inter - x_player_pixel, 2) + pow(y_inter - y_player_pixel, 2));
}


double get_vertical(t_map *p_map, double ray_angle)
{
    double x_inter, y_inter;
    double x_step, y_step;

    // Player position in pixels
    double x_player_pixel = p_map->player.x * TILE_SIZE + TILE_SIZE / 2;
    double y_player_pixel = p_map->player.y * TILE_SIZE  + TILE_SIZE / 2;

    // Determine ray direction
    if (ray_angle >= M_PI / 2 && ray_angle <= 3 * M_PI / 2)
        x_step = -TILE_SIZE; // Facing left
    else
        x_step = TILE_SIZE; // Facing right

    x_inter = floor(x_player_pixel / TILE_SIZE) * TILE_SIZE;
    if (x_step > 0)
        x_inter += TILE_SIZE; // Adjust for rays facing right

    y_inter = y_player_pixel + (x_inter - x_player_pixel) * tan(ray_angle);
    y_step = x_step * tan(ray_angle);

    // Iterate through the grid
    while (1)
    {
        int map_x = (int)(x_inter / TILE_SIZE);
        int map_y = (int)(y_inter / TILE_SIZE);

        // Boundary and wall collision checks
        if (map_y < 0 || map_y >= ft_count(p_map->map) ||
            map_x < 0 || (size_t)map_x >= ft_strlen(p_map->map[map_y]) ||
            p_map->map[map_y][map_x] == '1')
        {
            break;
        }

        // Move to the next vertical intersection
        x_inter += x_step;
        y_inter += y_step;
    }

    // Return the distance
    return sqrt(pow(x_inter - x_player_pixel, 2) + pow(y_inter - y_player_pixel, 2));
}

#define DIST_PROJ_PLANE (WIDTH / (2 * tan((FOV * M_PI / 180) / 2)))
void raycasting(t_map *p_map, mlx_t *mlx, mlx_image_t *map)
{
	(void)mlx;
    double ray_angle;
    double increment = FOV * (M_PI / 180) / WIDTH; // Angle increment per ray
    double wall_height, wall_top, wall_bottom;
    double distance_h, distance_v, corrected_distance;

    // Start ray from player's field of view
    ray_angle = player_angle - (FOV * (M_PI / 180) / 2);

    for (int i = 0; i < WIDTH; i++, ray_angle += increment)
    {
		
        // Calculate distances
        distance_h = get_horizontal(p_map, ray_angle);
        distance_v = get_vertical(p_map, ray_angle);

	
			printf("distance_h = %f\n", distance_h);
			printf("distance_v = %f\n", distance_v);
			printf("ray_angle = %f\n", ray_angle);
			printf("player_angle = %f\n", player_angle);
			printf("min	 = %f\n", fmin(distance_h, distance_v));
        corrected_distance = fmin(distance_h, distance_v) * cos(ray_angle - player_angle);

        // Calculate wall height
        wall_height = ((TILE_SIZE * HEIGHT) / corrected_distance);
        wall_top = fmax(0, (HEIGHT / 2) - (wall_height / 2));
        wall_bottom = fmin(HEIGHT, (HEIGHT / 2) + (wall_height / 2));

        // Draw the wall
        for (int y = (int)wall_top; y < (int)wall_bottom; y++)
        {
            mlx_put_pixel(map, i, y, get_rgba(241, 196, 15, 255));
        }
    }
}
