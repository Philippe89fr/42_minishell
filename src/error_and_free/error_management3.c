/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 15:35:18 by prambaud          #+#    #+#             */
/*   Updated: 2025/01/23 14:31:16 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	waitpid_fail(void)
{
	write(2, "Waitpid fail\n", 13);
	return ;
}

void	permission_fail(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, ": Permission denied\n", 20);
	return ;
}

void	dup2_fail(void)
{
	write(2, "Dup2_failure\n", 13);
	return ;
}
