/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:07:36 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 00:52:18 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visu.h"

void		ft_y(t_data *data, char **jeu)
{
	if (data->save_x == data->x)
		jeu[data->y][data->x] = '|';
	if (data->save_y < data->y && data->save_x < data->x)
		jeu[data->y][data->x] = '\\';
	if (data->save_y < data->y && data->save_x > data->x)
		jeu[data->y][data->x] = '/';
	if (data->save_y > data->y && data->save_x > data->x)
		jeu[data->y][data->x] = '\\';
	if (data->save_y > data->y && data->save_x < data->x)
		jeu[data->y][data->x] = '/';
	data->verif = 1;
}

void		ft_x(t_data *data, char **jeu, int y_inc)
{
	if (data->x != data->save_x && data->y == data->save_y && data->verif == 0)
		jeu[data->y][data->x] = '=';
	else
	{
		if (jeu[data->y + y_inc][data->x] == ' ')
			jeu[data->y + y_inc][data->x] = '_';
	}
}


void	ft_print_trait(t_data *data, char **jeu, int y_inc)
{
	if (jeu[data->y][data->x] == ' ')
	{
		if (data->save_y != data->y)
			ft_y(data, jeu);
		else
			ft_x(data, jeu, y_inc);
		data->save_x = data->x;
		data->save_y = data->y;
	}

}

int		ft_oui(t_data *data)
{
	if (data->y >= 0 && data->y < (data->y_max * 4) &&
			data->y1 < (data->y_max * 4) && data->y1 >= 0 && data->x >= 0 &&
			data->x <= (data->x_max * 4 + 4) && data->x1 <= (data->x_max * 4 + 4)
			&& data->x1 > 0)
		return (0);
	return (-1);
}

int		ft_shell_tracertrait(t_data *data, char **jeu)
{
	const int	x_inc = data->x < data->x1 ? 1 : -1;
	const int	y_inc = data->y < data->y1 ? 1 : -1;
	const int	dx = data->x1 > data->x ? data->x1 - data->x : data->x - data->x1;
	const int	dy = data->y1 >data->y ? data->y1 - data->y : data->y - data->y1;
	int			e[2];

	data->save_x = data->x;
	data->save_y = data->y;
	data->verif = 0;
	e[0] = dx > dy ? dx / 2 : -dy / 2;
	while (data->x != data->x1 || data->y != data->y1)
	{
		if (ft_oui(data) == 0)
			ft_print_trait(data, jeu, y_inc);
		if ((e[1] = e[0]) > -dx)
		{
			e[0] -= dy;
			data->x += x_inc;
		}
		if (e[1] < dy)
		{
			e[0] += dx;
			data->y += y_inc;
		}
	}
	return (0);
}

void	ft_get_coord_max(t_room *room, t_data *data, int nbroom)
{
	int		i;

	i = 0;
	data->x_max = 0;
	data->y_max = 0;
	while (i < nbroom)
	{
		if (data->x_max < room[i].x)
			data->x_max = room[i].x;
		if (data->y_max < room[i].y)
			data->y_max = room[i].y;
		i++;
	}
}

void	ft_print_dbchar(char **tab, int end)
{
	int	deb;
	int	j;
	int	stop;

	j = 0;
	deb = 0;
	stop = 0;
	while (tab[deb] && stop == 0)
	{
		j = 0;
		while (tab[deb][j] && stop == 0)
		{
			if (tab[deb][j] != ' ' && tab[deb][j] != '\0')
				stop = 1;
			j++;
		}
		deb++;
	}
	deb--;
	while (deb <= end)
	{
		printf("%s\n", tab[deb]);
		deb++;
	}
}

int			ft_init_shell(t_data *data, t_room *room, int j, int i)
{
	ft_get_coord_max(room, data, data->room);
	if (!(data->jeu = (char **)malloc(sizeof(char *) * (data->y_max * 8 + 1))))
		return (-1);
	data->jeu[data->y_max * 8] = NULL;
	while (i < ((data->y_max * 8)))
	{
		if (!(data->jeu[i] = (char *)malloc(sizeof(char) * (data->x_max * 8 + 1))))
			return (-1);
		data->jeu[i][data->x_max * 6] = '\0';
		j = 0;
		while (j < data->x_max * 6)
		{
			data->jeu[i][j] = ' ';
			j++;
		}
		while (j < data->x_max * 8)
		{
			data->jeu[i][j] = '\0';
			j++;
		}
		i++;
	}
	return (0);
}

void		ft_place_room(char **jeu, t_room *room, int curr_room)
{
	int	x;
	int	y;
	int	i;
	int	k;

	k = 1;
	i = 0;
	y = room[curr_room].y * 4;
	x = room[curr_room].x * 4;
	while (jeu[y][x + k] && jeu[y][x + k] != ' ')
		k++;
	if (k != 0)
		k++;
	x += k;
	jeu[y][x] = '[';
	while (room[curr_room].name[i])
	{
		jeu[y][x + i + 1] = room[curr_room].name[i];
		i++;
	}
	jeu[y][x + i + 1] = ']';
}

void		ft_fill_jeu(char **jeu, t_room *room, t_data *data)
{
	int		y;

	y = 0;
	while (y < data->room)
	{
		ft_place_room(jeu, room, y);
		y++;
	}
}

int		ft_get_links(t_room *room, t_data *data)
{
	int		i;
	int		len;
	int		indexa;
	int		indexb;

	while ((nbr_space(data->map[data->step1], '-') != 1) || data->map[data->step1][0] == '#')
		data->step1++;
	i = data->step1;
	while (data->map[i] && data->map[i][0] != 'L')
	{
		if (data->map[i][0] != '#')
		{
			len = ft_len_to_c(data->map[i], '-');
			indexa = ft_index_for(ft_strndup(data->map[i], len), room, data->room);
			indexb = ft_index_for(ft_strdup(data->map[i] + len + 1), room, data->room);
			if (indexa != -1 && indexb != -1)
			{
				data->x = ((room[indexa].x * 4) + 4);
				data->y = (room[indexa].y * 4);
				data->x1 = ((room[indexb].x * 4) + 4);
				data->y1 = (room[indexb].y * 4);
				ft_shell_tracertrait(data, data->jeu);
			}
		}
		i++;
	}
	return (0);
}

int		ft_shell_visu(t_data *data, t_room *room)
{
	if ((ft_init_shell(data, room, 0, 0)) == -1)
		return (-1);
	ft_fill_jeu(data->jeu, room, data);
	ft_get_links(room, data);
	ft_print_dbchar(data->jeu, data->y_max * 4);
	return (0);
}
