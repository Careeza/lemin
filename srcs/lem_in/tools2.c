/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 05:41:52 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 23:38:14 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			ft_cpint_n(int *path, int *dest, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		dest[i] = path[i];
		i++;
	}
}

void			ft_cp_dbdint(t_path *way, int k, int nb_path, int exept)
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

t_special_ant	*ft_init_ant(int nbrfourmis, t_all *all)
{
	t_special_ant	*ant;
	int				i;

	i = 0;
	if (!(ant = (t_special_ant*)malloc(sizeof(t_special_ant) * (nbrfourmis))))
	{
		ft_parser_error("Malloc failed\n", -1, NULL, NULL);
		return (NULL);
	}
	while (i < nbrfourmis)
	{
		if (!(ant[i].path = (int*)malloc(sizeof(int) * (all->room))))
		{
			ft_parser_error("Malloc failed\n", -1, NULL, NULL);
			return (NULL);
		}
		ant[i].len = 0;
		ant[i].i = 0;
		ant[i].curr = 0;
		i++;
	}
	return (ant);
}

int				ft_file(t_all *all)
{
	int	i;

	i = system("echo "" > visu.txt");
	if (i == -1)
		ft_parser_error("Fork Waitpid failed\n", -1, NULL, NULL);
	if (i == 127)
		ft_parser_error("Shell execution failed\n", -1, NULL, NULL);
	if (i == 127 || i == -1)
		return (-1);
	if ((all->fd = open("visu.txt", O_RDWR)) == -1)
	{
		ft_parser_error("Open error can't open\n", -1, NULL, NULL);
		return (-1);
	}
	return (0);
}
