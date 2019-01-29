/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 13:41:56 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/29 15:39:56 by prastoin         ###   ########.fr       */
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

int		ft_algo(t_room *room, t_algo *algo, long fourmis, int nbrroom)
{
	if (!(algo->list1 = (int*)malloc(sizeof(int) * (nbrroom))))
		return (0);
	if (!(algo->list2 = (int*)malloc(sizeof(int) * (nbrroom))))
		return (0);
	(void)fourmis;
	algo->list1[0] = algo->index_end;
	algo->list1[1] = -42;
	ft_fill_power(room, algo);
	free(algo->list1);
	free(algo->list2);
	return (0);
}
