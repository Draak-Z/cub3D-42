/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 12:39:40 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 14:58:16 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	sprites_dist(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->z.nbspr)
	{
		data->z.order[i] = i;
		data->z.dist[i] = sqrt(pow((data->var.posx - data->sc[i].x), 2)
		+ pow((data->var.posy - data->sc[i].y), 2));
	}
}

void	sort_sprites(t_data *data)
{
	int		i;
	int		j;
	double	tmp;

	sprites_dist(data);
	i = -1;
	while (++i < data->z.nbspr)
	{
		j = -1;
		while (++j < data->z.nbspr - 1)
		{
			if (data->z.dist[j] < data->z.dist[j + 1])
			{
				tmp = data->z.dist[j];
				data->z.dist[j] = data->z.dist[j + 1];
				data->z.dist[j + 1] = tmp;
				tmp = (double)data->z.order[j];
				data->z.order[j] = data->z.order[j + 1];
				data->z.order[j + 1] = (int)tmp;
			}
		}
	}
}

void	sprite_math(t_data *data, int i)
{
	data->z.spritex = data->sc[data->z.order[i]].x - data->var.posx;
	data->z.spritey = data->sc[data->z.order[i]].y - data->var.posy;
	data->z.invdet = 1.0 / (data->var.planex * data->var.diry -
			data->var.dirx * data->var.planey);
	data->z.transformx = data->z.invdet * (data->var.diry *
			data->z.spritex - data->var.dirx * data->z.spritey);
	data->z.transformy = data->z.invdet * (-data->var.planey *
			data->z.spritex + data->var.planex * data->z.spritey);
	data->z.spritescreenx = (int)((data->rx / 2) * (1 + data->z.transformx
				/ data->z.transformy));
	data->z.spriteheight = abs((int)(data->ry / (data->z.transformy)));
	data->z.drawstarty = -data->z.spriteheight / 2 + data->ry / 2;
	if (data->z.drawstarty < 0)
		data->z.drawstarty = 0;
	data->z.drawendy = data->z.spriteheight / 2 + data->ry / 2;
	if (data->z.drawendy >= data->ry)
		data->z.drawendy = data->ry - 1;
	data->z.spritewidth = abs((int)(data->ry / (data->z.transformy)));
	data->z.drawstartx = -data->z.spritewidth / 2 + data->z.spritescreenx;
	if (data->z.drawstartx < 0)
		data->z.drawstartx = 0;
	data->z.drawendx = data->z.spritewidth / 2 + data->z.spritescreenx;
	if (data->z.drawendx >= data->rx)
		data->z.drawendx = data->rx - 1;
}

void	draw_sprite(t_data *data, int y, int texx, int stripe)
{
	int		d;
	int		texy;

	while (y < data->z.drawendy)
	{
		d = (y) * 256 - data->ry * 128 + data->z.spriteheight * 128;
		texy = ((d * data->text[4].h) / data->z.spriteheight) / 256;
		if (data->text[4].addr[texy * data->text[4].line_length / 4 +
				texx] != 0)
		{
			data->mlx.addr[y * data->mlx.line_length / 4 + stripe] =
				data->text[4].addr[texy * data->text[4].line_length /
				4 + texx];
		}
		y++;
	}
}

void	sprites(t_data *data)
{
	int i;
	int y;
	int stripe;
	int texx;

	i = -1;
	sort_sprites(data);
	while (++i < data->z.nbspr)
	{
		sprite_math(data, i);
		stripe = data->z.drawstartx;
		while (stripe < data->z.drawendx)
		{
			texx = (int)(256 * (stripe - (-data->z.spritewidth / 2 +
							data->z.spritescreenx)) * data->text[4].w
							/ data->z.spritewidth) / 256;
			if (data->z.transformy > 0 && stripe > 0 && stripe < data->rx
					&& data->z.transformy < data->z.zbuffer[stripe])
			{
				y = data->z.drawstarty;
				draw_sprite(data, y, texx, stripe);
			}
			stripe++;
		}
	}
}
