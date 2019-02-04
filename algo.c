/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:41:56 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/04 13:03:28 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_malloc_list(t_algo *algo, int room)
{
	if (!(algo->list1 = (int*)malloc(sizeof(int) * (room))))
		return (-1);
	if (!(algo->list2 = (int*)malloc(sizeof(int) * (room))))
		return (-1);
	algo->list1[0] = algo->index_end;
	algo->list1[1] = -42;
	return (0);
}


int		ft_fill_power2(t_room *room, t_algo *algo)
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
				if (room[ft_atoi(room[algo->list1[i]].way[j])].power2 == 0)
				{
					room[atoi(room[algo->list1[i]].way[j])].power2 = k;
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
//			printf("ITER%d = %d\n", k, algo->list2[i]);
			algo->list1[i] = algo->list2[i];
			i++;
		}
		algo->list1[i] = -42;
		k++;
	}
	return (0);
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

int		ft_verif_boucle(t_fourmi *ant, t_room *room, t_algo *algo, int curr_ant, int best, t_all *all)
{
	const int	curr = ant[curr_ant].curr;
	int save;
	int i;

	ft_malloc_list(algo, all->room);
	save = 1;
	room[curr].power2 = 1;
	ft_fill_power2(room, algo);
	save = room[best].power2;
	i = 0;
	while (i < all->room)
	{
		if (i != algo->index_end)
			room[i].power2 = 0;
		i++;
	}
	free(algo->list1);
	free(algo->list2);
//	printf("\n%s -- %s", room[curr].name, room[best].name);
	if (save == 0)
	{
//		printf("\nCycle\n");
		return (INT_MAX);
	}
	return (save);
}

int		ft_play(t_fourmi *ant, t_room *room, t_algo *algo, int curr_ant, t_all *all)
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

	(void)all;
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
			if (score > room[ft_atoi(room[curr].way[i])].power) // && ft_atoi(room[curr].way[i]) != ant[curr_ant].previous)
			{

				score = room[ft_atoi(room[curr].way[i])].power;
				best = ft_atoi(room[curr].way[i]);
				if (score - score2 == 2)
					score = ft_verif_boucle(ant, room, algo, curr_ant, best, all);
/*				if (curr_ant == 1)
				{
					ft_putstr(" --  index =");
					ft_putnbr(best);
					ft_putstr(" --  score =");
					ft_putnbr(score);
					ft_putstr(" -- ");
				}*/
			}
		}
		i++;
	}
//	if (score - score2 > algo->fourmis - room[algo->index_end].slot)
//		return (-1);
	if (score == INT_MAX)
		return (-1);
	return (best);
}

void	ft_display(int best, t_room *room, t_algo *algo, t_fourmi ant)
{
	if (best != -1)
	{
		if (ant.previous == algo->index_start)
			write(1, CSI_RED, (sizeof(CSI_RED) - 1));
		else if (best == algo->index_end)
			write(1, CSI_BLUE, (sizeof(CSI_BLUE) - 1));
		else
			write(1, CSI_WHITE, (sizeof(CSI_WHITE) - 1));
		ft_putchar('l');
		ft_putnbr(ant.name);
		ft_putchar('-');
		ft_putstr(room[best].name);
		ft_putchar(' ');
		write(1, CSI_RESET, (sizeof(CSI_RESET) - 1));
		/*
		ft_putchar('L');
		ft_putnbr(curr_ant + 1);
		ft_putchar('-');
		ft_putstr(room[best].name);
		ft_putchar(' ');*/
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

int		ft_fill_path(t_fourmi *ant, t_algo *algo, t_room *room, t_all *all)
{
	int	i;
	int best;
	int	x;

	while (room[algo->index_end].slot != algo->fourmis)
	{
		i = 0;
		x = 0;
		while (i != (algo->fourmis) && x < room[algo->index_end].links)
		{
			if (ant[i].curr != algo->index_end)
			{
				if ((best = ft_play(ant, room, algo, i, all)) != -1)
				{
					if (ant[i].curr == algo->index_start)
						x++;
					ft_move_ant(best, room, ant, i);
					ft_display(best, room, algo, ant[i]);
				}
			}
			i++;
		}
		ft_putchar('\n');
	}
	return (0);
}

int		ft_destroy_path(int index, t_room *room, t_algo *algo)
{
	int i;

	(void)algo;
	i = 0;
	room[index].power = INT_MAX;
	room[index].links2 = -42;
	while (i < room[index].links)
	{
		room[ft_atoi(room[index].way[i])].links2--;
		i++;
	}
	return (0);
}

int		ft_destroy(t_all *all, t_room *room, t_algo *algo)
{
	int i;
	int des;

	des = 1;
	while (des != 0)
	{
		des = 0;
		i = 0;
		while (i < all->room)
		{
			if (room[i].links2 == 1 && i != algo->index_end && i != algo->index_start)
			{
				ft_destroy_path(i, room, algo);
				des += 1;
			}
			i++;
		}
	}
	return (0);
}

int		ft_algo(t_room *room, t_algo *algo, long fourmis, t_all *all)
{
	t_fourmi *ant;

	ft_malloc_list(algo, all->room);
	algo->list1[0] = algo->index_end;
	algo->list1[1] = -42;
	room[algo->index_end].power = 1;
	room[algo->index_end].power2 = 1;
//	ft_print_struct(room, all->room);
	ft_fill_power(room, algo);
	free(algo->list1);
	free(algo->list2);
	if (room[algo->index_start].power == 0)
		return (ft_parser_error("Broken path\n"));
//	ft_destroy(all, room, algo);
	//checker si start a une power pour regarder si le path est valide entre start et end
	ant = ft_foumisse(fourmis, algo);
//	ft_print_ant(ant, fourmis);
	algo->fourmis = fourmis;
	printf("start = %d end = %d\n", room[algo->index_start].links, room[algo->index_end].links);
//	ft_print_struct(room, all->room);
	ft_fill_path(ant, algo, room, all);
	return (0);
}
