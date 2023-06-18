/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:02:42 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 14:55:55 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*ft_strndup(char *s1, int n)
{
	char	*dest;
	int		i;
	int		len;

	dest = 0;
	i = 0;
	len = ft_strlen(s1) + 1;
	if (!(dest = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	while (i < n && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*dst;
	int		i;
	int		j;

	if (s1 == NULL)
		return (ft_strndup(s2, n));
	i = -1;
	j = 0;
	if (!(dst = malloc(sizeof(char) * (ft_strlen(s1) + n + 1))))
	{
		free(s1);
		return (NULL);
	}
	while (s1[++i])
		dst[i] = s1[i];
	while (j < n && s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	free(s1);
	return (dst);
}

char	*ft_strncpy(char *dest, char *src)
{
	unsigned int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_strcchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
