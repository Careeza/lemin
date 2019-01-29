/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:30:37 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/29 15:41:22 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include <stdio.h>
# define BUFF_SIZE 4096


typedef struct	s_all
{
	char	**map;
	long	fourmis;
	int		room;
}				t_all;

typedef struct	s_room
{
	int		start_end; //ok
	char	*name; //ok
	int		links;
	char	*index;
	char	**way;
	int		power;
	int		slot;
	int		previous;
	int		passage;
	int		i;
}				t_room;

typedef struct	s_algo
{
	int		index_start;
	int		index_end;
	int		*list1;
	int		*list2;

}				t_algo;

int		ft_algo(t_room *room, t_algo *algo, long fourmis, int nbrroom);

int		ft_verif_doublons(t_room *room, t_all *all, t_algo *algo);

int		ft_str_is_digit(char *str, char c);
int		ft_verif_link(t_room *room, char *str, t_all *all);
int		nbr_space(char *str, char c);
int		ft_verif_link2(t_room *room, char *str, t_all *all, int inlink);
int		ft_index_for(char *str, t_room *room, int nbrroom, int lenstr);

void	ft_print_struct(t_room *room, int nb);
int		ft_parser_error(char *str);
int		ft_parser(t_all *all, t_room *room, int i);
int		ft_fill_name(char *str, t_room *room);
int		ft_check_link(t_all *all, t_room *room, int start);

#endif
