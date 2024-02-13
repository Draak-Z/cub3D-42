/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wasd_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:42:52 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 14:58:24 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	w(t_data *data)
{
	if (data->map[(int)(data->var.posx + data->var.dirx *
		data->var.movespeed)][(int)(data->var.posy)] == '0')
		data->var.posx += data->var.dirx * data->var.movespeed;
	if (data->map[(int)(data->var.posx)][(int)(data->var.posy + data->var.diry *
		data->var.movespeed)] == '0')
		data->var.posy += data->var.diry * data->var.movespeed;
}

void	s(t_data *data)
{
	if (data->map[(int)(data->var.posx - data->var.dirx *
		data->var.movespeed)][(int)(data->var.posy)] == '0')
		data->var.posx -= data->var.dirx * data->var.movespeed;
	if (data->map[(int)(data->var.posx)][(int)(data->var.posy - data->var.diry *
		data->var.movespeed)] == '0')
		data->var.posy -= data->var.diry * data->var.movespeed;
}

void	a(t_data *data)
{
	if (data->map[(int)((data->var.posx - data->var.diry * data->var.movespeed)
		- (0.02 * data->var.diry))][(int)(data->var.posy)] == '0')
		data->var.posx -= data->var.diry * data->var.movespeed;
	if (data->map[(int)(data->var.posx)][(int)((data->var.posy + data->var.dirx
		* data->var.movespeed) + (0.02 * data->var.dirx))] == '0')
		data->var.posy += data->var.dirx * data->var.movespeed;
}

void	d(t_data *data)
{
	if (data->map[(int)((data->var.posx + data->var.diry * data->var.movespeed)
		+ (0.02 * data->var.diry))][(int)(data->var.posy)] == '0')
		data->var.posx += data->var.diry * data->var.movespeed;
	if (data->map[(int)(data->var.posx)][(int)((data->var.posy - data->var.dirx
		* data->var.movespeed) - (0.02 * data->var.dirx))] == '0')
		data->var.posy -= data->var.dirx * data->var.movespeed;
}
