/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 13:20:30 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 22:33:57 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_putstr_color_yellow(char *str)
{
	write(2, CSI_YELLOW, (sizeof(CSI_YELLOW) - 1));
	ft_putstr_fd(str, 2);
	write(2, CSI_RESET, sizeof(CSI_RESET) - 1);
	return (0);
}

int		ft_putstr_color_red(char *str)
{
	write(2, CSI_RED, (sizeof(CSI_RED) - 1));
	ft_putstr_fd(str, 2);
	write(2, CSI_RESET, (sizeof(CSI_RESET) - 1));
	return (0);
}

void	ft_color(int line, int i)
{
	if (i == 0)
	{
		write(2, CSI_GREEN, (sizeof(CSI_GREEN) - 1));
		ft_putchar_fd('L', 1);
		ft_putnbr_fd(line, 1);
		ft_putstr_fd(" : ", 1);
		write(2, CSI_RESET, (sizeof(CSI_RESET) - 1));
	}
	if (i == 1)
		write(1, CSI_RED, (sizeof(CSI_RED) - 1));
	if (i == 2)
		write(1, CSI_BLUE, (sizeof(CSI_BLUE) - 1));
	if (i == 3)
		write(1, CSI_WHITE, (sizeof(CSI_WHITE) - 1));
}

void	ft_display(int curr_ant, t_special_ant *ghost, t_room *room,
	t_algo *algo)
{
	if (curr_ant != -1)
	{
		if (algo->flag == 2 || algo->flag == 3)
		{
			if (ghost[curr_ant].i == 0)
				ft_color(0, 1);
			else if (ghost[curr_ant].path[ghost[curr_ant].i] == algo->index_end)
				ft_color(0, 2);
			else
				ft_color(0, 3);
		}
		ft_putchar('L');
		ft_putnbr(curr_ant + 1);
		ft_putchar('-');
		ft_putstr(room[ghost[curr_ant].path[ghost[curr_ant].i]].name);
		ft_putchar(' ');
		if (algo->flag == 2 || algo->flag == 3)
			write(1, CSI_RESET, (sizeof(CSI_RESET) - 1));
	}
}
