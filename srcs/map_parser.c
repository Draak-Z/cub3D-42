/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:44:30 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 12:38:57 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_emptyline(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\0')
			return (1);
	return (0);
}

int		wrong_line(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\0'
			&& !(str[i] >= '0' && str[i] <= '2'))
			return (1);
	}
	return (0);
}

int		ft_get_map(char *str, t_data *data)
{
	int			j;

	j = -1;
	data->map[data->i] = NULL;
	if (!(data->map[data->i] = malloc(sizeof(char) * (data->sizeline + 1))))
		ft_error(data, "Malloc map failed\n");
	while (str[++j])
	{
		if (ft_start(str[j], data, data->i, j) == 1)
			data->map[data->i][j] = '0';
		else
			data->map[data->i][j] = str[j];
	}
	j--;
	while (++j <= (data->sizeline - 1))
		data->map[data->i][j] = ' ';
	data->map[data->i][j] = '\0';
	data->i++;
	return (0);
}

int		ft_is_in_map(char *str, t_data *data)
{
	int i;

	i = -1;
	if (!str)
		return (0);
	if ((ft_charinstr(str, '1') || ft_charinstr(str, '0')
		|| ft_charinstr(str, '2')) && (str[0] != 'R' && str[0] != 'F'
		&& str[0] != 'C' && !(str[0] == 'N' && str[1] == 'O')
		&& !(str[0] == 'S' && str[1] == 'O') && !(str[0] == 'W' &&
		str[1] == 'E') && !(str[0] == 'E' && str[1] == 'A') && str[0] != 'S'))
	{
		while (str[++i] != '\0')
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' &&
				str[i] != '2' && str[i] != 'N' && str[i] != 'S' &&
				str[i] != 'E' && str[i] != 'W')
				data->error = 13;
		return (1);
	}
	return (0);
}

void	ft_parse_map(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (ft_is_in_map(str, data) == 1)
	{
		if (!data->r || data->f == -1 || data->c == -1 || data->no == NULL ||
			data->so == NULL || data->we == NULL || data->ea == NULL ||
			data->sp == NULL)
			data->error = 9;
		if ((i = ft_strlen(str)) > data->sizeline)
			data->sizeline = i;
		data->nblines++;
	}
	else if (str[0] == ' ' || str[0] == '\t' || str[0] == '\0')
	{
		if (wrong_line(str) == 1)
			data->error = 18;
	}
}
