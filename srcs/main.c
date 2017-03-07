/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbegne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 19:18:49 by cbegne            #+#    #+#             */
/*   Updated: 2017/03/06 12:55:26 by cbegne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_prompt(char **env)
{
	char	buf[PATH_MAX + 1];
	int		j;
	int		len;
	char	*pwd;

	if (!(pwd = getcwd(buf, PATH_MAX + 1)))
	{
		j = get_env_var("PWD", env);
		len = ft_strlen(env[j]);
		while (len && env[j][len] != '=' && env[j][len] != '/')
			len--;
		pwd = &(env[j][len]);
	}
	else
	{
		len = ft_strlen(pwd);
		while (len && pwd[len] != '=' && pwd[len] != '/')
			len--;
		pwd = (len == 0 ? pwd + len : pwd + len + 1);
	}
	ft_printf("\033[33;1m%C \033[0m", 0x21E8);
	ft_printf("\033[31;1m %s \033[30;1m%C \33[0m", pwd, 0x2712);
}

static char	**start_command(char *line, char **env)
{
	char	**multi;
	char	**cmd;
	int		i;

	multi = ft_strsplit(line, ';');
	i = 0;
	while (multi[i])
	{
		cmd = parse_prompt(multi[i]);
		if (cmd[0] != 0)
			env = run_command(cmd, env);
		ft_tabdel(cmd);
		i++;
	}
	ft_tabdel(multi);
	return (env);
}

int			main(int ac, char **av, char **environ)
{
	char	**env;
	char	*line;

	if (ac == 1 && av)
	{
		if (environ)
			env = ft_tabdup(environ);
		else
			env = (char**)ft_memalloc(sizeof(char*));
		while (42)
		{
			print_prompt(env);
			get_next_line(0, &line);
			if (line[0] != 0)
				env = start_command(line, env);
			ft_strdel(&line);
		}
	}
	else
		ft_printf_fd(2, "usage: ./minishell\n");
	return (0);
}
