/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_table2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:02:16 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/30 17:32:08 by prambaud         ###   ########.fr       */
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

char	*get_uid(char **env)
{
	char	*uid;
	char	*uid2;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (ft_strncmp((const char *)env[i], "XDG_RUNTIME_DIR", 15))
		i++;
	while (!ft_isdigit(env[i][j]))
		j++;
	k = j;
	while (ft_isdigit(env[i][j]))
		j++;
	uid = ft_substr(env[i], k, j - k);
	if (!uid)
		return (NULL);
	uid2 = ft_strjoin("UID=", uid);
	if (!uid2)
		return (NULL);
	free(uid);
	return (uid2);
}

char	**ft_strdup_table2(char **env)
{
	char	**copy;
	int		i;

	copy = (char **)malloc((ft_strlen2((const char **)env) + 2)
			* sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
			return (liberator(env, i), NULL);
		i++;
	}
	copy[i] = get_uid(env);
	if (!copy[i])
		return (liberator(env, i), NULL);
	i++;
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
