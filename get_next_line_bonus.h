/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:03:37 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 14:57:09 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# define GNL_ERROR -1
# define GNL_OK 1
# define GNL_EOF 0
# define OPEN_MAX 10240

# include <stddef.h>

int		last_line(char **line, char *stock, int n, int result);
int		get_next_line(int fd, char **line);
char	*ft_strndup(char *s1, int n);
size_t	ft_strlen(char *s);
char	*ft_strnjoin(char *s1, char *s2, int n);
int		ft_strcchr(char *s, char c);
char	*ft_strncpy(char *dest, char *src);

#endif
