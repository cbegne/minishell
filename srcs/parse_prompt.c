/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbegne <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 11:01:10 by cbegne            #+#    #+#             */
/*   Updated: 2017/03/06 15:09:47 by cbegne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

static int	number_words(char const *s)
{
	int nb;

	nb = 0;
	while (*s)
	{
		if (is_space(*s))
			s++;
		else if (*s == '"')
		{
			nb++;
			s++;
			while (*s && *s != '"')
				s++;
			s++;
		}
		else
		{
			nb++;
			while (*s && !is_space(*s))
				s++;
		}
	}
	return (nb);
}

static int	get_end_word(char *s, char c)
{
	char	*tmp;

	tmp = s;
	if (c == '"')
	{
		s++;
		while (*s && *s != '"')
			s++;
		s++;
	}
	else
	{
		while (*s && !(is_space(*s)))
			s++;
	}
	return (s - tmp);
}

char		**parse_prompt(char *s)
{
	char	**tab;
	int		i;
	int		j;
	int		nb;

	i = 0;
	nb = number_words(s);
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * (nb + 1))))
		return (NULL);
	while (i < nb)
	{
		j = 0;
		while (is_space(*s))
			s++;
		if (*s == '"')
			j = get_end_word(s, '"');
		else
			j = get_end_word(s, 0);
		tab[i++] = ft_strndup(s, j);
		if (s[j] == '"')
			j++;
		s = s + j;
	}
	tab[i] = 0;
	return (tab);
}
