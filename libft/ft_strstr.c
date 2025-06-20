/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:52:27 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/14 11:54:03 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;
	size_t	h;

	h = 0;
	while (little[h])
		h++;
	j = 0;
	i = 0;
	if (h == 0)
		return ((char *)big);
	while (big[j])
	{
		while (big[j + i] == little[i] && little[i] && (j + i) < h)
			i++;
		if (i == h)
			return ((char *)&big[j]);
		i = 0;
		j++;
	}
	return (NULL);
}
