/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:12:01 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/19 04:52:36 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_sort_index(t_room *room, int i)
{
	int		j;
	long	tmp;
	int		corr;

	corr = 1;
	while (corr != 0)
	{
		corr = 0;
		j = 1;
		while (j < room[i].links)
		{
			if (room[room[i].index[j - 1]].power > room[room[i].index[j]].power)
			{
				tmp = room[i].index[j];
				room[i].index[j] = room[i].index[j - 1];
				room[i].index[j - 1] = tmp;
				j = j >= 2 ? j - 2 : 0;
				corr++;
			}
			j++;
		}
	}
}

void	ft_sort_room(t_room *room, t_all *all)
{
	int i;

	i = 0;
	while (i < all->room)
	{
		ft_sort_index(room, i);
		i++;
	}
}

int		ft_nm(char *str, t_room *room, int fourmis, int nbroom)
{
	int len;

	len = 0;
	while (str[len] != ' ')
		len++;
	if (nbr_space(str, ' ') != 2)
		return (-1);
	if (ft_str_is_digit((str + len), '\0') == -1)
		return (-1);
	room->name = ft_strndup(str, len);
	room->links = 0;
	room->prev = 0;
	room->slot = 0;
	room->power = 0;
	room->previous = -42;
	room->courant = INT_MAX;
	if (!(room->index = (int*)malloc(sizeof(int) * nbroom)))
		return (-2);
	(void)fourmis;
	return (0);
}

int		ft_verif_link(t_room *room, char *str, t_all *all)
{
	char	*name;
	int		len;
	int		index;

	len = 0;
	index = 0;
	while ((str[len] != '-') && str[len])
		len++;
	if (!(name = ft_strndup(str, len)))
		return (ft_parser_error("ft_strdup failed\n", 2, all, room));
	while ((index < all->room) && (ft_strcmp(name, room[index].name) != 0))
		index++;
	if (name != NULL)
		free(name);
	if (index == all->room)
		return (ft_parser_error("Linked room doesn't exist\n", -1, all, room));
	return (index);
}

int		ft_verif_link2(t_room *room, char *str, t_all *all, int indexa)
{
	char	*name;
	int		len;
	int		indexb;

	len = 0;
	indexb = 0;
	while ((str[len] != '-') && str[len])
		len++;
	if (!(name = ft_strdup(&str[len + 1])))
		return (ft_parser_error("ft_strdup failed\n", 2, all, room));
	while ((indexb < (all->room)) && (ft_strcmp(name, room[indexb].name) != 0))
		indexb++;
	if (name != NULL)
		free(name);
	if (indexb == all->room)
		return (ft_parser_error("Linked room doesn't exist\n", -1, all, room));
	if (indexa == indexb)
		return (ft_light_error("A room is linked to herself\n"));
	if (ft_verif_tube(indexa, indexb, room) == -1)
		return (ft_light_error("Tube already exists\n"));
	room[indexa].index[room[indexa].links] = indexb;
	room[indexb].index[room[indexb].links] = indexa;
	room[indexb].links += 1;
	room[indexa].links += 1;
	return (0);
}
