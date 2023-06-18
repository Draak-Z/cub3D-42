/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:52:15 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 12:38:30 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	math(t_data *data)
{
	data->var.camerax = 2 * data->var.x / (double)data->rx - 1;
	data->var.raydirx = data->var.dirx + data->var.planex * data->var.camerax;
	data->var.raydiry = data->var.diry + data->var.planey * data->var.camerax;
	data->var.mapx = (int)data->var.posx;
	data->var.mapy = (int)data->var.posy;
	data->var.deltadistx = fabs(1 / data->var.raydirx);
	data->var.deltadisty = fabs(1 / data->var.raydiry);
	data->var.hit = 0;
}

void	step(t_data *data)
{
	if (data->var.raydirx < 0)
	{
		data->var.stepx = -1;
		data->var.sidedistx = (data->var.posx - data->var.mapx) *
								data->var.deltadistx;
	}
	else
	{
		data->var.stepx = 1;
		data->var.sidedistx = (data->var.mapx + 1.0 - data->var.posx) *
								data->var.deltadistx;
	}
	if (data->var.raydiry < 0)
	{
		data->var.stepy = -1;
		data->var.sidedisty = (data->var.posy - data->var.mapy) *
								data->var.deltadisty;
	}
	else
	{
		data->var.stepy = 1;
		data->var.sidedisty = (data->var.mapy + 1.0 - data->var.posy) *
								data->var.deltadisty;
	}
}

void	get_dist(t_data *data)
{
	while (data->var.hit == 0)
	{
		if (data->var.sidedistx < data->var.sidedisty)
		{
			data->var.sidedistx += data->var.deltadistx;
			data->var.mapx += data->var.stepx;
			data->var.side = 0;
		}
		else
		{
			data->var.sidedisty += data->var.deltadisty;
			data->var.mapy += data->var.stepy;
			data->var.side = 1;
		}
		if (data->map[data->var.mapx][data->var.mapy] == '1')
			data->var.hit = 1;
	}
	if (data->var.side == 0)
		data->var.perpwalldist = (data->var.mapx - data->var.posx +
								(1 - data->var.stepx) / 2) / data->var.raydirx;
	else
		data->var.perpwalldist = (data->var.mapy - data->var.posy +
								(1 - data->var.stepy) / 2) / data->var.raydiry;
}

void	tex_texture(t_data *data)
{
	if (!data->var.side && data->var.stepx == 1)
		data->tv.texnum = 0;
	else if (!data->var.side && data->var.stepx == -1)
		data->tv.texnum = 1;
	else if (data->var.side && data->var.stepy == 1)
		data->tv.texnum = 2;
	else if (data->var.side && data->var.stepy == -1)
		data->tv.texnum = 3;
	if (data->var.side == 0)
		data->tv.wallx = data->var.posy + data->var.perpwalldist *
		data->var.raydiry;
	else
		data->tv.wallx = data->var.posx + data->var.perpwalldist *
		data->var.raydirx;
	data->tv.wallx -= floor(data->tv.wallx);
	data->tv.texx = (int)(data->tv.wallx *
		(double)data->text[data->tv.texnum].w);
	if (data->var.side == 0 && data->var.raydirx > 0)
		data->tv.texx = data->text[data->tv.texnum].w - data->tv.texx - 1;
	if (data->var.side == 1 && data->var.raydiry < 0)
		data->tv.texx = data->text[data->tv.texnum].w - data->tv.texx - 1;
	data->tv.step = 1.0 * data->text[data->tv.texnum].h /
		data->var.lineheight;
	data->tv.texpos = (data->var.drawstart - data->ry /
		2 + data->var.lineheight / 2) * data->tv.step;
}

void	calc(t_data *data)
{
	data->var.x = 0;
	while (data->var.x < data->rx)
	{
		math(data);
		step(data);
		get_dist(data);
		data->var.lineheight = (int)(data->ry / data->var.perpwalldist);
		data->var.drawstart = -data->var.lineheight / 2 + data->ry / 2;
		if (data->var.drawstart < 0)
			data->var.drawstart = 0;
		data->var.drawend = data->var.lineheight / 2 + data->ry / 2;
		if (data->var.drawend >= data->ry)
			data->var.drawend = data->ry - 1;
		data->tv = (t_texvar){0};
		tex_texture(data);
		drawline(data, 0);
		data->z.zbuffer[data->var.x] = data->var.perpwalldist;
		data->var.x++;
	}
	sprites(data);
}
