#include "lem_in.h"

int		ft_nbr_room(t_all *all)
{
	int		i;

	i = 0;
	all->room = 0;
	while (all->map[i])
	{
		if (nbr_space(all->map[i], ' ') == 2)
			all->room++;
		i++;
	}
	return (0);
}

int		ft_nbrfourmis(t_all *all)
{
	int	i;

	i = 0;
	while (all->map[i][0] == '#')
		i++;
	all->fourmis = ft_atoi(all->map[i]);
	if (all->fourmis <= 0)
		return (-1);
	return(0);
}

int		ft_reading(t_all *all)
{
	char	*str;
	char	buff[BUFF_SIZE];
	int		ret;

	str = ft_strnew(0);
	while ((ret = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		str = ft_strjoin(str, buff);
	}
	all->map = ft_strsplit(str, '\n');
	return (0);
}

int main(void)
{
	t_room	*room;
	t_all	all;
	int		i;

	ft_reading(&all);
	ft_nbrfourmis(&all);
	ft_nbr_room(&all);
	if(!(room = (t_room*)malloc(sizeof(t_room) * (all.room + 1))))
		return(0);
	i = ft_parser(&all, room);
	printf("%d\n", i);
	if (ft_check_link(&all, room, i) == -1)
		printf("NOP\n");
	return 0;
}
