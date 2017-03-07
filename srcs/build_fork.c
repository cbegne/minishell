/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbegne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 18:42:03 by cbegne            #+#    #+#             */
/*   Updated: 2017/03/05 19:36:58 by cbegne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_dir_path(char *path, char *cmd)
{
	DIR			*dir;
	t_dirent	*dirent;
	int			found;

	found = 0;
	if ((dir = opendir(path)) == NULL)
		return (-1);
	while ((dirent = readdir(dir)))
	{
		if (!ft_strcmp(cmd, dirent->d_name))
		{
			found = 1;
			break ;
		}
	}
	closedir(dir);
	return (found);
}

void		build_fork(char *full_path, char *path, char **cmd, char **env)
{
	pid_t	father;

	if (access(full_path, X_OK) != -1)
	{
		father = fork();
		if (father > 0)
			wait(0);
		if (father == 0)
		{
			if (execve(full_path, cmd, env) == -1)
				ft_printf_fd(2, "%s: command not found\n", full_path);
			exit(0);
		}
	}
	else if (access(full_path, X_OK) == -1 && find_dir_path(path, cmd[0]) == 1)
		ft_printf_fd(2, "%s: Permission denied\n", full_path);
	else
		ft_printf_fd(2, "%s: no such file or directory\n", cmd[0]);
}

void		find_ext_builtin(char **path, char **cmd, char **env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		if (find_dir_path(path[i], cmd[0]) == 1)
		{
			tmp = ft_strcjoin(path[i], cmd[0], '/');
			build_fork(tmp, path[i], cmd, env);
			ft_strdel(&tmp);
			ft_tabdel(path);
			return ;
		}
		i++;
	}
	if (path[i] == NULL)
	{
		ft_tabdel(path);
		ft_printf_fd(2, "%s: command not found\n", cmd[0]);
	}
}
