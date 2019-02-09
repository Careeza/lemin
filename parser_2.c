/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 05:27:39 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/09 05:28:28 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
			return (ft_parser_error("Doublons or no links\n"));
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
				break ;
			if ((ft_verif_link2(room, all->map[i], all, index)) == -1)
				break ;
		}
		if (all->map[i][0] != '#' && nbr_space(all->map[i], '-') != 1)
			break ;
		i++;
	}
	return (0);
}
