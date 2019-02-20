/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 09:24:57 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 19:11:03 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include "../libft/includes/libft.h"
# include <time.h>

# define SIZE 2
# define BUFF_SIZE 4096
# define KEY_LESS 78
# define KEY_ESC 53
# define KEY_CTRL 256
# define KEY_PLUS 69
# define KEY_UP 125
# define KEY_DOWN 126
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_SPACE 49
# define KEY_NUM6 88
# define KEY_NUM3 85
# define SCREEN_X 1000
# define SCREEN_Y 1000
# define SPEED 2

typedef struct		s_ant
{
	int		curr;
	int		previous;
	int		coup;
	int		i;
	int		firstind;
}					t_ant;

typedef struct		s_room
{
	char	*name;
	int		x;
	int		y;
	int		start_end;
	int		slot;
}					t_room;

typedef struct		s_data
{
	void	*mlx;
	void	*win;
	void	*img2;
	int		*img_ptr2;

	int		i;
	char	**map;
	int		room;
	int		step1;
	int		x_extrem;
	int		y_extrem;
	int		xstart;
	int		ystart;
	int		index_start;
	int		index_end;
	int		zm;
	int		zm2;
	int		fourmis;
	t_room	*room2;
	t_ant	*ant;
	int		oto;
	time_t	time;
	clock_t	clk;
	long	ticks;
	float	speed;
	int		antstart;
	int		antend;
	int		xpos[2];
	int		ypos[2];
	int		use;
	int		rayon;
	int		fd;
}					t_data;

/*
** reading.c
*/
char				*ft_reading(void);
char				**ft_read(void);
void				ft_init_data(t_data *data);
void				ft_check_visu_txt(t_data *data);
void				ft_circle(int x, int y, t_data *data, int color);

/*
** main.c
*/
int					ft_tracertrait(t_data *data, int x, int y);
int					deal_key(int key, t_data *data);
void				ft_init_join(t_data *data, t_room *room);
int					auto_play(t_data *data);

/*
** init.c
*/
int					ft_fill_info(char *str, t_room *room, t_data *data);
int					ft_fill_room(t_data *data, t_room *room, int i);
t_room				*ft_init_complete(t_data *data);
void				ft_init_sqare(t_data *data, t_room *room);
t_room				*ft_init(t_data *data);

/*
** tools.c
*/
int					nbr_space(char *str, char c);
int					ft_nbr_room(t_data *data);
int					ft_index_for_links(char *str, t_room *room, int nbrroom,
						int len);
int					ft_index_for(char *str, t_room *room, int nbrroom);
int					ft_len_to_c(char *str, char c);

/*
** play.c
*/
int					ft_get_index_start(t_room *room, t_data *data);
t_ant				*ft_init_ant(t_data *data, t_room *room);
void				ft_put_red_square(t_data *data, t_room *room, int i);
void				ft_put_green_square(t_data *data, t_room *room, int i,
						t_ant ant);
int					ft_play_cut2(t_room *room, t_data *data, t_ant *ant, int y);

/*
** play2.c
*/
int					ft_play_cut(t_room *room, t_data *data, t_ant *ant, int y);
int					ft_play(t_data *data);
void				ft_play_inv_cut(t_room *room, t_data *data, t_ant *ant,
						int y);
int					ft_play_inv_cut3(t_room *room, t_data *data, t_ant *ant,
						int y);
int					ft_inv_play(t_data *data);

/*
** free.c
*/
void				ft_free_visu(t_data *data);
void				ft_free_visu_room(t_room *room, int nbr);

#endif
