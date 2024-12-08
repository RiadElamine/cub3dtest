/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 08:52:15 by relamine          #+#    #+#             */
/*   Updated: 2024/12/08 09:55:07 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static const char	*skip_separator(const char *p, char *c)
{
	while (*p && ft_strchr(c, *p))
		p++;	
	return (p);
}

static int	rows(const char *s, char *c)
{
	int	nblignes;
	int	i;

	nblignes = 0;
	i = 0;
	while (*s)
	{
		s = skip_separator(s, c);
		if (!*s)
			break ;
		while (*s && !ft_strchr(c, *s))
			s++;
		nblignes++;
	}
	return (nblignes);
}

static int	column(const char *s, char *c)
{
	int	number_colmns;

	number_colmns = 0;
	while (*s && !ft_strchr(c, *s))
	{
		number_colmns++;
		s++;
	}
	return (number_colmns);
}

static char	**split_str(char const *s, char *c, char **s1, int row_tabtwo)
{
	int	nblignes2;
	int	row;
	int	col;

	row = 0;
	while (row < row_tabtwo)
	{
		s = skip_separator(s, c);
		nblignes2 = column(s, c);
		col = 0;
		s1[row] = malloc((nblignes2 + 1) * sizeof(char));
		if (!s1[row])
		{
			while (row >= 0)
				free(s1[--row]);
			free(s1);
			return (0);
		}
		while (*s && !ft_strchr(c, *s))
			s1[row][col++] = *(s++);
		s1[row][col] = '\0';
		row++;
	}
	s1[row_tabtwo] = NULL;
	return (s1);
}

char	**my_split(char const *s, char *c)
{
	int		row_tabtwo;
	char	**s1;

	if (!s)
		return (NULL);
	row_tabtwo = rows(s, c);
	s1 = malloc((row_tabtwo + 1) * sizeof(char *));
	if (!s1)
		return (NULL);
	return (split_str(s, c, s1, row_tabtwo));
}
