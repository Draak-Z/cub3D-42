/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:37:09 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 14:58:06 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_get_text_addr(t_data *data)
{
	data->text[0].addr = (int*)mlx_get_data_addr(data->text[0].img,
			&data->text[0].bits_per_pixel, &data->text[0].line_length,
			&data->text[0].endian);
	data->text[1].addr = (int*)mlx_get_data_addr(data->text[1].img,
			&data->text[1].bits_per_pixel, &data->text[1].line_length,
			&data->text[1].endian);
	data->text[2].addr = (int*)mlx_get_data_addr(data->text[2].img,
			&data->text[2].bits_per_pixel, &data->text[2].line_length,
			&data->text[2].endian);
	data->text[3].addr = (int*)mlx_get_data_addr(data->text[3].img,
			&data->text[3].bits_per_pixel, &data->text[3].line_length,
			&data->text[3].endian);
	data->text[4].addr = (int*)mlx_get_data_addr(data->text[4].img,
			&data->text[4].bits_per_pixel, &data->text[4].line_length,
			&data->text[4].endian);
}

void	ft_get_text_img(t_data *data)
{
	if (!(data->text[0].img = mlx_xpm_file_to_image(data->mlx.mlx,
					data->no, &(data->text[0].w), &(data->text[0].h))))
		ft_error(data, "Invalid NO texture\n");
	if (!(data->text[1].img = mlx_xpm_file_to_image(data->mlx.mlx,
					data->so, &(data->text[1].w), &(data->text[1].h))))
		ft_error(data, "Invalid SO texture\n");
	if (!(data->text[2].img = mlx_xpm_file_to_image(data->mlx.mlx,
					data->we, &(data->text[2].w), &(data->text[2].h))))
		ft_error(data, "Invalid WE texture\n");
	if (!(data->text[3].img = mlx_xpm_file_to_image(data->mlx.mlx,
					data->ea, &(data->text[3].w), &(data->text[3].h))))
		ft_error(data, "Invalid EA texture\n");
	if (!(data->text[4].img = mlx_xpm_file_to_image(data->mlx.mlx,
					data->sp, &(data->text[4].w), &(data->text[4].h))))
		ft_error(data, "Invalid sprite texture\n");
	ft_get_text_addr(data);
}

void	drawline(t_data *data, int y)
{
	while (y < data->var.drawstart)
		data->mlx.addr[y++ * data->rx + data->var.x] = data->c;
	while (y <= data->var.drawend)
	{
		data->tv.texy = (int)data->tv.texpos &
			(data->text[data->tv.texnum].h - 1);
		data->tv.texpos += data->tv.step;
		data->mlx.addr[y * data->rx + data->var.x] =
		data->text[data->tv.texnum].addr[data->text[data->tv.texnum].h
			* data->tv.texy + data->tv.texx];
		y++;
	}
	while (y < data->ry)
		data->mlx.addr[y++ * data->rx + data->var.x] = data->f;
}

int		main_loop(t_data *data)
{
	calc(data);
	if (data->save == 1)
		ft_save(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	key_press(data);
	return (0);
}

void	raycasting(t_data *data)
{
	data->i = 0;
	init_var(data);
	while (data->i++ < 1024)
		data->var.tab[data->i] = 0;
	if (!(data->mlx.mlx = mlx_init()))
		ft_error(data, "Mlx init failed\n");
	mlx_get_screen_size(data->mlx.mlx, &data->screenx, &data->screeny);
	data->rx = (data->rx > data->screenx) ? data->screenx : data->rx;
	data->ry = (data->ry > data->screeny) ? data->screeny : data->ry;
	ft_get_text_img(data);
	data->mlx.img = mlx_new_image(data->mlx.mlx, data->rx, data->ry);
	data->mlx.addr = (int*)mlx_get_data_addr(data->mlx.img,
		&data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
	if (data->save == 1)
		main_loop(data);
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->rx, data->ry, "Cub3D");
	mlx_hook(data->mlx.win, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, key_released, data);
	mlx_hook(data->mlx.win, 33, 1L << 17, ft_close, data);
	mlx_loop_hook(data->mlx.mlx, &main_loop, data);
	mlx_loop(data->mlx.mlx);
}
