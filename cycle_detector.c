/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_detector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 11:59:10 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/08 12:21:54 by prastoin         ###   ########.fr       */
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


int		ft_cycle_detector(t_special_ant *ant, t_algo *algo, int curr_ant)
{
	int	*path;
	int	len;
	int cycle;

	(void)algo;
	cycle = 0;
	len = ant[curr_ant].len;
	path = ant[curr_ant].path;
	curr_ant--;
	while (curr_ant >= 0)
	{
		if (len == ant[curr_ant].len)
			if (ft_int_cmp(path, ant[curr_ant].path, len) == 0)
				cycle++;
		if (cycle == 2)
		{
			
		}
//			return (0);
		curr_ant--;
	}
	return (-1);
}
