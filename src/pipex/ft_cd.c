/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenatar <lbenatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:05:39 by prambaud          #+#    #+#             */
/*   Updated: 2025/02/11 15:21:10 by lbenatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Va chercher le Paths de home dans l env pour le renvoyer*/
char	*ft_home_path(char **env, char *path)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!env[i])
		return (NULL);
	while (env[i] && ft_strncmp(env[i], path, ft_strlen(path)))
		i++;
	if (!env[i])
		return (NULL);
	while (env[i][j])
		j++;
	str = ft_substr(env[i], ft_strlen(path), j - ft_strlen(path));
	if (!str)
		return (NULL);
	return (str);
}

void	update_pwd(t_pipex *pipex)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = NULL;
	while (pipex->env[j] && ft_strncmp(pipex->env[j], "PWD", 3))
		j++;
	while (pipex->env[i] && ft_strncmp(pipex->env[i], "OLDPWD", 6))
		i++;
	if (!pipex->env[i] || !pipex->env[j])
		return ;
	free(pipex->env[i]);
	pipex->env[i] = ft_strjoin("OLD", pipex->env[j]);
	free(pipex->env[j]);
	temp = getcwd(NULL, 0);
	pipex->env[j] = ft_strjoin("PWD=", temp);
	free(temp);
}

char	*get_home_path(char **env)
{
	char	*home_path;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4))
		i++;
	if (env[i])
	{
		while (env[i][j + 4] && k < 3)
		{
			if (env[i][j + 4] == '/')
				k++;
			j++;
		}
		home_path = ft_substr(env[i], 4, j - 1);
		if (!home_path)
			return (NULL);
		return (home_path);
	}
	return (NULL);
}

char	*ft_get_home_path(char **env)
{
	char	*home_path;

	int (i) = 0;
	int (k) = 0;
	int (j) = 0;
	home_path = get_home_path(env);
	if (!home_path)
	{
		while (env[i] && ft_strncmp(env[i], "HOME=", 5))
			i++;
		if (!env[i])
			return (NULL);
		while (env[i][j + 4] && k < 3)
		{
			if (env[i][j + 4] == '/')
				k++;
			j++;
		}
		home_path = ft_substr(env[i], 5, j - 1);
		if (!home_path)
			return (malloc_fail(), NULL);
	}
	return (home_path);
}

void	ft_cd(t_cmd *lst_cmd, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (lst_cmd->full_cmd[i])
		i++;
	if (i > 2)
	{
		ft_printf("minishell: cd: too many arguments\n");
		return ;
	}
	if (!lst_cmd->full_cmd[1])
		ft_cd1(pipex);
	else if (!ft_strncmp(lst_cmd->full_cmd[1], "~", 2))
		ft_cd2(pipex);
	else if (!ft_strncmp(lst_cmd->full_cmd[1], "-", 2))
		ft_cd3(pipex);
	else if (!chdir(lst_cmd->full_cmd[1]))
		ft_cd4(pipex);
	else
		ft_cd5(pipex, lst_cmd);
}
