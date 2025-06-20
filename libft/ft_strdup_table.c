/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:02:16 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/22 16:11:41 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	liberator(char **s, int k)
{
	int	i;

	i = 0;
	while (i <= k)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_strdup_table(char **env)
{
	char	**copy;
	int		i;

	copy = (char **)malloc((ft_strlen2((const char **)env) + 1)
			* sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			liberator(env, i);
			return (NULL);
		}
		i++;
	}
	copy[i] = 0;
	return (copy);
}
/*
int	main(int argc, char **argv)
{
	char	*s;
	char	*u;

	argc = argc + 0;
	s = ft_strdup(argv[1]);
	u = strdup(argv[1]);
	printf("v%s\nm%s\n", u, s);
	free(u);
	free(s);
	return (0);
}*/
