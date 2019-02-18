/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 16:48:47 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/18 23:30:42 by fbecerri         ###   ########.fr       */
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
				if (room[room[algo->list1[i]].index[j]].power == 0 && room[algo->list1[i]].index[j] != algo->index_end && (!(room[algo->list1[i]].prev == 1 && room[room[algo->list1[i]].index[j]].courant == INT_MAX)))
				{
								//		printf("Je suis ici %s et je veux aller %s\n J'ai un courant de %d et il a un courant de %d\n", room[algo->list1[i]].name, room[room[algo->list1[i]].index[j]].name, room[algo->list1[i]].courant, room[room[algo->list1[i]].index[j]].courant);
						if (room[algo->list1[i]].courant == INT_MAX || room[algo->list1[i]].courant <= room[room[algo->list1[i]].index[j]].courant)
						{
							room[room[algo->list1[i]].index[j]].power = 1;
							algo->list2[cmt] = room[algo->list1[i]].index[j];
							if (room[room[algo->list1[i]].index[j]].courant == INT_MAX)
								room[room[algo->list1[i]].index[j]].previous = algo->list1[i];
							else
								room[room[algo->list1[i]].index[j]].prev = room[algo->list1[i]].prev + 1;
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

void			ft_reset_power(t_room *room, int nbroom, t_algo *algo)
{
	int i;

	i = 0;
	while (i < nbroom)
	{
		room[i].power = 0;
		room[i].prev = 0;
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
	if (!(way = (t_path*)malloc(sizeof(t_path) * lesslink)))
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

void	ft_cp_dbdint(t_path *way, int k, int nb_path, int exept)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (j < nb_path)
	{
		if (j != exept)
		{
			ft_cpint_n(way[k].path[j], way[k + 1].path[i], way[k].len_path[j]);
			way[k + 1].len_path[i] = way[k].len_path[j];
			i++;
		}
		j++;
	}
	way[k + 1].nb_path = i;
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

void		ft_move(t_special_ant *ant, int curr_ant, t_room *room)
{
	const int		previous = ant[curr_ant].curr;
	const int		curr = ant[curr_ant].path[ant[curr_ant].i];

	room[previous].slot = 0;
	room[curr].slot += 1;
	ant[curr_ant].curr = curr;
}

int		ft_play_and_print(t_special_ant *ant, t_room *room, t_algo *algo, t_all *all)
{
	int	curr_ant;
	int	i;

	i = 0;
	curr_ant = 0;
	while (i < all->fourmis)
	{
		ant[curr_ant].curr = algo->index_start;
		i++;
	}
	room[algo->index_start].slot = all->fourmis;
	while (room[algo->index_end].slot != all->fourmis)
	{
		if (algo->flag == 1 || algo->flag == 3)
			ft_color(algo->step, 0);
		curr_ant = 0;
		while (curr_ant < all->fourmis)
		{
			if (ant[curr_ant].curr != algo->index_end)
			{
				if (room[ant[curr_ant].path[ant[curr_ant].i]].slot == 0 || ant[curr_ant].path[ant[curr_ant].i] == algo->index_end)
				{
					ft_move(ant, curr_ant, room);
					ft_display(curr_ant, ant, room, algo);
					ant[curr_ant].i++;
				}
			}
			curr_ant++;
		}
		algo->step++;
		ft_putchar('\n');
	}
	return (0);
}

int		ft_call_power(t_room *room, t_algo *algo, t_all *all)
{
	t_path	*way;
	int		i;
	t_special_ant	*ant;

	algo->fourmis = all->fourmis;
	algo->lesslink = room[algo->index_start].links > room[algo->index_end].links ? room[algo->index_end].links : room[algo->index_start].links;
	if (ft_init_algo(algo, all, room) == -1)
		return (-1);
	if (!(way = (ft_init_path(room, algo, all))))
		return (-1);
	while (1)
	{
		if (ft_fill_power(room, algo, 1, 2) == -1)
			break ;
		if (ft_create_flux(room, algo, way) == -1)
			break ;
		ft_reset_power(room, all->room, algo);
	}
	i = ft_gestion_pack(algo, way);
	ant = ft_give_path_to_ant(algo, way, i, all);
	ft_play_and_print(ant, room, algo, all);
	return (0);
}
