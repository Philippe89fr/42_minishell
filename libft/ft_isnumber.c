/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:54:26 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/30 13:52:04 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_big_number(char *c)
{
	if (ft_strlen(c) == 19)
	{
		if (ft_strncmp(c, "9223372036854775808", 19) >= 0)
			return (0);
	}
	if (ft_strlen(c) == 20)
	{
		if (ft_strncmp(c, "-9223372036854775809", 20) >= 0)
			return (0);
	}
	if (ft_strlen(c) > 19 && c[0] != '-')
		return (0);
	if (ft_strlen(c) > 20)
		return (0);
	return (1);
}

int	ft_isnumber(char *c)
{
	int	i;

	i = 0;
	if (!ft_big_number(c))
		return (0);
	if (c[0] == '-' || c[0] == '+')
		i++;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			return (0);
		i++;
	}
	return (1);
}
