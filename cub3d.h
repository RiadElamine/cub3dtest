/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:03:40 by relamine          #+#    #+#             */
/*   Updated: 2024/12/08 11:30:12 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "./libft/libft.h"

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_map
{
	char *no;
	char *so;
	char *we;
	char *ea;
	t_color f;
	t_color c;
} t_map;

char	**my_split(char const *s, char *c);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_free(char **str);
int		parsing_texture(char *line, t_map *map, int counter);
