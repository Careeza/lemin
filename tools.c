/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:24:22 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/04 13:14:42 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_verif_tube(int indexa, int indexb, t_room *room)
{
	int	i;
	int	len;
	int	val;

	val = 0;
	i = 0;
	len = 0;
	while (i < room[indexa].links)
	{
		val = ft_atoi((room[indexa].index) + len);
		len = ft_lennbr(val) + 1;
		if (indexb == val)
			return (-1);
		i++;
	}
	return (0);
}

int	nbr_space(char *str, char c)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (str[0] == '#')
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			space++;
		i++;
	}
	return (space);
}

int		ft_str_is_digit(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != ' ' && str[i] != '\0')
			return (-1);
		i++;
	}
	return (0);
}

int		ft_malloc_list(t_algo *algo, int room)
{
	if (!(algo->list1 = (int*)malloc(sizeof(int) * (room))))
		return (-1);
	if (!(algo->list2 = (int*)malloc(sizeof(int) * (room))))
		return (-1);
	algo->list1[0] = algo->index_end;
	algo->list1[1] = -42;
	return (0);
}
