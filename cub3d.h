/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 19:48:08 by bmaudet           #+#    #+#             */
/*   Updated: 2021/05/03 15:03:27 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define K_A 97
# define K_D 100
# define K_S 115
# define K_W 119
# define K_AR_L 65361
# define K_AR_R 65363
# define K_ESC 65307
# define BUFFER_SIZE 4096

typedef struct		s_spritescoord
{
	double			x;
	double			y;
}					t_spritescoord;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_texvar
{
	double			step;
	double			wallx;
	int				texx;
	int				texy;
	double			texpos;
	int				texnum;
}					t_texvar;

typedef struct		s_sprites
{
	int				nbspr;
	int				*order;
	double			*dist;
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstartx;
	int				drawstarty;
	int				drawendy;
	int				drawendx;
	int				spritewidth;
	double			*zbuffer;
}					t_sprites;

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				w;
	int				h;
}					t_mlx;

typedef struct		s_variables
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			movespeed;
	double			rotspeed;
	int				tab[1024];
	int				color;
	double			raydirx;
	double			raydiry;
	double			camerax;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			perpwalldist;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				x;
}					t_variables;

typedef struct		s_data
{
	int				rx;
	int				ry;
	int				r;
	int				f;
	int				c;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sp;
	int				nblines;
	int				sizeline;
	char			**map;
	char			start;
	int				dx;
	int				dy;
	int				fcnb;
	int				rnb;
	int				save;
	int				screenx;
	int				screeny;
	int				error;
	int				inmap;
	int				index;
	int				sum;
	int				i;
	char			*line;
	t_spritescoord	*sc;
	t_mlx			mlx;
	t_mlx			text[5];
	t_variables		var;
	t_texvar		tv;
	t_rgb			rgb;
	t_list			*list;
	t_sprites		z;
}					t_data;

int					ft_lstsize(t_list *lst);
void				ft_lstclear(t_list **lst);
void				ft_lstadd_back(t_list **alst, t_list *new, t_data *data);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
int					ft_close(t_data *vars);
void				drawline(t_data *data, int y);
void				math(t_data *data);
void				calc(t_data *data);
int					key_press(t_data *data);
int					key_pressed(int keycode, t_data *data);
int					key_released(int keycode, t_data *data);
int					main_loop(t_data *data);
void				init_var(t_data *data);
void				raycasting(t_data *data);
void				w(t_data *data);
void				a(t_data *data);
void				s(t_data *data);
void				d(t_data *data);
void				find_sprites(t_data *data);
void				sprite_coords(t_data *data, int i, int j, int v);
void				sprites(t_data *data);
void				ft_cub(char *str, t_data *data);
void				ft_parsing(char *fichier, t_data *data);
void				ft_parsing_map(t_data *data, t_list	*tmp);
int					ft_strclen(char *str);
int					ft_charinstr(char *str, char c);
int					ft_start(char c, t_data *data, int i, int j);
void				ft_rfc(char **str, t_data *data);
int					ft_r(char *str, t_data *data);
int					ft_fc(char *str, t_data *data);
void				ft_texture(char *str, t_data *data);
void				ft_init(t_data *data);
void				ft_walls(t_data *data, int i, int j);
int					ft_is_in_map(char *str, t_data *data);
void				ft_parse_map(char *str, t_data *data);
int					ft_get_map(char *str, t_data *data);
void				ft_error(t_data *data, char *str);
void				ft_check_errors(t_data *data);
void				ft_save(t_data *data);
void				ft_init_more(t_data *data);
int					ft_emptyline(char *str);
int					wrong_line(char *str);
int					ft_check_save(char *str);
int					ft_it_char(char *str, char c);
void				ft_get_text_addr(t_data *data);
void				ft_get_text_img(t_data *data);
int					ft_is_char_good(char *str, int rorfc);
void				rgb(char *str, t_data *data);

#endif
