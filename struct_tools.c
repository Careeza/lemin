/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:12:01 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/06 12:44:13 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_fill_name(char *str, t_room *room, int fourmis, int nbroom)
{
	int len;

	(void)nbroom;
	len = 0;
	while (str[len] != ' ')
		len++;
	if (nbr_space(str, ' ') != 2)
		return (-1);
	if (ft_str_is_digit((str + len), '\0') == -1)
		return (-1);
	room->name = ft_strndup(str, len);
	room->links = 0;
	room->slot = 0;
	room->power = INT_MAX;
	room->previous = -42;
	room->pass = 0;
	if (room->start_end == 1)
		room->slot = fourmis;
	room->index = ft_strnew(0);
	return (0);
}

void	print_dbint(int *tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("-- %d -- ", tab[i]);
		i++;
	}
	printf("\n");
}

void	ft_print_ant(t_fourmi *room, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		printf("ROOM[%d]\n", i);
		printf("Name =%d\n", room[i].name);
		printf("index = %d\n", room[i].curr);
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
	printf("liaisons =%s\n", room[i].index);
	printf("\n");
}
void	ft_print_struct(t_room *room, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		printf("ROOM[%d]\n", i);
		printf("Name =%s\n", room[i].name);
		printf("Start_end =%d\n", room[i].start_end);
		printf("Links =%d\n", room[i].links);
		printf("liaisons =%s\n", room[i].index);
		printf("power =%ld\n", room[i].power);
		printf("pass =%ld\n", room[i].pass);
		printf("\n");
		i++;
	}
}

int		ft_index_for(char *str, t_room *room, int nbrroom, int lenstr)
{
	int		a;
	int		z;

	a = 0;
	z = nbrroom;
	while (a > z)
	{
		if (ft_strncmp(room[a].name, str, lenstr) == 0)
			return(a);
		if (ft_strncmp(room[z].name, str, lenstr) == 0)
			return (z);
		a++;
		z--;
	}
	return (-1);
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
		return (ft_parser_error("ft_strdup failed\n"));
	while ((index < all->room) && (ft_strcmp(name, room[index].name) != 0))
		index++;
	if (index == all->room)
		return (ft_parser_error("Linked room doesn't exist\n"));
	free(name);
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
		return (ft_parser_error("ft_strdup failed\n"));
	while ((indexb < (all->room)) && (ft_strcmp(name, room[indexb].name) != 0))
		indexb++;
	if (indexb == all->room)
		return (ft_parser_error("Linked room doesn't exist\n"));
	if (indexa == indexb)
		return(ft_light_error("A room is linked to herself\n"));
	if (ft_verif_tube(indexa, indexb, room) == -1)
		return (ft_light_error("Tube already exists\n"));
	room[indexb].links += 1;
	room[indexa].links += 1;
//	printf("indexa = %d, indexb = %d\n", indexa, indexb);
	if ((!(room[indexb].index = ft_strjoin(room[indexb].index, ft_itoa(indexa))))
			|| (!(room[indexb].index = ft_strjoin(room[indexb].index, " "))))
		return (ft_parser_error("Ouspy join crashed\n"));
	if ((!(room[indexa].index = ft_strjoin(room[indexa].index, ft_itoa(indexb))))
			|| (!(room[indexa].index = ft_strjoin(room[indexa].index, " "))))
		return (ft_parser_error("Ouspy join crashed\n"));
	return (0);
}
