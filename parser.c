/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:11:45 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/19 04:44:54 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_start_end(t_room *room, t_all *all, int index, int *i)
{
	int	start_end;

	start_end = 0;
	while (all->map[*i][0] == '#')
	{
		if (ft_strcmp("##start", all->map[*i]) == 0)
			start_end = 1;
		if (ft_strcmp("##end", all->map[*i]) == 0)
			start_end = 2;
		*i = *i + 1;
	}
	room[index].start_end = start_end;
	return (start_end);
}

int			ft_result(int start_and_end[2], int i, t_all *all, t_room *room)
{
	if (start_and_end[0] == 1 && start_and_end[1] == 1)
		return (i);
	return (ft_parser_error("Start end error\n", 1, all, room));
}

static void	ft_init(int *start_end, int start_and_end[2])
{
	start_and_end[0] = 0;
	start_and_end[1] = 0;
	*start_end = 0;
}

int			ft_parser(t_all *all, t_room *room, int i, int index)
{
	int	start_end;
	int	start_and_end[2];

	ft_init(&start_end, start_and_end);
	while (index < all->room)
	{
		if (all->map[i][0] != '#')
		{
			if (ft_nm(all->map[i], &room[index], all->fourmis, all->room) == -1)
				return (ft_parser_error("Coordoonnees invalides\n", 1, all, room));
			index++;
		}
		else if (all->map[i][0] == '#')
		{
			start_end = ft_start_end(room, all, index, &i);
			start_and_end[0] += start_end == 1 ? 1 : 0;
			start_and_end[1] += start_end == 2 ? 1 : 0;
			i--;
		}
		if (start_end == 0)
			room[index].start_end = 0;
		start_end = 0;
		i++;
	}
	return (ft_result(start_and_end, i, all, room));
}
