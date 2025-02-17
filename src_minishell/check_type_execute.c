/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:00:49 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/17 14:33:48 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "../include_minishell/minishell.h"

void	check_type_execute(t_config *ms_data)
{
	if (((t_node2 *)(ms_data->ast->item))->type == ECHO)
		echo(ms_data);
	else if (((t_node2 *)(ms_data->ast->item))->type == CMD)
		pipes(ms_data);
	else if (((t_node2 *)(ms_data->ast->item))->type == PIPE_TOKEN)
		pipes(ms_data);
	else if (((t_node2 *)(ms_data->ast->item))->type == PWD)
		execute_pwd(((t_node2 *)(ms_data->ast->item))->command, ms_data);
	else if (((t_node2 *)(ms_data->ast->item))->type == ENV)
		execute_env(((t_node2 *)(ms_data->ast->item))->command, ms_data);
	else if (((t_node2 *)(ms_data->ast->item))->type == EXIT)
		execute_exit(((t_node2 *)(ms_data->ast->item))->command, ms_data);
	else if (((t_node2 *)(ms_data->ast->item))->type == CD)
		execute_cd(((t_node2 *)(ms_data->ast->item))->command, ms_data);
	else if (((t_node2 *)(ms_data->ast->item))->type == UNSET)
		execute_unset(((t_node2 *)(ms_data->ast->item))->command, ms_data);
	else if (((t_node2 *)(ms_data->ast->item))->type == EXPORT)
		execute_export(((t_node2 *)(ms_data->ast->item))->command, ms_data);
	// else if (((t_node *)(tree->item))->type == ECHO)
	// 	echo(tree, envp);
	//a completer avec tous les builtin
}
