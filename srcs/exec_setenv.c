/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbegne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 20:01:37 by cbegne            #+#    #+#             */
/*   Updated: 2017/03/05 18:28:04 by cbegne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			get_env_var(char *cmd, char **env)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(cmd);
	while (env[i])
	{
		if (!ft_strncmp(env[i], cmd, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char		**add_env_var(char *name, char *value, char **env)
{
	char	**new_env;
	int		tab_len;
	int		i;

	i = 0;
	tab_len = ft_tablen(env);
	new_env = (char**)ft_memalloc(sizeof(char*) * (tab_len + 2));
	while (i < tab_len)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	if (value)
	{
		new_env[i] = ft_strcjoin(name, value, '=');
	}
	else
		new_env[i] = ft_strdup(name);
	ft_tabdel(env);
	return (new_env);
}

void		change_env_var(char *name, char *value, char **env)
{
	char	**tmp;

	tmp = env;
	ft_strdel(env);
	if (value)
		*tmp = ft_strcjoin(name, value, '=');
	else
		*tmp = ft_strdup(name);
}

static char	**exec_one_setenv(char *name, char *value, char **env)
{
	int	j;

	if ((j = get_env_var(name, env)) != -1)
		change_env_var(name, value, env + j);
	else
		env = add_env_var(name, value, env);
	return (env);
}

char		**exec_setenv(char **cmd, char **env)
{
	int	len;
	int	i;

	i = 1;
	len = ft_tablen(cmd);
	while (i < len)
	{
		if (ft_isdigit(cmd[i][0]))
			ft_printf_fd(2, "setenv: '%s' not a valid identifier\n", cmd[i]);
		else if (!ft_strisalnum(cmd[i]))
			ft_printf_fd(2, "setenv: '%s' not a valid identifier\n", cmd[i]);
		else if (!cmd[i + 1])
			ft_printf_fd(2, "usage: setenv [name] [value]\n");
		else
			env = exec_one_setenv(cmd[i], cmd[i + 1], env);
		i = i + 2;
	}
	return (env);
}
