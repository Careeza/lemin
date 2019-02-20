/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:11:52 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 22:35:48 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_nbr_room(t_all *all)
{
	int		i;

	i = 0;
	all->room = 0;
	while (all->map[i])
	{
		if (nbr_space(all->map[i], '-') == 1)
			break ;
		if (all->map[i][0] != '#')
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

int		ft_nbrfourmis(t_all *all, t_algo *algo)
{
	int	i;

	i = 0;
	while (all->map[i][0] == '#')
		i++;
	all->fourmis = ft_atoi(all->map[i]);
	algo->fourmis = all->fourmis;
	if (all->fourmis <= 0 || all->fourmis >= INT_MAX)
		return (-1);
	return (i + 1);
}

int		ft_reading(t_all *all)
{
	char	buff[BUFF_SIZE];
	int		ret;
	int		check;
	char	*tmp;

	tmp = NULL;
	check = 0;
	all->str = ft_strnew(0);
	while ((ret = read(0, buff, BUFF_SIZE - 1)) > 0)
	{
		buff[ret] = '\0';
		check++;
		tmp = all->str;
		if (!(all->str = ft_strjoin(all->str, buff)))
			return (-1);
		if (tmp != NULL)
			free(tmp);
	}
	if (!(all->map = ft_strsplit_lem(all->str, '\n')))
		return (-1);
	if (ret < 0 || check == 0)
		return (-1);
	return (0);
}

int		ft_check_arg(t_algo *algo, const char **argv, int argc)
{
	int		i;

	i = 1;
	if (argc > 4)
		ft_stop();
	while (i < argc)
	{
		if (ft_strlen(argv[i]) != 2)
			ft_stop();
		else
		{
			if (ft_strcmp("-c", argv[i]) == 0)
				algo->flag += 2;
			else if (ft_strcmp("-l", argv[i]) == 0)
				algo->flag += 1;
			else if (ft_strcmp("-v", argv[i]) == 0)
				algo->flag = 42;
			else
				ft_stop();
		}
		i++;
	}
	return (0);
}

int		main(int argc, const char **argv)
{
	t_room	*room;
	t_all	all;
	t_algo	algo;
	int		i;

	algo.flag = 0;
	if (argc != 1)
		ft_check_arg(&algo, argv, argc);
	if (ft_reading(&all) == -1)
		return (ft_parser_error("Reading failed\n", 0, &all, NULL));
	if ((i = ft_nbrfourmis(&all, &algo)) == -1)
		return (ft_parser_error("Invalid ant number\n", 0, &all, NULL));
	if (ft_nbr_room(&all) == -1)
		return (ft_parser_error("Not enought rooms\n", 0, &all, NULL));
	if (!(room = (t_room *)malloc(sizeof(t_room) * (all.room + 1))))
		return (ft_parser_error("Malloc failed\n", 0, &all, NULL));
	if ((i = ft_parser(&all, room, i, 0)) == -1)
		return (-1);
	if (ft_check_link(&all, room, i) == -1)
		return (-1);
	ft_verif_doublons(room, &all, &algo);
	ft_call_power(room, &algo, &all);
	return (0);
}
