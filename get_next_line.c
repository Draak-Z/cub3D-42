/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:02:04 by bmaudet           #+#    #+#             */
/*   Updated: 2021/04/23 16:42:00 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	last_line(char **line, char *stock, int n, int result)
{
	if (!(*line = ft_strnjoin(*line, stock, n == -1 ? result : n)))
		return (GNL_ERROR);
	ft_strncpy(stock, stock + n + 1);
	return (GNL_EOF);
}

int	get_next_line(int fd, char **line)
{
	static char	stock[OPEN_MAX][BUFFER_SIZE + 1];
	int			result;
	int			n;

	if (fd < 0 || fd > OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (GNL_ERROR);
	*line = 0;
	while ((n = ft_strcchr(stock[fd], '\n')) < 0)
	{
		if ((*line = ft_strnjoin(*line, stock[fd], BUFFER_SIZE)) == NULL)
			return (GNL_ERROR);
		if ((result = read(fd, stock[fd], BUFFER_SIZE)) < 0)
			return (GNL_ERROR);
		if (result < BUFFER_SIZE && (n = ft_strcchr(stock[fd], '\n')) < 0)
			return (last_line(line, stock[fd], n, result));
		stock[fd][result] = '\0';
	}
	if (!(*line = ft_strnjoin(*line, stock[fd], n == -1 ? result : n)))
		return (GNL_ERROR);
	ft_strncpy(stock[fd], stock[fd] + n + 1);
	return (GNL_OK);
}
