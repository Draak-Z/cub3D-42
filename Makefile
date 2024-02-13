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

SRCS = 	srcs/raycasting.c\
		srcs/errors.c\
		srcs/ft_lst.c\
		srcs/get_next_line_utils.c\
		srcs/get_next_line.c\
		srcs/init.c\
		srcs/rfc.c\
		srcs/map_parser.c\
		srcs/parsing_utils.c\
		srcs/save.c\
		srcs/texture.c\
		srcs/map_walls.c\
		srcs/img_drawing.c\
		srcs/keys.c\
		srcs/wasd.c\
		srcs/sprites.c\
		srcs/main.c\

SRCSBONUS = bonus/raycasting_bonus.c\
			bonus/errors_bonus.c\
			bonus/ft_lst_bonus.c\
			bonus/get_next_line_utils_bonus.c\
			bonus/get_next_line_bonus.c\
			bonus/init_bonus.c\
			bonus/rfc_bonus.c\
			bonus/map_parser_bonus.c\
			bonus/parsing_utils_bonus.c\
			bonus/save_bonus.c\
			bonus/texture_bonus.c\
			bonus/map_walls_bonus.c\
			bonus/img_drawing_bonus.c\
			bonus/keys_bonus.c\
			bonus/wasd_bonus.c\
			bonus/sprites_bonus.c\
			bonus/main_bonus.c\

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
