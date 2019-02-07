/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:52:03 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/07 13:45:56 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_special_ant *ft_init_ant(int nbrfourmis, t_all *all)
{
	t_special_ant *ant;
	int i;

	i = 0;
	if(!(ant = (t_special_ant*)malloc(sizeof(t_special_ant) * (nbrfourmis))))
		return (NULL);
	while (i < nbrfourmis)
	{
		ant[i].coup = 0;
		if (!(ant[i].path = (int*)malloc(sizeof(int) * (all->room))))
			return (NULL);
		ant[i].len = 0;
		i++;
	}
	return (ant);
}

void	ft_init_db_int(int *list, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		list[i] = 0;
		i++;
	}
}

int			ft_move(t_room *room, t_special_ant *ant, int curr_ant)
{
	int		curr;
	int		best;

	curr = ant[curr_ant].curr;
	best = -42;
	if (room[curr].i < room[curr].links)
	{
		best = room[curr].index[room[curr].i];
		if (best == room[curr].previous)
		{
			printf("Je veux revenir sur mes pas mais je nai pas le droit\n");
			room[curr].i++;
			best = -42;
		}
		else
		{
			room[best].previous = ant[curr_ant].curr;
			room[curr].i++;
		}
	}
	return (best);
}

int		ft_previous(t_algo *algo, t_room *room, t_special_ant *ant, int curr_ant)
{
	int		curr;

	curr = ant[curr_ant].curr;
	if (curr == algo->index_start)
		return (-42);
	room[curr].pass = 0;
	room[curr].i = 0;
	ant->curr = room[curr].previous;
	return(0);
}

int		ft_find_best_path(t_algo *algo, t_room *room, t_all *all, t_special_ant *ant)
{
	int		curr_ant = 0;
	int		next;
	int		cmt;

	(void)all;
	cmt = 0;
	while (curr_ant < 1)
	{
		ant[curr_ant].curr = algo->index_start;
		while (cmt != -42)
		{
			if (ant[curr_ant].curr != algo->index_end)
			{
				if ((next = ft_move(room, ant, curr_ant)) != -42)
				{
					printf("from %s to %s\n", room[ant[curr_ant].curr].name, room[next].name);
					ant[curr_ant].curr = next;
				}
				else
				{
					printf("I am here %s And i am stuck\n", room[ant[curr_ant].curr].name);
					cmt = ft_previous(algo, room, ant, curr_ant);
//					printf("Je reviens en arrier\n");
				}
			}
			else
			{
					cmt = ft_previous(algo, room, ant, curr_ant);
					printf("Je reviens en arrier\n");
			}
		}
		curr_ant++;
	}
	return (0);
}

int		ft_found_path(t_algo *algo, t_room *room, t_all *all)
{
	t_special_ant *ant;

	if (!(room->coup = (int*)malloc(sizeof(int) * (10 * room[algo->index_start].links))))
		return (-2);
	ft_init_db_int(room->coup, 10 * room[algo->index_start].links);
	ant = ft_init_ant(all->fourmis, all);
	printf("TOUT SE PASSSE BIEN\n");
	ft_find_best_path(algo, room, all, ant);
	return (0);
}
