/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ant_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:52:37 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/08 14:26:10 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_print_ant_path(t_special_ant *ant, t_all *all, t_room *room, t_algo *algo)
{
	int i;

	i = -1;
	while (++i < all->fourmis)
		ant[i].i = 0;
	room[algo->index_end].slot = 0;
	room[algo->index_start].slot = all->fourmis;
	while (room[algo->index_end].slot != all->fourmis)
	{
		i = 0;
		while (i < all->fourmis)
		{
			if (ant[i].i < ant[i].len)
			{
				if (room[ant[i].path[ant[i].i]].pass == 0)
				{
					if (ant[i].path[ant[i].i] == algo->index_end)
						room[algo->index_end].slot++;
					else
						room[ant[i].path[ant[i].i]].pass = 1;
					ft_display(i, ant, room, algo);
					if (ant[i].i != 0)
						room[ant[i].path[ant[i].i - 1]].pass = 0;
					ant[i].i++;
				}
			}
			i++;
		}
		ft_putchar('\n');
	}
	return(0);
}
