/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 01:14:23 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/19 01:39:26 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_list2_to1(t_algo *algo, int cmt)
{
	int	i;

	algo->list2[cmt] = -42;
	i = 0;
	while (algo->list2[i] != -42)
	{
		algo->list1[i] = algo->list2[i];
		i++;
	}
	algo->list1[i] = -42;
	return (0);
}

void	ft_reset_power(t_room *room, int nbroom, t_algo *algo)
{
	int i;

	i = 0;
	while (i < nbroom)
	{
		room[i].power = 0;
		room[i].prev = 0;
		i++;
	}
	room[algo->index_start].power = 1;
	algo->list1[0] = algo->index_start;
	algo->list1[1] = -42;
}
