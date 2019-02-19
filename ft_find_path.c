/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 01:05:08 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/19 01:09:04 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_create_flux2(t_room *room, t_path *way, int k, int len)
{
	int i;

	(void)room;
	while (len >= 0)
	{
		i = way[k].len_path[way[k].nb_path];
		way[k].path[way[k].nb_path][i] = way[0].rev[len];
		way[k].len_path[way[k].nb_path]++;
		len--;
	}
	way[k].nb_path++;
}

void	ft_create_new_flux(t_room *room, t_path *way, int *k, int len)
{
	int i;
	int j;

	(void)room;
	i = 0;
	while (way[0].rev[len - 1] != way[*k].path[i][0])
		i++;
	j = 0;
	while (way[0].rev[len - j - 1] == way[*k].path[i][j])
		j++;
	while (j < way[*k].len_path[i])
	{
		room[way[*k].path[i][j]].courant = INT_MAX;
		j++;
	}
	ft_cp_dbdint(way, *k, way[*k].nb_path, i);
	(*k)++;
}

int		ft_create_flux(t_room *room, t_algo *algo, t_path *way)
{
	int len;
	int curr;
	int prev;
	static int k;

	len = 0;
	prev = 0;
	curr = algo->index_end;
	while (curr != algo->index_start)
	{
		way[0].rev[len] = curr;
		curr = room[curr].previous;
		len++;
		if (room[curr].courant != INT_MAX && curr != algo->index_start)
			prev = curr;
		room[curr].courant = len;
	}
	len--;
	if (prev == 0)
		ft_create_flux2(room, way, k, len);
	else
	{
		if (k + 1 == algo->lesslink)
		{
			printf("I have broke here\n");
			return (-1);
		}
		ft_create_new_flux(room, way, &k, len + 1);
		ft_create_flux2(room, way, k, len);
	}
	algo->k = k;
	return (0);
}

int		ft_gestion_pack(t_algo *algo, t_path *way)
{
	int		i;
	int		j;
	int		somme;
	float	best;
	int		index;

	i = 0;
	best = INT_MAX;
	while (i <= algo->k)
	{
		somme = 0;
		j = 0;
		while (j < way[i].nb_path)
		{
			somme += way[i].len_path[j];
			j++;
		}
		if (best > ((somme + algo->fourmis) / (float)way[i].nb_path) - 1)
		{
			best = ((somme + algo->fourmis) / (float)way[i].nb_path) - 1;
			index = i;
		}
		i++;
	}
	return (index);
}

t_special_ant	*ft_give_path_to_ant(t_algo *algo, t_path *way, int i, t_all *all)
{
	t_special_ant	*ant;
	int				cmt;
	int				*power;
	int				best;
	int				index;
	int				j;

	if (!(ant = ft_init_ant(all->fourmis, all)))
		return (NULL);
	if (!(power = (int*)malloc(sizeof(int) * way[i].nb_path)))
		return (NULL);
	ft_cpint_n(way[i].len_path, power, way[i].nb_path);
	cmt = 0;
	while (cmt < algo->fourmis)
	{
		j = 0;
		best = INT_MAX;
		while (j < way[i].nb_path)
		{
			if (best > power[j])
			{
				best = power[j];
				index = j;
			}
			j++;
		}
		ft_cpint_n(way[i].path[index], ant[cmt].path, way[i].len_path[index]);
		ant[cmt].len = way[i].len_path[index];
		cmt++;
		power[index]++;
	}
	return (ant);
}

