/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:11:45 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/04 15:45:11 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_parser(t_all *all, t_room *room, int i)
{
	int	index;
	int	start_end;
	int	start;
	int	end;

	start = 0;
	end = 0;
	start_end = 0;
	index = 0;
	while (index < all->room)
	{
		if (all->map[i][0] != '#')
		{
			if (ft_fill_name(all->map[i], &room[index], all->fourmis) == -1)
				return (ft_parser_error("Coordoonnees invalides\n"));
			index++;
		}
		else if (all->map[i][0] == '#')
		{
			while (all->map[i][0] == '#')
			{
				if (ft_strcmp("##start", all->map[i]) == 0) //il faut alors verifier qu il n y a pas plusieurs rooms start et end
					start_end = 1;
				if (ft_strcmp("##end", all->map[i]) == 0)
					start_end = 2;
				i++;
			}
			room[index].start_end = start_end;
			start += start_end == 1 ? 1 : 0;
			end += start_end == 2 ? 1 : 0;
			i--;
		}
		if (start_end == 0)
			room[index].start_end = 0;
		start_end = 0;
		i++;
	}
//	printf("%d et %d i%d?\n", start, end, i);
	if (end == 1 && start == 1)
		return (i);
	return (ft_parser_error("Start end error\n"));
}

int		ft_verif_doublons(t_room *room, t_all *all, t_algo *algo)
{
	int	i;

	i = 0;
	while (i < all->room)
	{
		if (room[i].start_end == 1)
			algo->index_start = i;
		if (room[i].start_end == 2)
			algo->index_end = i;
		if (room[i].links == 0)
		{
			printf("%s\n", room[i].name);
//			ft_print_room(room ,i);
			return (ft_parser_error("Doublons or no links\n"));
		}
		room[i].way = ft_strsplit((const char *)room[i].index, ' ');
//		free(room[i].index);
		i++;
	}
	return (0);
}

int		ft_check_link(t_all *all, t_room *room, int start)
{
	int i;
	int	index;

	i = start;
	while (all->map[i])
	{
		if (nbr_space(all->map[i], '-') == 1 && all->map[i][0] != '#')
		{
			if ((index = ft_verif_link(room, all->map[i], all)) == -1)
				break;
			if ((ft_verif_link2(room, all->map[i], all, index)) == -1)
				break;
		}
		if (all->map[i][0] != '#' && nbr_space(all->map[i], '-') != 1)
			break;
		i++;
	}
	return (0);
}
