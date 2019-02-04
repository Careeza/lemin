#include <stdlib.h>
#include <stdio.h>

int		ft_lennbr(long long nb)
{
	int		i;

	printf("%lldntm\n", nb);
	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		i = 1;
		nb = -nb;
	}
	while (nb > 0)
	{
		printf("ntm\n");
		nb /= 10;
		i++;
	}
	return (i);
}

int main(int argc, const char *argv[])
{
	int i;

	i = ft_lennbr(atoi(argv[1]));
	printf("%d--%d\n", i, atoi(argv[1]));
	return 0;
}
