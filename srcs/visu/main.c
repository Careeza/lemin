/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 09:23:37 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 22:48:22 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		ft_tracertrait(t_data *data, int x, int y)
{
	const int	x_inc = data->xstart < x ? 1 : -1;
	const int	y_inc = data->ystart < y ? 1 : -1;
	const int	dx = x > data->xstart ? x - data->xstart : data->xstart - x;
	const int	dy = y > data->ystart ? y - data->ystart : data->ystart - y;
	int			e[2];

	e[0] = dx > dy ? dx / 2 : -dy / 2;
	while (data->xstart != x || data->ystart != y)
	{
		if (data->ystart >= 0 && data->ystart < SCREEN_Y
			&& y < SCREEN_Y && y >= 0 && data->xstart >= 0
				&& data->xstart < SCREEN_X && x < SCREEN_X && x > 0)
			data->img_ptr2[data->ystart * SCREEN_X + data->xstart] = 0xFFFFFF;
		if ((e[1] = e[0]) > -dx)
		{
			e[0] -= dy;
			data->xstart += x_inc;
		}
		if (e[1] < dy)
		{
			e[0] += dx;
			data->ystart += y_inc;
		}
	}
	return (0);
}

int		deal_key(int key, t_data *data)
{
	data->use = 1;
	if (key == KEY_RIGHT && data->oto == 0)
		ft_play(data);
	if (key == KEY_LEFT && data->oto == 0)
		ft_inv_play(data);
	if (key == KEY_ESC)
	{
		ft_free_visu(data);
		exit(0);
	}
	if (key == KEY_PLUS)
		data->speed *= 1.5;
	if (key == KEY_LESS)
		data->speed *= 0.75;
	if (key == KEY_SPACE)
	{
		data->clk = clock();
		data->time = time(NULL);
		data->oto = data->oto == 0 ? 1 : 0;
	}
	return (0);
}

void	ft_init_join(t_data *data, t_room *room)
{
	int		y;
	int		ln;
	char	**map;
	int		indexa;
	int		indexb;

	map = data->map;
	y = 0;
	while (nbr_space(map[y], '-') != 1 || map[y][0] == '#')
		y++;
	while (map[y][0] != 'L' && map[y])
	{
		if (map[y][0] != '#')
		{
			ln = ft_len_to_c(map[y], '-');
			indexa = ft_index_for(ft_strndup(map[y], ln), room, data->room);
			indexb = ft_index_for(ft_strdup(map[y] + ln + 1), room, data->room);
			data->xstart = data->zm + room[indexa].x * data->zm;
			data->ystart = data->zm2 + room[indexa].y * data->zm2;
			ft_tracertrait(data, (data->zm + room[indexb].x * data->zm),
				(data->zm2 + room[indexb].y * data->zm2));
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img2, 0, 0);
}

int		auto_play(t_data *data)
{
	if (clock() > (data->clk + (data->ticks / data->speed)) && data->oto == 1)
	{
		ft_play(data);
		data->time = time(NULL);
	}
	if (data->use == 1 || (clock() > (data->clk
		+ (data->ticks / data->speed)) && data->oto == 1))
	{
		mlx_string_put(data->mlx, data->win,
			data->xpos[0] - 22, data->ypos[0] - 10, 0xFFFFFF, "START");
		mlx_string_put(data->mlx, data->win,
			data->xpos[1] - 14, data->ypos[1] - 10, 0xFFFFFF, "END");
		mlx_string_put(data->mlx, data->win,
			700, 960, 0xFFFFFF, "Ant number in end   = ");
		mlx_string_put(data->mlx, data->win,
			700, 930, 0xFFFFFF, "Ant number in start = ");
		ft_display_nbr_ant_visu(data);
		data->use = 0;
		data->clk = clock();
	}
	return (0);
}

int		main(void)
{
	t_data	data;
	t_room	*room;
	t_ant	*ant;

	ft_check_visu_txt(&data);
	ft_init_data(&data);
	if (!(room = ft_init(&data)))
		return (-1);
	if (!(ant = ft_init_ant(&data, room)))
		return (-1);
	data.antstart = data.fourmis;
	data.ant = ant;
	data.room2 = room;
	mlx_key_hook(data.win, deal_key, &data);
	mlx_loop_hook(data.mlx, auto_play, &data);
	mlx_loop(data.mlx);
	return (0);
}
