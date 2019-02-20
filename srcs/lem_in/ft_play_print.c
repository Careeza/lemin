/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_play_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 01:12:07 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 22:33:50 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_move(t_special_ant *ant, int curr_ant, t_room *room)
{
	const int		previous = ant[curr_ant].curr;
	const int		curr = ant[curr_ant].path[ant[curr_ant].i];

	room[previous].slot = 0;
	room[curr].slot += 1;
	ant[curr_ant].curr = curr;
}

static	void	ft_play_and_print2(int *curr_ant, t_algo *algo, t_room *room,
	t_special_ant *ant)
{
	while (*curr_ant < algo->fourmis)
	{
		if (ant[*curr_ant].curr != algo->index_end)
		{
			if (room[ant[*curr_ant].path[ant[*curr_ant].i]].slot == 0
				|| ant[*curr_ant].path[ant[*curr_ant].i] == algo->index_end)
			{
				ft_move(ant, *curr_ant, room);
				ft_display(*curr_ant, ant, room, algo);
				ant[*curr_ant].i++;
			}
		}
		(*curr_ant)++;
	}
}

void			ft_play_and_print(t_special_ant *ant, t_room *room,
	t_algo *algo, t_all *all)
{
	int	curr_ant;
	int	i;

	i = 0;
	curr_ant = 0;
	if (algo->flag >= 42 && all->room < 30)
		ft_putstr_fd("#Visu OK\n", all->fd);
	close(all->fd);
	ft_putstr(all->str);
	ft_putchar('\n');
	while (i < all->fourmis)
	{
		ant[curr_ant].curr = algo->index_start;
		i++;
	}
	room[algo->index_start].slot = all->fourmis;
	while (room[algo->index_end].slot != all->fourmis)
	{
		if (algo->flag == 1 || algo->flag == 3)
			ft_color(algo->step, 0);
		curr_ant = 0;
		ft_play_and_print2(&curr_ant, algo, room, ant);
		algo->step++;
		ft_putchar('\n');
	}
}
