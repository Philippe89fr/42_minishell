/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_fonctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:50:54 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/11 15:21:54 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->env[i])
	{
		if (ft_strchr(pipex->env[i], '='))
			ft_printf("%s\n", pipex->env[i]);
		i++;
	}
}

void	ft_pwd(t_pipex *pipex)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_printf("pwd: error retrieving current directory:\n");
		ft_printf("getcwd: cannot access parent directories:");
		ft_printf(" No such file or directory\n");
		pipex->status = 1;
		pipex->status_check = 1;
		return ;
	}
	ft_printf("%s\n", pwd);
	free(pwd);
}

void	ft_exit(t_pipex *pipex, t_cmd *lst_cmd)
{
	int	i;

	i = ft_strlen2((const char **)lst_cmd->full_cmd);
	if (lst_cmd->full_cmd[1])
	{
		if (i > 2 && ft_isnumber(lst_cmd->full_cmd[1]))
		{
			ft_printf("exit\n");
			ft_printf("Minishell: exit: too many arguments\n");
			return ;
		}
		if (!ft_isnumber(lst_cmd->full_cmd[1]))
		{
			ft_printf("exit\n");
			ft_printf("bash: exit: %s: numeric argument required\n",
				lst_cmd->full_cmd[1]);
			liberator_god(pipex, 1);
			exit(0);
		}
	}
	ft_printf("exit\n");
	liberator_god(pipex, 1);
	exit(0);
}

void	ft_builtins2(t_cmd *lst_cmd, t_pipex *pipex, char c)
{
	if (lst_cmd->echo_arg != NULL && c == 'f')
	{
		ft_echo(lst_cmd);
		liberator_god(pipex, 0);
		exit(0);
	}
	if ((!ft_strncmp(lst_cmd->cmd_str, "env", 4)
			|| !ft_strncmp(lst_cmd->cmd_str, "/bin/env", 9)) && c == 'f')
	{
		if (pipex->env_check)
			ft_env(pipex);
		liberator_god(pipex, 0);
		exit(0);
	}
	if (!ft_strncmp(lst_cmd->cmd_str, "pwd", 4) && c == 'f')
	{
		ft_pwd(pipex);
		liberator_god(pipex, 0);
		exit(0);
	}
}

/*le char c permet de savoir si l'on execute
builtins du processus fille ou du pere*/
void	ft_builtins(t_cmd *lst_cmd, t_pipex *pipex, char c)
{
	if (!ft_strncmp(lst_cmd->cmd_str, "export", 7) && (c == 'p' || c == 'u')
		&& (lst_cmd->next_arg && lst_cmd->next_arg_type == ARG))
		ft_export(lst_cmd, pipex, 0, 0);
	if (!ft_strncmp(lst_cmd->cmd_str, "export", 7) && (c == 'f')
		&& (!lst_cmd->next_arg || lst_cmd->next_arg_type != ARG))
		ft_export(lst_cmd, pipex, 0, 0);
	if (!ft_strncmp(lst_cmd->cmd_str, "unset", 6) && (c == 'p' || c == 'u'))
		ft_unset(lst_cmd, pipex);
	if (!ft_strncmp(lst_cmd->cmd_str, "exit", 5) && (c == 'u'))
		ft_exit(pipex, lst_cmd);
	if (!ft_strncmp(lst_cmd->cmd_str, "cd", 3) && (c == 'u'))
		ft_cd(lst_cmd, pipex);
	ft_builtins2(lst_cmd, pipex, c);
}

// int main(void)
// {
//     char *str = "-nnnn";
//     ft_printf("%d\n", echo_valid_arg(str));
//     return (0);
// }
