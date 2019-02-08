/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:08:53 by prastoin          #+#    #+#             */
/*   Updated: 2019/02/08 18:09:55 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*ft_strsub_lem(char const *s, unsigned int start, size_t len)
{
	char		*fresh;
	size_t		i;

	i = 0;
	if (!(s))
		return (NULL);
	if (s[0] == '\0')
		return (NULL);
	if (len == 0)
	{
		if (!(fresh = (char *)malloc(sizeof(char) * (2))))
			return (NULL);
		fresh[0] = '\n';
		fresh[1] = '\0';
		return (fresh);
	}
	if (!(fresh = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		fresh[i] = ((char *)s)[start + i];
		i++;
	}
	fresh[len] = '\0';
	return (fresh);
}
