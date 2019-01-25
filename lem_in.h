/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 14:30:37 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/24 13:25:52 by prastoin         ###   ########.fr       */
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
	int		fourmis;
	int		room;
}				t_all;

typedef struct	s_room
{
	int		start_end; //ok
	char	*name; //ok
	int		links;
	int		*index;
}				t_room;

int		ft_verif_link(t_room *room, char *str, t_all *all);
int		nbr_space(char *str, char c);
int		ft_verif_link2(t_room *room, char *str, t_all *all, int inlink);
int		ft_parser(t_all *all, t_room *room);
t_room	ft_fill_name(char *str, t_room room);
int		ft_check_link(t_all *all, t_room *room, int start);

#endif
