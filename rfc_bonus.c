/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rfc_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:18:56 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 14:58:09 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int		ft_r(char *str, t_data *data)
{
	int		sum;

	sum = 0;
	if (ft_is_char_good(str, 0) || (str[1] != ' ' && str[1] != '\t'))
		return (0);
	while (str[data->i] == ' ' || str[data->i] == '\t')
		data->i++;
	if (str[data->i] >= '0' && str[data->i] <= '9')
		data->rnb++;
	while (str[data->i] >= '0' && str[data->i] <= '9')
	{
		if (sum >= 214748364)
			break ;
		sum = (sum * 10) + (str[data->i] - 48);
		data->i++;
	}
	while (str[data->i] >= '0' && str[data->i] <= '9')
		data->i++;
	return (sum);
}

void	rgb(char *str, t_data *data)
{
	data->fcnb++;
	if (data->fcnb > 3)
		data->error = 16;
	data->sum = 0;
	while (str[data->i] >= '0' && str[data->i] <= '9')
	{
		data->sum = (data->sum * 10) + (str[data->i] - 48);
		data->i++;
	}
	if ((data->sum > 255 || data->sum < 0) && data->error != 16)
		data->error = 1;
	if (data->fcnb == 1)
		data->rgb.r = data->sum;
	else if (data->fcnb == 2)
		data->rgb.g = data->sum;
	else if (data->fcnb == 3)
		data->rgb.b = data->sum;
}

int		ft_fc(char *str, t_data *data)
{
	if ((str[1] != ' ' && str[1] != '\t') ||
		ft_it_char(str, ',') != 2 || ft_is_char_good(str, 1))
		data->error = 2;
	while (str[data->i] == ' ' || str[data->i] == '\t' ||
			str[data->i] == ',')
	{
		if (str[data->i] == ',' && ((!data->fcnb || data->fcnb == 3)
			|| str[data->i - 1] == ',') && data->error != 2)
			data->error = 3;
		data->i++;
		if (str[data->i] >= '0' && str[data->i] <= '9')
			rgb(str, data);
	}
	return (data->rgb.r << 16 | data->rgb.g << 8 | data->rgb.b);
}

void	ft_rfc(char **str, t_data *data)
{
	data->i = 1;
	data->fcnb = 0;
	if ((*str[0] == 'F' && data->f != -1) || (*str[0] == 'C' && data->c != -1))
		ft_error(data, "Multiple F or C informations\n");
	if (*str[0] == 'R')
	{
		data->r = 1;
		if (data->rx != 0 && data->ry != 0)
			data->error = 4;
		data->rx = ft_r(*str, data);
		data->ry = ft_r(*str, data);
		if ((ft_r(*str, data) > 0 || data->rx == 0 || data->ry == 0
			|| data->rnb > 2) && data->error != 4)
			data->error = 5;
	}
	else if (*str[0] == 'F')
		data->f = ft_fc(*str, data);
	else if (*str[0] == 'C')
		data->c = ft_fc(*str, data);
	if ((*str[0] == 'F' || *str[0] == 'C') && (data->fcnb != 3
		&& data->error != 2 && data->error != 3 && data->error != 16))
		data->error = 17;
}
