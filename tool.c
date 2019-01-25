#include "lem_in.h"

t_room ft_fill_name(char *str, t_room room)
{
	int len;

	len = 0;
	while (str[len] != ' ')
		len++;
	room.name = ft_strndup(str, len);
	room.links = 0;
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
	printf("--DEBUG1--\n");
	while (str[len] != '-' && str[len])
		len++;
	printf("--DEBUG2--%d -- %s\n", len, str);
	name = ft_strndup(str, len);
	printf("--DEBUG3--\n");
	while (ft_strcmp(name, room[index].name) != 0 && index < all->room)
		index++;
	printf("--DEBUG4--\n");
	if (ft_strcmp(name, room[index].name) != 0)
		return (-1);
	printf("DEBUG5\n");
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
//	printf("%s\n", name);
	while (ft_strcmp(name, room[index].name) != 0 && index < all->room)
		index++;
	if (ft_strcmp(name, room[index].name) != 0)
		return (-1);
//	if (room[index].links != 0)
//		free(room[index].index);
//	printf("%d\n", room[index].links);
	room[index].links += 1;
	if (!(room[index].index = (int*)malloc(sizeof(int) * room[index].links)))
		return (-1);
	room[index].index[index - 1] = inlink;

	return (index);
}
