/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:41:56 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/30 14:56:48 by prastoin         ###   ########.fr       */
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
		ants[i - 1].previous = -42;
		i++;
	}
	return (ants);
}

int		ft_play(t_fourmi *ant, t_room *room, t_algo *algo, int curr_ant)
{
	const int	curr = ant[curr_ant].curr;
	int			i;
	int			score;
	int			score2;
	int			best;

	best = -42;
	score = INT_MAX;
	score2 = INT_MAX;
	i = 0;

	while (i < room[curr].links)
	{
		if (score2 > room[ft_atoi(room[curr].way[i])].power)
			score2 = room[ft_atoi(room[curr].way[i])].power;
		i++;
	}
	i = 0;
	while (i < room[curr].links)
	{
		if (room[ft_atoi(room[curr].way[i])].slot == 0 || ft_atoi(room[curr].way[i]) == algo->index_end)
		{
			if (score > room[ft_atoi(room[curr].way[i])].power)
			{
				score = room[ft_atoi(room[curr].way[i])].power;
//				printf("%d\n", score);
				best = ft_atoi(room[curr].way[i]);
			}
		}
		i++;
	}
//	printf("score2 = %d\n", score - score2);
	if (score - score2 > room[algo->index_start].slot)
		return (-1);
	if (score == INT_MAX)
		return (-1);
	return (best);
}

void	ft_display(int curr_ant, int best, t_room *room)
{
	if (best != -1)
	{
		ft_putchar('L');
		ft_putnbr(curr_ant + 1);
		ft_putchar('-');
		ft_putstr(room[best].name);
		ft_putchar(' ');
	}
}

int		ft_move_ant(int best_index, t_room *room, t_fourmi *ant, int curr_ant)
{
	ant[curr_ant].previous = ant[curr_ant].curr;
	ant[curr_ant].curr = best_index;
	room[ant[curr_ant].previous].slot -= 1;
	room[ant[curr_ant].curr].slot += 1;
	return (0);
}

int		ft_fill_path(t_fourmi *ant, t_algo *algo, t_room *room)
{
	int	i;
	int best;

	while (room[algo->index_end].slot != algo->fourmis)
	{
		i = 0;
		while (i != (algo->fourmis))
		{
			if (ant[i].curr != algo->index_end)
			{
				if ((best = ft_play(ant, room, algo, i)) != -1)
				{
					ft_move_ant(best, room, ant, i);
					ft_display(i, best, room);
				}
			}
			i++;
		}
		ft_putchar('\n');
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
	algo->list1[0] = algo->index_end;
	algo->list1[1] = -42;
	ft_fill_power(room, algo);
	free(algo->list1);
	free(algo->list2);
	if (room[algo->index_start].power == 0)
		return (ft_parser_error("Broken path\n"));
	//checker si start a une power pour regarder si le path est valide entre start et end
	ant = ft_foumisse(fourmis, algo);
//	ft_print_ant(ant, fourmis);
	algo->fourmis = fourmis;
	ft_fill_path(ant, algo, room);
	return (0);
}
