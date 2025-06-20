/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:17:39 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/03 13:12:29 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_petite_help2(int indice, t_pipex *pipex)
{
	pipex->status_check = 1;
	pipex->status = 0;
	if (indice != -1)
		pipex->status = 1;
}

int	ft_indice(int indice, int *i, int *j)
{
	*i = 0;
	*j = 0;
	if (indice == 0 || indice == -3)
		return (-2);
	return (indice);
}

int	ft_first_while(int *i, int k, int indice, t_cmd *lst_cmd)
{
	while (lst_cmd->full_cmd[k][*i] && (*i == 0
			|| lst_cmd->full_cmd[k][*i] != '=') && indice < 0)
	{
		if (ft_export2(lst_cmd, *i, k, indice))
			indice = 0;
		*i = *i + 1;
	}
	return (indice);
}

void	ft_export_petite_la(t_pipex *pipex, t_cmd *lst_cmd, int k, int j)
{
	if (!pipex->env[j])
		pipex->env = ft_copy_env_export(pipex->env, lst_cmd->full_cmd[k]);
	else if (pipex->env[j])
		ft_change_env_variable(pipex, lst_cmd->full_cmd[k], j);
}

int	petit_a_petit_fait_son_nid(int *j)
{
	*j = *j - 1;
	return (-3);
}
