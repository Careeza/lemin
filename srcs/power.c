/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:48:47 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/19 20:34:21 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_fill_power_cut(t_room *room, t_algo *algo, int i, int j)
{
	if (room[room[algo->list1[i]].index[j]].power == 0
		&& room[algo->list1[i]].index[j] != algo->index_end
		&& (!(room[algo->list1[i]].prev == 1
		&& room[room[algo->list1[i]].index[j]].courant == INT_MAX)))
	{
		if (room[algo->list1[i]].courant == INT_MAX
			|| room[algo->list1[i]].courant
			<= room[room[algo->list1[i]].index[j]].courant)
		{
			room[room[algo->list1[i]].index[j]].power = 1;
			algo->list2[algo->cmt] = room[algo->list1[i]].index[j];
			if (room[room[algo->list1[i]].index[j]].courant == INT_MAX)
				room[room[algo->list1[i]].index[j]].previous = algo->list1[i];
			else
				room[room[algo->list1[i]].index[j]].prev =
					room[algo->list1[i]].prev + 1;
			algo->cmt++;
		}
	}
}

int		ft_fill_power(t_room *room, t_algo *algo, int i)
{
	int j;

	while (algo->cmt != 0)
	{
		i = 0;
		algo->cmt = 0;
		while (algo->list1[i] != -42)
		{
			j = -1;
			while (++j < room[algo->list1[i]].links)
			{
				if (room[algo->list1[i]].index[j] == algo->index_end
					&& room[algo->list1[i]].courant == INT_MAX)
				{
					room[room[algo->list1[i]].index[j]].previous =
						algo->list1[i];
					return (0);
				}
				ft_fill_power_cut(room, algo, i, j);
			}
			i++;
		}
		ft_list2_to1(algo, algo->cmt);
	}
	return (-1);
}

int		ft_call_power(t_room *room, t_algo *algo, t_all *all)
{
	t_path			*way;
	int				i;
	t_special_ant	*ant;

	algo->fourmis = all->fourmis;
	algo->lesslink = room[algo->index_start].links
		> room[algo->index_end].links ? room[algo->index_end].links
		: room[algo->index_start].links;
	if (ft_init_algo(algo, all, room) == -1)
		return (-1);
	if (!(way = (ft_init_path(algo, all))))
		return (-1);
	while (1)
	{
		algo->cmt = 1;
		if (ft_fill_power(room, algo, 0) == -1)
			break ;
		if (ft_create_flux(room, algo, way) == -1)
			break ;
		ft_reset_power(room, all->room, algo);
	}
	i = ft_gestion_pack(algo, way);
	ant = ft_give_path_to_ant(algo, way, i, all);
	ft_play_and_print(ant, room, algo, all);
	ft_free_ant(ant, all->fourmis);
	return (ft_free(room, all, way, algo));
}
