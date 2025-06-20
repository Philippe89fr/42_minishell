/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:44:35 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/13 14:44:17 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int		g_var;

/*dup2(fd, 0) --> on prend l'infile comme entree s'il existe vraiment*/
/*besoin de gerer les acces pour le message d'erreur (access)*/
int	open_infile(t_pipex *pipex, t_cmd *lst_cmd)
{
	int	fd;

	fd = open(lst_cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		close(pipex->pipefd[1]);
		exit(EXIT_FAILURE);
	}
	else if (dup2(fd, 0) == -1)
		return (perror(strerror(errno)), close(pipex->pipefd[1]), close(fd));
	close(fd);
	return (1);
}

/*dup2(fd, 1) --> on prend l'oufile comme sorti s'il y en as un*/
/*besoin de gerer les acces pour le message d'erreur (access)*/
/*gerer si c'est >>*/
int	open_outfile(t_pipex *pipex, t_cmd *lst_cmd)
{
	int	fd;

	if (lst_cmd->outfile_append_check == 0)
	{
		fd = open(lst_cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (close(pipex->pipefd[1]), exit(EXIT_FAILURE), 1);
		else if (dup2(fd, 1) == -1)
			return (dup2_fail(), close(pipex->pipefd[1]), close(fd));
	}
	else
	{
		fd = open(lst_cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			close(pipex->pipefd[1]);
			exit(EXIT_FAILURE);
		}
		else if (dup2(fd, 1) == -1)
			return (dup2_fail(), close(pipex->pipefd[1]), close(fd));
	}
	close(fd);
	return (1);
}

/*1) On fait une boucle qui va suivre chaque commande
2) On ouvre le pipe entre les deux commandes
3) On fait un fork pour creer un processus fille
4) On va dans fille si fork = 0 sinon dans papa
*/
int	call_pipex(t_pipex *pipex)
{
	g_var = 4;
	t_cmd *(current) = pipex->lst_cmd;
	if (pipex->cmd_size == 1)
		return (call_pipex_cmd_unique(pipex));
	pipex->saved_stdin = dup(0);
	pipex->saved_stdout = dup(1);
	while (current)
	{
		if (pipe(pipex->pipefd) == -1)
			return (pipe_fail(), close(pipex->saved_stdin),
				close(pipex->saved_stdout), 1);
		pipex->pid[pipex->exec_count] = fork();
		if (pipex->pid[pipex->exec_count] == -1)
			return (fork_fail(), close(pipex->saved_stdin),
				close(pipex->saved_stdout), 1);
		if (pipex->pid[pipex->exec_count] == 0)
			life_fille(pipex, current);
		else if (pipex->pid[pipex->exec_count] > 0)
			life_papa(pipex, current);
		pipex->exec_count++;
		current = current->next;
	}
	dup2(pipex->saved_stdin, 0);
	dup2(pipex->saved_stdout, 1);
	return (close(pipex->saved_stdin), close(pipex->saved_stdout), 1);
}
