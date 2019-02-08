/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:48:47 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/07 13:47:38 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_sort_index(t_room *room, int i)
{
	int j;
	long tmp;
	int corr;

	corr = 1;
	while (corr != 0)
	{
		corr = 0;
		j = 1;
		while (j < room[i].links)
		{
			if (room[room[i].index[j - 1]].power > room[room[i].index[j]].power)
			{
	//			printf("Je swap %d avec %d\n", room[i].index[j], room[i].index[j - 1]);
				tmp = room[i].index[j];
				room[i].index[j] = room[i].index[j - 1];
				room[i].index[j - 1] = tmp;
				j = j >= 2 ? j - 2 : 0;
				corr++;
	//			printf("JE TRIE\n");
			}
			j++;
		}
	}
}

void	ft_sort_room(t_room *room, t_all *all)
{
	int i;

	i = 0;
	while (i < all->room)
	{
		ft_sort_index(room, i);
		i++;
	}
}

int		ft_fill_power(t_room *room, t_algo *algo)
{
	int i;
	int j;
	int cmt;
	int k;

	k = 2;
	cmt = 1;
	while (cmt != 0)
	{
		i = 0;
		cmt = 0;
		while (algo->list1[i] != -42)
		{
			j = 0;
			while (j < room[algo->list1[i]].links)
			{
				if (room[room[algo->list1[i]].index[j]].power == 0)
				{
					room[room[algo->list1[i]].index[j]].power = k;
					algo->list2[cmt] = room[algo->list1[i]].index[j];
					cmt++;
				}
				j++;
			}
			i++;
		}
		algo->list2[cmt] = -42;
		i = 0;
		while (algo->list2[i] != -42)
		{
	//		printf("ITER%d = %d\n", k, algo->list2[i]);
			algo->list1[i] = algo->list2[i];
			i++;
		}
		algo->list1[i] = -42;
		k++;
	}
	return (0);
}

int		ft_call_power(t_room *room, t_algo *algo,t_all *all)
{
	int i;
	int save;

	if (!(algo->list1 = (int*)malloc(sizeof(int) * (all->room))))
		return (-1);
	if (!(algo->list2 = (int*)malloc(sizeof(int) * (all->room))))
		return (-1);
	room[algo->index_end].power = 1;
	algo->list1[0] = algo->index_end;
	algo->list1[1] = -42;
	room[algo->index_start].power = (LONG_MAX / 2) + 1;
	ft_fill_power(room, algo);
	save = 0;
	i = 0;
	while (i < room[algo->index_start].links)
	{
		if (room[room[algo->index_start].index[i]].power == 0)
		{
			save++;
			room[room[algo->index_start].index[i]].power= INT_MAX;
		}
		i++;
	}
	free(algo->list1);
	free(algo->list2);
	if (room[algo->index_start].power == 0)
		return (ft_parser_error("Broken path\n"));
//	ft_print_struct(room, all->room);
	ft_sort_room(room, all);
	room[algo->index_start].links -= save;
//	ft_print_struct(room, all->room);
	return (0);
}
