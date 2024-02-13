/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:45:07 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 12:39:18 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strclen(char *str)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while (str[i] != '.')
		i++;
	while (str[i++])
		j++;
	return (j);
}

int		ft_charinstr(char *str, char c)
{
	int i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i] != '\0')
		if (str[i] == c)
			return (1);
	return (0);
}

int		ft_start(char c, t_data *data, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (data->start != 'l')
			data->error = 11;
		data->start = c;
		data->dx = i;
		data->dy = j;
		return (1);
	}
	return (0);
}

int		ft_is_char_good(char *str, int rorfc)
{
	int	i;

	i = 1;
	while (str[i++])
		if (!(str[i] == ' ' || str[i] == '\t' || (str[i] >= '0' &&
				str[i] <= '9') || str[i] == '\0' || (str[i] == ',' && rorfc)))
			return (1);
	return (0);
}

int		ft_it_char(char *str, char c)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == c)
			j++;
	}
	return (j);
}
