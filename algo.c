/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:41:56 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/28 18:20:52 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_restart(t_room *room, t_algo *algo)
{
//	if (room[algo->index_end].i < room[algo->index_end].links)
//		return (-42);
	printf ("RESTART%d\n", room[algo->index_end].i);
	if (room[ft_atoi(room[algo->index_end].way[room[algo->index_end].i])].i < room[ft_atoi(room[algo->index_end].way[room[algo->index_end].i])].links)
		return (algo->index_end);
	else
		room[algo->index_end].i++;
	if (room[algo->index_end].i >= room[algo->index_end].links)
		return (-42);
	return (algo->index_end);
}

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
		if (room[index].i < room[index].links && ft_atoi(room[index].way[room[index].i]) != room[index].previous && (room[ft_atoi(room[index].way[room[index].i])].start_end != 2))
		{
			next = ft_atoi(room[index].way[room[index].i]);
			printf("From %d to %d\n", index, next);
			room[next].previous = index;
			if (room[index].power + 1 <= room[next].power)
				room[next].power = room[index].power + 1;
			if (room[index].start_end != 2)
				room[index].i++;
			index = next;
			if (room[index].start_end == 1)
				if ((index = ft_restart(room, algo)) == -42)
					break ;
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
