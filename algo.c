/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:11:53 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/06 16:42:22 by prastoin         ###   ########.fr       */
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

int		ft_move_ghost(t_room *room, t_algo *algo, t_special_ant *ghost, int i)
{
	int curr;
	int next;
	int power;
	int k;

	curr = algo->index_start;
	ghost[i].path[ghost[i].len] = curr;
	ghost[i].len++;
	room[curr].pass++;
	while (curr != algo->index_end)
	{
		power = INT_MAX;
		k = 0;
		while (k < room[curr].links)
		{
			if (power > room[ft_atoi(room[curr].way[k])].power + room[ft_atoi(room[curr].way[k])].pass)
			{
				power = room[ft_atoi(room[curr].way[k])].power + room[ft_atoi(room[curr].way[k])].pass;
				next = ft_atoi(room[curr].way[k]);
			}
			k++;
		}
		curr = next;
		room[curr].pass++;
		ghost[i].path[ghost[i].len] = curr;
		ghost[i].len++;
	}
	k = 0;
	while (k < ghost[i].len)
	{
		printf("%s --", room[ghost[i].path[k]].name);
		k++;
	}
	printf("%d\n", ghost[i].len);
	return (0);
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
//				printf("Je suis dans %d Et j'ai une power de %d Je regare dans %d il a une power de %d\n", algo->list1[i], room[algo->list1] curr, room[curr].power);
				if ((room[curr].power) > (room[algo->list1[i]].power))
				{
//					printf("Je suis dans ce if ?\n");
					room[curr].power = room[algo->list1[i]].power + 1;
					if (room[curr].pass > room[algo->list1[i]].pass)
						room[curr].power += (room[curr].pass - room[algo->list1[i]].pass);
					algo->list2[cmt] = curr;
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
	}
	return (0);
}

void			ft_refresh_power(t_all *all, t_room *room, t_algo *algo)
{
	int i;

	i = 0;
	while (i < all->room)
	{
		room[i].power = INT_MAX;
		i++;
	}
	room[algo->index_end].pass = 0;
	room[algo->index_end].power = 0;
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
		ghost[i].i = 1;
		ghost[i].len = 0;
		if (!(ghost[i].path = (int*)malloc(sizeof(int) * (all->room))))
			return (NULL);
		i++;
	}
	return (ghost);
}

void	ft_moove_ant(t_room *room, t_special_ant *ghost, t_algo *algo, t_all *all)
{
	int i;

	while (room[algo->index_end].slot < all->fourmis)
	{
		i = 0;
		while (i < all->fourmis)
		{
//			ft_putnbr(i);
//			ft_putchar('\n');
			if (ghost[i].i < ghost[i].len)
			{
				if (room[ghost[i].path[ghost[i].i]].slot == 0 || ghost[i].path[ghost[i].i] == algo->index_end)
				{
//					printf("JE SUIS DEDANS\n");
					ft_display(i, ghost, room, algo);
					room[ghost[i].path[(ghost[i].i) - 1]].slot--;
					room[ghost[i].path[(ghost[i].i)]].slot++;
					ghost[i].i++;
				}
			}
			printf("fourmis sont dans end%d sur %ld fourmis\n", room[algo->index_end].slot, all->fourmis);
			i++;
		}
		ft_putchar('\n');
	}
}

int		ft_power_call(t_algo *algo, t_room *room, t_all *all, t_special_ant *ghost)
{
	int i;

	i = 0;
	while (i < all->fourmis)
	{
		algo->list1[0] = algo->index_end;
		algo->list1[1] = -42;
		ft_refresh_power(all, room, algo);
		ft_fill_power(room, algo);
//		ft_print_struct(room, all->room);
//		printf("\n\n\nLa fourmis marche\n\n\n");
		ft_move_ghost(room, algo, ghost, i);
//		ft_print_struct(room, all->room);
//		printf("\n\n\n\n\n\n");
		i++;
	}
	ft_print_ant(ghost, all->fourmis);
	return (0);
	ft_moove_ant(room, ghost, algo, all);
}

int		ft_algo(t_room *room, t_algo *algo, t_all *all)
{
	t_fourmi *ant;
	t_special_ant *ghost;

	if (!(algo->list1 = (int*)malloc(sizeof(int) * (all->room + 1))))
		return (0);
	if (!(algo->list2 = (int*)malloc(sizeof(int) * (all->room + 1))))
		return (0);
	ghost = ft_init_ghost(all);
	ft_power_call(algo, room, all, ghost);
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
