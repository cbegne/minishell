/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unsetenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbegne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 20:02:21 by cbegne            #+#    #+#             */
/*   Updated: 2017/03/05 18:25:33 by cbegne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	suppr_env_var(char **env)
{
	char *tmp;

	tmp = *env;
	while (*env)
	{
		*env = *(env + 1);
		env++;
	}
	ft_strdel(&tmp);
}

static char	**exec_one_unsetenv(char *name, char **env)
{
	int	j;

	if ((j = get_env_var(name, env)) != -1)
		suppr_env_var(env + j);
	else
		ft_printf_fd(2, "unsetenv: %s: Invalid argument\n", name);
	return (env);
}

char		**exec_unsetenv(char **cmd, char **env)
{
	int	len;
	int i;

	i = 1;
	len = ft_tablen(cmd);
	while (i < len)
	{
		env = exec_one_unsetenv(cmd[i], env);
		i++;
	}
	return (env);
}
