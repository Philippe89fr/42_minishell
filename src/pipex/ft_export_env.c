/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:17:39 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/03 13:07:20 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	liberator(char **s, int k)
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

char	**ft_copy_env_export(char **env, char *new_str)
{
	char	**copy;
	int		i;

	copy = (char **)malloc((ft_strlen2((const char **)env) + 2)
			* sizeof(char *));
	if (!copy)
		return (malloc_fail(), NULL);
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
	copy[i] = ft_strdup(new_str);
	if (!copy[i])
		return (malloc_fail(), NULL);
	i++;
	copy[i] = 0;
	ft_liberator_max(env);
	return (copy);
}

void	ft_change_env_variable(t_pipex *pipex, char *str, int j)
{
	free(pipex->env[j]);
	pipex->env[j] = ft_strdup(str);
	if (!pipex->env[j])
		return (malloc_fail());
}

void	ft_advanced_sort_string_tab(char **tab, int (*cmp)(char *, char *))
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = i + 1;
	while (tab[i])
	{
		while (tab[j])
		{
			if (cmp(tab[i], tab[j]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
		j = i + 1;
	}
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}
