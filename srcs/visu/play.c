/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecerri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 00:47:31 by fbecerri          #+#    #+#             */
/*   Updated: 2019/02/20 18:32:07 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		ft_get_index_start(t_room *room, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->room)
	{
		if (room[i].start_end == 1)
			data->index_start = i;
		if (room[i].start_end == 2)
			data->index_end = i;
		i++;
	}
	data->xpos[0] = data->zm + room[data->index_start].x * data->zm;
	data->xpos[1] = data->zm + room[data->index_end].x * data->zm;
	data->ypos[0] = data->zm2 + room[data->index_start].y * data->zm2;
	data->ypos[1] = data->zm2 + room[data->index_end].y * data->zm2;
	return (0);
}

t_ant	*ft_init_ant(t_data *data, t_room *room)
{
	int		i;
	t_ant	*ant;

	i = 0;
	ft_get_index_start(room, data);
	if (!(ant = (t_ant *)malloc(sizeof(t_ant) * data->fourmis)))
		return (NULL);
	while (i < data->fourmis)
	{
		ant[i].i = i;
		ant[i].curr = 0;
		ant[i].previous = data->index_start;
		ant[i].coup = 0;
		ant[i].firstind = 0;
		i++;
	}
	return (ant);
}

void	ft_put_red_square(t_data *data, t_room *room, int i)
{
	int x;
	int y;

	x = data->zm + room[i].x * data->zm;
	y = data->zm2 + room[i].y * data->zm2;
	ft_circle(x, y, data, 0xFFFFFF);
}

void	ft_put_green_square(t_data *data, t_room *room, int i, t_ant ant)
{
	int			x;
	int			y;
	int			dx;
	int			dy;
	static int	color;

	if (ant.coup == 1)
		color = 0xffcc99;
	else if (ant.coup == 2)
		color = 0xffa64d;
	else if (ant.coup == 3)
		color = 0xff8000;
	else if (ant.coup == 4)
		color = 0xb35900;
	else
		color = 0x663300;
	dx = (SCREEN_X / (data->room * SIZE)) / 2;
	dy = (SCREEN_Y / (data->room * SIZE)) / 2;
	x = data->zm + room[i].x * data->zm;
	y = data->zm2 + room[i].y * data->zm2;
	ft_circle(x, y, data, color);
}

int		ft_play_cut2(t_room *room, t_data *data, t_ant *ant, int y)
{
	if (ant->coup == 0)
	{
		ant->firstind = ant->curr;
		ant->coup = (y % 5) + 1;
	}
	if (ant->curr != data->index_end)
		ft_put_green_square(data, room, ant->curr,
				*ant);
	else
		data->antend++;
	return (0);
}
