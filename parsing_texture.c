/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:32:55 by relamine          #+#    #+#             */
/*   Updated: 2024/12/09 18:43:40 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_texture_valid(t_map *map)
{
	int no;
	int so;
	int we;
	int ea;

	no = open(map->no, O_RDONLY);
	if (no == -1)
		return (0);
	so = open(map->so, O_RDONLY);
	if (so == -1)
		return ( close(no), 0);
	we = open(map->we, O_RDONLY);
	if (we == -1)
		return (close(no), close(so), 0);
	ea = open(map->ea, O_RDONLY);
	if (ea == -1)
		return (close(no), close(so), close(we), 0);
	close(no);
	close(so);
	close(we);
	close(ea);
	return (1);
}

char *get_value(char *line, char **texture, int *status)
{
	int argc;

	argc = ft_count(texture);
	if (argc >= 3)
	{
		char *tmp = ft_strnstr(line, texture[0], ft_strlen(line));
		if (!tmp)
			return (ft_free(texture), *status = 0, NULL);
		tmp = ft_substr(tmp, ft_strlen(texture[0]), ft_strlen(tmp) - 2);
		tmp = ft_strtrim(tmp, " \t\v\f\r\n");
		if (!tmp)
			return (ft_free(texture), *status = 0, NULL);
		return (*status = 1, tmp);
	}
	return (*status = 1, texture[1]);
}

int parsing_texture(char *line, t_map *map, int counter)
{
	char **texture;
	int status;

	status = 1;
	if (counter == 6)
		return (2);
	texture = my_split(line, "\t\v\f\r\n ");
	if (!texture)
		return (0);
	if (ft_count(texture) < 2)
		return (ft_free(texture), 0);
	else if (!ft_strcmp(texture[0], "NO"))
		map->no = get_value(line, texture, &status);
	else if (!ft_strcmp(texture[0], "SO"))
		map->so = get_value(line, texture, &status);
	else if (!ft_strcmp(texture[0], "WE"))
		map->we = get_value(line, texture, &status);
	else if (!ft_strcmp(texture[0], "EA"))
		map->ea = get_value(line, texture, &status);
	else
		return (ft_free(texture), 0);
	if (!status)
		return (ft_free(texture), 0);
	if (map->no && map->so && map->we && map->ea)
		return (free(texture[0]), free(texture), is_texture_valid(map));
	return (free(texture[0]), free(texture), 1);
}
