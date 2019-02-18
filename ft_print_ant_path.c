/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ant_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:52:37 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/18 23:27:11 by fbecerri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//static void		ft_move_ant(t_room *room, t_algo *algo, int i,
//		t_special_ant *ant)
//{
//}

void	ft_reset_play(t_special_ant *ant, int fourmis)
{
	int i;

	i = 0;
	while (i < fourmis)
	{
		ant[i].play = 0;
		i++;
	}
}

int				ft_print_ant_path(t_special_ant *ant, t_all *all, t_room *room,
		t_algo *algo)
{
	int i;
	int coup;

	ft_putstr(all->str);
	ft_putchar('\n');
	algo->step = 1;
	i = -1;
	while (++i < all->fourmis)
		ant[i].i = 0;
	room[algo->index_end].slot = 0;
	room[algo->index_start].slot = all->fourmis;
	while (room[algo->index_end].slot != all->fourmis)
	{
//		ft_putstr("VOICI LE NOMBRE DE FOURMI DANS END");
//		ft_putnbr(room[algo->index_end].slot);
//		ft_putchar('\n');
		ft_reset_play(ant, all->fourmis);
		if (algo->flag == 1 || algo->flag == 3)
			ft_color(algo->step, 0);
		coup = 1;
		while (coup != 0)
		{
			i = 0;
			coup = 0;
			while (i < all->fourmis)
			{
				if (ant[i].i < ant[i].len)
				{
					if (room[ant[i].path[ant[i].i]].pass == 0 && ant[i].play == 0)
					{
						if (ant[i].path[ant[i].i] == algo->index_end)
							room[algo->index_end].slot++;
						else
							room[ant[i].path[ant[i].i]].pass = 1;
						ft_display(i, ant, room, algo);
						if (ant[i].i != 0)
							room[ant[i].path[ant[i].i - 1]].pass = 0;
						ant[i].i++;
						ant[i].play = 1;
						coup++;
					}
				}
				i++;
			}
		}
		algo->step++;
		ft_putchar('\n');
	}
	return (0);
}
