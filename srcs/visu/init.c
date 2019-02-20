/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecerri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 23:14:53 by fbecerri          #+#    #+#             */
/*   Updated: 2019/02/20 03:19:02 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/visu.h"

int			ft_fill_info(char *str, t_room *room, t_data *data)
{
	int len;

	len = 0;
	while (str[len] != ' ')
		len++;
	room->name = ft_strndup(str, len);
	room->slot = 0;
	room->x = ft_atoi(&(str[len]));
	if (room->start_end != 1 && room->start_end != 2)
		room->start_end = 0;
	data->x_extrem = room->x > data->x_extrem ? room->x : data->x_extrem;
	len += ft_lennbr(room->x);
	room->y = ft_atoi(&(str[len + 1]));
	data->y_extrem = room->y > data->y_extrem ? room->y : data->y_extrem;
	return (0);
}

int			ft_fill_room(t_data *data, t_room *room, int i)
{
	int cmt;

	while (data->map[i][0] == '#')
		i++;
	data->fourmis = ft_atoi(data->map[i]);
	i++;
	cmt = 0;
	while (cmt < data->room)
	{
		if (data->map[i][0] != '#')
		{
			ft_fill_info(data->map[i], &room[cmt], data);
			cmt++;
		}
		else
		{
			if (ft_strcmp("##start", data->map[i]) == 0)
				room[cmt].start_end = 1;
			if (ft_strcmp("##end", data->map[i]) == 0)
				room[cmt].start_end = 2;
		}
		i++;
	}
	return (0);
}

t_room		*ft_init_complete(t_data *data)
{
	t_room *room;

	ft_nbr_room(data);
	if (!(room = (t_room*)malloc(sizeof(t_room) * (data->room))))
		return (NULL);
	ft_fill_room(data, room, 0);
	return (room);
}

void		ft_circle(int x, int y, t_data *data, int color)
{
	int x2;
	int y2;

	y2 = -data->rayon;
	while (y2 < data->rayon)
	{
		x2 = -data->rayon;
		while (x2 < data->rayon)
		{
			if (((x2 / (double)data->rayon) * (x2 / (double)data->rayon)
					+ (y2 / (double)data->rayon)
					* (y2 / (double)data->rayon)) <= 1)
				data->img_ptr2[(y2 + y) * (SCREEN_X) + (x2 + x)] = color;
			x2++;
		}
		y2++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img2, 0, 0);
}

void		ft_init_sqare(t_data *data, t_room *room)
{
	int x;
	int y;
	int i;

	i = 0;
	while (i < data->room)
	{
		x = data->zm + room[i].x * data->zm;
		y = data->zm2 + room[i].y * data->zm2;
		if (room[i].start_end == 0)
			ft_circle(x, y, data, 0xFFFFFF);
		else if (room[i].start_end == 1)
			ft_circle(x, y, data, 0x0000FF);
		else
			ft_circle(x, y, data, 0xFF0000);
		i++;
	}
}

t_room		*ft_init(t_data *data)
{
	int		k;
	t_room	*room;

	k = -1;
	if (!(data->map = ft_read()))
		return (NULL);
	if (!(room = ft_init_complete(data)))
		return (NULL);
	if (!(data->mlx = mlx_init()))
		return (NULL);
	if (!(data->win = mlx_new_window(data->mlx, SCREEN_X, SCREEN_Y,
		"Visu lem_in fbecerri prastoin")))
		return (NULL);
	data->rayon = SCREEN_X / (data->room * SIZE * 2);
	data->zm = SCREEN_X / (data->x_extrem + 5);
	data->zm2 = SCREEN_Y / (data->y_extrem + 5);
	data->img2 = mlx_new_image(data->mlx, SCREEN_X, SCREEN_Y);
	data->img_ptr2 = (int *)mlx_get_data_addr(data->img2, &k, &k, &k);
	ft_init_join(data, room);
	ft_init_sqare(data, room);
	return (room);
}
