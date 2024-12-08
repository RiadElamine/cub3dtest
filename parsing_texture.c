/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:32:55 by relamine          #+#    #+#             */
/*   Updated: 2024/12/08 11:25:13 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_count(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int parsing_texture(char *line, t_map *map, int counter)
{
	char **texture;

	if (counter == 6)
		return (2);
	texture = my_split(line, "\t\v\f\r\n ");
	if (!texture)
		return (0);
	if (ft_count(texture) != 2)
		return (ft_free(texture), 0);
	else if (!ft_strcmp(texture[0], "NO"))
		map->no = ft_strdup(texture[1]);
	else if (!ft_strcmp(texture[0], "SO"))
		map->so = ft_strdup(texture[1]);
	else if (!ft_strcmp(texture[0], "WE"))
		map->we = ft_strdup(texture[1]);
	else if (!ft_strcmp(texture[0], "EA"))
		map->ea = ft_strdup(texture[1]);
	return (ft_free(texture), 1);
}
