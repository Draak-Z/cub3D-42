/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:56:03 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 17:33:32 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	bmp_header(t_data *data, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * data->rx * data->ry;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &data->rx, 4);
	write(fd, &data->ry, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &data->mlx.bits_per_pixel, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	ft_save(t_data *data)
{
	int	fd;
	int	x;
	int	y;

	y = data->ry - 1;
	if ((fd = open("./image.bmp", O_CREAT | O_RDWR)) == -1)
		ft_error(data, "Impossible to create .bmp file\n");
	bmp_header(data, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < data->rx)
		{
			write(fd, &data->mlx.addr[y * data->mlx.line_length / 4 + x], 4);
			x++;
		}
		y--;
	}
	close(fd);
	ft_close(data);
}

int		ft_check_save(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == 'e' && str[i - 2] == 'v' && str[i - 3] == 'a' &&
		str[i - 4] == 's' && str[i - 5] == '-' && str[i - 6] == '-'
		&& ft_strlen(str) < 7)
		return (1);
	else
		return (0);
}
