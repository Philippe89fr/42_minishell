/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_brackets_management.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:01:23 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/31 11:37:31 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*single_quote_management(char *line, int i, int ascii)
{
	char	*line_copy;
	int		j;
	int		t;
	int		end_quote;

	line_copy = (char *)malloc((ft_strlen(line) - 1) * sizeof(char));
	if (!line_copy)
		return (NULL);
	j = 0;
	t = 0;
	end_quote = i + 1 + check_next_quote(line, ascii, i + 1);
	while (line[j + t])
	{
		if (line[j + t] == ascii && j + t >= i && j + t <= end_quote)
			t++;
		else
		{
			line_copy[j] = line[j + t];
			j++;
		}
	}
	line_copy[j] = '\0';
	free(line);
	return (line_copy);
}

char	*parsing_pre_token2(char *line, t_pipex *pipex, int i)
{
	int	j;

	while (line[i])
	{
		if (line[i] == 39 && ((check_next_quote(line, 39, i + 1) != 0)
				|| (line[i + 1] && line[i + 1] == 39)))
		{
			j = check_next_quote(line, 39, i + 1);
			line = single_quote_management(line, i, 39);
			i += j;
		}
		else if (line[i] == 34 && (check_next_quote(line, 34, i + 1) != 0
				|| (line[i + 1] && line[i + 1] == 34)))
		{
			line = double_quote_management(line, i, 34, pipex);
			i += pipex->compteur_characters;
		}
		else
			i++;
		if (!line)
			return (NULL);
	}
	return (line);
}

char	*parsing_pre_token(char *line, t_pipex *pipex)
{
	if (line[0] == '\0')
		return (ft_strdup(line));
	line = ft_parsing_dollars_without_brackets(line, pipex);
	if (!line)
		return (NULL);
	line = replace_status(line, pipex);
	if (!line)
		return (NULL);
	line = parsing_pre_token2(line, pipex, 0);
	if (!line)
		return (NULL);
	return (line);
}
