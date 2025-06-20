/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:35:18 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/04 13:19:38 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_fail(void)
{
	write(2, "Malloc error\n", 13);
	return ;
}

void	creation_fail(void)
{
	write(2, "Cannot create file\n", 19);
	return ;
}

void	pipe_fail(void)
{
	write(2, "Pipe failure\n", 13);
	return ;
}

void	fork_fail(void)
{
	write(2, "Fork failure\n", 13);
	return ;
}

void	perm_or_file_missing(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	if ((access(str, R_OK) == -1) && errno == EACCES)
		write(2, ": Permission denied\n", 20);
	else
		write(2, ": No such file or directory\n", 28);
}
