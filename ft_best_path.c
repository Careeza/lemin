/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   power.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:52:03 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/07 20:54:47 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	ft_init_db_int(int *list, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		list[i] = 0;
		i++;
	}
}

t_special_ant *ft_init_ant(int nbrfourmis, t_all *all)
{
	t_special_ant *ant;
	int i;

	i = 0;
	if(!(ant = (t_special_ant*)malloc(sizeof(t_special_ant) * (nbrfourmis))))
		return (NULL);
	while (i < nbrfourmis)
	{
		ant[i].coup = 0;
		if (!(ant[i].wait = (int*)malloc(sizeof(int) * (all->room))))
			return (NULL);
		ft_init_db_int(ant[i].wait, all->room);
		if (!(ant[i].path = (int*)malloc(sizeof(int) * (all->room))))
			return (NULL);
		if (!(ant[i].savepath = (int*)malloc(sizeof(int) * (all->room))))
			return (NULL);
		ant[i].len = 0;
		ant[i].savelen = 0;
		i++;
	}
	return (ant);
}

int			ft_move(t_room *room, t_special_ant *ant, int curr_ant, t_algo *algo)
{
	int		curr;
	int		best;

	curr = ant[curr_ant].curr;
	best = -42;
	while (room[curr].i < room[curr].links)
	{
		best = room[curr].index[room[curr].i];
		if (best == room[curr].previous || best == algo->index_start)
		{
			best = -42;
			room[curr].i++;
		}
		else
		{
			room[best].previous = ant[curr_ant].curr;
			room[curr].i++;
			break;
		}
	}
	if(best == -42)
		return (best);
	ant[curr_ant].coup++;
	while (room[best].coup[ant[curr_ant].coup] == 1)
	{
//		printf("curr %d\n", curr);
		ant[curr_ant].wait[best]++;
		ant[curr_ant].coup++;
	}
//	printf("best = %d -- coup = %d\n", best, ant[curr_ant].coup);
//	room[best].coup[ant[curr_ant].coup] = 1;
	return (best);
}

int		ft_previous(t_algo *algo, t_room *room, t_special_ant *ant, int curr_ant)
{
	int		curr;

	curr = ant[curr_ant].curr;
//	printf("je return a %d\n", ant-curr);
	room[curr].coup[ant[curr_ant].coup] = 0;
	if (curr == algo->index_start)
		return (-42);
//	printf("coup = %d et coup de start %d\n", ant[curr_ant].coup, room[algo->index_start].coup[0]);
//	printf("%d curr-- %s\n", ant[curr_ant].wait[curr], room[curr].name);
	ant[curr_ant].coup -= ant[curr_ant].wait[curr];
	ant[curr_ant].wait[curr] = 0;
	ant[curr_ant].coup--;
//	printf("coup2 = %d et coup de start %d\n", ant[curr_ant].coup, room[algo->index_start].coup[0]);
	room[curr].pass = 0;
	room[curr].i = 0;
	ant[curr_ant].len--;
	ant[curr_ant].curr = room[curr].previous;
	return(0);
}

void		ft_fill_coup(t_room *room, int *path, int len)
{
	int		i;
	int		coup;

	coup = 1;
	i = 0;
	while (i < len - 1)
	{
		while (room[path[i]].coup[coup] == 1)
			coup++;
		room[path[i]].coup[coup] = 1;
		i++;
		coup++;
	}
	return ;
}

void	ft_reset_i(t_room *room, int nbroom)
{
	int i;

	i = 0;
	while (i < nbroom)
	{
		room[i].i = 0;
		room[i].previous = -42;
		i++;
	}
}

int		ft_find_best_path(t_algo *algo, t_room *room, t_all *all, t_special_ant *ant)
{
	int		curr_ant = 0;
	int		next;
	int		cmt;
	int		i;

	(void)all;
	cmt = 0;
	while (curr_ant < 4)
	{
		ant[curr_ant].curr = algo->index_start;
		while (cmt != -42)
		{
			if (ant[curr_ant].curr != algo->index_end)
			{
				if ((next = ft_move(room, ant, curr_ant, algo)) != -42) // && ant[curr_ant].coup <= (algo->lesscoup + 1))
				{
	//				printf("from %s to %s je suis a mon %deme coups\n", room[ant[curr_ant].curr].name, room[next].name, ant[curr_ant].coup);
					ant[curr_ant].path[ant[curr_ant].len] = next;
					ant[curr_ant].len++;
					ant[curr_ant].curr = next;
				}
				else
				{
				//	if (ant[curr_ant].coup >= algo->lesscoup + 1)
//						printf("CHEMIN de MERDE%d\n", ant[curr_ant].coup);
//					printf("I am here %s And i am stuck\n", room[ant[curr_ant].curr].name);
					cmt = ft_previous(algo, room, ant, curr_ant);
//					printf("Je reviens en arrier\n");
				}
			}
			else
			{
//				printf("Je suis dans end\n");
				if (ant[curr_ant].coup == algo->lesscoup + 1)
				{
					ft_cpint_n(ant[curr_ant].path, ant[curr_ant].savepath, ant[curr_ant].len);
					ant[curr_ant].savelen = ant[curr_ant].len;
					printf("CHEMIN de Exploitable\n");
				}
				if (algo->lesscoup == ant[curr_ant].coup)
				{
					printf("UNE fourmis A TROUVER UN CHEMIN OPTI\n");
					break ;
				}
		//		printf("Previous\n");
	//			printf("I am in end with a coup of %d", ant[curr_ant].coup);
				cmt = ft_previous(algo, room, ant, curr_ant);
//					printf("Je reviens en arrier\n");
			}
		}
		if (cmt != -42)
		{
			ft_fill_coup(room, ant[curr_ant].path, ant[curr_ant].len);
			print_dbint(ant[curr_ant].path, ant[curr_ant].len, room);
		}
		else
		{
			printf("Ok\n");
			algo->lesscoup++;
			ft_fill_coup(room, ant[curr_ant].savepath, ant[curr_ant].savelen);
			print_dbint(ant[curr_ant].savepath, ant[curr_ant].savelen, room);
		}
		i = 0;
/*		while (i < 5)
		{
			printf("room 1 coup[%d] = %d\n", i, room[4].coup[i]);
			printf("room 2 coup[%d] = %d\n", i, room[5].coup[i]);
			i++;
		}*/
		ft_reset_i(room, all->room);
		curr_ant++;
	}
	return (0);
}

int		ft_found_path(t_algo *algo, t_room *room, t_all *all)
{
	t_special_ant *ant;
	int i;

	algo->lesscoup = room[room[algo->index_start].index[0]].power;
	i = 0;
	while (i < all->room)
	{
		if (!(room[i].coup = (int*)malloc(sizeof(int) * (algo->lesscoup + 1000))))
			return (-2);
		ft_init_db_int(room[i].coup, algo->lesscoup + 1000);
		i++;
	}
//	room[4].coup[1] = 1;
	ant = ft_init_ant(all->fourmis, all);
//	printf("TOUT SE PASSSE BIEN\n");
//	printf("%d -- %d\n", algo->lesscoup, room[algo->index_start].links * all->room);
	ft_find_best_path(algo, room, all, ant);
	return (0);
}
