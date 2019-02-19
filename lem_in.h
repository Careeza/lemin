/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:30:37 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/19 01:22:01 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include <stdio.h>

# define BUFF_SIZE 4096

#define CSI "\033["
#define CSI_GREEN CSI "32;01m"
#define CSI_WHITE CSI "37;01m"
#define CSI_BLUE CSI "34;01m"
#define CSI_YELLOW CSI "33;01m"
#define CSI_RED CSI "31m"
#define CSI_RESET CSI "0m"


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
}				t_all;

/*typedef struct	s_data
{
	int	power;
	int len;
	int	*path;
}				t_path;*/

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
	int		lesscoup;
	int		step;
	int		courant;
	int		flag;
	int		k;
	int		lesslink;
	int		deck;
}				t_algo;

char		**ft_strsplit_lem(char const *s, char c);
int		ft_malloc_list(t_algo *algo, int room);
int		ft_algo(t_room *room, t_algo *algo, t_all *all);

int		ft_verif_doublons(t_room *room, t_all *all, t_algo *algo);
char	*ft_strsub_lem(char const *s, unsigned int start, size_t len);

void	print_dbint(int *list, int len, t_room *room);
int		ft_str_is_digit(char *str, char c);
int		ft_verif_link(t_room *room, char *str, t_all *all);
int		nbr_space(char *str, char c);
int		ft_verif_link2(t_room *room, char *str, t_all *all, int inlink);
int		ft_index_for(char *str, t_room *room, int nbrroom, int lenstr);
int		ft_verif_tube(int indexa, int indexb, t_room *room);

void	ft_display(int curr_ant, t_special_ant *ghost, t_room *room, t_algo *algo);
void	ft_print_room(t_room *room, int i);
void	ft_print_ant(t_special_ant *room, int nb);
void	ft_print_struct(t_room *room, int nb);
int		ft_parser(t_all *all, t_room *room, int i, int index);
int		ft_nm(char *str, t_room *room, int fourmis, int nbroom);
int		ft_check_link(t_all *all, t_room *room, int start);

int		ft_parser_error(char *str);
int		ft_light_error(char *str);

int		ft_call_power(t_room *room, t_algo *algo, t_all *all);

int		ft_found_path(t_algo *algo, t_room *room, t_all *all);
int		ft_cycle_detector(t_special_ant *fourmis, int curr_ant, t_room *room);
void	ft_cpint_n(int *path, int *dest, int len);
int		ft_fill_fourmi(int curr_ant, t_special_ant *ant, int lencycle, t_all *all);

int		ft_print_ant_path(t_special_ant *ant, t_all *all, t_room *room, t_algo *algo);

void	ft_color(int step, int i);
void	ft_stop(void);
void	ft_sort_room(t_room *room, t_all *all);

int		ft_putstr_color_red(char *str);
int		ft_putstr_color_yellow(char *str);
void	ft_reset_i(t_room *room, int nbroom);
void	ft_init_db_int(int *list, int len);
t_special_ant *ft_init_ant(int nbrfourmis, t_all *all);

t_path *ft_init_path(t_room *room, t_algo *algo, t_all *all);
int		ft_init_algo(t_algo *algo, t_all *all, t_room *room);
void	ft_cp_dbdint(t_path *way, int k, int nb_path, int exept);

int		ft_create_flux(t_room *room, t_algo *algo, t_path *way);
int		ft_gestion_pack(t_algo *algo, t_path *way);
t_special_ant	*ft_give_path_to_ant(t_algo *algo, t_path *way, int i, t_all *all);
int		ft_play_and_print(t_special_ant *ant, t_room *room, t_algo *algo, t_all *all);

void			ft_reset_power(t_room *room, int nbroom, t_algo *algo);
int		ft_list2_to1(t_algo *algo, int cmt);

#endif
