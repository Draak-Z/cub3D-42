/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:45:44 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 14:57:28 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_var(t_data *data)
{
	data->var.posx = (double)data->dx + 0.5;
	data->var.posy = (double)data->dy + 0.5;
	data->var.dirx = 0;
	data->var.diry = 0;
	data->var.planex = 0;
	data->var.planey = 0;
	data->var.movespeed = 0.05;
	data->var.rotspeed = 0.03;
	if (data->start == 'N')
		data->var.dirx = -1;
	if (data->start == 'S')
		data->var.dirx = 1;
	if (data->start == 'E')
		data->var.diry = 1;
	if (data->start == 'W')
		data->var.diry = -1;
	if (data->start == 'N')
		data->var.planey = 0.66;
	if (data->start == 'S')
		data->var.planey = -0.66;
	if (data->start == 'E')
		data->var.planex = 0.66;
	if (data->start == 'W')
		data->var.planex = -0.66;
}

void	ft_init_more(t_data *data)
{
	data->start = 'l';
	data->fcnb = 0;
	data->rnb = 0;
	data->mlx.img = NULL;
	data->mlx.win = NULL;
	data->map = NULL;
	data->list = NULL;
	data->text[0].img = NULL;
	data->text[1].img = NULL;
	data->text[2].img = NULL;
	data->text[3].img = NULL;
	data->text[4].img = NULL;
	data->z.order = NULL;
	data->z.dist = NULL;
	data->z.zbuffer = NULL;
	data->sc = NULL;
}

void	ft_init(t_data *data)
{
	data->save = 0;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->sp = NULL;
	data->f = -1;
	data->c = -1;
	data->rx = 0;
	data->ry = 0;
	data->r = 0;
	data->nblines = 0;
	data->sizeline = 0;
	data->map = NULL;
	data->dx = 0;
	data->dy = 0;
	data->inmap = 0;
	data->index = 0;
	data->sum = 0;
	data->error = 0;
	data->line = NULL;
	ft_init_more(data);
}

void	find_sprites(t_data *data)
{
	int i;
	int j;

	i = -1;
	data->z.nbspr = 0;
	while (++i < data->nblines)
	{
		j = -1;
		while (++j < data->sizeline)
			if (data->map[i][j] == '2')
				data->z.nbspr++;
	}
	if (!(data->sc = malloc(sizeof(t_spritescoord) * data->z.nbspr)))
		ft_error(data, "Malloc sc* failed\n");
	if (!(data->z.order = malloc(sizeof(int) * data->z.nbspr)))
		ft_error(data, "Malloc z.order* failed\n");
	if (!(data->z.dist = malloc(sizeof(double) * data->z.nbspr)))
		ft_error(data, "Malloc z.dist* failed\n");
	if (!(data->z.zbuffer = malloc(sizeof(double) * data->rx)))
		ft_error(data, "Malloc z.zbuffer* failed\n");
	sprite_coords(data, -1, 0, 0);
}

void	sprite_coords(t_data *data, int i, int j, int v)
{
	while (++i < data->nblines)
	{
		j = -1;
		while (++j < data->sizeline)
		{
			if (data->map[i][j] == '2')
			{
				data->sc[v].x = (double)i + 0.5;
				data->sc[v].y = (double)j + 0.5;
				v++;
			}
		}
	}
}
