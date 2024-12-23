/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 05:41:43 by relamine          #+#    #+#             */
/*   Updated: 2024/12/09 02:19:31 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int comma_countre(char *line)
{
	int count;

	count = 0;
	if (line && line[0] == ',')
		return (0);
	while (*line)
	{
		if (*line == ',')
		{
			if(*(line + 1) == ',')
				return (0);
			count++;
		}
		line++;
	}
	if (count != 2)
		return (0);
	return (1);
}

int check_color(char **colors)
{
	int i;
	int j;
	char *color;

	i = 0;
	while (colors[i])
	{
		j = 0;
		color = ft_strtrim(colors[i], "\t\v\f\r ");
		if (!color)
			return (0);
		if (!*color)
			return (free(color), 0);
		while (color[j])
		{
			if (color[j] < '0' || color[j] > '9')
				return (free(color), 0);
			j++;
		}
		if (ft_atoi(color) < 0 || ft_atoi(color) > 255)
			return (free(color), 0);
		free(color);
		i++;
	}
	return (1);
}

int colors_handler(char *line, t_color *color)
{
	char **colors;

	line++;
	if (!comma_countre(line))
		return (0);
	colors = my_split(line, ",\t\v\f\r\n ");
	if (!colors)
		return (0);
	if (!check_color(colors))
		return (ft_free(colors), 0);
	color->r = ft_atoi(colors[0]);
	color->g = ft_atoi(colors[1]);
	color->b = ft_atoi(colors[2]);
	return (ft_free(colors), 1);
}

int parsing_color(char *line, t_map *map)
{
	line =  skip_space(line);
	if (*line == 'F')
	{
		if (map->f.r != -1 || !colors_handler(line, &map->f))
			return (0);
	}
	else if (*line == 'C')
	{
		if (map->c.r != -1 || !colors_handler(line, &map->c))
			return (0);
	}
	else
		return (2);
	return (1);
}
