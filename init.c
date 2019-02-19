/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:57:31 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/19 01:23:47 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_init_algo(t_algo *algo, t_all *all, t_room *room)
{
	if (!(algo->list1 = (int*)malloc(sizeof(int) * (all->room))))
		return (-1);
	if (!(algo->list2 = (int*)malloc(sizeof(int) * (all->room))))
		return (-1);
	algo->list1[0] = algo->index_start;
	algo->list1[1] = -42;
	algo->courant = 0;
	algo->step = 1;
	room[algo->index_start].power = 1;
	return (0);
}

t_path *ft_init_path(t_room *room, t_algo *algo, t_all *all)
{
	t_path		*way;
	int			i;
	int			j;
	int			lesslink;

	lesslink = room[algo->index_start].links > room[algo->index_end].links ? room[algo->index_end].links : room[algo->index_start].links;
	if (!(way = (t_path*)malloc(sizeof(t_path) * lesslink)))
		return (NULL);
	i = 0;
	while (i < lesslink)
	{
		way[i].nb_path = 0;
		if (!(way[i].len_path = (int*)malloc(sizeof(int) * (lesslink))))
			return (NULL);
		j = 0;
		while (j < lesslink)
		{
			way[i].len_path[j] = 0;
			j++;
		}
		if (!(way[i].rev = (int*)malloc(sizeof(int) * (all->room))))
			return (NULL);
		if (!(way[i].path = (int**)malloc(sizeof(int*) * (lesslink))))
			return (NULL);
		j = 0;
		while (j < lesslink)
		{
			if (!(way[i].path[j] = (int*)malloc(sizeof(int) * (all->room))))
				return (NULL);
			j++;
		}
		i++;
	}
	return (way);
}

