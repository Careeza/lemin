/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:53:49 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/23 13:14:38 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dst;
	size_t	i;

	i = 0;
	printf("OK1--\n");
	if (!(dst = (char*)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	printf("OK2\n");
	while (s1[i] && i < n)
	{
		dst[i] = s1[i];
		i++;
	}
	printf("OK3\n");
	dst[i] = '\0';
	printf("OK4\n");
	return (dst);
}


