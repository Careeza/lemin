/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:48:47 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/09 04:50:28 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_list2_to1(t_algo *algo, int cmt, int *k)
{
	int	i;

	algo->list2[cmt] = -42;
	i = 0;
	while (algo->list2[i] != -42)
	{
		algo->list1[i] = algo->list2[i];
		i++;
	}
	algo->list1[i] = -42;
	*k = *k + 1;
	return (0);
}

void	ft_fill_power(t_room *room, t_algo *algo, int cmt, int k)
{
	int i;
	int j;

	while (cmt != 0)
	{
		i = 0;
		cmt = 0;
		while (algo->list1[i] != -42)
		{
			j = -1;
			while (++j < room[algo->list1[i]].links)
			{
				if (room[room[algo->list1[i]].index[j]].power == 0)
				{
					room[room[algo->list1[i]].index[j]].power = k;
					algo->list2[cmt] = room[algo->list1[i]].index[j];
					cmt++;
				}
			}
			i++;
		}
		ft_list2_to1(algo, cmt, &k);
	}
}

int		ft_init_algo(t_algo *algo, t_all *all, t_room *room)
{
	if (!(algo->list1 = (int*)malloc(sizeof(int) * (all->room))))
		return (-1);
	if (!(algo->list2 = (int*)malloc(sizeof(int) * (all->room))))
		return (-1);
	room[algo->index_end].power = 1;
	algo->list1[0] = algo->index_end;
	algo->list1[1] = -42;
	room[algo->index_start].power = (LONG_MAX / 2) + 1;
	return (0);
}

int		ft_check_lonely_room(t_room *room, t_algo *algo)
{
	int i;
	int save;

	save = 0;
	i = 0;
	while (i < room[algo->index_start].links)
	{
		if (room[room[algo->index_start].index[i]].power == 0)
		{
			save++;
			room[room[algo->index_start].index[i]].power = INT_MAX;
		}
		i++;
	}
	return (save);
}

int		ft_call_power(t_room *room, t_algo *algo, t_all *all)
{
	int		save;

	if (ft_init_algo(algo, all, room) == -1)
		return (-1);
	ft_fill_power(room, algo, 1, 2);
	save = ft_check_lonely_room(room, algo);
	free(algo->list1);
	free(algo->list2);
	if (room[algo->index_start].power == 0)
		return (ft_parser_error("Broken path\n"));
	ft_sort_room(room, all);
	room[algo->index_start].links -= save;
	return (0);
}
