/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:24:22 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/04 13:02:01 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_verif_tube(int indexa, int indexb, t_room *room)
{
	int	i;
	int	len;
	int	val;

	val = 0;
	i = 0;
	len = 0;
//	printf("Verif de indexa =%d et de indexb =%d\n room[%d].index  =%s\n",indexa, indexb, indexa ,room[indexa].index);
	while (i < room[indexa].links)
	{
		val = ft_atoi((room[indexa].index) + len);
//		printf("%d\n", val);
		len = ft_lennbr(val) + 1;
		if (indexb == val)
			return (-1);
		i++;
	}
	return (0);
}

int		ft_putstr_color_yellow(char *str)
{
	write(1, CSI_YELLOW, (sizeof(CSI_YELLOW) - 1));
	ft_putstr(str);
	write(1, CSI_RESET, sizeof(CSI_RESET) - 1);
	return (0);
}

int		ft_putstr_color_red(char *str)
{
	write(1, CSI_RED, (sizeof(CSI_RED) - 1));
	ft_putstr(str);
	write(1, CSI_RESET, (sizeof(CSI_RESET) - 1));
	return (0);
}

int		ft_light_error(char *str)
{
	ft_putstr_color_yellow("NOTE : ");
	ft_putstr(str);
	return (0);
}

int		ft_parser_error(char *str)
{
	ft_putstr_color_red("ERROR : ");
	ft_putstr(str);
	return (-1);
}


int	nbr_space(char *str, char c)
{
	int	i;
	int	space;

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

int		ft_str_is_digit(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != ' ' && str[i] != '\0')
			return (-1);
		i++;
	}
	return (0);
}
