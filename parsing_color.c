/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 05:41:43 by relamine          #+#    #+#             */
/*   Updated: 2024/12/08 11:57:23 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


char *skip_space(char *line)
{
	while (*line == ' ' || *line == '\t' || *line == '\v' || *line == '\f' || *line == '\r')
		line++;
	return (line);
}

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

void init_map(t_map *map)
{
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
}

void f()
{
	system("leaks a.out");
}

int skip_line_empty(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\v' && *line != '\f' && *line != '\r' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}


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

int main(int argc, char **argv)
{
	t_map map;
	int status;
	int i;
	int counter;

	i = 1;
	counter = 0;
	atexit(f);
	init_map(&map);
	while (i < argc)
	{
		if (skip_line_empty(argv[i]))
		{
			i++;
			if (i == argc && (counter != 6 || !is_texture_valid(&map)))
					return (printf("Error\n"), free_map(&map), 1);
			continue;
		}
		status = parsing_color(argv[i], &map);
		if (status == 0)
			return (printf("Error\n"), free_map(&map), 1);
		else if (status == 2)
		{
			status = parsing_texture(argv[i], &map, counter);
			if (status == 2)
			{
				if (counter != 6 || !is_texture_valid(&map))
					return (printf("Error\n"), free_map(&map), 1);
				// hna fin khasak t3ayat 3la map_parsing
				continue;;
			}
			else if (status == 0)
				return (printf("Error\n"), free_map(&map), 1);
		}
		counter++;
		i++;
	}

}
