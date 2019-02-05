/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:50:33 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/05 13:42:51 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			*ft_realloc_int(int *list, int len, t_all *all)
{
	static int i;
	int	j;
	int	*fresh;

	i++;
	j = 0;
	if (!(fresh = (int *)malloc(sizeof(int) * (all->room + len ))))
		return (NULL);
	while (j < len)
	{
		fresh[j] = list[j];
		j++;
	}
	free(list);
	return (fresh);
}

int			*ft_cpdbint(int *list, int len, t_all *all)
{
	int i;
	int *list2;

	i = 0;
	if (!(list2 = (int *)malloc(sizeof(int) * all->room)))
		return (NULL);
	while (i < len)
	{
		list2[i] = list[i];
		i++;
	}
	if (list != NULL)
	{
		free(list);
		list = NULL;
	}
	return (list2);
}

t_path		*ft_realloc_path(t_path *path, t_all *all)
{
	t_path		*path2;
	static int	i;
	int			j;

	i++;
	j = 0;
	if (!(path2 = (t_path *)malloc(sizeof(t_path) * (all->room * (i + 1)))))
		return (NULL);
	while (j < (all->room * i))
	{
		path2[j].len = path[j].len;
		path2[j].power = path[j].power;
		path2[j].path = ft_cpdbint(path[j].path, path2[j].len, all);
		j++;
	}
	if (path != NULL)
	{
		free (path);
		path = NULL;
	}
	while (j < (all->room * (i + 1)))
	{
		path2[j].len = 0;
		path2[j].power = 0;
		if (!(path2[j].path = (int *)malloc(sizeof(int) * all->room)))
			return (NULL);
		j++;
	}
	return (path2);
}

/*int	ft_ant_path(int curr_ant, t_room *room, t_algo *algo, t_fourmi *ant)
{
	return (0);
}*/

/*int		ft_fill_path(t_fourmi *ant, t_algo *algo, t_room *room, t_all *all)
{
	int		curr;

	return (0);
}*/

t_fourmi	*ft_foumisse(long fourmis, t_algo *algo, t_all *all)
{
	long	i;
	t_fourmi *ants;

	if (!(ants = (t_fourmi*)malloc(sizeof(t_fourmi) * (fourmis))))
		return (NULL);
	i = 1;
	while (i <= fourmis)
	{
		ants[i - 1].name = i;
		ants[i - 1].curr = algo->index_start;
		ants[i - 1].previous = -42;
		if (!(ants[i - 1].path = malloc(sizeof(int) * all->room)))
			return (NULL);
		i++;
	}
	return (ants);
}

t_path		*ft_init_path(t_all *all)
{
	int	i;
	t_path *path;

	i = 0;
	if (!(path = (t_path *)malloc(sizeof(t_path) * all->room)))
		return (NULL);
	while (i < all->room)
	{
		path[i].power = 0;
		path[i].len = 0;
		if (!(path[i].path = (int *)malloc(sizeof(int) * all->room)))
			return (NULL);
		i++;
	}
	return (path);
}

int		ft_algo(t_room *room, t_algo *algo, long fourmis, t_all *all)
{
	t_path *path;
	t_fourmi *ant;

	(void)room;
	(void)fourmis;
	if (!(path = ft_init_path(all)))
		return (-1);
	if (!(ant = ft_foumisse(algo->fourmis, algo, all)))
		return (-1);
	ft_fill_power_path(algo, room, all, path);
	return (0);
}
