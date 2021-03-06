/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 09:52:55 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/21 00:47:47 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_free_room(t_room *room, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (room[i].index != NULL)
		{
			free(room[i].index);
			room[i].index = NULL;
		}
		if (room[i].name != NULL)
		{
			free(room[i].name);
			room[i].name = NULL;
		}
		i++;
	}
	if (room != NULL)
	{
		free(room);
		room = NULL;
	}
	return (0);
}

int		ft_free_path(t_path *way, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		ft_freedbint(way[i].path, nb);
		if (way[i].len_path != NULL)
		{
			free(way[i].len_path);
			way[i].len_path = NULL;
		}
		if (way[i].rev != NULL)
		{
			free(way[i].rev);
			way[i].rev = NULL;
		}
		i++;
	}
	if (way != NULL)
	{
		free(way);
		way = NULL;
	}
	return (0);
}

int		ft_free_ant(t_special_ant *ant, int nb)
{
	int		i;

	i = 0;
	while (i < nb)
	{
		if (ant[i].path != NULL)
		{
			free(ant[i].path);
			ant[i].path = NULL;
		}
		i++;
	}
	if (ant != NULL)
		free(ant);
	return (0);
}

int		ft_free_all(t_all *all)
{
	if (all->str)
		free(all->str);
	if (all->map)
		ft_freedbchar(all->map);
	return (0);
}
