/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falmeida <falmeida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 20:47:19 by falmeida          #+#    #+#             */
/*   Updated: 2021/08/19 16:08:39 by falmeida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	conditions_change_map(t_data *img, char **map, int pi, int pj)
{
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == 'C')
		img->bag--;
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == 'E')
		check_exit(img, map, pi, pj);
	if (map[pi + img->playerx / 100][pj + img->playery / 100] == '1'
		|| map[pi + img->playerx / 100][pj + img->playery / 100]
			== 'E' && img->bag > 0)
		return ;
	map[pi][pj] = '0';
	map[pi + img->playerx / 100][pj + img->playery / 100] = 'P';
}

void	change_map(t_data *img, char **map)
{
	int	i;
	int	j;
	int	pi;
	int	pj;

	img->bag = count_bag(img, map);
	i = 0;
	while (i < img->size_y)
	{
		j = 0;
		while (j < img->size_x)
		{
			if (map[i][j] == 'P')
			{
				pi = i;
				pj = j;
			}
			j++;
		}
		i++;
	}
	conditions_change_map(img, map, pi, pj);
}

void	conditions_build_map(t_data *img, char **map, int i, int j)
{
	char	*num;

	num = ft_itoa(img->moviment);
	if (map[i][j] == '0')
		draw_image(img, img->floor, i, j);
	else if (map[i][j] == '1')
		draw_image(img, img->wall, i, j);
	else if (map[i][j] == 'P')
		draw_image(img, img->player, i, j);
	else if (map[i][j] == 'C')
		draw_image(img, img->collect, i, j);
	else if (map[i][j] == 'E')
		draw_image(img, img->door, i, j);
	mlx_string_put(img->mlx, img->win, 50, 50, 0xFFFFFF, num);
}

void	build_map(t_data *img)
{
	int		i;
	int		j;
	int		p;
	char	**map;

	p = 100;
	map = img->map;
	change_map(img, map);
	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			conditions_build_map(img, map, i, j);
			j++;
		}
		i++;
	}
}

int	key_print(int key, t_data *img)
{
	static int	i;

	img->playerx = 0;
	img->playery = 0;
	if (key == ESC)
		close_win(img);
	img->player = "./cowboy.xpm";
	if (key == W)
	{
		img->player = "./cowboy_back.xpm";
		img->playerx = -100;
	}
	else if (key == S)
		img->playerx = 100;
	else if (key == A)
		img->playery = -100;
	else if (key == D)
		img->playery = 100;
	build_map(img);
	img->moviment = ++i;
	printf("Moviments: %d\n", i);
	return (0);
}
