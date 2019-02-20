/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:52:02 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 22:46:32 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	ft_display_nbr_ant_visu(t_data *data)
{
	char *str;

	if (!(str = ft_itoa(data->antend)))
	{
		ft_free_visu(data);
		ft_putstr("Malloc failed\n");
		exit(0);
	}
	mlx_string_put(data->mlx, data->win,
		940, 960, 0xFFFFFF, str);
	free(str);
	if (!(str = ft_itoa(data->antstart)))
	{
		ft_free_visu(data);
		ft_putstr("Malloc failed\n");
		exit(0);
	}
	mlx_string_put(data->mlx, data->win,
		940, 930, 0xFFFFFF, str);
	free(str);
}

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
