/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_management3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:08:47 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/04 14:06:30 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	segmenting_line1(char **line_segmentee, char *line, int ascii, int i)
{
	int	j;

	line_segmentee[1] = (char *)malloc(sizeof(char) * (check_next_quote(line,
					ascii, i + 1) + 1));
	if (!line_segmentee[1])
		return (-1);
	j = 0;
	i++;
	while (line[i + j] && line[i + j] != ascii)
	{
		line_segmentee[1][j] = line[i + j];
		j++;
	}
	line_segmentee[1][j] = '\0';
	i = i + j + 1;
	j = 0;
	while (line[i + j])
		j++;
	line_segmentee[2] = (char *)malloc(sizeof(char) * (j + 1));
	if (!line_segmentee[2])
		return (-2);
	return (i);
}

void	segmenting_line2(char **line_segmentee, char *line, int i)
{
	int	j;

	j = 0;
	while (line[i + j])
	{
		line_segmentee[2][j] = line[i + j];
		j++;
	}
	line_segmentee[2][j] = '\0';
}

char	**segmenting_line(char *line, int ascii, int i)
{
	int		j;
	char	**line_segmentee;

	line_segmentee = (char **)malloc(sizeof(char *) * (4));
	if (!line_segmentee)
		return (NULL);
	line_segmentee[3] = 0;
	j = 0;
	line_segmentee[0] = (char *)malloc(sizeof(char) * i + 1);
	if (!line_segmentee[0])
		return (free(line_segmentee), NULL);
	while (j < i)
	{
		line_segmentee[0][j] = line[j];
		j++;
	}
	line_segmentee[0][j] = '\0';
	i = segmenting_line1(line_segmentee, line, ascii, i);
	if (i == -1)
		return (free(line_segmentee[0]), free(line_segmentee), NULL);
	if (i == -2)
		return (free(line_segmentee[0]), free(line_segmentee[1]),
			free(line_segmentee), NULL);
	segmenting_line2(line_segmentee, line, i);
	return (line_segmentee);
}

char	*get_part_without_dollars(char *line, int i)
{
	int		j;
	char	*line_cut;

	j = i;
	while (line[i] && (!line[i + 1] || line[i] != '$'
			|| !char_is_ok(line[i + 1])))
		i++;
	line_cut = (char *)malloc(sizeof(char) * (i - j + 1));
	if (!line_cut)
		return (NULL);
	i = 0;
	while (line[i] && (!line[j + 1] || line[j] != '$'
			|| !char_is_ok(line[j + 1])))
	{
		line_cut[i] = line[j];
		j++;
		i++;
	}
	line_cut[i] = '\0';
	return (line_cut);
}

char	*search_env_get_variable(int i, int j, t_pipex *pipex, int format)
{
	char	*variable;

	if (!pipex->env[j])
	{
		variable = (char *)malloc(sizeof(char));
		if (!variable)
			return (NULL);
		variable[0] = '\0';
	}
	else
	{
		variable = ft_strdup(&pipex->env[j][i + 1]);
		if (!variable)
			return (NULL);
	}
	if (format && pipex->env[j] && variable && variable[0] != '\0')
	{
		variable = fixe_variable(variable);
		if (!variable)
			return (NULL);
		les_espaces_cest_pas_cool(variable);
	}
	return (variable);
}
