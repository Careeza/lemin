/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:52:02 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 19:11:27 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visu.h"

void	ft_free_visu_room(t_room *room, int nbr)
{
	int i;

	i = 0;
	while (i < nbr)
	{
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
}

void	ft_free_visu(t_data *data)
{
	if (data->ant != NULL)
		free(data->ant);
	ft_free_visu_room(data->room2, data->room);
	ft_freedbchar(data->map);
	mlx_destroy_image(data->mlx, data->img2);
	mlx_destroy_window(data->mlx, data->win);
}
