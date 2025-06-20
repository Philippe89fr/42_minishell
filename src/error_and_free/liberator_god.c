/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liberator_god.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:44:44 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/04 13:17:44 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear_token(t_token **lst)
{
	t_token	*current;
	t_token	*temp;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->str_malloc)
			free(temp->str);
		if (temp->cmd_malloc)
			free(temp->cmd);
		free(temp);
	}
	*lst = NULL;
}

void	ft_lstclear_cmd2(t_cmd *temp)
{
	if (temp->outfile_tab_malloc)
		free(temp->outfile_tab);
	if (temp->outfile_append_check_tab_malloc)
		free(temp->outfile_append_check_tab);
	if (temp->infile_tab_malloc)
		free(temp->infile_tab);
	free(temp);
}

void	ft_lstclear_cmd(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*temp;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->full_cmd_malloc)
			free(temp->full_cmd);
		if (temp->echo_arg_malloc)
			free(temp->echo_arg);
		if (temp->limiters_malloc)
			free(temp->limiters);
		if (temp->infile_malloc)
		{
			unlink(temp->infile);
			free(temp->infile);
		}
		ft_lstclear_cmd2(temp);
	}
	*lst = NULL;
}

void	liberator_small_god(t_pipex *pipex)
{
	if (pipex->lst_token_malloc)
	{
		ft_lstclear_token(&pipex->lst_token);
		pipex->lst_token_malloc = 0;
	}
	if (pipex->lst_cmd_malloc)
	{
		ft_lstclear_cmd(&pipex->lst_cmd);
		pipex->lst_cmd_malloc = 0;
	}
	if (pipex->pid_malloc)
	{
		free(pipex->pid);
		pipex->pid_malloc = 0;
	}
	if (pipex->pipefd_malloc)
	{
		free(pipex->pipefd);
		pipex->pipefd_malloc = 0;
	}
	if (pipex->path_env_malloc)
	{
		ft_liberator_max(pipex->path_env);
		pipex->path_env_malloc = 0;
	}
}

void	liberator_god(t_pipex *pipex, int sup_all)
{
	liberator_small_god(pipex);
	pipex->compteur_characters = 0;
	if (sup_all)
	{
		if (pipex->env_malloc)
		{
			ft_liberator_max(pipex->env);
			pipex->env_malloc = 0;
		}
		if (pipex->first_path_malloc)
		{
			free(pipex->first_path);
			pipex->first_path_malloc = 0;
		}
		rl_clear_history();
		exit(0);
	}
	pipex->exec_count = 0;
	return ;
}
