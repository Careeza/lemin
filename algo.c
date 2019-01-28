/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:41:56 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/28 16:53:48 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_previous(t_room *room, int index)
{
	printf("start ou end\n");
	while (room[index].i >= room[index].links || room[index].start_end == 1)
	{
		if (room[index].start_end == 2)
			return (-42);
		room[index].i = 0;
		index = room[index].previous;
	}
	return (index);
}

int		ft_fill_power(t_room *room, t_algo *algo)
{
	int		index;
	int		next;

	index = algo->index_end;
	while (index != -42)
	{
		printf("index =%d\n", index);
		if (ft_atoi(room[index].way[room[index].i]) != room[index].previous)
		{
			next = ft_atoi(room[index].way[room[index].i]);
			room[next].previous = index;
			if (room[index].power + 1 <= room[next].power)
				room[next].power = room[index].power + 1;
			room[index].i++;
			index = next;
			if (room[index].start_end == 1)
				index = ft_previous(room, index);
		}
		else
		{
			room[index].i++;
			if (room[index].i >= room[index].links)
				index = ft_previous(room, index);
		}
	}
	return (0);
}

int		ft_algo(t_room *room, t_algo *algo, long fourmis)
{
	(void)fourmis;
	ft_fill_power(room, algo);
	return (0);
}
