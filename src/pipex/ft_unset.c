/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:24:08 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/03 11:38:34 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*malloc protect*/
char	**ft_copy_env_unset(char **env, int j)
{
	char	**copy;
	int		i;
	int		t;

	copy = (char **)malloc((ft_strlen2((const char **)env)) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = ((t = 0));
	while (env[i + t])
	{
		if (i + t != j)
		{
			copy[i] = ft_strdup(env[i + t]);
			if (!copy[i])
			{
				liberator(env, i);
				return (NULL);
			}
			i++;
		}
		if (i == j)
			t = 1;
	}
	copy[i] = 0;
	return (ft_liberator_max(env), copy);
}

int	ft_not_unset(t_cmd *lst_cmd, t_pipex *pipex)
{
	if (!lst_cmd->full_cmd[1])
	{
		pipex->status = 0;
		pipex->status_check = 1;
		return (1);
	}
	return (0);
}

int	get_j_unset(t_cmd *lst_cmd, t_pipex *pipex, int k, int i)
{
	int	j;

	j = 0;
	if (!lst_cmd->full_cmd[k][i])
	{
		while (pipex->env[j] && ft_strncmp(pipex->env[j],
				lst_cmd->full_cmd[k], i + 1) != 0)
			j++;
	}
	if (!pipex->env[j])
	{
		j = 0;
		while (pipex->env[j] && ft_strncmp(pipex->env[j],
				lst_cmd->full_cmd[k], i) != 0)
			j++;
	}
	return (j);
}

void	ft_unset(t_cmd *lst_cmd, t_pipex *pipex)
{
	int (i) = 0;
	int (j) = 0;
	int (k) = 1;
	if (ft_not_unset(lst_cmd, pipex))
		return ;
	while (lst_cmd->full_cmd[k])
	{
		while (lst_cmd->full_cmd[k][i] && lst_cmd->full_cmd[k][i] != '=')
			i++;
		j = get_j_unset(lst_cmd, pipex, k, i);
		if (pipex->env[j])
			pipex->env = ft_copy_env_unset(pipex->env, j);
		k++;
		i = 0;
		j = 0;
	}
	pipex->status = 0;
	pipex->status_check = 1;
}
