/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:11:09 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/12 18:02:16 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

int	clear_minishell(t_config *minishell)
{
	int	errorcode;

	if (!minishell)
		return (0);
	rl_clear_history();
	errorcode = minishell->last_error_code;
	if (minishell->prompt)
		free(minishell->prompt);
	if (minishell->current_path)
		free(minishell->current_path);
	ft_free_double_ptr(&minishell->environnement);
	free(minishell->pidstr);
	free(minishell);
	return (errorcode);
}
