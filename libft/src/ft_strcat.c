/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:07:45 by ltanenba          #+#    #+#             */
/*   Updated: 2018/02/26 17:57:53 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char	*tmp;

	tmp = s1;
	while (*tmp)
		tmp++;
	while (*s2)
		*(tmp++) = *(s2++);
	*tmp = '\0';
	return (s1);
}
