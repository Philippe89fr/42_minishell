/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:05:39 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/07 11:34:54 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd1(t_pipex *pipex)
{
	char	*home_path;

	home_path = ft_home_path(pipex->env, "HOME=");
	if (!home_path)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return ;
	}
	chdir(home_path);
	pipex->status = 0;
	pipex->status_check = 1;
	update_pwd(pipex);
	free(home_path);
}

void	ft_cd2(t_pipex *pipex)
{
	char	*home_path;

	home_path = ft_get_home_path(pipex->env);
	if (!home_path)
	{
		ft_printf("minishell : cd: HOME not set\n");
		return ;
	}
	chdir(home_path);
	pipex->status = 0;
	pipex->status_check = 1;
	update_pwd(pipex);
	free(home_path);
}

void	ft_cd3(t_pipex *pipex)
{
	char	*home_path;

	home_path = ft_home_path(pipex->env, "OLDPWD=");
	if (!home_path)
	{
		ft_printf("minishell : cd: OLDPWD not set\n");
		pipex->status = 1;
		pipex->status_check = 1;
		return ;
	}
	chdir(home_path);
	pipex->status = 0;
	pipex->status_check = 1;
	ft_printf("%s\n", home_path);
	update_pwd(pipex);
	free(home_path);
}

void	ft_cd4(t_pipex *pipex)
{
	pipex->status = 0;
	pipex->status_check = 1;
	update_pwd(pipex);
}

void	ft_cd5(t_pipex *pipex, t_cmd *lst_cmd)
{
	ft_printf("minishell : %s: No such file or directory\n",
		lst_cmd->full_cmd[1]);
	pipex->status = 1;
	pipex->status_check = 1;
}
