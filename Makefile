# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 17:38:02 by bmaudet           #+#    #+#              #
#    Updated: 2021/05/03 15:12:34 by bmaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = 	raycasting.c\
		errors.c\
		ft_lst.c\
		get_next_line_utils.c\
		get_next_line.c\
		init.c\
		rfc.c\
		map_parser.c\
		parsing_utils.c\
		save.c\
		texture.c\
		map_walls.c\
		img_drawing.c\
		keys.c\
		wasd.c\
		sprites.c\
		main.c\

SRCSBONUS = raycasting_bonus.c\
			errors_bonus.c\
			ft_lst_bonus.c\
			get_next_line_utils_bonus.c\
			get_next_line_bonus.c\
			init_bonus.c\
			rfc_bonus.c\
			map_parser_bonus.c\
			parsing_utils_bonus.c\
			save_bonus.c\
			texture_bonus.c\
			map_walls_bonus.c\
			img_drawing_bonus.c\
			keys_bonus.c\
			wasd_bonus.c\
			sprites_bonus.c\
			main_bonus.c\

OBJS = ${SRCS:.c=.o}

OBJSBONUS = ${SRCSBONUS:.c=.o}

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -c

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	${NAME}

${NAME}:	${OBJS} compil_other
		${CC} -o ${NAME} ${OBJS} -lm minilibx-linux/libmlx_Linux.a -lXext -lX11

bonus:	${OBJSBONUS} compil_other
		${CC} -o ${NAME} ${OBJSBONUS} -lm minilibx-linux/libmlx_Linux.a -lXext -lX11

clean:	clean_other
		${RM} ${OBJS}
		${RM} ${OBJSBONUS}

fclean:		clean
			${RM} ${NAME}

compil_other:
		cd minilibx-linux && make

clean_other:
		cd minilibx-linux && make clean

re:		fclean all

.PHONY: clean all fclean re
