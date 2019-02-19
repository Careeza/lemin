/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:24:22 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/19 20:38:40 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_free(t_room *room, t_all *all, t_path *way, t_algo *algo)
{
	(void)way;
	ft_free_room(room, all->room);
	ft_free_path(way, algo->lesslink);
	ft_free_all(all);
	ft_free_list(algo->list1, algo->list2);
	return (0);
}

int		ft_verif_tube(int indexa, int indexb, t_room *room)
{
	int	i;
	int	val;

	val = 0;
	i = 0;
	while (i < room[indexa].links)
	{
		val = room[indexa].index[i];
		if (indexb == val)
			return (-1);
		i++;
	}
	return (0);
}

int		nbr_space(char *str, char c)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (str[0] == '#')
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			space++;
		i++;
	}
	return (space);
}

int		ft_str_is_digit(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != ' ' && str[i] != '\0')
			return (-1);
		i++;
	}
	return (0);
}

void	ft_stop(void)
{
	ft_putstr("Usage = ./lem-in -c -l < [map]\n");
	ft_putstr("-c :print colors\n-l print lines\n");
	exit(0);
}
