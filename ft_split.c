/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hidhmmou <hidhmmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:01:30 by hidhmmou          #+#    #+#             */
/*   Updated: 2022/12/04 01:52:29 by hidhmmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}


char	*ft_strdup(const char *s1)
{
	int		len;
	int		index;
	char	*src_copy;	

	len = 0;
	index = -1;
	while (s1[len])
		len++;
	src_copy = malloc(sizeof(char) * (len + 1));
	if (!src_copy)
		return (NULL);
	while (s1[++index])
		src_copy[index] = s1[index];
	src_copy[index] = 0;
	return (src_copy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len_1;
	int		len_2;
	int		i;

	i = -1;
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (0);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	str = malloc(sizeof(char) * len_1 + len_2 + 1);
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	i = 0;
	while (s2[i])
		str[len_1++] = s2[i++];
	str[len_1] = 0;
	return (str);
}

static int	ft_count_words(char const *str, char charset)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == charset))
			i++;
		if (str[i])
			nbr++;
		while (str[i] && !(str[i] == charset))
			i++;
	}
	nbr++;
	return (nbr);
}

static int	ft_word_len(char const *str, char charset)
{
	int	i;

	i = 0;
	while (str[i] && !(str[i] == charset))
		i++;
	return (i);
}

static char	*ft_word_grep(char const *str, char charset)
{
	int		len_w;
	int		i;
	char	*word;

	i = 0;
	len_w = ft_word_len(str, charset);
	word = malloc(sizeof(char) * (len_w + 1));
	if (!word)
		return (NULL);
	while (i < len_w)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char *s, char c)
{
	int			i;
	char		**splited;

	if (!s)
		return (NULL);
	i = 0;
	splited = malloc(sizeof(char *) * ft_count_words(s, c));
	if (!splited)
		return (NULL);
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
			splited[i++] = ft_word_grep(s, c);
		while (*s && !(*s == c))
			s++;
	}
	splited[i] = 0;
	return (splited);
}
