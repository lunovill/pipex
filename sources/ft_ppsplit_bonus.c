/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ppsplit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lunovill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 04:59:24 by lunovill          #+#    #+#             */
/*   Updated: 2022/06/01 04:59:36 by lunovill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static size_t	ft_nworld(const char *s)
{
	unsigned int	i;
	char			c;
	size_t			nb_w;

	i = 0;
	nb_w = 0;
	while (s[i])
	{
		while (s[i] == ' ' && s[i])
			i++;
		while (s[i] != ' ' && s[i])
		{
			if (s[i] == '\'' || s[i] == '\"')
			{
				c = s[i++];
				while (s[i] != c && s[i])
					i++;
			}
			if (s[i])
				i++;
		}
		nb_w++;
	}
	return (nb_w);
}

static size_t	ft_nchar(const char *s)
{
	char	c;
	size_t	i;

	i = 0;
	while (s[i] != ' ' && s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i++];
			while (s[i] != c && s[i])
				i++;
		}
		if (s[i])
			i++;
	}
	return (i);
}

static char	*ft_cell(const char **s, char *cell)
{
	unsigned int	i;
	char			c;

	i = 0;
	while (**s != ' ' && **s)
	{
		if (**s == '\'' || **s == '\"')
		{
			cell[i++] = **s;
			c = *(*s)++;
			while (**s != c && **s)
				cell[i++] = *(*s)++;
		}
		if (**s)
			cell[i++] = *(*s)++;
	}
	cell[i] = '\0';
	return (cell);
}

static char	**ft_issplit(const char *s, char **tabs, size_t nb_w)
{
	unsigned int	i;

	i = 0;
	while (i < nb_w)
	{
		while (*s == ' ' && *s)
			s++;
		tabs[i] = (char *)malloc(sizeof(char) * (ft_nchar(s) + 1));
		if (!tabs[i])
			return (NULL);
		tabs[i] = ft_cell(&s, tabs[i]);
		i++;
	}
	tabs[i] = NULL;
	return (tabs);
}

char	**ft_ppsplit(const char *s)
{
	char		**tabs;
	size_t		nb_w;

	if (!s || ft_strcmp(s, "") == 0)
		return (NULL);
	nb_w = ft_nworld(s);
	if (nb_w == 0)
		return (NULL);
	tabs = (char **)malloc(sizeof(char *) * (nb_w + 1));
	if (!tabs)
		return (NULL);
	return (ft_issplit(s, tabs, nb_w));
}
