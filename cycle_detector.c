/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_detector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 11:59:10 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/11 15:36:34 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_fill_fourmi(int curr_ant, t_special_ant *ant, int lencycle,
		t_all *all)
{
	int		i;
	int		deb_cy;

	deb_cy = curr_ant - lencycle;
	i = 0;
	curr_ant++;
	while (curr_ant < all->fourmis)
	{
		ft_cpint_n(ant[deb_cy + (i % (lencycle + 1))].path, ant[curr_ant].path,
				ant[deb_cy + (i % (lencycle + 1))].len);
		ant[curr_ant].len = ant[deb_cy + (i % (lencycle + 1))].len;
		i++;
		curr_ant++;
	}
	return (0);
}

int		ft_cycle_detector(t_special_ant *ant, int curr_ant, t_room *room)
{
	int count;
	int save;
	int i;
	int lenpath[2];

	count = 0;
	save = ant[curr_ant].path[0];
	i = curr_ant - 1;
	lenpath[0] = 0;
	lenpath[1] = INT_MAX;
//	printf("Je commence ave =");
//	print_dbint(ant[curr_ant].path, ant[curr_ant].len, room);
	while (i >= 0 && count < 2)
	{
		if (save == ant[i].path[0])
		{
//			printf("Je finis ave =");
//			print_dbint(ant[i].path, ant[i].len, room);
//			printf("%d -- %d\n", save, ant[i].path[0]);
			lenpath[count] = curr_ant - i;
			count++;
			curr_ant = i;
		}
		i--;
	}
//	printf("%d -- %d -- %d -- %d\n", lenpath[0], lenpath[1], lenpath[2], lenpath[3]);
	if (lenpath[0] == lenpath[1])
	{
//		printf("FAP\n");
		return (lenpath[1] - 1);
	}
	(void)room;
//	printf("DFAP\n");
	return (-1);
}
