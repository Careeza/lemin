/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 01:05:08 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 22:34:17 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_create_new_flux(t_room *room, t_path *way,
	t_algo *algo, int len)
{
	int i;
	int j;

	i = 0;
	while (way[0].rev[len - 1] != way[algo->k].path[i][0])
		i++;
	j = 0;
	while (way[0].rev[len - j - 1] == way[algo->k].path[i][j])
		j++;
	while (j < way[algo->k].len_path[i])
	{
		room[way[algo->k].path[i][j]].courant = INT_MAX;
		j++;
	}
	ft_cp_dbdint(way, algo->k, way[algo->k].nb_path, i);
	algo->k++;
}

int				ft_create_flux(t_room *room, t_algo *algo, t_path *way)
{
	int len;
	int curr;
	int prev;

	ft_init_create_flux(&len, &curr, &prev, algo);
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
		ft_create_flux2(way, algo, len);
	else
	{
		if (algo->k + 1 == algo->lesslink)
			return (-1);
		ft_create_new_flux(room, way, algo, len + 1);
		ft_create_flux2(way, algo, len);
	}
	return (0);
}

int				ft_gestion_pack(t_algo *algo, t_path *way)
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

int				ft_give_path_to_ant2(t_path *way, int i, int *power)
{
	int j;
	int best;
	int index;

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
	return (index);
}

t_special_ant	*ft_give_path_to_ant(t_algo *algo, t_path *way,
	int i, t_all *all)
{
	t_special_ant	*ant;
	int				*power;
	int				index;

	if (!(ant = ft_init_ant(all->fourmis, all)))
		return (NULL);
	if (!(power = (int*)malloc(sizeof(int) * way[i].nb_path)))
		return (NULL);
	ft_cpint_n(way[i].len_path, power, way[i].nb_path);
	algo->cmt = 0;
	while (algo->cmt < algo->fourmis)
	{
		index = ft_give_path_to_ant2(way, i, power);
		ft_cpint_n(way[i].path[index], ant[algo->cmt].path,
			way[i].len_path[index]);
		ant[algo->cmt].len = way[i].len_path[index];
		algo->cmt++;
		power[index]++;
	}
	if (power != NULL)
		free(power);
	return (ant);
}
