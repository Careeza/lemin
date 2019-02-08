/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:52:03 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/08 13:44:42 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_previous(t_room *room, int index, t_special_ant *ghost, int index_end, t_path *path)
{
	//	printf("No way need to previous %d\n", room[index].previous);
	if (index == index_end)
		return (-42);
	room[ghost->curr].pass = 0;
	room[ghost->curr].i = 0;
	ghost->power--;
	ghost->curr = room[index].previous;
	path[ghost->nb].len--;
	//	ghost->previous = index; //normalement inutile
	room[room[index].previous].i++;;
	return(room[index].previous);
}

void	ft_cpint_n(int *path, int *dest, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		dest[i] = path[i];
		i++;
	}
}

int		ft_move_ghost_ant(t_room *room, t_special_ant *ghost, t_algo *algo, t_path **path, t_all *all)
{
	int next;
	static int i;

	next = -42;
	while (room[ghost->curr].i < room[ghost->curr].links)
	{
		next = ft_atoi(room[ghost->curr].way[room[ghost->curr].i]);
		if (room[next].pass != 1)
		{
			room[ghost->curr].pass = 1;
			ghost->power++;
			room[next].previous = ghost->curr;
			//			printf("ghost.nb %d et len %d\n", ghost->nb, path[ghost->nb].len);
			(*path)[ghost->nb].path[(*path)[ghost->nb].len] = ghost->curr;
			(*path)[ghost->nb].len++;
			if (next == algo->index_start)
			{
				(*path)[ghost->nb].path[(*path)[ghost->nb].len] = next;
				//				(*path)[nb].len++;
				(*path)[ghost->nb].power = ghost->power;
				i++;
//				if (i % 10000 == 0)
//				{
//					printf("\033[31;01mJe viens de %d et je vais dans start\n\033[0m", ghost->curr);
//					print_dbint((*path)[ghost->nb].path, (*path)[ghost->nb].len);
//				}
				ghost->nb++;
				if (ghost->nb >= all->room * ghost->i)
				{
//					printf("I USE REAL %d\n", ghost->nb);
					*path = ft_realloc_path(*path, all);
					ghost->i++;
				}
				(*path)[ghost->nb].len = (*path)[(ghost->nb - 1)].len - 1;
				(*path)[ghost->nb].power = (*path)[(ghost->nb - 1)].power - 1;
				ft_cpint_n((*path)[(ghost->nb - 1)].path, (*path)[ghost->nb].path, (*path)[ghost->nb].len);
				room[ghost->curr].i++;
				return (ghost->curr);
			}
			return (next);
		}
		room[ghost->curr].i++;
	}
	return (-42);
}

static int		ft_fill_power(t_room *room, t_algo *algo, t_special_ant *ghost, t_path *path, t_all *all)
{
	int	i;
	int j;
	int	curr;
	int	ok;

	ok = 1;
	curr = algo->index_end;
	i = 0;
	j = 0;
	while (ok != -42 && ghost->nb < (room[algo->index_end].links + room[algo->index_start].links) * 10)
	{
		if ((curr = (ft_move_ghost_ant(room, ghost, algo, &path, all))) != -42)
			ghost->curr = curr;
		else
			ok = ft_previous(room, ghost->curr, ghost, algo->index_end, path);
	}
	i = 0;
	while (i < ghost->nb)
	{
		j = 1;
		while (j < path[i].len)
		{
			room[path[i].path[j]].path[room[path[i].path[j]].nbrpath] = i;
			room[path[i].path[j]].nbrpath++;
			if (room[path[i].path[j]].nbrpath >= all->room * room[path[i].path[j]].j)
			{
				room[path[i].path[j]].path = ft_realloc_int(room[path[i].path[j]].path, room[path[i].path[j]].nbrpath, all);
				room[path[i].path[j]].j++;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < ghost->nb)
	{
		j = 0;
		printf("path =");
		while (j < path[i].len)
		{
			printf ("%d --", path[i].path[j]);
			j++;
		}
		printf ("%d --", j);
		printf("power = %d\n", path[i].len);
		i++;
	}
	print_dbint(room[3].path, room[3].nbrpath);
	printf("\n%d -- %d\n", room[3].path[0], room[3].nbrpath);
	return (0);
}

int		ft_fill_power_path(t_algo *algo, t_room *room, t_all *all, t_path *path)
{
	ft_print_struct(room, all->room);
	room[algo->index_end].pass = 1;
	t_special_ant ghost;
	ghost.power = 0;
	ghost.i = 1;
	ghost.curr = algo->index_end;
	ghost.nb = 0;
	ghost.previous = -42;
	ft_fill_power(room, algo, &ghost, path, all);
	ft_print_struct(room, all->room);
	return (0);
}
