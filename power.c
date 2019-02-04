/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:52:03 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/04 16:45:41 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_init_power(t_room *room, t_all *all)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < all->room)
	{
		j = 0;
		if (!(room[i].powertest = (long *)malloc(sizeof(long) * room[i].links)))
			return (-1);
		while (j < room[i].links)
		{
			room[i].powertest[j] = INT_MAX;
			j++;
		}
		i++;
	}
	return (0);
}

int		ft_previous(t_room *room, int index, t_special_ant *ghost, int index_end)
{
	room[ghost->curr].pass = 0;
//	printf("No way need to previous %d\n", room[index].previous);
	if (index == index_end)
		return (-42);
	ghost->power--;
	ghost->curr = room[index].previous;
	ghost->previous = index; //normalement inutile
	return(room[index].previous);
}

int		ft_move_ghost_ant(t_room *room, t_special_ant *ghost, t_algo *algo)
{
	int i;
	int j;
	int next;

	i = 0;
	room[ghost->curr].pass = 1;
	while (i < room[ghost->curr].links)
	{
		next = ft_atoi(room[ghost->curr].way[i]);
		if (next != algo->index_end && room[next].pass != 1)
		{
//			printf("from %d now %d to %d\n", room[ghost->curr].previous, ghost->curr, next);
			j = 0;
			while (atoi(room[next].way[j]) != ghost->curr)
				j++;
			if (room[next].powertest[j] > ghost->power + 1)
			{
				room[next].powertest[j] = ghost->power + 1;
				ghost->power++;
				room[next].previous = ghost->curr;
//				printf("achieve to go to%d\n", next);
				return (next);
			}
		}
		i++;
	}
	return (-42);
}

static int		ft_fill_power(t_room *room, t_algo *algo, t_special_ant *ghost)
{
	int	i;
	int j;
	int	curr;
	int	ok;

	ok = 1;
	curr = algo->index_end;
	i = 0;
	j = 0;
	while (ok != -42)
	{
//		printf("from %d to %d\n", ghost->previous, ghost->curr);
		if ((curr = (ft_move_ghost_ant(room, ghost, algo))) != -42)
		{
//			printf("so curr =%d\n", curr);
			ghost->curr = curr;
		}
		else
			ok = ft_previous(room, ghost->curr, ghost, algo->index_end);
//		ghost->curr = ft_atoi(room[ghost->curr].way[i]);
	}
	return (0);
}

int		ft_power_algo(t_room *room, t_all *all, t_algo *algo)
{
	t_special_ant ghost;
	ft_init_power(room, all);
	ghost.power = 0;
	ghost.curr = algo->index_end;
	ghost.previous = -42;
	ft_fill_power(room, algo, &ghost);
	return (0);
}
