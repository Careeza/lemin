/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 05:41:52 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/09 05:47:01 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_reset_i(t_room *room, int nbroom)
{
	int i;

	i = 0;
	while (i < nbroom)
	{
		room[i].pass = 0;
		room[i].i = 0;
		room[i].previous = -42;
		i++;
	}
}

void			ft_cpint_n(int *path, int *dest, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		dest[i] = path[i];
		i++;
	}
}

void			ft_init_db_int(int *list, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		list[i] = 0;
		i++;
	}
}

t_special_ant	*ft_init_ant(int nbrfourmis, t_all *all)
{
	t_special_ant	*ant;
	int				i;

	i = 0;
	if (!(ant = (t_special_ant*)malloc(sizeof(t_special_ant) * (nbrfourmis))))
		return (NULL);
	while (i < nbrfourmis)
	{
		ant[i].coup = 0;
		if (!(ant[i].wait = (int*)malloc(sizeof(int) * (all->room))))
			return (NULL);
		ft_init_db_int(ant[i].wait, all->room);
		if (!(ant[i].path = (int*)malloc(sizeof(int) * (all->room))))
			return (NULL);
		if (!(ant[i].savepath = (int*)malloc(sizeof(int) * (all->room))))
			return (NULL);
		ant[i].len = 0;
		ant[i].savelen = 0;
		i++;
	}
	return (ant);
}
