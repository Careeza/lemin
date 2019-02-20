/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:30:37 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 21:46:39 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFF_SIZE 4096
# define CSI "\033["
# define CSI_GREEN CSI "32;01m"
# define CSI_WHITE CSI "37;01m"
# define CSI_BLUE CSI "34;01m"
# define CSI_YELLOW CSI "33;01m"
# define CSI_RED CSI "31m"
# define CSI_RESET CSI "0m"

typedef struct	s_special_ant
{
	int		*path;
	int		len;
	int		curr;
	int		i;
}				t_special_ant;

typedef struct	s_path
{
	int		**path;
	int		nb_path;
	int		*len_path;
	int		*rev;
	float	powermax;
}				t_path;

typedef struct	s_all
{
	char	**map;
	long	fourmis;
	int		room;
	char	*str;
	int		fd;
}				t_all;

typedef struct	s_room
{
	int		start_end;
	char	*name;
	int		links;
	int		previous;
	int		*index;
	long	power;
	int		courant;
	int		slot;
	int		prev;
}				t_room;

typedef struct	s_algo
{
	int		index_start;
	int		index_end;
	int		*list1;
	int		*list2;
	int		fourmis;
	int		step;
	int		courant;
	int		flag;
	int		k;
	int		lesslink;
	int		cmt;
}				t_algo;

/*
** ft_find_path.c
*/

void			ft_create_new_flux(t_room *room, t_path *way,
					t_algo *algo, int len);
int				ft_create_flux(t_room *room, t_algo *algo, t_path *way);
int				ft_gestion_pack(t_algo *algo, t_path *way);
int				ft_give_path_to_ant2(t_path *way, int i, int *power);
t_special_ant	*ft_give_path_to_ant(t_algo *algo, t_path *way,
					int i, t_all *all);

/*
** ft_find_path2.c
*/
void			ft_create_flux2(t_path *way, t_algo *algo, int len);
void			ft_init_create_flux(int *len, int *curr,
					int *prev, t_algo *algo);

/*
** display.c
*/

int				ft_putstr_color_yellow(char *str);
int				ft_putstr_color_red(char *str);
void			ft_color(int line, int i);
void			ft_display(int curr_ant, t_special_ant *ghost, t_room *room,
					t_algo *algo);

/*
** ft_play_print.c
*/

void			ft_move(t_special_ant *ant, int curr_ant, t_room *room);
int				ft_play_and_print(t_special_ant *ant, t_room *room,
					t_algo *algo, t_all *all);

/*
** init.c
*/

int				ft_init_algo(t_algo *algo, t_all *all, t_room *room);
t_path			*ft_init_path(t_algo *algo, t_all *all);

/*
** parser.c
*/

int				ft_start_end(t_room *room, t_all *all, int index, int *i);
int				ft_result(int start_and_end[2], int i, t_all *all,
					t_room *room);
int				ft_parser(t_all *all, t_room *room, int i, int index);
int				ft_broken_path(t_path *way, t_algo *algo, t_all *all);

/*
** parser_2.c
*/
int				ft_verif_doublons(t_room *room, t_all *all, t_algo *algo);
int				ft_check_link(t_all *all, t_room *room, int start);
int				ft_light_error(char *str);
int				ft_parser_error(char *str, int i, t_all *all, t_room *room);

/*
** power.c
*/

void			ft_fill_power_cut(t_room *room, t_algo *algo, int i, int j);
int				ft_fill_power(t_room *room, t_algo *algo, int i, t_path *path);
int				ft_call_power(t_room *room, t_algo *algo, t_all *all);

/*
** power_tools.c
*/
int				ft_list2_to1(t_algo *algo, int cmt);
void			ft_reset_power(t_room *room, int nbroom, t_algo *algo);

/*
** struct_tools.c
*/
void			ft_sort_index(t_room *room, int i);
void			ft_sort_room(t_room *room, t_all *all);
int				ft_nm(char *str, t_room *room, int fourmis, int nbroom);
int				ft_verif_link(t_room *room, char *str, t_all *all);
int				ft_verif_link2(t_room *room, char *str, t_all *all, int indexa);

/*
** tools.c
*/
int				ft_verif_tube(int indexa, int indexb, t_room *room);
int				nbr_space(char *str, char c);
int				ft_str_is_digit(char *str, char c);
int				ft_free(t_room *room, t_all *all, t_path *way, t_algo *algo);

/*
** tools2.c
*/
void			ft_cpint_n(int *path, int *dest, int len);
void			ft_cp_dbdint(t_path *way, int k, int nb_path, int exept);
t_special_ant	*ft_init_ant(int nbrfourmis, t_all *all);
int				ft_file(t_all *all);

/*
** free.c
*/
int				ft_free_room(t_room *room, int nb);
int				ft_free_path(t_path *way, int nb);
int				ft_free_list(int *s1, int *s2);
int				ft_free_ant(t_special_ant *ant, int nb);
int				ft_free_all(t_all *all);

/*
** OTHERS
*/
char			*ft_strsub_lem(char const *s, unsigned int start, size_t len);
char			**ft_strsplit_lem(char const *s, char c);
void			ft_stop(void);

#endif
