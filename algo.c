/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:11:53 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/06 10:46:07 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//int		ft_fill_power(t_room *room, t_algo *algo)

t_fourmi	*ft_foumisse(long fourmis, t_algo *algo)
{
	long	i;
	t_fourmi *ants;

	if (!(ants = (t_fourmi*)malloc(sizeof(t_fourmi) * (fourmis))))
		return (NULL);
	i = 1;
	while (i <= fourmis)
	{
		ants[i - 1].name = i;
		ants[i - 1].curr = algo->index_start;
		ants[i - 1].previous = -42;
		i++;
	}
	return (ants);
}

int		ft_fill_power(t_room *room, t_algo *algo)
{
	int i;
	int j;
	int cmt;
	int curr;

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
				curr = ft_atoi(room[algo->list1[i]].way[j]);
				if (room[curr].power + room[curr].pass)
				{
					room[atoi(room[algo->list1[i]].way[j])].power = k;
					algo->list2[cmt] = ft_atoi(room[algo->list1[i]].way[j]);
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

void			ft_refresh_power(t_all *all, t_room *room, t_algo *algo)
{
	int i;

	i = 0;
	while (i < all->room)
	{
		if (i != algo->index_end)
			room[i].power = INT_MAX;
		else
			room[i].power = 0;
	}
	room[algo->index_end].pass = 0;
}

t_special_ant	*ft_init_ghost(t_all *all)
{
	int i;
	t_special_ant *ghost;

	i = 0;
	if (!(ghost = (t_special_ant*)malloc(sizeof(t_special_ant) * (all->fourmis))))
		return (NULL);
	while (i < all->fourmis)
	{
		ghost[i].i = i;
		ghost[i].len = 0;
		if (!(ghost[i].path = (int*)malloc(sizeof(int) * (all->room))))
			return (NULL);
		i++;
	}
	return (ghost);
}

int		ft_power_call(t_algo *algo, t_room *room, t_all *all)
{
	algo->list1[0] = algo->index_end;
	algo->list1[1] = -42;
	ft_refresh_power(all, room, algo);
	ft_fill_power(room, algo);
//	ft_move_ghost(room, algo);
	return (0);
}

int		ft_algo(t_room *room, t_algo *algo, t_all *all)
{
	t_fourmi *ant;
	t_special_ant *ghost;

	if (!(algo->list1 = (int*)malloc(sizeof(int) * (all->room))))
		return (0);
	if (!(algo->list2 = (int*)malloc(sizeof(int) * (all->room))))
		return (0);
	ghost = ft_init_ghost(all);
	ft_power_call(algo, room, all);
	free(algo->list1);
	free(algo->list2);
	if (room[algo->index_start].power == 0)
		return (ft_parser_error("Broken path\n"));
	//checker si start a une power pour regarder si le path est valide entre start et end
	ant = ft_foumisse(all->fourmis, algo);
//	ft_print_ant(ant, fourmis);
	algo->fourmis = all->fourmis;
	return (0);
}
