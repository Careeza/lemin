/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:48:47 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 21:57:17 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_fill_power_cut(t_room *room, t_algo *algo, int i, int j)
{
	if (room[room[algo->list1[i]].index[j]].power == 0
		&& room[algo->list1[i]].index[j] != algo->index_end
		&& (!(room[algo->list1[i]].prev == 1
		&& room[room[algo->list1[i]].index[j]].courant == INT_MAX)))
	{
		if (room[algo->list1[i]].courant == INT_MAX
			|| room[algo->list1[i]].courant
			<= room[room[algo->list1[i]].index[j]].courant)
		{
			room[room[algo->list1[i]].index[j]].power = 1;
			algo->list2[algo->cmt] = room[algo->list1[i]].index[j];
			if (room[room[algo->list1[i]].index[j]].courant == INT_MAX)
				room[room[algo->list1[i]].index[j]].previous = algo->list1[i];
			else
				room[room[algo->list1[i]].index[j]].prev =
					room[algo->list1[i]].prev + 1;
			algo->cmt++;
		}
	}
}

int		ft_check_path(t_path *way)
{
	if (way[0].nb_path == 0)
		return (-2);
	else
		return (-1);
}

int		ft_fill_power(t_room *room, t_algo *algo, int i, t_path *way)
{
	int j;

	while (algo->cmt != 0)
	{
		i = 0;
		algo->cmt = 0;
		while (algo->list1[i] != -42)
		{
			j = -1;
			while (++j < room[algo->list1[i]].links)
			{
				if (room[algo->list1[i]].index[j] == algo->index_end
					&& room[algo->list1[i]].courant == INT_MAX)
				{
					room[room[algo->list1[i]].index[j]].previous =
						algo->list1[i];
					return (0);
				}
				ft_fill_power_cut(room, algo, i, j);
			}
			i++;
		}
		ft_list2_to1(algo, algo->cmt);
	}
	return (ft_check_path(way));
}

t_path	*ft_init_power_cut(t_algo *algo, t_room *room, t_all *all)
{
	t_path *way;

	algo->list1 = NULL;
	algo->list2 = NULL;
	if (ft_file(all) == -1)
		return(NULL);
	algo->lesslink = room[algo->index_start].links
		> room[algo->index_end].links ? room[algo->index_end].links
		: room[algo->index_start].links;
	if (algo->lesslink == 0)
		algo->lesslink = 1;
	if (ft_init_algo(algo, all, room) == -1)
	{
		close(all->fd);
		return (NULL);
	}
	if (!(way = (ft_init_path(algo, all))))
	{
		close(all->fd);
		ft_parser_error("Malloc failed\n", -1, NULL, NULL);
		return (NULL);
	}
	return (way);
}

int		ft_call_power(t_room *room, t_algo *algo, t_all *all)
{
	t_path			*way;
	int				i;
	t_special_ant	*ant;

	if (!(way = ft_init_power_cut(algo, room, all)))
		return (ft_free(room, all, NULL, algo));
	while (1)
	{
		algo->cmt = 1;
		i = ft_fill_power(room, algo, 0, way);
		if (i == -1)
			break ;
		if (i == -2)
			ft_parser_error("Broken path\n", 1, all, room);
		if (i == -2)
			ft_broken_path(way, algo, all);
		if (ft_create_flux(room, algo, way) == -1)
			break ;
		ft_reset_power(room, all->room, algo);
	}
	i = ft_gestion_pack(algo, way);
	ant = ft_give_path_to_ant(algo, way, i, all);
	ft_play_and_print(ant, room, algo, all);
	ft_free_ant(ant, all->fourmis);
	return (ft_free(room, all, way, algo));
}
