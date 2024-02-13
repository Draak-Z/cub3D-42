/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:43:48 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/05 15:57:32 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parsing_map(t_data *data, t_list *tmp)
{
	data->i = 0;
	if (!(data->map = malloc(sizeof(char*) * (data->nblines + 1))))
		ft_error(data, "Malloc map failed\n");
	while (tmp->next)
	{
		if (data->inmap && !ft_emptyline(tmp->content)
			&& data->index < data->nblines)
			data->error = 12;
		if ((data->inmap = ft_is_in_map(tmp->content, data)) == 1)
		{
			data->index++;
			ft_get_map(tmp->content, data);
		}
		tmp = tmp->next;
	}
	data->map[data->i] = NULL;
	ft_check_errors(data);
	find_sprites(data);
}

void	ft_parsing(char *fichier, t_data *data)
{
	int			fd;
	int			ret;

	ret = 1;
	if ((fd = open(fichier, O_RDONLY)) == -1)
		ft_error(data, "Invalid .cub file\n");
	while (ret > 0)
	{
		ret = get_next_line(fd, &data->line);
		if (ret != -1 && data->error != 10)
			ft_lstadd_back(&data->list, ft_lstnew(data->line), data);
		if (data->error > 0 || ret == -1)
			ft_error(data, "");
		ft_rfc(&data->line, data);
		ft_texture(data->line, data);
		ft_parse_map(data->line, data);
	}
	close(fd);
	if (data->sizeline == 0 || data->nblines == 0)
		ft_error(data, "Missing map\n");
	ft_parsing_map(data, data->list);
}

void	ft_cub(char *str, t_data *data)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		if (!i)
			ft_error(data, "Map file extension is not .cub\n");
		i--;
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b'
		&& str[i + 4] == '\0')
		ft_parsing(str, data);
	else
		ft_error(data, "Map file extension is not .cub\n");
}

int		main(int argc, char **argv)
{
	t_data data;

	ft_init(&data);
	if (argc == 2 || (argc == 3 && ft_check_save(argv[1]) == 1))
	{
		if (argc == 3)
		{
			data.save = 1;
			ft_cub(argv[2], &data);
		}
		else
			ft_cub(argv[1], &data);
		raycasting(&data);
	}
	else
		write(2, "Error\nInvalid arguments\n", 24);
}
