/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbegne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 13:50:59 by cbegne            #+#    #+#             */
/*   Updated: 2017/03/06 17:56:41 by cbegne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_path(char ***path, char **env, char *cmd)
{
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			break ;
		env++;
	}
	if (*env)
		*path = ft_strsplit(*env + 5, ':');
	else
		ft_printf_fd(2, "%s: no such file or directory\n", cmd);
}

static int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "setenv"))
		return (1);
	if (!ft_strcmp(cmd, "unsetenv"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

static char	**exec_builtin(char *builtin, char **cmd, char **env)
{
	if (!ft_strcmp(builtin, "cd"))
		env = exec_cd(cmd, env);
	else if (!ft_strcmp(builtin, "echo"))
		exec_echo(cmd, env);
	else if (!ft_strcmp(builtin, "env"))
		env = exec_env(cmd, env);
	else if (!ft_strcmp(builtin, "setenv"))
		env = exec_setenv(cmd, env);
	else if (!ft_strcmp(builtin, "unsetenv"))
		env = exec_unsetenv(cmd, env);
	else if (!ft_strcmp(builtin, "exit"))
		exec_exit(cmd, env);
	return (env);
}

char		**run_command(char **cmd, char **env)
{
	char	**path;

	path = NULL;
	if (ft_strchr(cmd[0], '/'))
		build_fork(cmd[0], cmd[0], cmd, env);
	else if (is_builtin(cmd[0]))
		env = exec_builtin(cmd[0], cmd, env);
	else
	{
		get_path(&path, env, cmd[0]);
		if (path)
			find_ext_builtin(path, cmd, env);
	}
	return (env);
}
