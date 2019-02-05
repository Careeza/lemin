/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:11:52 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/05 16:06:28 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	ft_nbr_room(t_all *all)
{
	int		i;

	i = 0;
	all->room = 0;
	while (all->map[i])
	{
		if (nbr_space(all->map[i], '-') == 1) //s'arrete au liaison
			break;
		if (all->map[i][0] != '#') //evites les commandes et les comments
		{
			if (nbr_space(all->map[i], ' ') == 2)
				all->room++;
		}
		i++;
	}
	if (all->room <= 1)
		return (-1);
	return (0);
}

int		ft_nbrfourmis(t_all *all)
{
	int	i;

	i = 0;
	while (all->map[i][0] == '#')
		i++;
	all->fourmis = ft_atoi(all->map[i]);
	if (all->fourmis <= 0 || all->fourmis >= INT_MAX)
		return (-1);
	return(i + 1);
}

int		ft_reading(t_all *all)
{
	char	buff[BUFF_SIZE];
	int		ret;
	int		check;

	check = 0;
	all->str = ft_strnew(0);
	while ((ret = read(0, buff, BUFF_SIZE - 1)) > 0)
	{
		buff[ret] = '\0';
		check++;
		if (!(all->str = ft_strjoin(all->str, buff)))
			return (-1);
	}
	if(!(all->map = ft_strsplit(all->str, '\n')))
		return (-1);
	if (ret < 0 || check == 0)
		return (-1);
	return (0);
}

//verifier que le tube n exsite pas dans le way de end et de start car pb au niveau de links

int main(void)
{
	t_room	*room;
	t_all	all;
	t_algo	algo;
	int		i;

	if (ft_reading(&all) == -1)
		return (ft_parser_error("Reading failed\n"));
	if ((i = ft_nbrfourmis(&all)) == -1)
		return (ft_parser_error("Nombre de fourmis invalides\n"));
	if (ft_nbr_room(&all) == -1)
		return (ft_parser_error("Pas assez de room\n"));
	if (!(room = (t_room *)malloc(sizeof(t_room) * (all.room + 1))))
		return (ft_parser_error("Impossible malloc\n"));
	if ((i = ft_parser(&all, room, i)) == -1)
		return (-1);
	if (ft_check_link(&all, room, i) == -1)
		return (-1);
//	ft_print_struct(room, all.room);
	ft_verif_doublons(room, &all, &algo);
	ft_algo(room, &algo, all.fourmis, &all);
	return (0);
}
