/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:30:32 by saharchi          #+#    #+#             */
/*   Updated: 2024/12/30 09:52:04 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
//------------
#include <string.h>
# include <limits.h>
//------------

# include "libft/libft.h"
#include "./MLX42/include/MLX42/MLX42.h"


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 145
#endif

// map size
#define WIDTH 1200
#define HEIGHT 1000
#define M_WIDTH (WIDTH / 4)
#define M_HEIGHT (HEIGHT / 4)

// raycasting
#define FOV 60
#define TILE_SIZE 30
#define DIST_PROJ_PLANE (WIDTH / (2 * tan((FOV * M_PI / 180) / 2)))


typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;


typedef struct s_player
{
	mlx_image_t*	player;
	int x;
	int y;
	double x_double;
	double y_double;
	double rot_angle;
	int walk_dir; // -1 for back, 1 for front
	int walk_side; // -1 for move left, 1 for right
	int turn_dir; // -1 for left, 1 for right
	double walk_speed;
	double turn_speed;
} t_player;

typedef struct s_ray
{
	float angle;
	float dist;
} t_ray;

typedef struct s_map
{
    char **map;
	double x_inter;
	double y_inter;
	int	cell_width;
	int	cell_height;
    int fd;
	char *no;
	char *so;
	char *we;
	char *ea;
	t_color f;
	t_color c;
	t_player player;
	mlx_t* mlx;
	mlx_image_t* map_img;
	mlx_texture_t *textures[4];
} t_map;


char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_strchr2( char *s);



// part parsing

char	**my_split(char const *s, char *c);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_free(char **str);
int		parsing_color(char *line, t_map *map);
int		parsing_texture(char *line, t_map *map, int counter);
int		ft_count(char **str);
int		is_texture_valid(t_map *map);
int		skip_line_empty(char *line);
char	*skip_space(char *line);
void	init_map(t_map **p_map);
void	free_map(t_map *map);
void		parse_map(t_map *p_map);
int		check_namnf(t_map *p_map, char *av);
void	get_posplayer(t_map *p_map, int i, int j);

// part exucution

void	map_render(t_map *p_map);
void	minimap(t_map *p_map, mlx_t* mlx);
int		get_rgba(int r, int g, int b, int a);
int		get_cell_color(t_map *p_map, int x, int y);
void	move_player(t_map *p_map);
// raycasting
void raycasting(t_map *p_map);

