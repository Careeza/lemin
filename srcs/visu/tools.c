/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbecerri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 23:19:49 by fbecerri          #+#    #+#             */
/*   Updated: 2019/02/20 22:50:08 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int			nbr_space(char *str, char c)
{
	int i;
	int space;

	i = 0;
	space = 0;
	if (str[0] == '#')
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			space++;
		i++;
	}
	return (space);
}

int			ft_nbr_room(t_data *data)
{
	int i;

	i = 0;
	while (data->map[i])
	{
		if (nbr_space(data->map[i], '-') == 1)
			break ;
		if (nbr_space(data->map[i], ' ') == 2)
			data->room++;
		i++;
	}
	return (0);
}

int			ft_index_for_links(char *str, t_room *room, int nbrroom, int len)
{
	int		a;
	int		lenstr;

	a = 0;
	while (a < nbrroom)
	{
		lenstr = ft_strlen(room[a].name);
		if (len == lenstr)
			if (ft_strncmp(room[a].name, str, lenstr) == 0)
			{
				if (str != NULL)
					free(str);
				return (a);
			}
		a++;
	}
	if (str != NULL)
		free(str);
	return (-1);
}

int			ft_index_for(char *str, t_room *room, int nbrroom)
{
	int		a;
	int		len;
	int		lenstr;

	lenstr = ft_strlen(str);
	len = 0;
	a = 0;
	while (a < nbrroom)
	{
		len = ft_strlen(room[a].name);
		if (len == lenstr)
			if (ft_strncmp(room[a].name, str, lenstr) == 0)
			{
				if (str != NULL)
					free(str);
				return (a);
			}
		a++;
	}
	if (str != NULL)
		free(str);
	return (-1);
}

int			ft_len_to_c(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
