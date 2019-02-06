/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:48:47 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/06 17:39:42 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_sort_index(t_room *room, int i)
{
	int j;
	int tmp;
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
				tmp = room[i].index[j];
				room[i].index[j] = room[i].index[j - 1];
				room[i].index[j - 1] = tmp;
				j -= j >= 2 ? -2 : j;
				corr++;
				printf("JE TRIE\n");
			}
			j++;
		}
	}
}

void	ft_sort_room(t_room *room, t_algo *algo, t_all *all)
{
	int i;

	(void)algo;
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

int		ft_algo(t_room *room, t_algo *algo,t_all *all)
{
	int i;

	if (!(algo->list1 = (int*)malloc(sizeof(int) * (all->room))))
		return (0);
	if (!(algo->list2 = (int*)malloc(sizeof(int) * (all->room))))
		return (0);
	algo->list1[0] = algo->index_end;
	algo->list1[1] = -42;
	ft_fill_power(room, algo);
	free(algo->list1);
	free(algo->list2);
	if (room[algo->index_start].power == 0)
		return (ft_parser_error("Broken path\n"));
//	ft_print_struct(room, all->room);
	i = 0;
	while (i < all->room)
	{
		printf("room[%d] = ", i);
		print_dbint(room[i].index, room[i].links);
		i++;
	}
	ft_sort_room(room, algo, all);
	i = 0;
	while (i < all->room)
	{
		printf("room[%d] = ", i);
		print_dbint(room[i].index, room[i].links);
		i++;
	}
//	printf("\n\n\nj4qitriermamen\n\n\n\n");
//	ft_print_struct(room, all->room);
	return (0);
}
