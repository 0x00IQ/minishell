/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:14:38 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/17 18:00:54 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

bool	is_quoted(bool *quotes)
{
	return (quotes[0] == true || quotes[1] == true);
}

void	clean_quotes(char *s)
{
	int		i;
	int		j;
	bool	quoted;

	if (!s)
		return ;
	i = 0;
	quoted = false;
	while (s[i])
	{
		j = 0;
		if (s[i] == '\'' && quoted == false)
		{
			j = i + 1;
			while (s[j] && s[j] != '\'')
				j++;
			if (s[j] == '\0')
				break ;
			ft_strlcpy(&s[j], &s[j + 1], ft_strlen(&s[j]));
			ft_strlcpy(&s[i], &s[i + 1], ft_strlen(&s[i]));
			i = j - 2;
		}
		else if (s[i] == '\"' && quoted == false)
		{
			j = i + 1;
			while (s[j] && s[j] != '\"')
				j++;
			if (s[j] == '\0')
				break ;
			ft_strlcpy(&s[j], &s[j + 1], ft_strlen(&s[j]));
			ft_strlcpy(&s[i], &s[i + 1], ft_strlen(&s[i]));
			i = j - 2;
		}
		i++;
	}
}

void	expand_pls(char **str, char **env, t_config *config, int *index)
{
	char	*ptrs[4];// 0: varname, 1: value, 2: beforevar, 3: aftervar
	int		j;
	char	*s;

	if (!str || !index || !env)
		return ;
	ft_bzero(ptrs, sizeof(char *) * 4);
	s = *str;
	if (s[*index + 1] == '\0')
		return ;
	j = *index + 1;
	if (ft_isdigit(s[j]))
		return ((void)ft_memmove(&s[*index], &s[j + 1], ft_strlen(&s[j]) + 1));
	else if (s[j] == '\"' || s[j] == '\'')
		return ((void)ft_memmove(&s[*index], &s[j], ft_strlen(&s[j]) + 1));
	else if (s[j] == '?')
	{
		ptrs[1] = ft_itoa(config->last_error_code);
		ptrs[2] = ft_substr(s, 0, *index);
		ptrs[3] = ft_substr(s, j + 1, ft_strlen(s));
		ptrs[0] = ft_str_three_join(ptrs[2], ptrs[1], ptrs[3]);
		*index += ft_strlen(ptrs[1]) - 1;
		free(*str);
		free(ptrs[1]);
		free(ptrs[2]);
		free(ptrs[3]);
		*str = ptrs[0];
		return ;
	}
	else if (s[j] == '$')
	{
		ptrs[2] = ft_substr(s, 0, *index);
		ptrs[3] = ft_substr(s, j + 1, ft_strlen(s));
		ptrs[0] = ft_str_three_join(ptrs[2], config->pidstr, ptrs[3]);
		*index += ft_strlen(ptrs[1]) - 1;
		free(*str);
		free(ptrs[2]);
		free(ptrs[3]);
		*str = ptrs[0];
		return ;
	}
	while (s[j] && ft_isalpha(s[j]) && ft_isalpha(s[j + 1]))
		j++;
	// if j == *index + 1 digit name -> need to handle
	// write(1, &s[*index + 1], j - *index);
	ptrs[0] = ft_substr(s, *index + 1 , j - *index);
	if (!ptrs[0])
		return ;
	ptrs[1] = get_value_by_name(env, ptrs[0]);
	free(ptrs[0]);
	if (!ptrs[1]) // no valid name
	{
		ft_memmove(&s[*index], &s[j + 1], ft_strlen(&s[j]) + 1);
		*index += j;
	}
	else
	{
		ptrs[2] = ft_substr(s, 0, *index);
		ptrs[3] = ft_substr(s, j + 1, ft_strlen(s));
		ptrs[0] = ft_str_three_join(ptrs[2], ptrs[1], ptrs[3]);
		*index += ft_strlen(ptrs[1]) - 1;
		free(*str);
		free(ptrs[1]);
		free(ptrs[2]);
		free(ptrs[3]);
		*str = ptrs[0];
	}
}

void expand_token(char **tokenstr, char **envp, t_config *config)
{
	int		i;
	int		state; // 0: no quotes, 1: ', 2: "
	bool	expand;
	char	*s;

	if (!tokenstr || !*tokenstr || !envp || !config)
		return;

	s = *tokenstr;
	state = 0;
	expand = false;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && state == 0)
			state = 1;
		else if (s[i] == '\'' && state == 1)
			state = 0;
		else if (s[i] == '\"' && state == 0)
			state = 2;
		else if (s[i] == '\"' && state == 2)
			state = 0;
		else if (s[i] == '$' && (state == 0 || state == 2))
			expand = true;
		if (expand)
		{
			expand_pls(tokenstr, envp, config, &i);
			expand = false;
			s = *tokenstr;
		}
		i++;
	}
}

bool	expander(t_dlist *lexed_list, t_config *config)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	if (!lexed_list)
		return (false);
	tmp = lexed_list;
	while (tmp)
	{
		if (ft_strchr(ptr_to_lexertoklist(tmp->content)->token, '$'))
		{
				expand_token(&ptr_to_lexertoklist(tmp->content)->token, config->environnement, config);
				if (ft_strlen(ptr_to_lexertoklist(tmp->content)->token) == 0 && dll_size(&lexed_list) > 1)
				{
					tmp2 = tmp;
					tmp->prev->next = tmp->next;
					tmp2->next->prev = tmp2->prev;
				}
		}
		// expand_wildcards(&ptr_to_lexertoklist(tmp->content)->token);
		clean_quotes(ptr_to_lexertoklist(tmp->content)->token);
		tmp = tmp->next;
		if (tmp == lexed_list)
			break ;
	}
	return (true);
}
