/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 09:52:55 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/05 09:55:02 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_free_room(t_room *room, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (room[i].name)
		{
			free(room[i].name);
			room[i].name = NULL;
		}
		if (room[i].way)
			ft_freedbchar(room[i].way);
		if (room[i].index)
		{
			free(room[i].index);
			room[i].index = NULL;
		}
		i++;
	}
	if (room)
	{
		free(room);
		room = NULL;
	}
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
