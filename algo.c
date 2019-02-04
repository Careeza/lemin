/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:50:33 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/04 18:53:18 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_power_plus(int center_room, int cac_room, t_room *room)
{
	int		i;

	i = 0;
	while (i < room[cac_room].links)
	{
		if (ft_atoi(room[cac_room].way[i]) == center_room)
		{
			room[cac_room].powertest[i]++;
			return(0);
		}
		i++;
	}
	return (0);
}

int	ft_ant_path(int curr_ant, t_room *room, t_algo *algo, t_fourmi *ant)
{
	int	i;
	long power;
	int j;
	int	k;

	i = 0;
	while (ant[curr_ant].curr != algo->index_end)
	{
		j = 0;
		power = INT_MAX;
		while (j < room[ant[curr_ant].curr].links)
		{
			if (power > room[ant[curr_ant].curr].powertest[j])
			{
				power = room[ant[curr_ant].curr].powertest[j];
				ant[curr_ant].path[i] = j;
	//			ant[curr_ant].next = j;
			}
			j++;
		}
		k = 0;
		while (k < room[ft_atoi(room[ant[curr_ant].curr].way[ant[curr_ant].path[i]])].links)
		{
			ft_power_plus(ft_atoi(room[ant[curr_ant].curr].way[ant[curr_ant].path[i]]), ft_atoi(room[ft_atoi(room[ant[curr_ant].curr].way[ant[curr_ant].path[i]])].way[k]), room);
			k++;
		}
//		printf("from %d to %d finsish %d\n", ant[curr_ant].curr, atoi(room[ant[curr_ant].curr].way[ant[curr_ant].next]), algo->index_end);
//		printf("%d -- %d\n", ant[curr_ant].path[i], i);
//		printf("%d -- ", ant[curr_ant].pat);
		ant[curr_ant].curr = atoi(room[ant[curr_ant].curr].way[ant[curr_ant].path[i]]);
//		ant[curr_ant].path[i] = ant[curr_ant].next;
		i++;
	}
	return (i);
}

int		ft_fill_path(t_fourmi *ant, t_algo *algo, t_room *room, t_all *all)
{
	int	i;
	int	j;
	int index;
	int	k = 0;
	int	four = 0;

	i = 0;
	j = 0;
	(void)all;
	while (i < all->fourmis)
	{
		printf("\n ____________________________ \n ____________________________ \n ____________________________ \n");
	//	ft_print_struct(room, all->room);
		j = ft_ant_path(i, room, algo, ant);
		i++;
//	while (four < all->fourmis)
//	{
		k = 0;
		index = algo->index_start;
		while ((index = ft_atoi(room[index].way[ant[four].path[k]])) != algo->index_end)
		{
			printf("%s -- ", room[index].name);
			k++;
		}
		printf("%s\n", room[index].name);
		four++;
	}
//	printf("%d -- %d\n", algo->index_end, index);
	return (0);
}

t_fourmi	*ft_foumisse(long fourmis, t_algo *algo, t_all *all)
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
		if (!(ants[i - 1].path = malloc(sizeof(int) * all->room)))
			return (NULL);
		i++;
	}
	return (ants);
}

int		ft_algo(t_room *room, t_algo *algo, long fourmis, t_all *all)
{
	t_fourmi *ant;
	(void)fourmis;
//	ft_print_struct(room, all->room);
	ft_power_algo(room, all, algo);
//	ft_check_start(room, algo->index_start); //checker si start a une power pour regarder si le path est valide entre start et end
	ant = ft_foumisse(fourmis, algo, all);
//	ft_print_ant(ant, fourmis);
	algo->fourmis = fourmis;
//	printf("start = %d end = %d\n", room[algo->index_start].links, room[algo->index_end].links);
	ft_fill_path(ant, algo, room, all);
//	ft_print_struct(room, all->room);
	return (0);
}
