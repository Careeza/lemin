/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:52:03 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/09 05:48:34 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int			ft_move(t_room *room, t_special_ant *ant, int curr_ant, t_algo *algo)
{
	int		curr;
	int		best;

	curr = ant[curr_ant].curr;
	best = -42;
	while (room[curr].i < room[curr].links)
	{
		best = room[curr].index[room[curr].i];
		if (best == room[curr].previous || room[best].pass == 1)
		{
			best = -42;
			room[curr].i++;
		}
		else
		{
			room[best].previous = ant[curr_ant].curr;
			room[curr].i++;
			break;
		}
	}
	if(best == -42)
		return (best);
	ant[curr_ant].coup++;
	if ((ant[curr_ant].coup == algo->lesscoup + 1) && best != algo->index_end)
	{
		ant[curr_ant].coup--;
		return (-42);
	}
	while (room[best].coup[ant[curr_ant].coup] == 1)
	{
		ant[curr_ant].wait[best]++;
		ant[curr_ant].coup++;
	}
	room[best].pass = 1;
	return (best);
}

int		ft_previous(t_algo *algo, t_room *room, t_special_ant *ant, int curr_ant)
{
	int		curr;

	curr = ant[curr_ant].curr;
	room[curr].coup[ant[curr_ant].coup] = 0;
	if (curr == algo->index_start)
		return (-42);
	room[ant[curr_ant].curr].pass = 0;
	ant[curr_ant].coup -= ant[curr_ant].wait[curr];
	ant[curr_ant].wait[curr] = 0;
	ant[curr_ant].coup--;
	room[curr].pass = 0;
	room[curr].i = 0;
	ant[curr_ant].len--;
	ant[curr_ant].curr = room[curr].previous;
	return(0);
}

void		ft_fill_coup(t_room *room, int *path, int len)
{
	int		i;
	int		coup;

	coup = 1;
	i = 0;
	while (i < len - 1)
	{
		while (room[path[i]].coup[coup] == 1)
			coup++;
		room[path[i]].coup[coup] = 1;
		i++;
		coup++;
	}
	return ;
}


int		ft_find_best_path(t_algo *algo, t_room *room, t_all *all, t_special_ant *ant)
{
	int		curr_ant;
	int		next;
	int		cmt;
	int		lesslink;
	int		len;

	curr_ant = 0;
	lesslink = room[algo->index_start].links > room[algo->index_end].links ? room[algo->index_end].links : room[algo->index_start].links;
	while (curr_ant < all->fourmis)
	{
		room[algo->index_start].pass = 1;
		cmt = 0;
		ant[curr_ant].curr = algo->index_start;
		while (cmt != -42)
		{
			if (ant[curr_ant].curr != algo->index_end)
			{
				if ((next = ft_move(room, ant, curr_ant, algo)) != -42)
				{
					ant[curr_ant].path[ant[curr_ant].len] = next;
					ant[curr_ant].len++;
					ant[curr_ant].curr = next;
				}
				else
					cmt = ft_previous(algo, room, ant, curr_ant);
			}
			else
			{
				if (ant[curr_ant].coup == algo->lesscoup + 1)
				{
					ft_cpint_n(ant[curr_ant].path, ant[curr_ant].savepath, ant[curr_ant].len);
					ant[curr_ant].savelen = ant[curr_ant].len;
				}
				if (algo->lesscoup == ant[curr_ant].coup)
				{
					if (curr_ant != 0 || all->fourmis == 1 || algo->lesscoup == 1)
						break ;
					else
					{
						ft_cpint_n(ant[curr_ant].path, ant[curr_ant].savepath, ant[curr_ant].len);
						ant[curr_ant].savelen = ant[curr_ant].len;
					}
				}
				cmt = ft_previous(algo, room, ant, curr_ant);
			}
		}
		if (cmt != -42)
			ft_fill_coup(room, ant[curr_ant].path, ant[curr_ant].len);
		else
		{
			ft_cpint_n(ant[curr_ant].savepath, ant[curr_ant].path, ant[curr_ant].savelen);
			ant[curr_ant].len = ant[curr_ant].savelen;
			algo->lesscoup++;
			ft_fill_coup(room, ant[curr_ant].path, ant[curr_ant].len);
		}
		ft_reset_i(room, all->room);
		if (curr_ant > (3 * lesslink + 5))
		{
			if ((len = ft_cycle_detector(ant, curr_ant - 1, ant[curr_ant].len, ant[curr_ant].path)) != -1)
			{
				ft_fill_fourmi(curr_ant, ant, len, all);
				break ;
			}
		}
		curr_ant++;
	}
	return (0);
}

int		ft_found_path(t_algo *algo, t_room *room, t_all *all)
{
	t_special_ant *ant;
	int i;

	room[algo->index_start].pass = 1;
	if (room[algo->index_start].links == 0)
		return (ft_parser_error("Broken path\n"));
	algo->lesscoup = room[room[algo->index_start].index[0]].power;
	i = 0;
	while (i < all->room)
	{
		if (!(room[i].coup = (int*)malloc(sizeof(int)
							* (algo->lesscoup + 1000))))
			return (-2);
		ft_init_db_int(room[i].coup, algo->lesscoup + 1000);
		i++;
	}
	ant = ft_init_ant(all->fourmis, all);
	ft_find_best_path(algo, room, all, ant);
	ft_reset_i(room, all->room);
	ft_print_ant_path(ant, all, room, algo);
	return (0);
}
