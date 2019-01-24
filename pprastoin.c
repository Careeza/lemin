int		ft_parser(t_all *all)
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
