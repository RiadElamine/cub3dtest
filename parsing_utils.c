/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saharchi <saharchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 09:41:29 by relamine          #+#    #+#             */
/*   Updated: 2024/12/09 17:58:54 by saharchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	while (st1[i] != '\0' && st2[i] != '\0' && st1[i] == st2[i])
		i++;
	return (st1[i] - st2[i]);
}

void ft_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int ft_count(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

char *skip_space(char *line)
{
	while (*line == ' ' || *line == '\t' || *line == '\v' || *line == '\f' || *line == '\r')
		line++;
	return (line);
}

