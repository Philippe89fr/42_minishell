/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipex_struc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:05:19 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/25 14:38:37 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_first_path(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	return (pwd);
}

/*Initialise la structure hors commande qui se feront
dans la boucle d ouverture du prompt quand Readline est appele*/
int	init_pipex_struc(t_pipex *pipex, char **env, int ac, char **av)
{
	pre_init(pipex);
	pipex->variables_parsing = NULL;
	pipex->exec_count = 0;
	pipex->env_malloc = 0;
	pipex->variables_parsing_malloc = 0;
	pipex->compteur_characters = 0;
	pipex->env_check = 1;
	if (!env[0])
		pipex->env = create_env();
	else
		pipex->env = ft_strdup_table2(env);
	if (!pipex->env)
		return (1);
	pipex->env_malloc = 1;
	pipex->lst_cmd = NULL;
	ac = ac + 0;
	av = NULL;
	pipex->first_path = get_first_path();
	pipex->first_path_malloc = 1;
	return (0);
}

/*Suite de l initialisation quand le prompt s ouvre.
Necessaire car on attend la lecture de Readline*/
int	init_pipex_struc_cmd(t_pipex *pipex, char *line)
{
	if (!line)
		return (1);
	if (ft_strncmp(line, "", 1) == 0)
		return (free(line), 1);
	pipex->path_env = NULL;
	if (path_check(pipex->env))
	{
		pipex->path_env = ft_path(pipex->env);
		if (!pipex->path_env)
			return (free(line), 1);
		pipex->path_env_malloc = 1;
	}
	pipex->lst_token = lst_token_maker(line, pipex);
	pipex->lst_token_malloc = 1;
	pipex->lst_cmd = lst_cmd_maker(pipex->lst_token);
	pipex->lst_cmd_malloc = 1;
	pipex->cmd_size = ft_lstsize_cmd(pipex->lst_cmd);
	pipex->pipefd = malloc(2 * sizeof(int));
	pipex->pipefd_malloc = 1;
	pipex->pid = (pid_t *)malloc((pipex->cmd_size) * sizeof(pid_t));
	pipex->pid_malloc = 1;
	if (!pipex->lst_token || !pipex->lst_cmd || !pipex->pipefd || !pipex->pid)
		return (malloc_fail(), liberator_god(pipex, 0), 1);
	return (0);
}
/*
void	ft_printf_pipex(t_pipex *pipex)
{
	int	i;

	ft_print_lst_cmd(pipex->lst_cmd);
	ft_print_lst_token(pipex->lst_token);
	ft_printf("cmd_size: %d\nStatus check: %d\nStatus:%d\n", pipex->cmd_size,
		pipex->status_check, pipex->status);
	i = 0;
	while (pipex->path_env[i])
	{
		ft_printf("%s:", pipex->path_env[i]);
		i++;
	}
	ft_printf("\n\n");
}*/
