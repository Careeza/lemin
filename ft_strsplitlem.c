/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitlem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 03:50:31 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/09 03:55:54 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_countwords(char *s, char c)
{
	int	i;
	int	count_words;
	int	is_words;

	i = 0;
	count_words = 0;
	is_words = 0;
	while (s[i])
	{
		if (is_words == 0 && s[i] != c)
		{
			is_words = 1;
			count_words++;
		}
		else if (is_words == 1 && s[i] == c)
			is_words = 0;
		else if (is_words == 0 && s[i] == c)
			count_words++;
		i++;
	}
	return (count_words);
}

static int		ft_len_words(char *s, int c, int k)
{
	int	len;

	len = 0;
	while (s[k] != c && s[k])
	{
		len++;
		k++;
	}
	return (len);
}

static int		ft_cut(char const *s, char c, char **tab, int nbr_words)
{
	int	k;
	int	i;
	int	len;

	k = 0;
	i = 0;
	len = 0;
	while (i < nbr_words)
	{
		if (s[k] == c && s[k] && k > 0)
			k++;
		if (!(tab[i] = ft_strsub_lem((char *)s, k,
						ft_len_words((char *)s, c, k))))
			return (-1);
		if ((len = ft_len_words((char *)s, c, k)) == 0)
		{
			tab[i + 1] = NULL;
			return (0);
		}
		i++;
		k += ft_len_words((char *)s, c, k);
	}
	tab[i] = NULL;
	return (0);
}

char			**ft_strsplit_lem(char const *s, char c)
{
	int		nbr_words;
	char	**tab;

	if (!s)
		return (NULL);
	nbr_words = ft_countwords((char *)s, c);
	if (!(tab = (char**)malloc(sizeof(char *) * (nbr_words + 1))))
		return (NULL);
	ft_cut(s, c, tab, nbr_words);
	return (tab);
}
