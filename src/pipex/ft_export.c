/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:17:39 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/03 13:08:26 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_go(t_pipex *pipex)
{
	int		i;
	char	**copy_env;

	i = 0;
	copy_env = ft_strdup_table(pipex->env);
	if (!copy_env)
	{
		pipex->status = 1;
		pipex->status_check = 1;
		return (malloc_fail(), 1);
	}
	ft_advanced_sort_string_tab(copy_env, ft_strcmp);
	while (copy_env[i])
	{
		ft_printf("export %s\n", copy_env[i]);
		i++;
	}
	ft_liberator_max(copy_env);
	pipex->status = 0;
	pipex->status_check = 1;
	return (0);
}

int	ft_export2(t_cmd *lst_cmd, int i, int k, int indice)
{
	if (!ft_isalpha(lst_cmd->full_cmd[k][0])
		&& lst_cmd->full_cmd[k][0] != '_')
	{
		export_fail(lst_cmd->full_cmd[k]);
		return (1);
	}
	if (!ft_isalnum(lst_cmd->full_cmd[k][i])
		&& lst_cmd->full_cmd[k][i] != '_' && indice < 0)
	{
		export_fail(lst_cmd->full_cmd[k]);
		return (1);
	}
	return (0);
}

int	ft_petite_help(t_cmd *lst_cmd, t_pipex *pipex)
{
	if (!lst_cmd->next_arg || lst_cmd->next_arg_type != ARG)
	{
		ft_export_go(pipex);
		return (1);
	}
	return (0);
}

void	ft_export(t_cmd *lst_cmd, t_pipex *pipex, int j, int i)
{
	int (k) = 1;
	int (indice) = -1;
	ft_petite_help(lst_cmd, pipex);
	while (lst_cmd->full_cmd[k])
	{
		indice = ft_indice(indice, &i, &j);
		while (pipex->env[j] && ft_strncmp(pipex->env[j], lst_cmd->full_cmd[k],
				i + 1) != 0 && indice < 0 && indice > -3)
		{
			indice = ft_first_while(&i, k, indice, lst_cmd);
			if (ft_strncmp(pipex->env[j], lst_cmd->full_cmd[k], i) == 0
				&& !lst_cmd->full_cmd[k][i + 1])
				indice = 0;
			else if (ft_strncmp(pipex->env[j], lst_cmd->full_cmd[k], i) == 0
				&& !pipex->env[j][i])
				indice = petit_a_petit_fait_son_nid(&j);
			j++;
		}
		if (indice < 0)
			ft_export_petite_la(pipex, lst_cmd, k, j);
		k++;
	}
	ft_petite_help2(indice, pipex);
}
