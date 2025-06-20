/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family_life_catho.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:55:58 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/03 11:20:39 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*dans la fille on gere les infile / here_doc et outfile.
On execute les builtins si besoin, sauf cd qui doit s executer dans le papa car
les fonctions utilisees doivent regarder l environement du pere*/

int	life_fille_enfance(t_pipex *pipex, t_cmd *lst_cmd)
{
	close(pipex->saved_stdin);
	close(pipex->saved_stdout);
	close(pipex->pipefd[0]);
	if (lst_cmd->fail_outfile)
		return (close(pipex->pipefd[1]), exit(1), 1);
	if (lst_cmd->infile)
		open_infile(pipex, lst_cmd);
	if (lst_cmd->outfile != NULL)
		open_outfile(pipex, lst_cmd);
	else if (pipex->exec_count < pipex->cmd_size - 1 && dup2(pipex->pipefd[1],
			1) == -1)
		return (dup2_fail(), close(pipex->pipefd[1]), exit(1), 1);
	else
	{
		if (dup2(1, 1) == -1)
			return (dup2_fail(), close(pipex->pipefd[1]), exit(1), 1);
	}
	close(pipex->pipefd[1]);
	return (0);
}

int	life_fille(t_pipex *pipex, t_cmd *lst_cmd)
{
	life_fille_enfance(pipex, lst_cmd);
	if (!ft_strncmp(lst_cmd->cmd_str, "cd", 3))
		return (liberator_god(pipex, 0), exit(1), 1);
	ft_builtins(lst_cmd, pipex, 'f');
	if (!lst_cmd->cmd)
	{
		liberator_god(pipex, 0);
		exit(0);
	}
	else if (lst_cmd->cmd)
		execve(lst_cmd->cmd, lst_cmd->full_cmd, NULL);
	liberator_god(pipex, 0);
	exit(127);
}

/*buildints permet de lancer nos propres fonctions
'p' permet de savoir qu on doit lancer celle qui
se lance dans le pere comme cd,pwd etc.
status_check permet de savoir si le status a deja
ete recupere dans la fonction buildins
(dans le cas d unset et export on ne peut pas le recup
via	exit(0) car sinon on quitte le pere)*/
int	life_papa(t_pipex *pipex, t_cmd *lst_cmd)
{
	int (status) = 0;
	int (i) = 0;
	ft_builtins(lst_cmd, pipex, 'p');
	close(pipex->pipefd[1]);
	if (dup2(pipex->pipefd[0], 0) == -1)
		return (dup2_fail(), close(pipex->pipefd[0]), 1);
	close(pipex->pipefd[0]);
	if (pipex->cmd_size - 1 == pipex->exec_count)
	{
		while (i < pipex->cmd_size)
		{
			if (waitpid(pipex->pid[i], &status, 0) == -1)
			{
				pipex->status = 130;
				return (1);
			}
			i++;
		}
	}
	if (pipex->status_check != 0)
		pipex->status = status;
	pipex->status_check = 0;
	return (1);
}
