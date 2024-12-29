/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:47:41 by saharchi          #+#    #+#             */
/*   Updated: 2024/12/18 23:44:27 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int check_namnf(t_map *p_map, char *av)
{
    if(ft_strlen(ft_strchr(av, '.')) == 4 && !ft_strcmp(ft_strchr(av, '.'), ".cub"))
    {
		p_map->fd = open(av, O_RDONLY);
		if (p_map->fd == -1) 
		{
	        printf("Error Number % d\n", errno);
        	perror("Program");
			return (0);
    	}
		return (1);
    }
	return (0);
}

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void check_wall(char *map)
{
	int j;
	j = 0;
	while(map[j])
	{
		if (map[j] != '1' && !is_space(map[j]))
		{
			printf("Error\n");
			exit(1);
		}
		j++;
	}
}


int check_space(char **map, int i, int j)
{
	if (is_space(map[i][j + 1]) || is_space(map[i][j - 1]) || is_space(map[i - 1][j]) || is_space(map[i + 1][j]))
		return (1);
	return (0);
}

int check_player(char map)
{
	if (map == 'N' || map == 'S' || map == 'W' || map == 'E')
		return (1);
	return (0);
}


int valid_element(char map)
{
	if (map != '1' && map != '0' && !is_space(map) && !check_player(map))
	{
		printf("Error\n");
		exit(1);
	}
	return (1);
}

void valid_line(char **line, int i, t_map *p_map, int *cou)
{
	int j = 0;
	while(is_space(line[i][j]))
		j++;
	while(line[i][j] && valid_element(line[i][j]))
	{
		if (check_player(line[i][j]))
		{
			(*cou)++;
			if (check_space(line, i, j) || j >= (int)ft_strlen(line[i - 1]) || j >= (int)ft_strlen(line[i + 1]))
			{
				printf("Error\n");
				exit(1);
			}
			get_posplayer(p_map, i, j);
		}
		if (line[i][j] == '0' && (check_space(line, i, j) || j >= (int)ft_strlen(line[i - 1]) || j >= (int)ft_strlen(line[i + 1])))
		{
			printf("Error\n");
			exit(1);
		}
		j++;
	}
}

void parse_map(t_map *p_map)
{
	int i = 0;
	char *check;
	int cou;

	cou = 0;
	check_wall(p_map->map[0]);
	check_wall(p_map->map[ft_count(p_map->map) - 1]);
	while(p_map->map[i])
	{
		check = ft_strtrim(p_map->map[i], " \t\v\f\r\n");
		if (check[0] != '1' || check[ft_strlen(check) - 1] != '1')
		{
			printf("Error\n");
			free(check);
			exit(1);
		}
		valid_line(p_map->map, i, p_map, &cou);
		free(check);
		i++;
	}
	if (cou != 1)
	{
		printf("Error\n");
		exit(1);
	}
}
