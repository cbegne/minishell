/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbegne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 20:07:50 by cbegne            #+#    #+#             */
/*   Updated: 2017/03/06 15:08:21 by cbegne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dir(char *cmd)
{
	t_stat	dir_stat;

	if (stat(cmd, &dir_stat))
	{
		ft_printf_fd(2, "cd: no such file or directory: %s\n", cmd);
		return (-1);
	}
	else if (!S_ISDIR(dir_stat.st_mode))
	{
		ft_printf_fd(2, "cd: not a directory: %s\n", cmd);
		return (-1);
	}
	else if (access(cmd, X_OK))
	{
		ft_printf_fd(2, "cd: permission denied: %s\n", cmd);
		return (-1);
	}
	return (0);
}

static char	**update_pwd_and_move(char *cmd, char **env, char *ini_cmd)
{
	char	*pwd;
	char	buf[PATH_MAX + 1];
	int		j;
	int		i;

	if (check_dir(cmd) == -1)
		return (env);
	if (chdir(cmd) == -1)
		return (env);
	i = get_env_var("PWD", env);
	j = get_env_var("OLDPWD", env);
	change_env_var("OLDPWD", &(env[i][4]), env + j);
	if (!(pwd = getcwd(buf, PATH_MAX + 1)))
		return (env);
	change_env_var("PWD", pwd, env + i);
	if (ini_cmd && !ft_strcmp(ini_cmd, "-"))
		ft_printf("%s\n", pwd);
	return (env);
}

static char	**check_env(char *name, char **env, char *cmd)
{
	int		j;
	int		len;
	char	*home;

	if ((j = get_env_var(name, env)) == -1)
		ft_printf_fd(2, "cd: %s not set\n", name);
	else
	{
		len = ft_strlen(name);
		if (cmd && cmd[0] == '~' && cmd[1])
		{
			if (cmd[0] == '~' && cmd[1] != '/')
			{
				ft_printf_fd(2, "cd: no such file or directory: %s\n", cmd);
				return (env);
			}
			home = ft_strjoin(&(env[j][len + 1]), cmd + 1);
			if (check_dir(home) != -1)
				env = update_pwd_and_move(home, env, cmd);
			ft_strdel(&home);
		}
		else
			env = update_pwd_and_move(&(env[j][len + 1]), env, cmd);
	}
	return (env);
}

char		**exec_cd(char **cmd, char **env)
{
	int		i;

	i = 1;
	if (!cmd[i] || cmd[i][0] == '~' || !ft_strcmp(cmd[i], "--"))
		env = check_env("HOME", env, cmd[i]);
	else if (!ft_strcmp(cmd[i], "-"))
		env = check_env("OLDPWD", env, cmd[i]);
	else if (check_dir(cmd[i]) != -1)
		env = update_pwd_and_move(cmd[i], env, cmd[i]);
	return (env);
}
