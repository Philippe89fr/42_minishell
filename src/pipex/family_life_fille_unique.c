/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_life_fille_unique.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:55:58 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/03 11:18:54 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_commande_unique_outfile(t_pipex *pipex)
{
	int	fd;

	if (pipex->lst_cmd->outfile)
	{
		if (pipex->lst_cmd->outfile_append_check == 0)
		{
			fd = open(pipex->lst_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (fd == -1)
				exit(1);
			else if (dup2(fd, 1) == -1)
				return (dup2_fail(), close(fd), exit(1));
			close(fd);
		}
		else
		{
			fd = open(pipex->lst_cmd->outfile, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (fd == -1)
				exit(1);
			else if (dup2(fd, 1) == -1)
				return (dup2_fail(), close(fd), exit(1));
			close(fd);
		}
	}
}

/*gestion erreur*/
int	exec_commande_unique(t_pipex *pipex)
{
	int	fd;

	if (pipex->lst_cmd->infile)
	{
		fd = open(pipex->lst_cmd->infile, O_RDONLY);
		if (fd == -1)
			exit(1);
		else if (dup2(fd, 0) == -1)
			return (dup2_fail(), close(fd), exit(1), 1);
		close(fd);
	}
	exec_commande_unique_outfile(pipex);
	ft_builtins(pipex->lst_cmd, pipex, 'f');
	if (!pipex->lst_cmd->cmd)
	{
		liberator_god(pipex, 0);
		exit(0);
	}
	else if (pipex->lst_cmd->cmd)
		execve(pipex->lst_cmd->cmd, pipex->lst_cmd->full_cmd, NULL);
	liberator_god(pipex, 0);
	exit(127);
}

int	call_pipex_cmd_unique(t_pipex *pipex)
{
	int	status;

	status = 0;
	if (pipex->lst_cmd->fail_outfile)
		return (0);
	pipex->pid[pipex->exec_count] = fork();
	if (pipex->pid[pipex->exec_count] == -1)
		return (pipe_fail(), 1);
	if (pipex->pid[pipex->exec_count] == 0)
		exec_commande_unique(pipex);
	ft_builtins(pipex->lst_cmd, pipex, 'u');
	if (waitpid(pipex->pid[pipex->exec_count], &status, 0) == -1)
	{
		pipex->status = 130;
		return (1);
	}
	if (pipex->status_check == 0)
		pipex->status = status / 256;
	pipex->status_check = 0;
	return (0);
}
