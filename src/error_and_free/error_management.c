/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:35:18 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/04 14:01:15 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_fail(void)
{
	write(2, "Invalid read\n", 13);
	return ;
}

void	ctrld_actioned(char *limiter)
{
	ft_printf("Warning: here-document delimited");
	ft_printf("by end-of-file (wanted `%s')\n", limiter);
	return ;
}

void	export_fail(char *s)
{
	int	i;

	i = 0;
	write(2, "export: '", 9);
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	write(2, "': not a valid identifier", 25);
	write(2, "\n", 1);
	return ;
}

/*check si tous les files on pu s ouvrir. Si ce n est pas le cas
il ne faut pas envoyer de message cmd_not_found*/
int	open_infiles_checker(t_cmd *lst_cmd)
{
	int	i;
	int	fd;

	i = 0;
	if (!lst_cmd->infile_tab)
		return (0);
	while (lst_cmd->infile_tab[i])
	{
		fd = open(lst_cmd->infile_tab[i], O_RDONLY);
		if (fd == -1)
			return (1);
		close(fd);
		i++;
	}
	return (0);
}

void	cmd_fail(t_pipex *pipex)
{
	int		i;
	t_cmd	*current;

	i = 0;
	current = pipex->lst_cmd;
	while (current)
	{
		if (!open_infiles_checker(current))
		{
			if (!current->cmd && current->cmd_str
				&& ft_strncmp(current->cmd_str, "fake_fdp", 9) != 0)
			{
				write(2, "minishell: ", 11);
				while (current->cmd_str[i])
					write(2, &current->cmd_str[i++], 1);
				write(2, ": command not found\n", 21);
				pipex->status = 127;
				pipex->status_check = 1;
			}
			i = 0;
		}
		current = current->next;
	}
	return ;
}
