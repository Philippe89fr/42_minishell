/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex_struc2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:05:19 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/04 13:22:29 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pre_init(t_pipex *pipex)
{
	pipex->lst_cmd_malloc = 0;
	pipex->status = 0;
	pipex->status_check = 0;
	pipex->cmd_size = 0;
	pipex->lst_token_malloc = 0;
	pipex->pid_malloc = 0;
	pipex->pipefd_malloc = 0;
	pipex->path_env_malloc = 0;
	pipex->first_path_malloc = 0;
	pipex->first_path = NULL;
}

/*permet d avoir un env quand on fait "export"*/
char	**create_env(void)
{
	char	**env;

	env = (char **)malloc(sizeof(char *) * 5);
	if (!env)
		return (malloc_fail(), NULL);
	env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!env[0])
		return (free(env), malloc_fail(), NULL);
	env[1] = ft_strdup("PATH=/usr/bin/env:/usr/bin:/usr");
	if (!env[1])
		return (free(env[0]), free(env), malloc_fail(), NULL);
	env[2] = ft_strdup("OLDPWD");
	if (!env[2])
		return (free(env[0]), free(env[1]), free(env), malloc_fail(), NULL);
	env[3] = ft_strdup("SHLVL=1");
	if (!env[2])
		return (free(env[0]), free(env[1]), free(env[2]), free(env),
			malloc_fail(), NULL);
	env[4] = 0;
	return (env);
}
