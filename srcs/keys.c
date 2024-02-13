/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:50:39 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 12:41:19 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	r(t_data *data)
{
	double olddirxr;
	double oldplanexr;

	olddirxr = data->var.dirx;
	data->var.dirx = data->var.dirx * cos(-data->var.rotspeed) - data->var.diry
		* sin(-data->var.rotspeed);
	data->var.diry = olddirxr * sin(-data->var.rotspeed) + data->var.diry *
		cos(-data->var.rotspeed);
	oldplanexr = data->var.planex;
	data->var.planex = data->var.planex * cos(-data->var.rotspeed)
		- data->var.planey * sin(-data->var.rotspeed);
	data->var.planey = oldplanexr * sin(-data->var.rotspeed) + data->var.planey
		* cos(-data->var.rotspeed);
}

void	l(t_data *data)
{
	double olddirxl;
	double oldplanexl;

	olddirxl = data->var.dirx;
	data->var.dirx = data->var.dirx * cos(data->var.rotspeed) - data->var.diry
		* sin(data->var.rotspeed);
	data->var.diry = olddirxl * sin(data->var.rotspeed) + data->var.diry *
		cos(data->var.rotspeed);
	oldplanexl = data->var.planex;
	data->var.planex = data->var.planex * cos(data->var.rotspeed)
		- data->var.planey * sin(data->var.rotspeed);
	data->var.planey = oldplanexl * sin(data->var.rotspeed) + data->var.planey
		* cos(data->var.rotspeed);
}

int		key_press(t_data *data)
{
	if (data->var.tab[K_W % 1000])
		w(data);
	if (data->var.tab[K_S % 1000])
		s(data);
	if (data->var.tab[K_A % 1000])
		a(data);
	if (data->var.tab[K_D % 1000])
		d(data);
	if (data->var.tab[K_AR_R % 1000])
		r(data);
	if (data->var.tab[K_AR_L % 1000])
		l(data);
	if (data->var.tab[K_ESC % 1000])
		ft_close(data);
	return (0);
}

int		key_pressed(int keycode, t_data *data)
{
	if (keycode % 1000 < 512)
		data->var.tab[keycode % 1000] = 1;
	return (0);
}

int		key_released(int keycode, t_data *data)
{
	if (keycode % 1000 < 512)
		data->var.tab[keycode % 1000] = 0;
	return (0);
}
