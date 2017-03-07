/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbegne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 19:41:21 by cbegne            #+#    #+#             */
/*   Updated: 2017/03/06 12:55:43 by cbegne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/ft_printf.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <limits.h>
# include <signal.h>

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

char	**parse_prompt(char *s);
void	build_fork(char *path, char *test, char **cmd, char **env);
char	**run_command(char **cmd, char **env);
void	find_ext_builtin(char **path, char **cmd, char **env);
char	**exec_env(char **cmd, char **env);
void	exec_exit(char **cmd, char **env);
char	**exec_setenv(char **cmd, char **env);
char	**exec_unsetenv(char **cmd, char **env);
char	**exec_cd(char **cmd, char **env);
void	exec_echo(char **cmd, char **env);
void	change_env_var(char *name, char *value, char **env);
int		get_env_var(char *cmd, char **env);
char	**add_env_var(char *name, char *value, char **env);
int		is_space(char c);

#endif
