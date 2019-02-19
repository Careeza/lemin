/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 02:01:34 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/19 20:06:43 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_init_create_flux(int *len, int *curr,
		int *prev, t_algo *algo)
{
	*len = 0;
	*prev = 0;
	*curr = algo->index_end;
}

void			ft_create_flux2(t_path *way, t_algo *algo, int len)
{
	int i;

	i = 0;
	while (len >= 0)
	{
		i = way[algo->k].len_path[way[algo->k].nb_path];
		way[algo->k].path[way[algo->k].nb_path][i] = way[0].rev[len];
		way[algo->k].len_path[way[algo->k].nb_path]++;
		len--;
	}
	way[algo->k].nb_path++;
}
