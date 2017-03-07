/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbegne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 20:02:30 by cbegne            #+#    #+#             */
/*   Updated: 2017/03/05 18:25:03 by cbegne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_env_var(char *cmd, char **env)
{
	int	len;
	int	i;

	len = 0;
	while (cmd[len] && cmd[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], cmd, len))
			return (i);
		i++;
	}
	return (-1);
}

char		**exec_env(char **cmd, char **env)
{
	int		i;
	int		j;
	char	**tmp_env;

	i = 1;
	if (cmd[i])
	{
		tmp_env = ft_tabdup(env);
		while (cmd[i] && ft_strchr(cmd[i], '='))
		{
			if ((j = is_env_var(cmd[i], tmp_env)) != -1)
				change_env_var(cmd[i], NULL, tmp_env + j);
			else
				tmp_env = add_env_var(cmd[i], NULL, tmp_env);
			i++;
		}
		!cmd[i] ? ft_print_tab(tmp_env) : run_command(cmd + i, tmp_env);
		ft_tabdel(tmp_env);
	}
	else
		ft_print_tab(env);
	return (env);
}
