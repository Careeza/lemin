/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:17:28 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 22:49:19 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		ft_play_cut(t_room *room, t_data *data, t_ant *ant, int y)
{
	int		curr_ant;
	int		i;

	i = 0;
	while (data->map[y][i])
	{
		if (data->map[y][i] == 'L')
			i++;
		curr_ant = ft_atoi(data->map[y] + i);
		i += ft_lennbr(curr_ant) + 1;
		if (ant[curr_ant - 1].previous != data->index_start)
			ft_put_red_square(data, room, ant[curr_ant - 1].previous);
		else
			data->antstart--;
		ant[curr_ant - 1].curr = ft_index_for_links(ft_strdup(data->map[y] + i),
			room, data->room, ft_len_to_c(data->map[y] + i, ' '));
		i += ft_len_to_c(data->map[y] + i, ' ');
		ft_play_cut2(room, data, &(ant[curr_ant - 1]), y);
		i += i < (int)ft_strlen(data->map[y]) ? 1 : 0;
		ant[curr_ant - 1].previous = ant[curr_ant - 1].curr;
	}
	return (0);
}

int		ft_play(t_data *data)
{
	static int	i;

	if (!(i))
	{
		while (data->map[data->i][0] != 'L')
			data->i++;
		i = 1;
	}
	if (data->map[data->i] && data->map[data->i][0] == 'L')
		ft_play_cut(data->room2, data, data->ant, data->i);
	else
	{
		ft_free_visu(data);
		exit(0);
	}
	data->i++;
	return (0);
}

void	ft_play_inv_cut(t_room *room, t_data *data, t_ant *ant, int y)
{
	int		curr_ant;
	int		i;

	i = 0;
	while (data->map[y][i])
	{
		if (data->map[y][i] == 'L')
			i++;
		curr_ant = ft_atoi(data->map[y] + i);
		i += ft_lennbr(curr_ant) + 1;
		ant[curr_ant - 1].curr = ft_index_for_links(ft_strdup(data->map[y] + i),
			room, data->room, ft_len_to_c(data->map[y] + i, ' '));
		i += ft_len_to_c(data->map[y] + i, ' ');
		if (ant[curr_ant - 1].curr != data->index_end)
			ft_put_red_square(data, room, ant[curr_ant - 1].curr);
		else
			data->antend--;
		if (ant[curr_ant - 1].curr == ant[curr_ant - 1].firstind)
		{
			data->antstart++;
			ant[curr_ant - 1].curr = data->index_start;
		}
		i += i < (int)ft_strlen(data->map[y]) ? 1 : 0;
		ant[curr_ant - 1].previous = ant[curr_ant - 1].curr;
	}
}

int		ft_play_inv_cut3(t_room *room, t_data *data, t_ant *ant, int y)
{
	int i;
	int curr_ant;

	i = 0;
	while (data->map[y][i])
	{
		if (data->map[y][i] == 'L')
			i++;
		curr_ant = ft_atoi(data->map[y] + i);
		i += ft_lennbr(curr_ant) + 1;
		ant[curr_ant - 1].curr = ft_index_for_links(ft_strdup(data->map[y] + i),
			room, data->room, ft_len_to_c(data->map[y] + i, ' '));
		i += ft_len_to_c(data->map[y] + i, ' ');
		if (ant[curr_ant - 1].coup == 0)
			ant[curr_ant - 1].coup = (y % 6) + 1;
		if (ant[curr_ant - 1].curr != data->index_end)
			ft_put_green_square(data, room, ant[curr_ant - 1].curr,
					ant[curr_ant - 1]);
		i += i < (int)ft_strlen(data->map[y]) ? 1 : 0;
		ant[curr_ant - 1].previous = ant[curr_ant - 1].curr;
	}
	return (0);
}

int		ft_inv_play(t_data *data)
{
	static int i;

	if (i == 0)
		while (data->map[i][0] != 'L')
			i++;
	data->i--;
	if (data->i >= i)
		ft_play_inv_cut(data->room2, data, data->ant, data->i);
	else
		data->i++;
	data->i--;
	if (data->i >= i)
		ft_play_inv_cut3(data->room2, data, data->ant, data->i);
	data->i++;
	return (i);
}
