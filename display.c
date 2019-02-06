/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:20:30 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/06 17:15:15 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	ft_display(int curr_ant, t_special_ant *ghost, t_room *room, t_algo *algo)
{
	if (curr_ant != -1)
	{
		if (ghost[curr_ant].path[(ghost[curr_ant].i) - 1] == algo->index_start)
			write(1, CSI_RED, (sizeof(CSI_RED) - 1));
		else if (ghost[curr_ant].path[ghost[curr_ant].i] == algo->index_end)
			write(1, CSI_BLUE, (sizeof(CSI_BLUE) - 1));
		else
			write(1, CSI_WHITE, (sizeof(CSI_WHITE) - 1));
		ft_putchar('l');
		ft_putnbr(curr_ant + 1);
		ft_putchar('-');
		ft_putstr(room[ghost[curr_ant].path[ghost[curr_ant].i]].name);
		ft_putchar(' ');
		write(1, CSI_RESET, (sizeof(CSI_RESET) - 1));
		/*
		ft_putchar('L');
		ft_putnbr(curr_ant + 1);
		ft_putchar('-');
		ft_putstr(room[curr_ant].name);
		ft_putchar(' ');*/
	}
}

