/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:41:56 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/29 17:18:04 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
				if (room[ft_atoi(room[algo->list1[i]].way[j])].power == 0)
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
		i++;
	}
	return (ants);
}

int		ft_play(t_fourmi *ant, t_room *room, t_algo *algo, int curr_ant)
{
	const int	curr = ant[curr_ant].curr;
	int			i;
	int			score;
	int			best;

	best = -42;
	score = -42;
	i = 0;
	while (i < room[curr].links)
	{
		if (room[ft_atoi(room[curr].way[i])].slot == 0 || ft_atoi(room[curr].way[i]) == algo->index_end)
		{
			if (score < room[ft_atoi(room[curr].way[i])].power)
			{
				score = room[ft_atoi(room[curr].way[i])].power;
				best = ft_atoi(room[curr].way[i]);
			}
		}
		i++;
	}
	if (score == -42)
		return (-1);
	return (best);
}

void	ft_display(int curr_ant, int best, t_room *room)
{
	if (best != -1)
	{
		ft_putchar('L');
		ft_putnbr(curr_ant);
		ft_putchar('-');
		ft_putstr(room[best].name);
		ft_putchar(' ');
	}
}

int		ft_fill_path(t_fourmi *ant, t_algo *algo, t_room *room)
{
	int	i;
	int	tour;
	int best;

	tour = 0;
	while (room[algo->index_end].slot != algo->fourmis)
	{
		i = 0;
		while (i != (algo->fourmis) && ((best = ft_play(ant, room, algo, i)) != -1))
		{
//			printf("test\n");
			ft_display(i, best, room);
			i++;
		}
		ft_putchar('\n');
		tour++;
	}
	return (0);
}

int		ft_algo(t_room *room, t_algo *algo, long fourmis, int nbrroom)
{
	t_fourmi *ant;

	if (!(algo->list1 = (int*)malloc(sizeof(int) * (nbrroom))))
		return (0);
	if (!(algo->list2 = (int*)malloc(sizeof(int) * (nbrroom))))
		return (0);
	printf("OK\n");
	algo->list1[0] = algo->index_end;
	algo->list1[1] = -42;
	printf("OK\n");
	ft_fill_power(room, algo);
	free(algo->list1);
	free(algo->list2);
	printf("OK\n");
	//checker si start a une power pour regarder si le path est valide entre start et end
	ant = ft_foumisse(fourmis, algo);
	ft_print_ant(ant, fourmis);
	algo->fourmis = fourmis;
	ft_fill_path(ant, algo, room);
	return (0);
}
