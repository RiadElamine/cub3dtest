/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:47:41 by saharchi          #+#    #+#             */
/*   Updated: 2024/12/10 07:19:05 by relamine         ###   ########.fr       */
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

void check_w(char *map)
{
	int j;
	j = 0;
	while(map[j])
	{
		if (map[j] != '1' && map[j] != ' ')
		{
			printf("Error\n");
			exit(1);
		}
		j++;
	}
}

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int check_space(char **map, int i, int j)
{
	if (is_space(map[i][j + 1]) || is_space(map[i][j - 1]) || is_space(map[i - 1][j]) || is_space(map[i + 1][j]))
		return (1);
	return (0);
}


int parse_map(t_map *p_map)
{
	int i = 0;
	int j = 0;
	int c ;
	char *check;
	check_w(p_map->map[0]);
	i = 1;
	c = ft_count(p_map->map);
	int cou = 0;
	while(p_map->map[i] && i < c - 1)
	{
		j = 0;
		while(is_space(p_map->map[i][j]))
			j++;
		check = ft_strtrim(p_map->map[i], " \t\v\f\r\n");
		if (check[0] != '1' || check[ft_strlen(check) - 1] != '1')
		{
			printf("Error\n");
			free(check);
			exit(1);
		}
		while(p_map->map[i][j])
		{
			if (p_map->map[i][j] != '1' && p_map->map[i][j] != '0' && !is_space(p_map->map[i][j]) && p_map->map[i][j] != 'N' && p_map->map[i][j] != 'S' && p_map->map[i][j] != 'W' && p_map->map[i][j] != 'E')
			{
				printf("Error\n");
				exit(1);
			}
			if (p_map->map[i][j] == 'N' || p_map->map[i][j] == 'S' || p_map->map[i][j] == 'W' || p_map->map[i][j] == 'E')
			{
				cou++;
				if (check_space(p_map->map, i, j) || j >= (int)ft_strlen(p_map->map[i - 1]) || j >= (int)ft_strlen(p_map->map[i + 1]))
				{
					printf("Error\n");
					exit(1);
				}
				get_posplayer(p_map, i, j);
			}
			if (p_map->map[i][j] == '0' && (check_space(p_map->map, i, j) || j >= (int)ft_strlen(p_map->map[i - 1]) || j >= (int)ft_strlen(p_map->map[i + 1])))
			{
				printf("Error\n");
				exit(1);
			}
			j++;
		}
		free(check);
		i++;
	}
	check_w(p_map->map[c - 1]);
	if (cou != 1)
	{
		printf("Error\n");
		exit(1);
	}

	
	return 0;
}
