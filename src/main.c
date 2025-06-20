/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:18:34 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/13 15:17:58 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_var;

void	close_inherited_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

char	*get_correct_line(t_pipex *pipex, char *line)
{
	char	*line1;

	if (ctrl_c_here_doc(pipex))
		return (free(line), NULL);
	line1 = parsing_pre_token(line, pipex);
	if (!line1)
		return (free(line), malloc_fail(), NULL);
	return (free(line), line1);
}

void	exec_correct_line(t_pipex *pipex, char *line)
{
	int		status;
	pid_t	pid;

	if (line && !init_pipex_struc_cmd(pipex, line))
	{
		pid = fork();
		if (pid == 0)
			open_here_doc(pipex);
		if (pid > 0)
		{
			g_var = 3;
			waitpid(pid, &status, 0);
			if (g_var == 3)
				g_var = 0;
			if (!g_var)
			{
				cmd_fail(pipex);
				open_files(pipex);
				set_signal_action1();
				call_pipex(pipex);
				set_signal_action();
			}
			liberator_god(pipex, 0);
		}
	}
}

void	boucle_principale(t_pipex *pipex)
{
	char	*line;
	char	*intro;
	char	*line1;

	intro = "[MINISHELL] :";
	while (1)
	{
		line = readline(intro);
		g_var = 0;
		if (!line)
		{
			ft_printf("exit\n");
			return (liberator_god(pipex, 1), exit(0));
		}
		add_history(line);
		line = parsing_champetre(line, pipex);
		if (line)
		{
			line1 = get_correct_line(pipex, line);
			exec_correct_line(pipex, line1);
		}
	}
}

/*init_pipex_struc >> initialise tout sauf les tokens */
int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	close_inherited_fds();
	pipex.exec_count = 0;
	init_pipex_struc(&pipex, env, ac, av);
	set_signal_action();
	boucle_principale(&pipex);
	liberator_god(&pipex, 1);
	return (0);
}
