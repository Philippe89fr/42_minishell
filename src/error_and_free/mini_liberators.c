/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_liberators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:36:17 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/03 10:10:43 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mini_liberator(char *next_line, char *buf)
{
	free(next_line);
	free(buf);
}

void	mini_liberator_exit(char *next_line, char *buf)
{
	free(next_line);
	free(buf);
	exit(130);
}
