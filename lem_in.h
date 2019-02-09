/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:30:37 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/09 04:20:02 by prastoin         ###   ########.fr       */
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
	int coup;
	int *path;
	int	*savepath;
	int	*wait;
	int savelen;
	int len;
//	int		nb;
	int		curr;
	int		i;
}				t_special_ant;

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
	int		i;
	long	power;
	int		slot;
	long	pass;
	int		*coup;
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

	int		flag;
}				t_algo;

typedef struct	s_fourmi
{
	int		name;
	int		curr;
	int		previous;
	int		next;
	int		*path;
}				t_fourmi;

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

void	ft_display(int best, t_special_ant *ghost, t_room *room, t_algo *algo);
void	ft_print_room(t_room *room, int i);
void	ft_print_ant(t_special_ant *room, int nb);
void	ft_print_struct(t_room *room, int nb);
int		ft_parser(t_all *all, t_room *room, int i);
int		ft_fill_name(char *str, t_room *room, int fourmis, int nbroom);
int		ft_check_link(t_all *all, t_room *room, int start);

int		ft_parser_error(char *str);
int		ft_light_error(char *str);

int		ft_call_power(t_room *room, t_algo *algo, t_all *all);

int		ft_found_path(t_algo *algo, t_room *room, t_all *all);
int		ft_cycle_detector(t_special_ant *fourmis, int curr_ant, int len, int *path);
void	ft_cpint_n(int *path, int *dest, int len);
int		ft_fill_fourmi(int curr_ant, t_special_ant *ant, int lencycle, t_all *all);

int		ft_print_ant_path(t_special_ant *ant, t_all *all, t_room *room, t_algo *algo);

void	ft_color(int step, int i);
void	ft_stop(void);
void	ft_sort_room(t_room *room, t_all *all);

#endif
