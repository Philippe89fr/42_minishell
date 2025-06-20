/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_doc_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:06:38 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/11 15:28:27 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_var;

void	open_here_doc(t_pipex *pipex)
{
	t_cmd	*current;

	g_var = 2;
	current = pipex->lst_cmd;
	while (current)
	{
		get_here_doc_input_console(current, pipex);
		current = current->next;
	}
	g_var = 0;
	exit(0);
}

int	check_files_here(char *file2)
{
	int	fd;

	if (access(file2, F_OK) == -1)
	{
		fd = open(file2, O_CREAT, 0644);
		if (fd == -1)
			return (-1);
		close(fd);
	}
	else if (access(file2, W_OK) == -1)
		return (-1);
	return (1);
}

int	verif_limiter(char *instructions, char **av)
{
	int	i;
	int	j;
	int	t;

	i = 0;
	while (instructions[i])
	{
		if (instructions[i] == '\n' || i == 0)
		{
			j = i;
			t = 0;
			while (instructions[j] && instructions[j] != '\n')
			{
				if (instructions[j] == av[2][t])
					t++;
				if (ft_strlen4(av[2]) == t)
					return (1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

char	*get_here_doc_input(char *limiter, t_pipex *pipex)
{
	char	*instructions;
	char	*current;

	instructions = (char *)malloc(1 * sizeof(char));
	if (!instructions)
		return (malloc_fail(), NULL);
	instructions[0] = '\0';
	current = (char *)malloc(1 * sizeof(char));
	if (!current)
		return (free(instructions), malloc_fail(), NULL);
	current[0] = '\0';
	while (current && (ft_strncmp(limiter, current, ft_strlen(current) - 1) != 0
			|| strlen(limiter) != strlen(current) - 1))
	{
		instructions = ft_strjoin5(instructions, current);
		if (!instructions)
			return (free(current), malloc_fail(), NULL);
		free(current);
		current = get_next_line(1, limiter, pipex);
		if (!current)
			return (free(instructions), NULL);
	}
	free(current);
	return (instructions);
}

int	get_here_doc_input_console(t_cmd *lst_cmd, t_pipex *pipex)
{
	char	*instructions;
	int		fd;
	int		i;

	if (lst_cmd->count_here_doc == 0)
		return (0);
	fd = open(lst_cmd->infile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return (close(fd), creation_fail(), 1);
	close(fd);
	i = get_here_doc_false_input(lst_cmd, pipex);
	if (i == -1)
		return (1);
	instructions = get_here_doc_input(lst_cmd->limiters[i], pipex);
	if (!instructions)
		return (1);
	if (lst_cmd->infile_here_doc == 0)
		return (free(instructions), 0);
	fd = open(lst_cmd->infile, O_WRONLY);
	if (fd == -1)
		return (close(fd), creation_fail(), 1);
	ft_putstr_fd(instructions, fd);
	return (close(fd), free(instructions), 0);
}
