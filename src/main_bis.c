/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prambaud <prambaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:18:34 by lbenatar          #+#    #+#             */
/*   Updated: 2025/02/04 13:20:15 by prambaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ctrl_c_here_doc(t_pipex *pipex)
{
	char	buf[1];
	int		fd;
	int		r;
	char	*path;

	path = ft_strjoin(pipex->first_path, "/libft/fuck130");
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (free(path), perm_or_file_missing(path), 1);
	r = read(fd, buf, 1);
	if (r == -1)
		return (free(path), read_fail(), 1);
	close(fd);
	if (buf[0] == '1')
	{
		fd = open(path, O_WRONLY | O_TRUNC);
		if (fd == -1)
			return (perm_or_file_missing(path), free(path), 1);
		write(fd, "0", 1);
		close(fd);
		pipex->status = 130;
		pipex->status_check = 1;
	}
	free(path);
	return (0);
}
