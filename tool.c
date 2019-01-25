#include "lem_in.h"

t_room ft_fill_name(char *str, t_room room)
{
	int len;

	len = 0;
	while (str[len] != ' ')
		len++;
	room.name = ft_strndup(str, len);
	room.links = 0;
	room.index = ft_strnew(0);
	return (room);
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

int		ft_verif_link(t_room *room, char *str, t_all *all)
{
	char	*name;
	int		len;
	int		index;

	len = 0;
	index = 0;
	while (str[len] != '-' && str[len])
		len++;
	name = ft_strndup(str, len);
	while (ft_strcmp(name, room[index].name) != 0 && index < all->room - 1)
		index++;
	if (ft_strcmp(name, room[index].name) != 0)
		return (-1);
	free(name);
	return (index);
}

int		ft_verif_link2(t_room *room, char *str, t_all *all, int inlink)
{
	char	*name;
	int		len;
	int		index;

	len = 0;
	index = 0;
	while (str[len] != '-' && str[len])
		len++;
	name = ft_strdup(&str[len + 1]);
	while (ft_strcmp(name, room[index].name) != 0 && index < all->room)
		index++;
	if (ft_strcmp(name, room[index].name) != 0)
		return (-1);
	if (inlink == index)
		return (-1);
	room[index].links += 1;
	room[inlink].links += 1;
	room[index].index = ft_strjoin(room[index].index, ft_itoa(inlink));
	room[index].index = ft_strjoin(room[index].index, " ");
	room[inlink].index = ft_strjoin(room[inlink].index, ft_itoa(index));
	room[inlink].index = ft_strjoin(room[inlink].index, " ");
	return (index);
}
