/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbegne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 20:02:03 by cbegne            #+#    #+#             */
/*   Updated: 2017/03/05 18:24:24 by cbegne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dollar(char *echo, char **env, int i)
{
	int		j;
	int		k;
	char	*tmp;
	char	*no_quote;

	k = 0;
	while (echo[k])
	{
		if (echo[k] == '"' || is_space(echo[k]))
			break ;
		k++;
	}
	no_quote = ft_strndup(echo, k);
	if ((j = get_env_var(no_quote, env)) >= 0)
	{
		tmp = ft_strchr(env[j], '=');
		ft_putstr(tmp + 1);
	}
	ft_strdel(&no_quote);
	return (i + k);
}

static int	print_words(char *echo, int i)
{
	while (echo[i])
	{
		if (echo[i] == '$' && echo[i + 1])
			break ;
		if (echo[i] != '"')
			ft_putchar(echo[i]);
		i++;
	}
	return (i);
}

static void	print_echo(char **cmd, char **env, int i, int dquote)
{
	int	len;
	int	j;

	len = ft_tablen(cmd);
	while (i < len)
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '$' && cmd[i][j + 1])
				j = check_dollar(&(cmd[i][j + 1]), env, j + 1);
			else
				j = print_words(cmd[i], j);
		}
		i++;
		if (i != len)
			dquote == 0 ? ft_putchar(' ') : ft_putchar('\n');
	}
}

static void	ask_line(char **cmd, char **env, int i)
{
	char	*line;
	char	**tmp;
	char	**tab;

	tmp = (char**)ft_memalloc(sizeof(char*) * 2);
	tmp[0] = ft_strdup("");
	ft_putstr("dquote> ");
	while (get_next_line(0, &line) == 1)
	{
		tab = ft_tabappend(tmp, line);
		ft_tabdel(tmp);
		tmp = tab;
		if (ft_strnbchar(line, '"') % 2)
			break ;
		ft_strdel(&line);
		ft_putstr("dquote> ");
	}
	ft_strdel(&line);
	print_echo(cmd, env, i, 0);
	ft_putchar('\n');
	print_echo(tab, env, i, 1);
	ft_tabdel(tab);
}

void		exec_echo(char **cmd, char **env)
{
	int	i;
	int	j;
	int	nb;

	nb = 0;
	i = 1;
	if (cmd[1] && !ft_strcmp(cmd[1], "-n"))
		i++;
	j = i;
	while (cmd[j])
		nb = nb + ft_strnbchar(cmd[j++], '"');
	if (nb % 2 == 0)
		print_echo(cmd, env, i, 0);
	else
		ask_line(cmd, env, i);
	if (!cmd[1] || ft_strcmp(cmd[1], "-n"))
		ft_printf("\n");
}
