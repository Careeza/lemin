/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:05:25 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/20 22:06:43 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

char	*ft_reading(void)
{
	char	buff[BUFF_SIZE];
	int		ret;
	int		check;
	char	*str;
	char	*tmp;

	check = 0;
	str = ft_strnew(0);
	while ((ret = read(0, buff, BUFF_SIZE - 1)) > 0)
	{
		tmp = str;
		buff[ret] = '\0';
		check++;
		if (!(str = ft_strjoin(str, buff)))
			return (NULL);
		if (tmp != NULL)
			free(tmp);
	}
	if (ret < 0 || check == 0)
		return (NULL);
	return (str);
}

char	**ft_read(void)
{
	char	*str;
	char	**map;

	if (!(str = ft_reading()))
		return (NULL);
	if (!(map = ft_strsplit(str, '\n')))
		return (NULL);
	if (str != NULL)
		free(str);
	return (map);
}

void	ft_circle(int x, int y, t_data *data, int color)
{
	int x2;
	int y2;

	y2 = -data->rayon;
	while (y2 < data->rayon)
	{
		x2 = -data->rayon;
		while (x2 < data->rayon)
		{
			if (((x2 / (double)data->rayon) * (x2 / (double)data->rayon)
					+ (y2 / (double)data->rayon)
					* (y2 / (double)data->rayon)) <= 1)
				data->img_ptr2[(y2 + y) * (SCREEN_X) + (x2 + x)] = color;
			x2++;
		}
		y2++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img2, 0, 0);
}

void	ft_init_data(t_data *data)
{
	data->room = 0;
	data->x_extrem = 0;
	data->y_extrem = 0;
	data->time = time(NULL);
	data->oto = 0;
	data->i = 0;
	data->step1 = 0;
	data->xstart = 0;
	data->ystart = 0;
	data->index_start = 0;
	data->index_end = 0;
	data->zm = 0;
	data->zm2 = 0;
	data->xpos[1] = 0;
	data->xpos[0] = 0;
	data->ypos[1] = 0;
	data->ypos[0] = 0;
	data->speed = SPEED;
	data->ticks = CLOCKS_PER_SEC;
	data->antstart = 0;
	data->antend = 0;
	data->use = 1;
}

void	ft_check_visu_txt(t_data *data)
{
	char	buff[10];
	int		i;

	if ((data->fd = open("visu.txt", O_RDWR)) == -1)
		ft_putstr("\nCan't open the file visu.txt .\n");
	read(data->fd, buff, 10);
	close(data->fd);
	if (data->fd == -1)
		exit(0);
	if (ft_strcmp(buff, "#Visu OK\n") != 0)
	{
		ft_putstr("\nInvalid map.\n");
		exit(0);
	}
	else
	{
		i = system("echo "" > visu.txt");
		if (i == 127)
			ft_putstr("\nShell execution failed.\n");
		if (i == -1)
			ft_putstr("\nFork or waitpid error.\n");
		if (i == 127 || i == -1)
			exit(0);
	}
}
