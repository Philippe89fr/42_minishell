/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:06:22 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/31 10:26:45 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_builtins(char *str)
{
	if (!ft_strncmp(str, "env", 4) || !ft_strncmp(str, "pwd", 4)
		|| !ft_strncmp(str, "cd", 3) || !ft_strncmp(str, "echo", 5)
		|| !ft_strncmp(str, "exit", 5) || !ft_strncmp(str, "unset", 6)
		|| !ft_strncmp(str, "export", 7))
		return (1);
	return (0);
}

/*On check si str a la forme d une commande en utilisant access().
Deux cas, 1) le chemin est inclu 2) le chemin n est pas inclu et on test
tous les chemins. Si rien ne marche, cmd reste initie a NULL.*/

int	access_check2(t_token *token, t_pipex *pipex)
{
	int		i;
	char	*str_path;

	i = 0;
	while (pipex->path_env && pipex->path_env[i])
	{
		str_path = ft_strjoin(pipex->path_env[i], token->str);
		if (!str_path)
			return (malloc_fail(), 1);
		if (!access(str_path, X_OK))
		{
			token->cmd = str_path;
			token->cmd_malloc = 1;
			return (1);
		}
		free(str_path);
		i++;
	}
	return (0);
}

int	access_check(t_token *token, t_pipex *pipex)
{
	if (token->type != CMD)
		return (0);
	if (ft_is_builtins(token->str))
	{
		token->cmd = ft_strdup(token->str);
		if (!token->cmd)
			return (malloc_fail(), 1);
		token->cmd_malloc = 1;
		return (1);
	}
	if (!access(token->str, X_OK))
	{
		token->cmd = ft_strdup(token->str);
		if (!token->cmd)
			return (malloc_fail(), 1);
		token->cmd_malloc = 1;
		return (1);
	}
	return (access_check2(token, pipex));
}
