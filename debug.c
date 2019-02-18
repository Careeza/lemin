/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 04:06:36 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/18 15:48:55 by fbecerri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_dbint(int *tab, int len, t_room *room)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("%s--", room[tab[i]].name);
		i++;
	}
	printf("\n");
}

void	ft_print_ant(t_special_ant *room, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		printf("ghost = [%d]\n", i);
		printf("len = %d\n", room[i].len);
		printf("path de 0 = %d", room[i].path[0]);
//		print_dbint(room[i].path, room[i].len, room);
		//		printf("index = %d\n", room[i].curr);
		printf("\n");
		i++;
	}
}

void	ft_print_room(t_room *room, int i)
{
	printf("ROOM[%d]\n", i);
	printf("Name =%s\n", room[i].name);
	printf("Start_end =%d\n", room[i].start_end);
	printf("Links =%d\n", room[i].links);
	printf("power =%ld\n", room[i].power);
	if (room[i].previous != -42)
		printf("previous =%s\n", room[room[i].previous].name);
	printf("\n");
}

void	ft_print_struct(t_room *room, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		printf("ROOM[%s]\n", room[i].name);
		printf("Start_end =%d\n", room[i].start_end);
		printf("Links =%d\n", room[i].links);
		printf("power =%ld\n", room[i].power);
		printf("courant =%d\n", room[i].courant);
		if (room[i].previous != -42)
			printf("previous =%s\n", room[room[i].previous].name);
		printf("liens :\n");
		print_dbint(room[i].index, room[i].links, room);
		printf("\n");
		i++;
	}
}

