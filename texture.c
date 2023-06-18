/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:45:29 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 12:39:48 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_texture_path(char *str, char **texture, t_data *data, int j)
{
	int	i;

	i = 0;
	if (*texture != NULL || ft_charinstr(str, '.') == 0 ||
		ft_charinstr(str, '/') == 0 || ft_strclen(str) <= 2)
	{
		data->error = 6;
		return ;
	}
	if (str[j] != ' ' && str[j] != '\t')
		data->error = 7;
	while (str[j] != '.')
	{
		if (str[j] != ' ' && str[j] != '\t')
			data->error = 7;
		j++;
	}
	if (str[j + 1] != '/')
		data->error = 6;
	if (!(*texture = (char *)(malloc(sizeof(char) * (ft_strclen(str) + 1)))))
		ft_error(data, "Malloc texture path failed\n");
	while (str[j])
		(*texture)[i++] = str[j++];
	(*texture)[i] = '\0';
}

void	ft_texture(char *str, t_data *data)
{
	if (str[0] == 'N' && str[1] == 'O')
		ft_texture_path(str, &data->no, data, 2);
	else if (str[0] == 'S' && str[1] == 'O')
		ft_texture_path(str, &data->so, data, 2);
	else if (str[0] == 'W' && str[1] == 'E')
		ft_texture_path(str, &data->we, data, 2);
	else if (str[0] == 'E' && str[1] == 'A')
		ft_texture_path(str, &data->ea, data, 2);
	else if (str[0] == 'S')
		ft_texture_path(str, &data->sp, data, 1);
	else if (str[0] != 'F' && str[0] != 'C' && str[0] != 'R' &&
			!(str[0] >= '0' && str[0] <= '2') && str[0] != ' ' &&
			str[0] != '\t' && str[0] != '\0')
		data->error = 8;
}
