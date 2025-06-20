/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:08:47 by lbenatar          #+#    #+#             */
/*   Updated: 2025/01/31 11:33:46 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_brackets(char **line_segmentee, int i, char **segmented_brackets)
{
	char	*brackets_united_back;

	i = 0;
	brackets_united_back = ft_strdup(segmented_brackets[0]);
	if (!brackets_united_back)
		return (ft_liberator_max(line_segmentee),
			ft_liberator_max(segmented_brackets), NULL);
	while (segmented_brackets[i + 1])
	{
		brackets_united_back = ft_strjoin_free(brackets_united_back,
				segmented_brackets[i + 1]);
		if (!brackets_united_back)
			return (ft_liberator_max(line_segmentee),
				ft_liberator_max(segmented_brackets), NULL);
		i++;
	}
	return (brackets_united_back);
}

char	*get_line_copy(char **line_segmentee, t_pipex *pipex,
		char **segmented_brackets, char *brackets_united_back)
{
	char	*line_copy;

	pipex->compteur_characters = ft_strlen(brackets_united_back);
	line_copy = ft_strjoin(line_segmentee[0], brackets_united_back);
	if (!line_copy)
		return (ft_liberator_max(line_segmentee),
			ft_liberator_max(segmented_brackets), free(brackets_united_back),
			NULL);
	line_copy = ft_strjoin_free(line_copy, line_segmentee[2]);
	if (!line_copy)
		return (ft_liberator_max(line_segmentee),
			ft_liberator_max(segmented_brackets), free(brackets_united_back),
			NULL);
	free(brackets_united_back);
	ft_liberator_max(segmented_brackets);
	ft_liberator_max(line_segmentee);
	return (line_copy);
}

char	*get_line_copy2(char **line_segmentee, t_pipex *pipex)
{
	char	*line_copy;

	line_copy = ft_strjoin(line_segmentee[0], line_segmentee[2]);
	if (!line_copy)
		return (ft_liberator_max(line_segmentee), NULL);
	pipex->compteur_characters = 0;
	ft_liberator_max(line_segmentee);
	return (line_copy);
}

char	*double_quote_management(char *line, int i, int ascii, t_pipex *pipex)
{
	char	**line_segmentee;
	char	**seg_bra;
	char	*line_copy;
	char	*brackets;

	line_segmentee = segmenting_line(line, ascii, i);
	free(line);
	if (!line_segmentee)
		return (NULL);
	if (line_segmentee[1][0] != '\0')
	{
		seg_bra = segmenting_brackets(line_segmentee[1], pipex);
		if (!seg_bra)
			return (ft_liberator_max(line_segmentee), NULL);
		brackets = get_brackets(line_segmentee, i, seg_bra);
		if (!brackets)
			return (NULL);
		line_copy = get_line_copy(line_segmentee, pipex, seg_bra, brackets);
		if (!line_copy)
			return (NULL);
		return (line_copy);
	}
	line_copy = get_line_copy2(line_segmentee, pipex);
	return (line_copy);
}
