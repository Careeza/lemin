#include "lem_in.h"

int		ft_parser(t_all *all, t_room *room)
{
	int i;
	int	index;

	i = 0;
	index = 0;
//	printf("%d\n", all->room);
	while (index < all->room)
	{
		if (nbr_space(all->map[i], ' ') == 2)
		{
			room[index] = ft_fill_name(all->map[i], room[index]);
			index++;
		}
		else
		{
			if (strcmp("##start", all->map[i]) == 0)
				room[index].start_end = 1;
			if (strcmp("##end", all->map[i]) == 0)
				room[index].start_end = 2;
		}
		i++;
	}
	return (i);
}

int		ft_check_link(t_all *all, t_room *room, int start)
{
	int i;
	int	index;

	i = start;
	while (all->map[i])
	{
		if (nbr_space(all->map[i], '-') == 1 && all->map[i][0] != '#')
		{
			if ((index = ft_verif_link(room, all->map[i], all)) == -1)
				return (-1);
			if ((ft_verif_link2(room, all->map[i], all, index)) == -1)
				return (-1);
		}
		if (all->map[i][0] != '#' && nbr_space(all->map[i], '-') != 1)
			return (-1);
		i++;
	}
	return (0);
}
