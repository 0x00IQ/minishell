/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:50:40 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/08 18:34:06 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

bool	expand_token(char	**tokenstr, char **envp)
{
	char	*value;
	int		i;
	int		len;
	char	*tmp;
	char	*varname;
	char	*expended;

	if (!(*tokenstr))
		return (false);
	value = NULL;
	i = 0;
	len = 0;
	tmp = *tokenstr;
	varname = NULL;
	expended = NULL;
	while (tmp[i] && tmp[i] != '$')
		i++;
	i++;
	if (tmp[i] == '\0')
		return (false);
	len = 0;
	while (tmp[i + len] && ft_isalnum(tmp[i + len]))
		len++;
	if (len == 0)
		return (false);
	varname = ft_calloc(sizeof(char), len + 1);
	if (!varname)
		return (false);
	ft_strlcpy(varname, &tmp[i], len + 1);
	value = get_value_by_name(envp, varname);
	if (!value) // variable invalide
		ft_strlcpy(&tmp[i - 1], &tmp[len], ft_strlen(&tmp[len]));
	else {
		expended = ft_calloc(sizeof(char), (ft_strlen(value) + (ft_strlen(tmp) - len)));
		if (!expended)
			return (free(varname), free(value), false);
		ft_strlcat(expended, tmp, ft_strchr(tmp, '$') - tmp);
		ft_strlcat(expended, value, (ft_strlen(value) + (ft_strlen(tmp))));
		ft_strlcat(expended, &tmp[i + len], ft_strlen(value) + (ft_strlen(tmp) - len));
		free(*tokenstr);
		*tokenstr = expended;
	}
	free(value);
	free(varname);
	return (true);
}

bool	check_expansion(char *token)
{
	bool	squote;
	bool	dquotes;
	int		numexp;
	int		i;

	if (!token)
		return (false);
	squote = false;
	dquotes = false;
	i = 0;
	numexp = 0;
	while (token[i])
	{
		if (token[i] == '\'')
			squote = !squote;
		if (token[i] == '\"')
			dquotes = !dquotes;
		if (token[i] == '\'' && dquotes)
			dquotes = !dquotes;
		if (token[i] == '$' && dquotes == false && token[i + 1] != '$')
			numexp++;
		i++;
	}
	if (numexp == 0)
		return (false);
	return (true);
}

bool	double_quotes_eraser(t_dlist *lexed_list)
{
	t_dlist	*tmp;
	char	*token;

	if (!lexed_list)
		return (false);
	tmp = lexed_list;
	while (tmp)
	{
		token = ptr_to_lexertoklist(tmp->content)->token;
		while (token && *token == '\"' && token[ft_strlen(token) - 1] == '\"')
		{
			token[ft_strlen(token)] = '\0';
			ft_strlcpy(token, &token[1], ft_strlen(&token[1]));
		}
		tmp = tmp->next;
		if (tmp == lexed_list)
			break ;
	}
	return (true);
}

// work for $PWD and for $PWD$$$$$$$ but not for multiple exp in same string
bool	expander(t_dlist *lexed_list, t_config *config)
{
	t_dlist	*tmp;

	if (!lexed_list)
		return (false);
	if (!double_quotes_eraser(lexed_list))
		return (false);
	tmp = lexed_list;
	while (tmp)
	{
		if (ft_strchr(ptr_to_lexertoklist(tmp->content)->token, '$'))
		{
			if (check_expansion(ptr_to_lexertoklist(tmp->content)->token))
			{
				while (check_expansion(ptr_to_lexertoklist(tmp->content)->token) &&	expand_token(&ptr_to_lexertoklist(tmp->content)->token, config->environnement) )
					;
			}
		}	
		tmp = tmp->next;
		if (tmp == lexed_list)
			break ;
	}
	print_token_list(&lexed_list);
	return (true);
}
