/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:44:51 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 14:54:46 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_check_errors(t_data *data)
{
	if (data->error == 11)
		ft_error(data, "More than 1 player\n");
	if (data->error == 12)
		ft_error(data, "Empty line in the map\n");
	if (data->error == 13)
		ft_error(data, "Invalid character in the map\n");
	if (data->start == 'l')
		ft_error(data, "No player\n");
	ft_walls(data, 0, 0);
	if (data->error == 14)
		ft_error(data, "Hole in the map\n");
}

void	more_errors(t_data *data)
{
	if (data->error == 13)
		write(2, "Invalid character in the map\n", 29);
	if (data->error == 16)
		write(2, "Too many numbers in F or C\n", 27);
	if (data->error == 17)
		write(2, "Not enough numbers in F or C\n", 29);
	if (data->error == 18)
		write(2, "Invalid character in the file\n", 30);
}

void	ft_error(t_data *data, char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	if (data->error == 1)
		write(2, "Invalid rgb value\n", 18);
	if (data->error == 2)
		write(2, "Incorrect characters in F or C\n", 31);
	if (data->error == 3)
		write(2, "Misplaced comma\n", 16);
	if (data->error == 4)
		write(2, "Multiple resolution informations\n", 33);
	if (data->error == 5)
		write(2, "Invalid resolution\n", 19);
	if (data->error == 6)
		write(2, "Multiple or invalid texture path\n", 33);
	if (data->error == 7)
		write(2, "Invalid characters before texture path\n", 39);
	if (data->error == 8)
		write(2, "Invalid character at beginning of line\n", 39);
	if (data->error == 9)
		write(2, "Information missing or misplaced\n", 33);
	if (data->error == 10)
		write(2, "Malloc new elem failed\n", 23);
	more_errors(data);
	ft_close(data);
}

void	free_data(t_data *data, int i)
{
	free(data->no);
	free(data->so);
	free(data->we);
	free(data->ea);
	free(data->sp);
	if (data->map)
	{
		while (++i < data->nblines)
			free(data->map[i]);
		free(data->map);
	}
	free(data->z.zbuffer);
	free(data->z.order);
	free(data->z.dist);
	free(data->sc);
	ft_lstclear(&data->list);
}

int		ft_close(t_data *data)
{
	free_data(data, -1);
	if (data->mlx.img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	if (data->text[0].img)
		mlx_destroy_image(data->mlx.mlx, data->text[0].img);
	if (data->text[1].img)
		mlx_destroy_image(data->mlx.mlx, data->text[1].img);
	if (data->text[2].img)
		mlx_destroy_image(data->mlx.mlx, data->text[2].img);
	if (data->text[3].img)
		mlx_destroy_image(data->mlx.mlx, data->text[3].img);
	if (data->text[4].img)
		mlx_destroy_image(data->mlx.mlx, data->text[4].img);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	if (data->mlx.mlx)
		mlx_destroy_display(data->mlx.mlx);
	if (data->mlx.mlx)
		free(data->mlx.mlx);
	exit(0);
	return (0);
}
