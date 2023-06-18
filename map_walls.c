/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:09:30 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 12:39:10 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		find(char c)
{
	char	*str;
	int		i;

	i = 0;
	str = "13";
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int		check_hole(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '3' && (!find(map[i][j + 1]) ||
				!find(map[i][j - 1]) || !find(map[i + 1][j]) ||
				!find(map[i - 1][j])))
				return (14);
			j++;
		}
		i++;
	}
	return (0);
}

int		flood_fill(int x, int y, char **map, int stop)
{
	int	x_max;

	x_max = 0;
	while (map[x_max + 1])
		x_max++;
	if (x == x_max || x == 0 || !map[x][y + 1] || !map[x][y] || y == 0)
		return (14);
	if (!stop)
	{
		map[x][y] = '3';
		if (map[x][y + 1] == '0' || map[x][y + 1] == '2')
			flood_fill(x, y + 1, map, stop);
		if (map[x][y - 1] == '0' || map[x][y - 1] == '2')
			flood_fill(x, y - 1, map, stop);
		if (map[x + 1][y] == '0' || map[x + 1][y] == '2')
			flood_fill(x + 1, y, map, stop);
		if (map[x - 1][y] == '0' || map[x - 1][y] == '2')
			flood_fill(x - 1, y, map, stop);
	}
	if (map[x][y] == ' ' || map[x + 1][y] == ' ' || map[x - 1][y] == ' '
		|| map[x][y + 1] == ' ' || map[x][y - 1] == ' ')
		stop = 1;
	return (check_hole(map));
}

void	free_tab(t_data *data, char **tab, int i, int er)
{
	while (++i < data->nblines)
		free(tab[i]);
	free(tab);
	if (er)
		ft_error(data, "Malloc tab j failed\n");
}

void	ft_walls(t_data *data, int i, int j)
{
	char	**tab;

	if (!(tab = malloc(sizeof(char*) * (data->nblines + 1))))
		ft_error(data, "Malloc tab i failed\n");
	while (data->map[i])
	{
		j = -1;
		if (!(tab[i] = malloc(sizeof(char) * (data->sizeline + 1))))
			free_tab(data, tab, -1, 1);
		while (data->map[i][++j] != '\0')
			tab[i][j] = data->map[i][j];
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = '\0';
	j = flood_fill(data->dx, data->dy, tab, 0);
	if (j)
		data->error = 14;
	free_tab(data, tab, -1, 0);
}
