/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:24:03 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/04 13:20:16 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_infiles_bis(t_cmd *lst_cmd, t_token *lst_token, t_pipex *pipex)
{
	int	fd;

	fd = open(lst_token->str, O_RDONLY);
	if (fd == -1)
	{
		pipex->status = 1;
		pipex->status_check = 1;
		perm_or_file_missing(lst_token->str);
		lst_cmd->fail_infile = 1;
		return (1);
	}
	close(fd);
	return (0);
}

int	open_append_bis(t_cmd *lst_cmd, t_token *lst_token, t_pipex *pipex)
{
	int	fd;

	fd = open(lst_token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		pipex->status = 1;
		pipex->status_check = 1;
		perm_or_file_missing(lst_token->str);
		lst_cmd->fail_outfile = 1;
		return (1);
	}
	close(fd);
	return (0);
}

int	open_trunc_bis(t_cmd *lst_cmd, t_token *lst_token, t_pipex *pipex)
{
	int	fd;

	fd = open(lst_token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		pipex->status = 1;
		pipex->status_check = 1;
		perm_or_file_missing(lst_token->str);
		lst_cmd->fail_outfile = 1;
		return (1);
	}
	close(fd);
	return (0);
}

int	open_files2(t_pipex *pipex, t_token *current, t_cmd *current_cmd, int verif)
{
	if (current->type == INPUT && current->next && verif == 0
		&& open_infiles_bis(current_cmd, current->next, pipex))
		return (1);
	else if (current->type == OUTPUT_APPEND && current->next && verif == 0
		&& open_append_bis(current_cmd, current->next, pipex))
		return (1);
	else if (current->type == OUTPUT_TRUNC && current->next && verif == 0
		&& open_trunc_bis(current_cmd, current->next, pipex))
		return (1);
	return (verif);
}

void	open_files(t_pipex *pipex)
{
	t_token	*current;
	t_cmd	*current_cmd;
	int		verif;

	verif = 0;
	current = pipex->lst_token;
	current_cmd = pipex->lst_cmd;
	while (current)
	{
		while (current && current->type != PIPE)
		{
			verif = open_files2(pipex, current, current_cmd, verif);
			current = current->next;
		}
		verif = 0;
		if (current && current->type == PIPE)
		{
			current = current->next;
			current_cmd = current_cmd->next;
		}
	}
}
