/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_status2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:08:47 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/31 11:56:30 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_status_get_first_part(int i, char *line)
{
	char	*first_part;

	if (i > 0)
		first_part = ft_copy_start(line, i);
	else
	{
		first_part = (char *)malloc(sizeof(char));
		if (!first_part)
			return (malloc_fail(), free(line), NULL);
		first_part[0] = '\0';
	}
	if (!first_part)
		return (malloc_fail(), free(line), NULL);
	return (first_part);
}

char	*replace_status_get_last_part(int i, char *line)
{
	char	*end_part;

	if (line[i + 2])
		end_part = ft_copy_end(line, i + 2);
	else
	{
		end_part = (char *)malloc(sizeof(char));
		if (!end_part)
			return (malloc_fail(), NULL);
		end_part[0] = '\0';
	}
	if (!end_part)
		return (malloc_fail(), NULL);
	return (end_part);
}

char	*replace_status2(char *line, char *error, int i)
{
	char	*first_part;
	char	*end_part;

	first_part = replace_status_get_first_part(i, line);
	if (!first_part)
		return (NULL);
	end_part = replace_status_get_last_part(i, line);
	if (!end_part)
		return (free(first_part), free(line), free(error), NULL);
	free(line);
	line = ft_rejoin_parts(first_part, error, end_part);
	if (!line)
		return (malloc_fail(), NULL);
	return (line);
}
