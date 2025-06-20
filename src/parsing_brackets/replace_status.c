/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:08:47 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/31 11:54:33 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_in_little_brackets(char *line, int k)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39 && check_next_quote(line, 39, i + 1))
			i += check_next_quote(line, 39, i) + 2;
		else if (line[i] == 39 && line[i + 1] == 39)
			i += 2;
		else if (i == k)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_rejoin_parts(char *first_part, char *error, char *end_part)
{
	char	*line_copy;

	line_copy = ft_strjoin_free(first_part, error);
	if (!line_copy)
		return (free(end_part), NULL);
	line_copy = ft_strjoin_free(line_copy, end_part);
	if (!line_copy)
		return (free(first_part), free(end_part), NULL);
	free(end_part);
	return (line_copy);
}

char	*ft_copy_start(char *s, int len)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_copy_end(char *s, int start)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc((ft_strlen(s) - start + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (s[start + i])
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*replace_status(char *line, t_pipex *pipex)
{
	int		i;
	char	*error;

	i = 0;
	while (line[i] && line[i + 1])
	{
		if (line[i] == '$' && line[i + 1] == '?'
			&& !is_in_little_brackets(line, i))
		{
			error = ft_itoa(pipex->status);
			if (!error)
				return (malloc_fail(), free(line), NULL);
			line = replace_status2(line, error, i);
			if (!line)
				return (free(error), NULL);
			i += ft_strlen(error) - 1;
			free(error);
		}
		i++;
	}
	return (line);
}
