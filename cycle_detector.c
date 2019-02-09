/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_detector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 11:59:10 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/09 04:04:47 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_int_cmp(int *list1, int *list2, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (list1[i] != list2[i])
			return (-42);
		i++;
	}
	return (0);
}

int		ft_fill_fourmi(int curr_ant, t_special_ant *ant, int lencycle,
		t_all *all)
{
	int		i;
	int		deb_cy;

	deb_cy = curr_ant - lencycle;
	i = 0;
	curr_ant++;
	while (curr_ant < all->fourmis)
	{
		ft_cpint_n(ant[deb_cy + (i % (lencycle + 1))].path, ant[curr_ant].path,
				ant[deb_cy + (i % (lencycle + 1))].len);
		ant[curr_ant].len = ant[deb_cy + (i % (lencycle + 1))].len;
		i++;
		curr_ant++;
	}
	return (0);
}

int		ft_cycle_detector(t_special_ant *ant, int curr_ant, int len, int *path)
{
	int cycle;
	int lencycle;
	int count;

	cycle = 0;
	count = 0;
	while (curr_ant >= 0)
	{
		if (len == ant[curr_ant].len)
			if ((ft_int_cmp(path, ant[curr_ant].path, len)) != -42)
			{
				if (cycle == 1 && lencycle != count)
					return (-1);
				lencycle = count;
				cycle++;
				count = -1;
			}
		if (cycle == 2)
			return (lencycle);
		curr_ant--;
		count++;
	}
	return (-1);
}
