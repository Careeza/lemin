/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:48:47 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/18 12:35:53 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_list2_to1(t_algo *algo, int cmt, int *k)
{
	int	i;

	algo->list2[cmt] = -42;
	i = 0;
	while (algo->list2[i] != -42)
	{
		algo->list1[i] = algo->list2[i];
		i++;
	}
	algo->list1[i] = -42;
	*k = *k + 1;
	return (0);
}

void			ft_reset_courant(t_room *room, int nbrroom)
{
	int i;

	i = 0;
	while (i < nbrroom)
	{
		room[i].courant = INT_MAX;
		i++;
	}
}


					//printf("Je suis ici %s et je veux aller %s\n J'ai un courant de %d et il a un courant de %d\n", room[algo->list1[i]].name, room[room[algo->list1[i]].index[j]].name, room[algo->list1[i]].courant, room[room[algo->list1[i]].index[j]].courant);
int		ft_fill_power(t_room *room, t_algo *algo, int cmt, int k)
{
	int i;
	int j;

	algo->courant = 0;
	while (cmt != 0)
	{
		i = 0;
		cmt = 0;
		while (algo->list1[i] != -42)
		{
			j = -1;
			while (++j < room[algo->list1[i]].links)
			{
				if (room[algo->list1[i]].index[j] == algo->index_end && room[algo->list1[i]].courant == INT_MAX)
				{
					room[room[algo->list1[i]].index[j]].previous = algo->list1[i];
					return (0);
				}
				if (room[room[algo->list1[i]].index[j]].power == 0 && room[algo->list1[i]].index[j] != algo->index_end)
				{
					if (room[algo->list1[i]].courant == INT_MAX || room[algo->list1[i]].courant <= room[room[algo->list1[i]].index[j]].courant)
					{
						room[room[algo->list1[i]].index[j]].power = k;
						algo->list2[cmt] = room[algo->list1[i]].index[j];
						if (room[room[algo->list1[i]].index[j]].courant == INT_MAX)
							room[room[algo->list1[i]].index[j]].previous = algo->list1[i];
						cmt++;
					}
				}
			}
			i++;
		}
		ft_list2_to1(algo, cmt, &k);
	}
	return (-1);
}

int		ft_init_algo(t_algo *algo, t_all *all, t_room *room)
{
	if (!(algo->list1 = (int*)malloc(sizeof(int) * (all->room))))
		return (-1);
	if (!(algo->list2 = (int*)malloc(sizeof(int) * (all->room))))
		return (-1);
	algo->list1[0] = algo->index_start;
	algo->list1[1] = -42;
	room[algo->index_start].power = 1;
	return (0);
}

void			ft_reset_previous(t_room *room, int nbroom)
{
	int i;

	i = 0;
	while (i < nbroom)
	{
		if (room[i].courant == INT_MAX)
			room[i].previous = -42;
		i++;
	}
}

void			ft_reset_power(t_room *room, int nbroom, t_algo *algo)
{
	int i;

	i = 0;
	while (i < nbroom)
	{
		room[i].power = 0;
		room[i].prev = 0;
		//		room[i].previous = -42;
		i++;
	}
	room[algo->index_start].power = 1;
	algo->list1[0] = algo->index_start;
	algo->list1[1] = -42;
}

t_path *ft_init_path(t_room *room, t_algo *algo, t_all *all)
{
	t_path		*way;
	int			i;
	int			j;
	int			lesslink;

	lesslink = room[algo->index_start].links > room[algo->index_end].links ? room[algo->index_end].links : room[algo->index_start].links;
	if (!(way = (t_path*)malloc(sizeof(t_path) * (lesslink))))
		return (NULL);
	i = 0;
	while (i < lesslink)
	{
		way[i].nb_path = 0;
		if (!(way[i].len_path = (int*)malloc(sizeof(int) * (lesslink))))
			return (NULL);
		j = 0;
		while (j < lesslink)
		{
			way[i].len_path[j] = 0;
			j++;
		}
		if (!(way[i].rev = (int*)malloc(sizeof(int) * (all->room))))
			return (NULL);
		if (!(way[i].path = (int**)malloc(sizeof(int*) * (lesslink))))
			return (NULL);
		j = 0;
		while (j < lesslink)
		{
			if (!(way[i].path[j] = (int*)malloc(sizeof(int) * (all->room))))
				return (NULL);
			j++;
		}
		i++;
	}
	return (way);
}

int		ft_create_flux(t_room *room, t_algo *algo, t_path *way)
{
	int i;
	int len;
	int curr;
	int prev;
	static int k = 0;

	len = 0;
	prev = 0;
	curr = algo->index_end;
	while (curr != algo->index_start)
	{
		printf("%s\n", room[curr].name);
		way[0].rev[len] = curr;
		curr = room[curr].previous;
		len++;
		if (room[curr].courant != INT_MAX)
			printf("J'ai remonte un courant a la salle %s\n", room[curr].name);
		room[curr].courant = len;
	}
	i = 0;
	len--;
	while (len >= 0)
	{
		i = way[k].len_path[way[k].nb_path];
		way[k].path[way[k].nb_path][i] = way[0].rev[len];
		way[k].len_path[way[k].nb_path]++;
		len--;
	}
	print_dbint(way[k].path[way[k].nb_path], way[k].len_path[way[k].nb_path], room);
	way[k].nb_path++;
	return (0);
}

int		ft_call_power(t_room *room, t_algo *algo, t_all *all)
{
	t_path	*way;
	int		ok;
	int		prev;
	int		lesslink;
	int		i;

	algo->k = 0;
	ok = 0;
	prev = 0;
	lesslink = room[algo->index_start].links > room[algo->index_end].links ? room[algo->index_end].links : room[algo->index_start].links;
	if (ft_init_algo(algo, all, room) == -1)
		return (-1);
	if (!(way = (ft_init_path(room, algo, all))))
		return (-1);
	i = -1;
	while (++i < 2)
	{
		ok = ft_fill_power(room, algo, 1, 2);
		if (ok == -1)
			break ;
		ft_create_flux(room, algo, way);
		ft_reset_power(room, all->room, algo);
	}
	/*	ft_fill_power(room, algo, 1, 2);
		ft_create_flux(room, algo, way);
		ft_reset_power(room, all->room, algo);
		ft_fill_power(room, algo, 1, 2);
		ft_reset_courant(room, all->room);
		ft_create_flux(room, algo, way);
		ft_reset_power(room, all->room, algo);
		ft_fill_power(room, algo, 1, 2);
		ft_create_flux(room, algo, way);*/
	//	ft_print_struct(room, all->room);
	//	save = ft_check_lonely_room(room, algo);
	//	free(algo->list1);
	//	free(algo->list2);
	//	if (room[algo->index_start].power == 0)
	//		return (ft_parser_error("Broken path\n"));
	//	ft_sort_room(room, all);
	//	room[algo->index_start].links -= save;
	return (0);
}
