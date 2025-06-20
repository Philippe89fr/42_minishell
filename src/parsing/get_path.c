/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 09:59:59 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/23 14:56:07 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*rajoute le backlash au debut des paths eg. /local/bin VS /local/bin/ */
char	**ft_add_backslash(char **path)
{
	int		i;
	int		k;
	char	**new_path;

	k = 0;
	i = ft_strlen2((const char **)path);
	new_path = malloc((i + 1) * sizeof(char *));
	if (!new_path)
		return (NULL);
	new_path[i] = NULL;
	while (path[k])
	{
		new_path[k] = ft_strjoin(path[k], "/");
		if (!new_path[k])
			return (ft_liberator_max(new_path), NULL);
		k++;
	}
	return (new_path);
}

/*est ce qu on trouve la variable PATH dans l env*/
int	path_check(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (0);
	return (1);
}

/*Va chercher les Paths et les decoupes dans
un tableau^2 pour les rendre utilisable*/
char	**ft_path(char **env)
{
	int		i;
	int		j;
	char	*str;
	char	**path;
	char	**new_path;

	i = 0;
	j = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	while (env[i][j])
		j++;
	str = ft_substr(env[i], 5, j - 4);
	if (!str)
		return (malloc_fail(), NULL);
	path = ft_split(str, ':');
	if (!path)
		return (malloc_fail(), free(str), NULL);
	new_path = ft_add_backslash(path);
	if (!new_path)
		return (malloc_fail(), free(str), ft_liberator_max(path), NULL);
	free(str);
	return (ft_liberator_max(path), new_path);
}
